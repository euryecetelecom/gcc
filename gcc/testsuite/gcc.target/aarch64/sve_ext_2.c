/* { dg-do compile } */
/* { dg-options "-O -march=armv8-a+sve -msve-vector-bits=256" } */

typedef int v8si __attribute__((vector_size (32)));

void
foo (void)
{
  register v8si x asm ("z0");
  register v8si y asm ("z1");

  asm volatile ("" : "=w" (y));
  x = __builtin_shuffle (y, y, (v8si) { 1, 2, 3, 4, 5, 6, 7, 8 });
  asm volatile ("" :: "w" (x));
}

/* { dg-final { scan-assembler {\tmov\tz0\.d, z1\.d\n} } } */
/* { dg-final { scan-assembler {\text\tz0\.b, z0\.b, z[01]\.b, #4\n} } } */
