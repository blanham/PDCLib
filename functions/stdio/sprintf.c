/* $Id$ */

/* sprintf( char *, const char *, ... )

   This file is part of the Public Domain C Library (PDCLib).
   Permission is granted to use, modify, and / or redistribute at will.
*/

#include <stdio.h>
#include <stdint.h>
#include <stdarg.h>

#ifndef REGTEST

int sprintf( char * _PDCLIB_restrict s, const char * _PDCLIB_restrict format, ...)
{
    int rc;
    va_list ap;
    va_start( ap, format );
    rc = vsnprintf( s, SIZE_MAX, format, ap ); /* TODO: replace with non-checking call */
    va_end( ap );
    return rc;
}

#endif

#ifdef TEST
#define _PDCLIB_FILEID "stdio/sprintf.c"
#include <_PDCLIB_test.h>

#include <string.h>
#include <limits.h>

#define testprintf( s, format, ... ) sprintf( s, format, __VA_ARGS__ )

int main( void )
{
    char target[100];
#include "printf_testcases.incl"
    return TEST_RESULTS;
}

#endif
