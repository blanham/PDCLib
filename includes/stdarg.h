/* ----------------------------------------------------------------------------
 * $Id$
 * ----------------------------------------------------------------------------
 * Public Domain C Library - http://pdclib.sourceforge.net
 * This code is Public Domain. Use, modify, and redistribute at will.
 * ----------------------------------------------------------------------------
 * Variable arguments
 * ----------------------------------------------------------------------------
 * This header is part of a freestanding implementation
 * --------------------------------------------------------------------------*/

#ifndef _STDARG_H
#define _STDARG_H _STDARG_H

/* TODO: This code was contributed by Michael Moody, who added:
 * "As always with my code it's not guaranteed bug-free (In fact I know for a
 * fact it won't work properly on certain archs)."
 * Code assumes that:
 * - arguments are passed on the stack;
 * - arguments are alligned to pointer size.
 */

/* ----------------------------------------------------------------------------
 * TYPEDEFS
 * --------------------------------------------------------------------------*/

typedef char * va_list;

/* ----------------------------------------------------------------------------
 * MACROS
 * --------------------------------------------------------------------------*/

/** Returns the size of 'type' rounded up to the nearest multiple of the size
 * of a pointer. This macro is just here for clarity.
 */
#define __va_round(type)                                                      \
   (                                                                          \
      (sizeof(type) + sizeof(void *) - 1) & ~(sizeof(void *) - 1)             \
   )

/** Initialises ap for use by va_arg by setting ap to point at the first
 * argument in the ellipsis. parmN is the last known parameter in the function
 * definition (ie the one before the ellipsis).
 */
#define va_start(ap, parmN)                                                   \
   (                                                                          \
      (ap) = (char *)&parmN + (__va_round(parmN))                               \
      ,                                                                       \
      (void)0                                                                 \
   )

/** Returns the next argument, assumed variable type is 'type', in the
 * ellipsis.
 */
#define va_arg(ap, type)                                                      \
   (                                                                          \
      (ap) += (__va_round(type))                                              \
      ,                                                                       \
      (*(type*)((ap) - (__va_round(type))))                                   \
   )

/** Cleans up ap.
 */
#define va_end(ap)                                                            \
   (                                                                          \
      (ap) = (void *)0                                                        \
      ,                                                                       \
      (void)0                                                                 \
   )

/** Makes the va_list dest be a copy of the va_list src.
 */
#define va_copy(dest, src)                                                    \
   (                                                                          \
      (dest) = (src)                                                          \
      ,                                                                       \
      (void)0                                                                 \
   )

#endif /* _STDARG_H */
