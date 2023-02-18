#include <stdio.h>
#include <stdlib.h>

#include "mpc.h"

#ifdef _WIN32
#include <string.h>

static char buffer[2048];

char* readline(char* prompt) {
  fputs(prompt, stdout);
  fgets(buffer, 2048, stdin);
  char* cpy = malloc(strlen(buffer)+1);
  strcpy(cpy, buffer);
  cpy[strlen(cpy)-1] = '\0';
}

void add_history(char* unused) {}

#else
#include <editline/readline.h>
#endif


/*
 * lithp Grammar Definition
 */

int main(int argc, char** argv) {
  puts("lithp version 0.0.0.0.1");
  puts("Press Ctrl+C to exit\n");

  mpc_parser_t* Number = mpc_new("number");
  mpc_parser_t* Operator = mpc_new("operator");
  mpc_parser_t* Expr = mpc_new("expr");
  mpc_parser_t* Lithp = mpc_new("lithp");

  while (1) {
    char* input = readline("lithp> ");
    add_history(input);
    printf("No, you're a %s\n", input);
    free(input);
  }

  return EXIT_SUCCESS;
}
