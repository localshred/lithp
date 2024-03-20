#include <errno.h>
#include <stdio.h>
#include <stdlib.h>

#include "lval.h"
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

lval eval_op(lval x, char *op, lval y) {
  if (x.type == LVAL_ERR) {
    return x;
  }
  if (y.type == LVAL_ERR) {
    return y;
  }

  if (strcmp(op, "+") == 0 || strcmp(op, "add") == 0) {
    return lval_num(x.num + y.num);
  }
  if (strcmp(op, "-") == 0 || strcmp(op, "sub") == 0) {
    return lval_num(x.num - y.num);
  }
  if (strcmp(op, "*") == 0 || strcmp(op, "mul") == 0) {
    return lval_num(x.num * y.num);
  }
  if (strcmp(op, "/") == 0 || strcmp(op, "div") == 0) {
    return y.num == 0 ? lval_err(LERR_DIV_ZERO) : lval_num(x.num / y.num);
  }
  return lval_err(LERR_BAD_OP);
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
lval eval(mpc_ast_t *t) {
  if (strstr(t->tag, "number")) {
    errno = 0;
    long x = strtol(t->contents, NULL, 10);
    return errno != ERANGE ? lval_num(x) : lval_err(LERR_BAD_NUM);
  }
  // t->children[0] will always be '('
  // t->children[len] will always be ')'
  // Get the operator and the first arg of the expr
  char *op = t->children[1]->contents;
  lval x = eval(t->children[2]);

  // Now get remaining args of the expr and recursively evaluate the operation
  // with those values
  // + 1 2 3 becomes (1 + (2 + (3)))
  int i = 3;
  while (strstr(t->children[i]->tag, "expr")) {
    x = eval_op(x, op, eval(t->children[i]));
    i++;
  }

  // Return the final of evaluating this node and it's children
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
      lval result = eval(r.output);
      lval_println(result);
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
