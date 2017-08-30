/* { dg-do compile } */
/* { dg-options "-O -march=armv8-a+sve -msve-vector-bits=256" } */

#ifndef BIAS
#define BIAS 0
#endif

typedef long v4di __attribute__((vector_size (32)));
typedef int v8si __attribute__((vector_size (32)));
typedef short v16hi __attribute__((vector_size (32)));
typedef char v32qi __attribute__((vector_size (32)));
typedef double v4df __attribute__((vector_size (32)));
typedef float v8sf __attribute__((vector_size (32)));

#define MASK_2(X, Y) X, Y + X
#define MASK_4(X, Y) MASK_2 (X, Y), MASK_2 (X + 2, Y)
#define MASK_8(X, Y) MASK_4 (X, Y), MASK_4 (X + 4, Y)
#define MASK_16(X, Y) MASK_8 (X, Y), MASK_8 (X + 8, Y)
#define MASK_32(X, Y) MASK_16 (X, Y), MASK_16 (X + 16, Y)

#define INDEX_4 v4di
#define INDEX_8 v8si
#define INDEX_16 v16hi
#define INDEX_32 v32qi

#define PERMUTE(TYPE, NUNITS)					\
  TYPE permute_##TYPE (TYPE values1, TYPE values2)		\
  {								\
    return __builtin_shuffle					\
      (values1, values2,					\
       ((INDEX_##NUNITS) { MASK_##NUNITS (BIAS, NUNITS) }));	\
  }

#define TEST_ALL(T)				\
  T (v4di, 4)					\
  T (v8si, 8)					\
  T (v16hi, 16)					\
  T (v32qi, 32)					\
  T (v4df, 4)					\
  T (v8sf, 8)

TEST_ALL (PERMUTE)

/* { dg-final { scan-assembler-not {\ttbl\t} } } */

/* { dg-final { scan-assembler-times {\ttrn1\tz[0-9]+\.d, z[0-9]+\.d, z[0-9]+\.d} 2 } } */
/* { dg-final { scan-assembler-times {\ttrn1\tz[0-9]+\.s, z[0-9]+\.s, z[0-9]+\.s} 2 } } */
/* { dg-final { scan-assembler-times {\ttrn1\tz[0-9]+\.h, z[0-9]+\.h, z[0-9]+\.h} 1 } } */
/* { dg-final { scan-assembler-times {\ttrn1\tz[0-9]+\.b, z[0-9]+\.b, z[0-9]+\.b} 1 } } */
