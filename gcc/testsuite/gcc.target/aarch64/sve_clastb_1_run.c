/* { dg-do run { target aarch64_sve_hw } } */
/* { dg-options "-O2 -ftree-vectorize -fno-inline -march=armv8-a+sve" } */

#include "sve_clastb_1.c"

extern void abort (void) __attribute__ ((noreturn));

int
main (void)
{
  int a[N] = {
  11, -12, 13, 14, 15, 16, 17, 18, 19, 20,
  1, 2, -3, 4, 5, 6, 7, -8, 9, 10,
  21, 22, 23, 24, 25, 26, 27, 28, 29, 30,
  31, 32
  };

  int ret = condition_reduction (a, 1);

  if (ret != 17)
    abort ();

  return 0;
}
