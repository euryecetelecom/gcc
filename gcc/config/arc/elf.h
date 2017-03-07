/* Target macros for arc*-elf targets.

   Copyright (C) 2017 Free Software Foundation, Inc.

This file is part of GCC.

GCC is free software; you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation; either version 3, or (at your option)
any later version.

GCC is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with GCC; see the file COPYING3.  If not see
<http://www.gnu.org/licenses/>.  */

#undef DWARF2_UNWIND_INFO
#define DWARF2_UNWIND_INFO 0

#undef LINK_SPEC
#define LINK_SPEC "%{mbig-endian:-EB} %{EB} %{EL}"

#define ARC_TLS_EXTRA_START_SPEC "crttls.o%s"

#define EXTRA_SPECS \
  { "arc_tls_extra_start_spec", ARC_TLS_EXTRA_START_SPEC }, \

#undef STARTFILE_SPEC
#define STARTFILE_SPEC "%{pg|p:gcrt0.o%s}%{!pg:%{!p:crt0.o%s}} crti%O%s " \
  "%(arc_tls_extra_start_spec) crtbegin.o%s"

#undef ENDFILE_SPEC
#define ENDFILE_SPEC "crtend.o%s crtn%O%s"

/* Leave the linker script to choose the appropriate libraries.  */
#undef LIB_SPEC
#define LIB_SPEC ""

/* SDATA default for elf.  */
#undef TARGET_SDATA_DEFAULT
#define TARGET_SDATA_DEFAULT 1

/* We no medium calls.  */
#undef TARGET_MMEDIUM_CALLS_DEFAULT
#define TARGET_MMEDIUM_CALLS_DEFAULT 0

#ifdef ARC_MULTILIB_CPU_DEFAULT
# ifndef MULTILIB_DEFAULTS
#  define MULTILIB_DEFAULTS { "mcpu=" ARC_MULTILIB_CPU_DEFAULT }
# endif
#endif
