/* { dg-do compile } */
/* { dg-options "-O2 -mcet" } */
/* { dg-final { scan-assembler-times "setssbsy" 2 } } */

#include <immintrin.h>

void f1 (void)
{
  __builtin_ia32_setssbsy ();
}

void f2 (void)
{
  _setssbsy ();
}
