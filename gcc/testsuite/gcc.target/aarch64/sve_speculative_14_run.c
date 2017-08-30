/* { dg-do run { target { aarch64_sve_hw } } } */
/* { dg-options "-O3 -fno-common -ffast-math -march=armv8-a+sve" } */
/* { dg-options "-O3 -fno-common -ffast-math -march=armv8-a+sve -msve-vector-bits=256" { target aarch64_sve256_hw } } */

#define STRIDE_LEVEL 4

#define FILL_DATA 5
#define EXIT_CONDITION 22
#define LOOP_COUNTS {43,27,19,54,25,27}

#include "sve_speculative_11_run.c"
