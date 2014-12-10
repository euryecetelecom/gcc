/* { dg-do run } */
/* { dg-options "-O3 -fno-inline" } */

#include <arm_neon.h>

extern void abort (void);

#define VARIANTS(VARIANT)	\
VARIANT (uint8, , 8, _u8, 5)	\
VARIANT (uint16, , 4, _u16, 3)	\
VARIANT (uint32, , 2, _u32, 1)	\
VARIANT (uint64, , 1, _u64, 0)	\
VARIANT (int8, , 8, _s8, 3)	\
VARIANT (int16, , 4, _s16, 2)	\
VARIANT (int32, , 2, _s32, 0)	\
VARIANT (int64, , 1, _s64, 0)	\
VARIANT (poly8, , 8, _p8, 7)	\
VARIANT (poly16, , 4, _p16, 2)	\
VARIANT (float32, , 2, _f32, 1)	\
VARIANT (float64, , 1, _f64, 0)	\
VARIANT (uint8, q, 16, _u8, 13)	\
VARIANT (uint16, q, 8, _u16, 5)	\
VARIANT (uint32, q, 4, _u32, 1)	\
VARIANT (uint64, q, 2, _u64, 0)	\
VARIANT (int8, q, 16, _s8, 15)	\
VARIANT (int16, q, 8, _s16, 3)	\
VARIANT (int32, q, 4, _s32, 1)	\
VARIANT (int64, q, 2, _s64, 1)	\
VARIANT (poly8, q, 16, _p8, 7)	\
VARIANT (poly16, q, 8, _p16, 4)	\
VARIANT (float32, q, 4, _f32, 2)\
VARIANT (float64, q, 2, _f64, 1)

#define TESTMETH(BASE, Q, ELTS, SUFFIX, LANE)			\
__attribute__((noinline)) BASE##x##ELTS##_t			\
wrap_vld1##Q##_lane##SUFFIX (const BASE##_t *load,		\
			     BASE##x##ELTS##_t vec)		\
{ return vld1##Q##_lane##SUFFIX (load, vec, LANE); }		\
int								\
test_vld1##Q##_lane##SUFFIX (const BASE##_t *data,		\
			     const BASE##_t *overwrite)		\
{								\
  BASE##_t out[ELTS];						\
  int j;							\
  BASE##x##ELTS##_t in = vld1##Q##SUFFIX (data);		\
  in = wrap_vld1##Q##_lane##SUFFIX (overwrite, in);		\
  vst1##Q##SUFFIX (out, in);					\
    for (j = 0; j < ELTS; j++)					\
      if (out[j] != (j == LANE ? *overwrite : data[j]))		\
        return 1;						\
  return 0;							\
}


VARIANTS (TESTMETH)

#define CHECK(BASE, Q, ELTS, SUFFIX, LANE)			\
  if (test_vld1##Q##_lane##SUFFIX ((const BASE##_t *)orig_data,	\
				   BASE##_data) != 0)	\
    abort ();

int
main (int argc, char **argv)
{
  /* Original data for all vector formats.  */
  uint64_t orig_data[2] = {0x1234567890abcdefULL, 0x13579bdf02468aceULL};

  /* Data with which vldN_lane will overwrite some of previous.  */
  uint8_t uint8_data[4] = { 7, 11, 13, 17 };
  uint16_t uint16_data[4] = { 257, 263, 269, 271 };
  uint32_t uint32_data[4] = { 65537, 65539, 65543, 65551 };
  uint64_t uint64_data[4] = { 0xdeadbeefcafebabeULL, 0x0123456789abcdefULL,
			      0xfedcba9876543210LL, 0xdeadbabecafebeefLL };
  int8_t int8_data[4] = { -1, 3, -5, 7 };
  int16_t int16_data[4] = { 257, -259, 261, -263 };
  int32_t int32_data[4] = { 123456789, -987654321, -135792468, 975318642 };
  int64_t *int64_data = (int64_t *)uint64_data;
  poly8_t poly8_data[4] = { 0, 7, 13, 18, };
  poly16_t poly16_data[4] = { 11111, 2222, 333, 44 };
  float32_t float32_data[4] = { 3.14159, 2.718, 1.414, 100.0 };
  float64_t float64_data[4] = { 1.010010001, 12345.6789, -9876.54321, 1.618 };

  VARIANTS (CHECK);
  return 0;
}
