/* ----------------------------------------------------------------------------
 * $Id$
 * ----------------------------------------------------------------------------
 * Public Domain C Library - http://pdclib.sourceforge.net
 * This code is Public Domain. Use, modify, and redistribute at will.
 * ----------------------------------------------------------------------------
 * Errors
 * --------------------------------------------------------------------------*/

#ifndef _ERRNO_H
#define _ERRNO_H _ERRNO_H

#ifndef _PERSONALITY
#define _PERSONALITY _PERSONALITY
#include "__personality.h"
#endif /* _PERSONALITY */

/* TODO: Documentation */

/* ----------------------------------------------------------------------------
 * DECLARATIONS
 * --------------------------------------------------------------------------*/

extern int errno;

/* ----------------------------------------------------------------------------
 * DEFINES
 * --------------------------------------------------------------------------*/

#define EDOM   _EDOM   /* domain error                                       */
#define EILSEQ _EILSEQ /* illegal (multibyte) sequence                       */
#define ERANGE _ERANGE /* range error                                        */

#endif /* _ERRNO_H */
