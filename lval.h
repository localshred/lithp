#ifndef lithp_lval_h
#define lithp_lval_h

#include <stdio.h>

/**
 * An lval is a Lisp Value, with error handling
 *
 **/

enum { LVAL_NUM, LVAL_ERR };

enum {
  LERR_DIV_ZERO,
  LERR_BAD_OP,
  LERR_BAD_NUM,
};

typedef struct {
  int type;
  long num;
  int err;
} lval;

lval lval_err(int x);
lval lval_num(long x);
void lval_print(lval v);
void lval_println(lval v);

#endif