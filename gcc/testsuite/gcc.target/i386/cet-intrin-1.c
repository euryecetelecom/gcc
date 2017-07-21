/* { dg-do compile } */
/* { dg-options "-O -finstrument-control-flow -mcet" } */
/* { dg-final { scan-assembler-times "endbr32" 2 { target ia32 } } } */
/* { dg-final { scan-assembler-times "endbr64" 4 { target { ! ia32 } } } } */
/* { dg-final { scan-assembler "rdsspd|incsspd\[ \t]+(%|)eax" { target ia32 } } } */
/* { dg-final { scan-assembler "rdssp\[dq]\[ \t]+(%|)\[re]ax" { target { ! ia32 } } } } */
/* { dg-final { scan-assembler "incssp\[dq]\[ \t]+(%|)\[re]di" { target { ! ia32 } } } } */

#include <immintrin.h>

unsigned int f1 ()
{
  unsigned int x = 0;
  return __builtin_ia32_rdsspd (x);
}

void f3 (unsigned int _a)
{
  __builtin_ia32_incsspd (_a);
}

#ifdef __x86_64__
unsigned long long f2 ()
{
  unsigned long long x = 0;
  return __builtin_ia32_rdsspq (x);
}

void f4 (unsigned int _a)
{
  __builtin_ia32_incsspq (_a);
}
#endif
