/* $Id$ */

/* _PDCLIB_digits

   This file is part of the Public Domain C Library (PDCLib).
   Permission is granted to use, modify, and / or redistribute at will.
*/

#include <_PDCLIB_int.h>

char _PDCLIB_digits[] = "0123456789abcdefghijklmnopqrstuvwxyz";

/* For _PDCLIB/print.c only; obsolete with ctype.h */
char _PDCLIB_Xdigits[] = "0123456789ABCDEF";

#ifdef TEST
#include <_PDCLIB_test.h>

#include <string.h>

int main( void )
{
    TESTCASE( strcmp( _PDCLIB_digits, "0123456789abcdefghijklmnopqrstuvwxyz" ) == 0 );
    TESTCASE( strcmp( _PDCLIB_Xdigits, "0123456789ABCDEF" ) == 0 );
    return TEST_RESULTS;
}

#endif
