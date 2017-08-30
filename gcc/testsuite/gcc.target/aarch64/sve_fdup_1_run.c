/* { dg-do run { target { aarch64_sve_hw } } } */
/* { dg-options "-O3 -fno-inline -march=armv8-a+sve" } */

#include "sve_fdup_1.c"

#include <stdlib.h>

#define TEST_SET_IMM(TYPE,IMM,SUFFIX)		\
  {						\
    TYPE v[NUM_ELEMS (TYPE)];			\
    set_##TYPE##SUFFIX (v);			\
    for (int i = 0; i < NUM_ELEMS (TYPE); i++ )	\
      if (v[i] != IMM)				\
        result++;				\
  }

#define TEST_SET_IMM_FP(IMM, SUFFIX) \
TEST_SET_IMM (float, IMM, SUFFIX)    \
TEST_SET_IMM (double, IMM, SUFFIX)


int main  (int argc, char **argv)
{
  int result = 0;

  TEST_SET_IMM_FP (1, imm1)
  TEST_SET_IMM_FP (0x1.1p0, imm1p0)
  TEST_SET_IMM_FP (0x1.fp0, immfp0)
  TEST_SET_IMM_FP (0x1.1p4, imm1p4)
  TEST_SET_IMM_FP (0x1.1p-3, imm1pm3)
  TEST_SET_IMM_FP (0x1.fp4, immfp4)
  TEST_SET_IMM_FP (0x1.fp-3, immfpm3)

  TEST_SET_IMM_FP (0, imm0)
  TEST_SET_IMM_FP (0x1.1fp0, imm1fp0)
  TEST_SET_IMM_FP (0x1.1p5, imm1p5)
  TEST_SET_IMM_FP (0x1.1p-4, imm1pm4)
  TEST_SET_IMM_FP (0x1.1fp5, imm1fp5)
  TEST_SET_IMM_FP (0x1.1fp-4, imm1fpm4)

  if (result != 0)
    abort ();

  return 0;
}
