/* { dg-additional-options "-O2" } */
/* { dg-additional-options "-fdump-tree-dom_oacc_kernels3" } */

#include <stdlib.h>

#define N (1024 * 512)
#define COUNTERTYPE unsigned int

COUNTERTYPE
foo (unsigned int *c)
{
  COUNTERTYPE ii;

#pragma acc kernels copyout (c[0:N])
  {
    for (ii = 0; ii < N; ii++)
      c[ii] = 1;
  }

  return ii;
}

/* We're expecting:

   .omp_data_i_10 = &.omp_data_arr.3;
   _11 = .omp_data_i_10->ii;
   *_11 = 0;
   _15 = .omp_data_i_10->c;
   c.1_16 = *_15;

   Check that there are two loads from anonymous ssa-names, which we assume to
   be:
   - the one to read c
   - the one to read ii after the kernels region.  */

/* { dg-final { scan-tree-dump-times "(?n)\\*_\[0-9\]\[0-9\]*;$" 2 "dom_oacc_kernels3" } } */
