/* ----------------------------------------------------------------------------
 * $Id$
 * ----------------------------------------------------------------------------
 * Public Domain C Library - http://pdclib.sourceforge.net
 * This code is Public Domain. Use, modify, and redistribute at will.
 * ----------------------------------------------------------------------------
 * Floating-point environment
 * --------------------------------------------------------------------------*/

#ifndef _FENV_H
#define _FENV_H _FENV_H

/* TODO: Documentation */

/* ----------------------------------------------------------------------------
 * MACROS
 * --------------------------------------------------------------------------*/

#define FE_DIVBYZERO  /* TODO - to __intern.h / __personality.h? */
#define FE_INEXACT    /* TODO - to __intern.h / __personality.h? */
#define FE_INVALID    /* TODO - to __intern.h / __personality.h? */
#define FE_OVERFLOW   /* TODO - to __intern.h / __personality.h? */
#define FE_UNDERFLOW  /* TODO - to __intern.h / __personality.h? */
#define FE_ALL_EXCEPT /* TODO - to __intern.h / __personality.h? */

#define FE_DOWNWARD   /* TODO - to __intern.h / __personality.h? */
#define FE_TONEAREST  /* TODO - to __intern.h / __personality.h? */
#define FE_TOWARDZERO /* TODO - to __intern.h / __personality.h? */
#define FE_UPWARD     /* TODO - to __intern.h / __personality.h? */

#define FE_DFL_ENV    /* TODO - to __intern.h / __personality.h? */

/* ----------------------------------------------------------------------------
 * TYPEDEFS
 * --------------------------------------------------------------------------*/

typedef fenv_t;    /* TODO - to __intern.h / __personality.h? */
typedef fexcept_t; /* TODO - to __intern.h / __personality.h? */

/* ----------------------------------------------------------------------------
 * FUNCTIONS
 * --------------------------------------------------------------------------*/

int feclearexcept( int exceptions );
int fegetexceptflag( fexcept_t * flags, int exceptions );
int feraiseexcept( int exceptions );
int fesetexceptflag( const fexcept_t * flags, int exceptions );
int fetestexcept( int exceptions );

int fegetround( void );
int fesetround( int mode );

int fegetenv( fenv_t * environment );
int feholdexcept( fenv_t * environment );
int fesetenv( const fenv_t * environment );
int feupdateenv( const fenv_t * environment );

#endif /* _FENV_H */
