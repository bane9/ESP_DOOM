/* Copyright (C) 1991-2017 Free Software Foundation, Inc.
   This file is part of the GNU C Library.
   The GNU C Library is free software; you can redistribute it and/or
   modify it under the terms of the GNU Lesser General Public
   License as published by the Free Software Foundation; either
   version 2.1 of the License, or (at your option) any later version.
   The GNU C Library is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
   Lesser General Public License for more details.
   You should have received a copy of the GNU Lesser General Public
   License along with the GNU C Library; if not, see
   <http://www.gnu.org/licenses/>.  */
/*
 *        ISO C99 Standard: 7.10/5.2.4.2.1 Sizes of integer types        <limits.h>
 */
#ifndef _LIBC_LIMITS_H_
#define _LIBC_LIMITS_H_        1
#define __GLIBC_INTERNAL_STARTING_HEADER_IMPLEMENTATION
#include "features.h"
/* ISO/IEC TR 24731-2:2010 defines the __STDC_WANT_LIB_EXT2__
   macro.  */
#undef __GLIBC_USE_LIB_EXT2
#if (defined __USE_GNU                                                        \
     || (defined __STDC_WANT_LIB_EXT2__ && __STDC_WANT_LIB_EXT2__ > 0))
# define __GLIBC_USE_LIB_EXT2 1
#else
# define __GLIBC_USE_LIB_EXT2 0
#endif
/* ISO/IEC TS 18661-1:2014 defines the __STDC_WANT_IEC_60559_BFP_EXT__
   macro.  */
#undef __GLIBC_USE_IEC_60559_BFP_EXT
#if defined __USE_GNU || defined __STDC_WANT_IEC_60559_BFP_EXT__
# define __GLIBC_USE_IEC_60559_BFP_EXT 1
#else
# define __GLIBC_USE_IEC_60559_BFP_EXT 0
#endif
/* ISO/IEC TS 18661-4:2015 defines the
   __STDC_WANT_IEC_60559_FUNCS_EXT__ macro.  */
#undef __GLIBC_USE_IEC_60559_FUNCS_EXT
#if defined __USE_GNU || defined __STDC_WANT_IEC_60559_FUNCS_EXT__
# define __GLIBC_USE_IEC_60559_FUNCS_EXT 1
#else
# define __GLIBC_USE_IEC_60559_FUNCS_EXT 0
#endif
/* ISO/IEC TS 18661-3:2015 defines the
   __STDC_WANT_IEC_60559_TYPES_EXT__ macro.  */
#undef __GLIBC_USE_IEC_60559_TYPES_EXT
#if defined __USE_GNU || defined __STDC_WANT_IEC_60559_TYPES_EXT__
# define __GLIBC_USE_IEC_60559_TYPES_EXT 1
#else
# define __GLIBC_USE_IEC_60559_TYPES_EXT 0
#endif

/* Maximum length of any multibyte character in any locale.
   We define this value here since the gcc header does not define
   the correct value.  */
#define MB_LEN_MAX        16
/* If we are not using GNU CC we have to define all the symbols ourself.
   Otherwise use gcc's definitions (see below).  */
#if !defined __GNUC__ || __GNUC__ < 2
/* We only protect from multiple inclusion here, because all the other
   #include's protect themselves, and in GCC 2 we may #include_next through
   multiple copies of this file before we get to GCC's.  */
# ifndef _LIMITS_H
#  define _LIMITS_H        1
#if defined __x86_64__
# define __WORDSIZE        64
# define __WORDSIZE_COMPAT32        1
#else
# define __WORDSIZE        32
#endif
/* We don't have #include_next.
   Define ANSI <limits.h> for standard 32-bit words.  */
/* These assume 8-bit `char's, 16-bit `short int's,
   and 32-bit `int's and `long int's.  */
/* Number of bits in a `char'.        */
#  define CHAR_BIT        8
/* Minimum and maximum values a `signed char' can hold.  */
#  define SCHAR_MIN        (-128)
#  define SCHAR_MAX        127
/* Maximum value an `unsigned char' can hold.  (Minimum is 0.)  */
#  define UCHAR_MAX        255
/* Minimum and maximum values a `char' can hold.  */
#  ifdef __CHAR_UNSIGNED__
#   define CHAR_MIN        0
#   define CHAR_MAX        UCHAR_MAX
#  else
#   define CHAR_MIN        SCHAR_MIN
#   define CHAR_MAX        SCHAR_MAX
#  endif
/* Minimum and maximum values a `signed short int' can hold.  */
#  define SHRT_MIN        (-32768)
#  define SHRT_MAX        32767
/* Maximum value an `unsigned short int' can hold.  (Minimum is 0.)  */
#  define USHRT_MAX        65535
/* Minimum and maximum values a `signed int' can hold.  */
#  define INT_MIN        (-INT_MAX - 1)
#  define INT_MAX        2147483647
/* Maximum value an `unsigned int' can hold.  (Minimum is 0.)  */
#  define UINT_MAX        4294967295U
/* Minimum and maximum values a `signed long int' can hold.  */
#  if __WORDSIZE == 64
#   define LONG_MAX        9223372036854775807L
#  else
#   define LONG_MAX        2147483647L
#  endif
#  define LONG_MIN        (-LONG_MAX - 1L)
/* Maximum value an `unsigned long int' can hold.  (Minimum is 0.)  */
#  if __WORDSIZE == 64
#   define ULONG_MAX        18446744073709551615UL
#  else
#   define ULONG_MAX        4294967295UL
#  endif
#  ifdef __USE_ISOC99
/* Minimum and maximum values a `signed long long int' can hold.  */
#   define LLONG_MAX        9223372036854775807LL
#   define LLONG_MIN        (-LLONG_MAX - 1LL)
/* Maximum value an `unsigned long long int' can hold.  (Minimum is 0.)  */
#   define ULLONG_MAX        18446744073709551615ULL
#  endif /* ISO C99 */
# endif        /* limits.h  */
#endif        /* GCC 2.  */
#endif        /* !_LIBC_LIMITS_H_ */
 /* Get the compiler's limits.h, which defines almost all the ISO constants.
    We put this #include_next outside the double inclusion check because
    it should be possible to include this file more than once and still get
    the definitions from gcc's header.  */
#if defined __GNUC__ && !defined _GCC_LIMITS_H_
/* `_GCC_LIMITS_H_' is what GCC's file defines.  */
# include_next <limits.h>
#endif
/* The <limits.h> files in some gcc versions don't define LLONG_MIN,
   LLONG_MAX, and ULLONG_MAX.  Instead only the values gcc defined for
   ages are available.  */
#if defined __USE_ISOC99 && defined __GNUC__
# ifndef LLONG_MIN
#  define LLONG_MIN        (-LLONG_MAX-1)
# endif
# ifndef LLONG_MAX
#  define LLONG_MAX        __LONG_LONG_MAX__
# endif
# ifndef ULLONG_MAX
#  define ULLONG_MAX        (LLONG_MAX * 2ULL + 1)
# endif
#endif
/* The integer width macros are not defined by GCC's <limits.h> before
   GCC 7, or if _GNU_SOURCE rather than
   __STDC_WANT_IEC_60559_BFP_EXT__ is used to enable this feature.  */
#if 1
# ifndef CHAR_WIDTH
#  define CHAR_WIDTH 8
# endif
# ifndef SCHAR_WIDTH
#  define SCHAR_WIDTH 8
# endif
# ifndef UCHAR_WIDTH
#  define UCHAR_WIDTH 8
# endif
# ifndef SHRT_WIDTH
#  define SHRT_WIDTH 16
# endif
# ifndef USHRT_WIDTH
#  define USHRT_WIDTH 16
# endif
# ifndef INT_WIDTH
#  define INT_WIDTH 32
# endif
# ifndef UINT_WIDTH
#  define UINT_WIDTH 32
# endif
# ifndef LONG_WIDTH
#  define LONG_WIDTH __WORDSIZE
# endif
# ifndef ULONG_WIDTH
#  define ULONG_WIDTH __WORDSIZE
# endif
# ifndef LLONG_WIDTH
#  define LLONG_WIDTH 64
# endif
# ifndef ULLONG_WIDTH
#  define ULLONG_WIDTH 64
# endif
#endif /* Use IEC_60559_BFP_EXT.  */
#ifdef        __USE_POSIX
/* POSIX adds things to <limits.h>.  */
# include "posix1_lim.h"
#endif
#ifdef        __USE_POSIX2
/* The maximum `ibase' and `obase' values allowed by the `bc' utility.  */
#define        _POSIX2_BC_BASE_MAX                99

/* The maximum number of elements allowed in an array by the `bc' utility.  */
#define        _POSIX2_BC_DIM_MAX                2048

/* The maximum `scale' value allowed by the `bc' utility.  */
#define        _POSIX2_BC_SCALE_MAX                99

/* The maximum length of a string constant accepted by the `bc' utility.  */
#define        _POSIX2_BC_STRING_MAX                1000

/* The maximum number of weights that can be assigned to an entry of
   the LC_COLLATE `order' keyword in the locale definition file.  */
#define        _POSIX2_COLL_WEIGHTS_MAX        2

/* The maximum number of expressions that can be nested
   within parentheses by the `expr' utility.  */
#define        _POSIX2_EXPR_NEST_MAX                32

/* The maximum length, in bytes, of an input line.  */
#define        _POSIX2_LINE_MAX                2048

/* The maximum number of repeated occurrences of a regular expression
   permitted when using the interval notation `\{M,N\}'.  */
#define        _POSIX2_RE_DUP_MAX                255

/* The maximum number of bytes in a character class name.  We have no
   fixed limit, 2048 is a high number.  */
#define        _POSIX2_CHARCLASS_NAME_MAX        14


/* These values are implementation-specific,
   and may vary within the implementation.
   Their precise values can be obtained from sysconf.  */

#ifndef        BC_BASE_MAX
#define        BC_BASE_MAX                _POSIX2_BC_BASE_MAX
#endif
#ifndef        BC_DIM_MAX
#define        BC_DIM_MAX                _POSIX2_BC_DIM_MAX
#endif
#ifndef        BC_SCALE_MAX
#define        BC_SCALE_MAX                _POSIX2_BC_SCALE_MAX
#endif
#ifndef        BC_STRING_MAX
#define        BC_STRING_MAX                _POSIX2_BC_STRING_MAX
#endif
#ifndef        COLL_WEIGHTS_MAX
#define        COLL_WEIGHTS_MAX        255
#endif
#ifndef        EXPR_NEST_MAX
#define        EXPR_NEST_MAX                _POSIX2_EXPR_NEST_MAX
#endif
#ifndef        LINE_MAX
#define        LINE_MAX                _POSIX2_LINE_MAX
#endif
#ifndef        CHARCLASS_NAME_MAX
#define        CHARCLASS_NAME_MAX        2048
#endif

/* This value is defined like this in regex.h.  */
#define        RE_DUP_MAX (0x7fff)
#endif
#ifdef        __USE_XOPEN
#endif
