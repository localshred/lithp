#ifndef lithp_lval_h
#define lithp_lval_h

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "mpc.h"

/**
 * An lval is a Lisp Value, with error handling
 *
 **/

enum { LVAL_ERR, LVAL_NUM, LVAL_SYM, LVAL_SEXPR };

typedef struct lval {
  int type;
  long num;
  // Error and Symbol types have some string data
  char *err;
  char *sym;
  // Count and point to list of lval pointers
  int count;
  struct lval **cell;
} lval;

/**
 * lval constructors
 **/
lval *lval_err(char *m);
lval *lval_num(long x);
lval *lval_sexpr(void);
lval *lval_sym(char *s);

/**
 * lval destructor
 **/
void lval_free(lval *v);

/**
 * Reading lvals
 **/
lval *lval_read(mpc_ast_t *t);

/**
 * lval utilities
 **/
void lval_print(lval *v);
void lval_println(lval *v);

#endif