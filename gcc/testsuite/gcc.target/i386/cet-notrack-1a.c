/* { dg-do compile } */
/* { dg-options "-O0 -fno-instrument-control-flow -mno-cet" } */
/* { dg-final { scan-assembler-not "endbr" } } */
/* { dg-final { scan-assembler-not "notrack call\[ \t]+" } } */

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
