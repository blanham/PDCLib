/* ----------------------------------------------------------------------------
 * $Id$
 * ----------------------------------------------------------------------------
 * Public Domain C Library - http://pdclib.sourceforge.net
 * This code is Public Domain. Use, modify, and redistribute at will.
 * ----------------------------------------------------------------------------
 * Diagnostics
 * --------------------------------------------------------------------------*/

#ifndef _ASSERT_H
#define _ASSERT_H _ASSERT_H

/* ----------------------------------------------------------------------------
 * AUXILIARY
 * --------------------------------------------------------------------------*/

/* Helper function doing the print to stderr and call to abort(). */
void __assert( char const * const expression, /* the tested expression       */
               char const * const file,       /* name of source file         */
               char const * const function,   /* name of function            */
               int const line );              /* number of source file line  */

#endif /* _ASSERT_H - note that the header guard ends here on purpose. The
                      assert macro is redefined upon each inclusion, in
                      dependence of NDEBUG.                                  */

/* ----------------------------------------------------------------------------
 * DEFINES
 * --------------------------------------------------------------------------*/

#undef assert
#if defined NDEBUG
#define assert( x ) ( (void) 0 )
#else
#define assert( x ) ( x ) ? ( (void) 0 ) \
                          :  __assert( #x, __FILE__, __func__, __LINE__ )
#endif
