/* { dg-do run { target aarch64_sve_hw } } */
/* { dg-options "-O2 -ftree-vectorize -march=armv8-a+sve" } */

#define TYPE float
#define ITYPE int
#include "sve_struct_vect_7_run.c"
