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
DO_IMMEDIATE_OPS (5, TYPE, 5);			\
DO_IMMEDIATE_OPS (255, TYPE, 255);		\
DO_IMMEDIATE_OPS (256, TYPE, 256);		\
DO_IMMEDIATE_OPS (257, TYPE, 257);		\
DO_IMMEDIATE_OPS (65280, TYPE, 65280);		\
DO_IMMEDIATE_OPS (65281, TYPE, 65281);		\
DO_IMMEDIATE_OPS (-1, TYPE, minus1);

DO_ARITH_OPS (char)
DO_ARITH_OPS (int)
DO_ARITH_OPS (long)

/* { dg-final { scan-assembler-not {\tsub\tz[0-9]+\.b, z[0-9]+\.b, z[0-9]+\.b\n} } } */
/* { dg-final { scan-assembler-times {\tsub\tz[0-9]+\.s, z[0-9]+\.s, z[0-9]+\.s\n} 2 } } */
/* { dg-final { scan-assembler-times {\tsub\tz[0-9]+\.d, z[0-9]+\.d, z[0-9]+\.d\n} 2 } } */

/* { dg-final { scan-assembler-times {\tsubr\tz[0-9]+\.b, z[0-9]+\.b, #1\n} 2 } } */
/* { dg-final { scan-assembler-times {\tsubr\tz[0-9]+\.b, z[0-9]+\.b, #5\n} 1 } } */
/* { dg-final { scan-assembler-not   {\tsubr\tz[0-9]+\.b, z[0-9]+\.b, #255\n} } } */
/* { dg-final { scan-assembler-not   {\tsubr\tz[0-9]+\.b, z[0-9]+\.b, #256\n} } } */
/* { dg-final { scan-assembler-not   {\tsubr\tz[0-9]+\.b, z[0-9]+\.b, #257\n} } } */
/* { dg-final { scan-assembler-not   {\tsubr\tz[0-9]+\.b, z[0-9]+\.b, #65280\n} } } */
/* { dg-final { scan-assembler-not   {\tsubr\tz[0-9]+\.b, z[0-9]+\.b, #65281\n} } } */
/* { dg-final { scan-assembler-not   {\tsubr\tz[0-9]+\.b, z[0-9]+\.b, #-1\n} } } */

/* { dg-final { scan-assembler-times {\tsubr\tz[0-9]+\.s, z[0-9]+\.s, #5\n} 1 } } */
/* { dg-final { scan-assembler-times {\tsubr\tz[0-9]+\.s, z[0-9]+\.s, #255\n} 1 } } */
/* { dg-final { scan-assembler-times {\tsubr\tz[0-9]+\.s, z[0-9]+\.s, #256\n} 1 } } */
/* { dg-final { scan-assembler-not   {\tsubr\tz[0-9]+\.s, z[0-9]+\.s, #257\n} } } */
/* { dg-final { scan-assembler-times {\tsubr\tz[0-9]+\.s, z[0-9]+\.s, #65280\n} 1 } } */
/* { dg-final { scan-assembler-not   {\tsubr\tz[0-9]+\.s, z[0-9]+\.s, #65281\n} } } */
/* { dg-final { scan-assembler-not   {\tsubr\tz[0-9]+\.s, z[0-9]+\.s, #-1\n} } } */

/* { dg-final { scan-assembler-times {\tsubr\tz[0-9]+\.d, z[0-9]+\.d, #5\n} 1 } } */
/* { dg-final { scan-assembler-times {\tsubr\tz[0-9]+\.d, z[0-9]+\.d, #255\n} 1 } } */
/* { dg-final { scan-assembler-times {\tsubr\tz[0-9]+\.d, z[0-9]+\.d, #256\n} 1 } } */
/* { dg-final { scan-assembler-not   {\tsubr\tz[0-9]+\.d, z[0-9]+\.d, #257\n} } } */
/* { dg-final { scan-assembler-times {\tsubr\tz[0-9]+\.d, z[0-9]+\.d, #65280\n} 1 } } */
/* { dg-final { scan-assembler-not   {\tsubr\tz[0-9]+\.d, z[0-9]+\.d, #65281\n} } } */
/* { dg-final { scan-assembler-not   {\tsubr\tz[0-9]+\.d, z[0-9]+\.d, #-1\n} } } */
