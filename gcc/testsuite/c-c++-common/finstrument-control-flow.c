/* { dg-do compile } */
/* { dg-options "-finstrument-control-flow" } */
/* { dg-error "'-finstrument-control-flow' requires CET support on this target. Use -mcet or one of -mibt, -mshstk options to enable CET." "" { target { "i?86-*-* x86_64-*-*" } } 0 } */
/* { dg-error "'-finstrument-control-flow' is not supported for this target" "" { target { ! "i?86-*-* x86_64-*-*" } } 0 } */
