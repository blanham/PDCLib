/* $Id$ */

/* Release $Name$ */

/* strncpy( char *, const char *, size_t )

   This file is part of the Public Domain C Library (PDCLib).
   Permission is granted to use, modify, and / or redistribute at will.
*/

#include <string.h>

#ifndef REGTEST

char * strncpy( char * _PDCLIB_restrict s1, const char * _PDCLIB_restrict s2, size_t n )
{
    char * rc = s1;
    while ( ( n > 0 ) && ( *s1++ = *s2++ ) )
    {
        /* Cannot do "n--" in the conditional as size_t is unsigned and we have
        to check it again for >0 in the next loop.
        */
        --n;
    }
    while ( --n )
    {
        *s1++ = '\0';
    }
    return rc;
}

#endif

#ifdef TEST
#include <_PDCLIB_test.h>

int main( void )
{
    char s[] = "xxxxxxx";
    TESTCASE( strncpy( s, "", 1 ) == s );
    TESTCASE( s[0] == '\0' );
    TESTCASE( s[1] == 'x' );
    TESTCASE( strncpy( s, abcde, 6 ) == s );
    TESTCASE( s[0] == 'a' );
    TESTCASE( s[4] == 'e' );
    TESTCASE( s[5] == '\0' );
    TESTCASE( s[6] == 'x' );
    TESTCASE( strncpy( s, abcde, 7 ) == s );
    TESTCASE( s[6] == '\0' );
    return TEST_RESULTS;
}
#endif
