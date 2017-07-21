/* Check the attribute do not proparate through assignment.  */
/* { dg-do compile } */
/* { dg-options "-O -finstrument-control-flow -mcet" } */
/* { dg-final { scan-assembler-times "endbr32" 1 { target ia32 } } } */
/* { dg-final { scan-assembler-times "endbr64" 1 { target { ! ia32 } } } } */
/* { dg-final { scan-assembler-times "\tcall\[ \t]+" 1 } } */
/* { dg-final { scan-assembler-times "notrack call\[ \t]+" 1 } } */

int (*fptr) (int) __attribute__ ((notrack));
int (*fptr1) (int);

int
foo (int arg)
{
  int a;
  a = (*fptr) (arg); /* notrack call.  */
  arg += a;
  fptr1 = fptr;
  a = (*fptr1) (arg); /* track call.  */
  return arg+a;
}
