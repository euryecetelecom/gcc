/* { dg-do compile } */
/* { dg-options "-O2 -mcet" } */
/* { dg-final { scan-assembler-times "saveprevssp" 2 } } */

#include <immintrin.h>

void f1 (void)
{
  __builtin_ia32_saveprevssp ();
}

void f2 (void)
{
  _saveprevssp ();
}
