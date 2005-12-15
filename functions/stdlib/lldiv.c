/* $Id$ */

/* Release $Name$ */

/* lldiv( long long int, long long int )

   This file is part of the Public Domain C Library (PDCLib).
   Permission is granted to use, modify, and / or redistribute at will.
*/

#include <stdlib.h>

#ifndef REGTEST

lldiv_t lldiv( long long int numer, long long int denom )
{
    lldiv_t rc;
    rc.quot = numer / denom;
    rc.rem  = numer % denom;
    /* TODO: pre-C99 compilers might require modulus corrections */
    return rc;
}

#endif

#ifdef TEST
#include <_PDCLIB_test.h>

#ifndef _PDCLIB_CONFIG_H
#include <_PDCLIB_config.h>
#endif

int main()
{
    lldiv_t div;
    BEGIN_TESTS;
    div = lldiv( 5, 2 );
    TESTCASE( div.quot == 2 && div.rem == 1 );
    div = lldiv( -5, 2 );
    TESTCASE( div.quot == -2 && div.rem == -1 );
    div = lldiv( 5, -2 );
    TESTCASE( div.quot == -2 && div.rem == 1 );
    TESTCASE( sizeof( div.quot ) == _PDCLIB_LLONG_BYTES );
    TESTCASE( sizeof( div.rem )  == _PDCLIB_LLONG_BYTES );
    return TEST_RESULTS;
}

#endif
