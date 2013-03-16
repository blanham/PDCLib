/* towupper( wint_t )

   This file is part of the Public Domain C Library (PDCLib).
   Permission is granted to use, modify, and / or redistribute at will.
*/

#include <wctype.h>
#ifndef REGTEST
#include <_PDCLIB_locale.h>

wint_t towupper( wint_t wc )
{
    wint_t uwc = _PDCLIB_unpackwint( wc );
    _PDCLIB_wcinfo_t *info = _PDCLIB_wcgetinfo( uwc );
    if( info && info->upper != uwc ) 
    {
        wc = info->upper;
    }
    return wc;
}

#endif

#ifdef TEST
#include <_PDCLIB_test.h>

int main( void )
{
    TESTCASE(towupper(0) == 0);
    TESTCASE(towupper(L'a') == L'A');
    TESTCASE(towupper(L'B') == L'B');
    TESTCASE(towupper(L'0') == L'0');

    return TEST_RESULTS;
}
#endif
