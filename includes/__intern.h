/* ----------------------------------------------------------------------------
 * $Id$
 * ----------------------------------------------------------------------------
 * Public Domain C Library - http://pdclib.sourceforge.net
 * This code is Public Domain. Use, modify, and redistribute at will.
 * ----------------------------------------------------------------------------
 * Internally used values (struct tm, _NULL, __size_t, __wchar_t, __wint_t,
 * _WCHAR_MIN, _WCHAR_MAX).
 * ----------------------------------------------------------------------------
 * Note that this file does not have a header guard. It is advised to check for
 * _NULL defore including it. (The idea is to avoid redundant opening of this
 * file during preprocessing.)
 * --------------------------------------------------------------------------*/

/* This should work on any environment. */
#define _NULL 0

#define _WCHAR_MAX /* TODO */
#define _WCHAR_MIN /* TODO */

#define _WEOF      /* TODO */

#define _EDOM      /* TODO */
#define _EILSEQ    /* TODO */
#define _ERANGE    /* TODO */

#define _SIGABRT   /* TODO */
#define _SIGFPE    /* TODO */
#define _SIGILL    /* TODO */
#define _SIGINT    /* TODO */
#define _SIGSEGV   /* TODO */
#define _SIGTERM   /* TODO */
#define _SIG_DFL   /* TODO */
#define _SIG_ERR   /* TODO */
#define _SIG_IGN   /* TODO */

typedef __size_t;       /* TODO */
typedef __wchar_t;      /* TODO */
typedef __wint_t;       /* TODO */
typedef __sig_atomic_t; /* TODO */

/* Including personality module so it can override generic settings, and set
 * the values that cannot be set generically.
 */
#include "__personality.h"
