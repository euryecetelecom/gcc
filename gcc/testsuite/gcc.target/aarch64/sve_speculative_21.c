/* { dg-do compile } */
/* { dg-options "-O3 -fno-common -ffast-math -march=armv8-a+sve -fdump-tree-vect-details -msve-vector-bits=scalable" } */

/* Speculative loop with two strided loads which cannot both be aligned.
   Will attempt first faulting and fail to use it.  */

#define STRIDE_LEVEL 4

#include "sve_speculative_9.c"

/* { dg-final { scan-tree-dump-not "loop versioned for vectorization to enhance alignment" "vect" } } */
/* { dg-final { scan-tree-dump-not "Alignment of access forced using peeling" "vect" } } */
/* { dg-final { scan-tree-dump-times "unknown alignment, setting loop as first faulting" 8 "vect" } } */
/* { dg-final { scan-tree-dump-not "LOOP VECTORIZED" "vect" } } */
