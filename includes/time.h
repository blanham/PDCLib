/* ----------------------------------------------------------------------------
 * $Id$
 * ----------------------------------------------------------------------------
 * Public Domain C Library - http://pdclib.sourceforge.net
 * This code is Public Domain. Use, modify, and redistribute at will.
 * ----------------------------------------------------------------------------
 * Date and time
 * --------------------------------------------------------------------------*/

#ifndef _TIME_H
#define _TIME_H _TIME_H

#ifndef _NULL
#include "__intern.h"
#endif

/* TODO: Documentation. */

/* ----------------------------------------------------------------------------
 * MACROS
 * --------------------------------------------------------------------------*/

#define NULL _NULL

#define CLOCKS_PER_SEC /* TODO - to __intern.h / __personality.h? */

/* ----------------------------------------------------------------------------
 * TYPES
 * --------------------------------------------------------------------------*/

/* TODO: Get struct tm into __intern.h */

#ifndef _SIZE_T
#define _SIZE_T _SIZE_T
typedef __size_t size_t;
#endif /* _SIZE_T */

typedef clock_t; /* TODO - to __intern.h / __personality.h? */
typedef time_t;  /* TODO - to __intern.h / __personality.h? */

/* ----------------------------------------------------------------------------
 * FUNCTIONS
 * --------------------------------------------------------------------------*/

char * asctime( const struct tm * tptr );
clock_t clock( void );
char * ctime( const time_t * tod );
double difftime( time_t t1, time_t t0 );
struct tm * gmtime( const time_t * tod );
struct tm * localtime( const time_t * tod );
time_t mktime( struct tm * tptr );
size_t strftime( char * restrict s, size_t n, const char * restrict format,
                 const struct tm * restrict tptr );
time_t time( time_t * tod );

#endif /* _TIME_H */
