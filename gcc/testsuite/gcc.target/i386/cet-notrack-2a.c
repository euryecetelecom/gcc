/* { dg-do compile } */
/* { dg-options "-O -finstrument-control-flow -mcet" } */
/* { dg-final { scan-assembler-times "endbr32" 1 { target ia32 } } } */
/* { dg-final { scan-assembler-times "endbr64" 1 { target { ! ia32 } } } } */
/* { dg-final { scan-assembler-times "notrack call\[ \t]+" 1 } } */

void
bar (void (*foo) (void))
{
  void (*func) (void) __attribute__((notrack)) = foo;
  func ();
}
