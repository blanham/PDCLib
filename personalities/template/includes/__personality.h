/* ----------------------------------------------------------------------------
 * $Id$
 * ----------------------------------------------------------------------------
 * Public Domain C Library - http://pdclib.sourceforge.net
 * This code is Public Domain. Use, modify, and redistribute at will.
 * ----------------------------------------------------------------------------
 * Personality #define's (see personality.txt)
 * --------------------------------------------------------------------------*/

/* No header guard - including file is expected to check this (improves
 * performance)
 */

#define _PERSONALITY

/* This structure is required by time.h and wchar.h. */
struct tm;

/* This type is required by wchar.h and wctype.h. */
typedef __wint_t;

/* #undef this if environment does not support _Imaginary. */
#define __PERSONALITY_SUPPORTS_IMAGINARY

#endif /* _PERSONALITY */
