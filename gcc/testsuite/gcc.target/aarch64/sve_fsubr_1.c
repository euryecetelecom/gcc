/* { dg-do assemble } */
/* { dg-options "-std=c99 -O3 -march=armv8-a+sve --save-temps" } */

#define DO_IMMEDIATE_OPS(VALUE, TYPE, NAME)			\
void vsubrarithimm_##NAME##_##TYPE (TYPE* dst, int count)	\
{								\
  for (int i = 0; i < count; ++i)				\
    dst[i] = VALUE - dst[i];					\
}

#define DO_ARITH_OPS(TYPE)			\
DO_IMMEDIATE_OPS (0, TYPE, 0);			\
DO_IMMEDIATE_OPS (1, TYPE, 1);			\
DO_IMMEDIATE_OPS (0.5, TYPE, 0point5);		\
DO_IMMEDIATE_OPS (2, TYPE, 2);			\
DO_IMMEDIATE_OPS (3.5, TYPE, 3point5);

DO_ARITH_OPS (float)
DO_ARITH_OPS (double)

/* { dg-final { scan-assembler-times {\tfsub\tz[0-9]+\.s, z[0-9]+\.s, z[0-9]+\.s\n} 3 } } */
/* { dg-final { scan-assembler-times {\tfsubr\tz[0-9]+\.s, p[0-7]/m, z[0-9]+\.s, #1.0\n} 1 } } */
/* { dg-final { scan-assembler-times {\tfsubr\tz[0-9]+\.s, p[0-7]/m, z[0-9]+\.s, #0.5\n} 1 } } */
/* { dg-final { scan-assembler-not   {\tfsubr\tz[0-9]+\.s, p[0-7]/m, z[0-9]+\.s, #2} } } */
/* { dg-final { scan-assembler-not   {\tfsubr\tz[0-9]+\.s, p[0-7]/m, z[0-9]+\.s, #3} } } */

/* { dg-final { scan-assembler-times {\tfsub\tz[0-9]+\.d, z[0-9]+\.d, z[0-9]+\.d\n} 3 } } */
/* { dg-final { scan-assembler-times {\tfsubr\tz[0-9]+\.d, p[0-7]/m, z[0-9]+\.d, #1.0\n} 1 } } */
/* { dg-final { scan-assembler-times {\tfsubr\tz[0-9]+\.d, p[0-7]/m, z[0-9]+\.d, #0.5\n} 1 } } */
/* { dg-final { scan-assembler-not   {\tfsubr\tz[0-9]+\.d, p[0-7]/m, z[0-9]+\.d, #2} } } */
/* { dg-final { scan-assembler-not   {\tfsubr\tz[0-9]+\.d, p[0-7]/m, z[0-9]+\.d, #3} } } */
