#include <signal.h>
#include <stdio.h>
#include <stdlib.h>

#define string char*

// Static input buffer
static char input[2048];

int main(int argc, string* argv) {
  puts("lithp version 0.0.0.0.1");
  puts("Press Ctrl+C to exit\n");

  while (1) {
    fputs("lithp> ", stdout);
    fgets(input, 2048, stdin);
    printf("No, you're a %s", input);
  }

  return EXIT_SUCCESS;
}
