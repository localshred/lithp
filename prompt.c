#include <signal.h>
#include <stdio.h>
#include <stdlib.h>

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

#define string char*

int main(int argc, string* argv) {
  puts("lithp version 0.0.0.0.1");
  puts("Press Ctrl+C to exit\n");

  while (1) {
    char* input = readline("lithp> ");
    add_history(input);
    printf("No, you're a %s\n", input);
    free(input);
  }

  return EXIT_SUCCESS;
}
