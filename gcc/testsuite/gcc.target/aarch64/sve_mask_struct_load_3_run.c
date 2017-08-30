/* { dg-do run { target aarch64_sve_hw } } */
/* { dg-options "-O2 -ftree-vectorize -fno-tree-dce -ffast-math -march=armv8-a+sve" } */

#include "sve_mask_struct_load_3.c"

#define N 100

volatile int x;

#undef TEST_LOOP
#define TEST_LOOP(NAME, OUTTYPE, INTYPE, MASKTYPE)	\
  {							\
    OUTTYPE out[N];					\
    INTYPE in[N * 4];					\
    MASKTYPE mask[N];					\
    for (int i = 0; i < N; ++i)				\
      {							\
	out[i] = i * 7 / 2;				\
	mask[i] = i % 5 <= i % 3;			\
      }							\
    for (int i = 0; i < N * 4; ++i)			\
      in[i] = i * 9 / 2;				\
    NAME##_4 (out, in, mask, N);			\
    for (int i = 0; i < N; ++i)				\
      {							\
	OUTTYPE if_true = (in[i * 4]			\
			   + in[i * 4 + 1]		\
			   + in[i * 4 + 2]		\
			   + in[i * 4 + 3]);		\
	OUTTYPE if_false = i * 7 / 2;			\
	if (out[i] != (mask[i] ? if_true : if_false))	\
	  __builtin_abort ();				\
	x += 1;						\
      }							\
  }

int
main (void)
{
  TEST (test);
  return 0;
}
