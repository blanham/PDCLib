/* $Id$ */

/* rewind( FILE * )

   This file is part of the Public Domain C Library (PDCLib).
   Permission is granted to use, modify, and / or redistribute at will.
*/

#include <stdio.h>

#ifndef REGTEST
#include <_PDCLIB_io.h>

void rewind_unlocked( FILE * stream )
{
    stream->status &= ~ _PDCLIB_ERRORFLAG;
    fseek_unlocked( stream, 0L, SEEK_SET );
}

void rewind( FILE * stream )
{
    flockfile(stream);
    rewind_unlocked(stream);
    funlockfile(stream);
}

#endif

#ifdef TEST
#include <_PDCLIB_test.h>

int main( void )
{
    /* Testing covered by ftell.c */
    return TEST_RESULTS;
}

#endif
