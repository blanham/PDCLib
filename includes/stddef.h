/* ----------------------------------------------------------------------------
 * $Id$
 * ----------------------------------------------------------------------------
 * Public Domain C Library - http://pdclib.sourceforge.net
 * This code is Public Domain. Use, modify, and redistribute at will.
 * ----------------------------------------------------------------------------
 * Common definitions
 * ----------------------------------------------------------------------------
 * This header is part of a freestanding implementation
 * --------------------------------------------------------------------------*/

#ifndef _STDDEF_H
#define _STDDEF_H _STDDEF_H

#ifndef _NULL
#include "__intern.h"
#endif

/* TODO: Documentation */

/* ----------------------------------------------------------------------------
 * MACROS
 * --------------------------------------------------------------------------*/

#define NULL _NULL

#define offsetof( s-type, mbr ) /* TODO - to __intern.h / __personality.h? */

/* ----------------------------------------------------------------------------
 * TYPEDEFS
 * --------------------------------------------------------------------------*/

#ifndef _SIZE_T
#define _SIZE_T _SIZE_T
typedef __size_t size_t;
#endif /* _SIZE_T */

#ifndef _WCHAR_T
#define _WCHAR_T _WCHAR_T
typedef __wchar_t wchar_t;
#endif /* _WCHAR_T */

/* Look this up in the C Standard Rationale, which has example code on this. */
typedef ptrdiff_t; /* TODO - to __intern.h / __personality.h? */

#endif /* _STDDEF_H */
