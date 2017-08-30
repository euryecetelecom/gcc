/* { dg-do assemble } */
/* { dg-options "-O -march=armv8-a+sve -msve-vector-bits=256 --save-temps" } */

typedef unsigned short v16hi __attribute__((vector_size (32)));

#define MASK_2(X, Y) (X) ^ (Y), (X + 1) ^ (Y)
#define MASK_4(X, Y) MASK_2 (X, Y), MASK_2 (X + 2, Y)
#define MASK_8(X, Y) MASK_4 (X, Y), MASK_4 (X + 4, Y)
#define MASK_16(X, Y) MASK_8 (X, Y), MASK_8 (X + 8, Y)
#define MASK_32(X, Y) MASK_16 (X, Y), MASK_16 (X + 16, Y)

#define INDEX_16 v16hi

#define PERMUTE(TYPE, NUNITS, REV_NUNITS)				\
  TYPE permute_##TYPE##_##REV_NUNITS (TYPE values1, TYPE values2)	\
  {									\
    return __builtin_shuffle						\
      (values1, values2,						\
       ((INDEX_##NUNITS) { MASK_##NUNITS (0, REV_NUNITS - 1) }));	\
  }

#define TEST_ALL(T)				\
  T (v16hi, 16, 2)				\
  T (v16hi, 16, 4)

TEST_ALL (PERMUTE)

/* { dg-final { scan-assembler-not {\ttbl\t} } } */

/* { dg-final { scan-assembler-times {\trevh\tz[0-9]+\.d, p[0-7]/m, z[0-9]+\.d} 1 } } */
/* { dg-final { scan-assembler-times {\trevh\tz[0-9]+\.s, p[0-7]/m, z[0-9]+\.s} 1 } } */
