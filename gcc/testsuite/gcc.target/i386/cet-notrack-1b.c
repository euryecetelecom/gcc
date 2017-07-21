/* { dg-do compile } */
/* { dg-options "-O -finstrument-control-flow -mcet" } */
/* { dg-final { scan-assembler-times "endbr32" 1 { target ia32 } } } */
/* { dg-final { scan-assembler-times "endbr64" 1 { target { ! ia32 } } } } */
/* { dg-final { scan-assembler-times "notrack call\[ \t]+" 2 } } */

int func (int a) __attribute__ ((notrack));
int (*fptr) (int a) __attribute__ ((notrack));

int foo (int arg)
{
int a, b;
  a = func (arg);
  b = (*fptr) (arg);
  return a+b;
}

int func (int arg)
{
int (*fptrl) (int a) __attribute__ ((notrack));
  return arg*(*fptrl)(arg);
}
