/* ----------------------------------------------------------------------------
 * $Id$
 * ----------------------------------------------------------------------------
 * Public Domain C Library - http://pdclib.sourceforge.net
 * This code is Public Domain. Use, modify, and redistribute at will.
 * ----------------------------------------------------------------------------
 * Boolean type and values
 * ----------------------------------------------------------------------------
 * This header is part of a freestanding implementation
 * --------------------------------------------------------------------------*/

#ifndef _STDBOOL_H
#define _STDBOOL_H _STDBOOL_H

/* ----------------------------------------------------------------------------
 * MACROS
 * --------------------------------------------------------------------------*/

#define __bool_true_false_are_defined 1

#ifndef __cplusplus

#define bool  _Bool
#define false 0
#define true  1

/* ----------------------------------------------------------------------------
 * TYPEDEFS
 * --------------------------------------------------------------------------*/

typedef int bool;

#endif /* __cplusplus */

#endif /* _STDBOOL_H */
