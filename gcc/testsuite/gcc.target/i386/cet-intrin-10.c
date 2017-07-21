/* { dg-do compile } */
/* { dg-options "-O2 -mcet" } */
/* { dg-final { scan-assembler-times "clrssbsy" 2 } } */

#include <immintrin.h>

void f1 (void *__B)
{
  __builtin_ia32_clrssbsy (__B);
}

void f2 (void *__B)
{
  _clrssbsy (__B);
}
