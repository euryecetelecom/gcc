/* { dg-do run { target aarch64_sve_hw } } */
/* { dg-options "-O2 -ftree-vectorize -march=armv8-a+sve" } */

#include "sve_slp_2.c"

#define N (103 * 2)

#define HARNESS(TYPE)						\
  {								\
    TYPE a[N], b[2] = { 10, 17 };				\
    for (unsigned int i = 0; i < N; ++i)			\
      a[i] = i * 2 + i % 5;					\
    vec_slp_##TYPE (a, N / 2);					\
    for (unsigned int i = 0; i < N; ++i)			\
      {								\
	TYPE orig = i * 2 + i % 5;				\
	TYPE expected = orig + b[i % 2];			\
	if (a[i] != expected)					\
	  __builtin_abort ();					\
      }								\
  }

int
main (void)
{
  TEST_ALL (HARNESS)
}
