/* ASCII codec

   This file is part of the Public Domain C Library (PDCLib).
   Permission is granted to use, modify, and / or redistribute at will.
*/

#include <stdbool.h>
#ifndef REGTEST
#include <uchar.h>
#include <_PDCLIB_encoding.h>

static bool ascii_mbsinit( const mbstate_t *ps )
{ return 1; }

static bool asciitoc32(
    char32_t       *restrict *restrict   p_outbuf,
    size_t                   *restrict   p_outsz,
    const char     *restrict *restrict   p_inbuf,
    size_t                   *restrict   p_insz,
    mbstate_t                *restrict   p_ps
)
{
    while(*p_outsz && *p_insz) {
        unsigned char c = **p_inbuf;
        if(c > 127)
            return false;
        
        if(p_outbuf) {
            **p_outbuf = c;
            (*p_outbuf)++; 
        }

        (*p_inbuf)++;
        (*p_insz)--; 
        (*p_outsz)--;
    }
    return true;
}

static bool c32toascii(
    char           *restrict *restrict  p_outbuf,
    size_t                   *restrict  p_outsz,
    const char32_t *restrict *restrict  p_inbuf,
    size_t                   *restrict  p_insz,
    mbstate_t                *restrict  p_ps
)
{
    while(*p_outsz && *p_insz) {
        char32_t c = **p_inbuf;
        if(c > 127)
            return false;

        if(p_outbuf) {
            **p_outbuf = c;
            (*p_outbuf)++; 
        }

        (*p_inbuf)++;
        (*p_insz)--; 
        (*p_outsz)--;        
    }
    return true;
}

const struct _PDCLIB_charcodec _PDCLIB_ascii_codec = {
    .__mbsinit   = ascii_mbsinit,
    .__mbstoc32s = asciitoc32,
    .__c32stombs = c32toascii,
    .__mb_max    = 1,
};

#endif

#ifdef TEST
#include <_PDCLIB_test.h>

int main( void )
{
#ifndef REGTEST
    // Valid conversion & back

    char32_t c32out[5];

    char32_t *c32ptr = &c32out[0];
    size_t    c32rem = 5;
    char     *chrptr = (char*) &abcde[0];
    size_t    chrrem = 5;
    mbstate_t mbs = { 0 };

    TESTCASE(asciitoc32(&c32ptr, &c32rem, &chrptr, &chrrem, &mbs) == true);
    TESTCASE(c32rem == 0);
    TESTCASE(chrrem == 0);
    TESTCASE(c32ptr == &c32out[5]);
    TESTCASE(chrptr == &abcde[5]);
    TESTCASE(c32out[0] == 'a' && c32out[1] == 'b' && c32out[2] == 'c' && \
             c32out[3] == 'd' && c32out[4] == 'e');

    char chrout[5];
    c32ptr = &c32out[0];
    c32rem = 5;
    chrptr = &chrout[0];
    chrrem = 5;


    TESTCASE(c32toascii(&chrptr, &chrrem, &c32ptr, &c32rem, &mbs) == true);
    TESTCASE(c32rem == 0);
    TESTCASE(chrrem == 0);
    TESTCASE(c32ptr == &c32out[5]);
    TESTCASE(chrptr == &chrout[5]);
    TESTCASE(memcmp(chrout, abcde, 5) == 0);

    // Invalid conversions
    char badascii = '\xC0';
    c32ptr = &c32out[0];
    c32rem = 5;
    chrptr = &badascii;
    chrrem = 1;
    TESTCASE(asciitoc32(&c32ptr, &c32rem, &chrptr, &chrrem, &mbs) == false);
    TESTCASE(c32ptr == &c32out[0]);
    TESTCASE(c32rem == 5);
    TESTCASE(chrptr == &badascii);
    TESTCASE(chrrem == 1);

    char32_t baduni = 0xC0;
    c32ptr = &baduni;
    c32rem = 1;
    chrptr = &chrout[0];
    chrrem = 5;
    TESTCASE(c32toascii(&chrptr, &chrrem, &c32ptr, &c32rem, &mbs) == false);
    TESTCASE(c32ptr == &baduni);
    TESTCASE(c32rem == 1);
    TESTCASE(chrptr == &chrout[0]);
    TESTCASE(chrrem == 5);
#endif
    return TEST_RESULTS;
}

#endif

