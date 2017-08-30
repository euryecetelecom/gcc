/* { dg-do run { target { aarch64_sve_hw } } } */
/* { dg-options "-O3 -fno-common -ffast-math -march=armv8-a+sve" } */
/* { dg-options "-O3 -fno-common -ffast-math -march=armv8-a+sve -msve-vector-bits=256" { target aarch64_sve256_hw } } */

#define STRIDE_LEVEL 3
#define EXIT_CONDITION 9
#define LOOP_COUNTS {19,47,15,35,23,33}

#include "sve_speculative_11_run.c"
