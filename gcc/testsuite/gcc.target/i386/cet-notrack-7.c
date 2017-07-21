/* Check the notrack prefix is not generated for direct call.  */
/* { dg-do compile } */
/* { dg-options "-O -finstrument-control-flow -mcet" } */
/* { dg-final { scan-assembler-times "endbr32" 1 { target ia32 } } } */
/* { dg-final { scan-assembler-times "endbr64" 1 { target { ! ia32 } } } } */
/* { dg-final { scan-assembler-times "notrack call\[ \t]+foo" 0 } } */
/* { dg-final { scan-assembler-times "\tcall\[ \t]+foo" 1 } } */

extern void foo (void) __attribute__((notrack));

void
bar (void)
{
  foo ();
}
