#include "lval.h"

lval lval_num(long x) {
  lval v;
  v.type = LVAL_NUM;
  v.num = x;
  return v;
}

lval lval_err(int x) {
  lval v;
  v.type = LVAL_ERR;
  v.err = x;
  return v;
}

void lval_print(lval v) {
  switch (v.type) {
  case LVAL_NUM:
    printf("%li", v.num);
    break;

  case LVAL_ERR:
    if (v.err == LERR_DIV_ZERO) {
      printf("Error: Division by zero");
    } else if (v.err == LERR_BAD_OP) {
      printf("Error: Invalid operator");
    } else if (v.err == LERR_BAD_NUM) {
      printf("Error: Invalid number");
    } else {
      printf("Error: unknown error occured: %d", v.err);
    }
    break;

  default:
    printf("Unknown lval. type=%d num=%ld err=%d", v.type, v.num, v.err);
    break;
  }
}

void lval_println(lval v) {
  lval_print(v);
  putchar('\n');
}

/* int main(int argc, char **argv) { */
/*   (void)argc; */
/*   (void)argv; */
/*   puts("what's up world"); */
/*   return 0; */
/* } */