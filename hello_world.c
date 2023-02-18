#include <stdio.h>

#define string char*

void loop(int n, void (*fn)()) {
  for (int i = 0; i < n; i++) {
    fn(i, n);
  }
}

void say_hi(int index, int total) {
  printf("[%2d of %d] : Hello World\n", index, total);
}

void print_args(int argc, char** argv) {
  for (int i = 0; i < argc; i++) {
    printf("arg %d: %s\n", i, argv[i]);
  }
}

int main(int argc, string* argv) {
  print_args(argc, argv);
  printf("Hello,");
  string a = "world";
  printf(" %s!\n", a);
  loop(25, say_hi);
  return 0;
}
