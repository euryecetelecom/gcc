/* { dg-do compile } */
/* { dg-options "-O0 -finstrument-control-flow -mcet" } */
/* { dg-final { scan-assembler-times "endbr32" 1 { target ia32 } } } */
/* { dg-final { scan-assembler-times "endbr64" 1 { target { ! ia32 } } } } */
/* { dg-final { scan-assembler-not "\tcall\[ \t]+" } } */
/* { dg-final { scan-assembler-times "notrack call\[ \t]+" 1 } } */

int foo (int arg);

int func (int arg)
{
  int (*fptrl) (int a) __attribute__ ((notrack)) = foo;

  return (*fptrl)(arg);  /* notrack call.  */
}
