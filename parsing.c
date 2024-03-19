#include <stdio.h>
#include <stdlib.h>

#include "mpc.h"

#ifdef _WIN32
#include <string.h>

static char buffer[2048];

char *readline(char *prompt) {
  fputs(prompt, stdout);
  fgets(buffer, 2048, stdin);
  char *cpy = malloc(strlen(buffer) + 1);
  strcpy(cpy, buffer);
  cpy[strlen(cpy) - 1] = '\0';
}

void add_history(char *unused) {}

#else
#include <editline/readline.h>
#endif

long eval_op(long x, char *op, long y) {
  if (strcmp(op, "+") == 0 || strcmp(op, "add") == 0) {
    return x + y;
  }
  if (strcmp(op, "-") == 0 || strcmp(op, "sub") == 0) {
    return x - y;
  }
  if (strcmp(op, "*") == 0 || strcmp(op, "mul") == 0) {
    return x * y;
  }
  if (strcmp(op, "/") == 0 || strcmp(op, "div") == 0) {
    return x / y;
  }
  return 0;
}

/*
 * typedef struct mpc_ast_t {
 *   char* tag;
 *   char* contents;
 *   mpc_state_t state;
 *   int children_num;
 *   struct mpc_ast_t** children;
 * } mpc_ast_t;
 */
long eval(mpc_ast_t *t) {
  if (strstr(t->tag, "number")) {
    return atoi(t->contents);
  }
  char *op = t->children[1]->contents;
  long x = eval(t->children[2]);

  int i = 3;
  while (strstr(t->children[i]->tag, "expr")) {
    x = eval_op(x, op, eval(t->children[i]));
    i++;
  }

  return x;
}

int main(int argc, char **argv) {
  // Dismiss unused arg warnings
  (void)argc;
  (void)argv;

  mpc_parser_t *Number = mpc_new("number");
  mpc_parser_t *Operator = mpc_new("operator");
  mpc_parser_t *Expr = mpc_new("expr");
  mpc_parser_t *Lithp = mpc_new("lithp");

  mpca_lang(MPCA_LANG_DEFAULT, "                        \
    number   : /-?[0-9]+(\\.[0-9]+)?/ ;                 \
    operator : /(-|+|*|\\/|%|add|sub|mul|div)/ ;        \
    expr     : <number> | '(' <operator> <expr>+ ')'  ; \
    lithp    : /^/ <operator> <expr>+ /$/ ;             \
",
            Number, Operator, Expr, Lithp);

  puts("lithp version 0.0.0.0.1");
  puts("Press Ctrl+C to exit\n");

  while (1) {
    char *input = readline("lithp> ");
    add_history(input);

    mpc_result_t r;
    if (mpc_parse("<stdin>", input, Lithp, &r)) {
      mpc_ast_print(r.output);
      long result = eval(r.output);
      printf("%li\n", result);
      mpc_ast_delete(r.output);
    } else {
      mpc_err_print(r.error);
      mpc_err_delete(r.error);
    }

    free(input);
  }

  mpc_cleanup(4, Number, Operator, Expr, Lithp);
  return EXIT_SUCCESS;
}
