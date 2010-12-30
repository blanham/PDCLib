/* $Id$ */

/* _PDCLIB_flushbuffer( struct _PDCLIB_file_t * )

   This file is part of the Public Domain C Library (PDCLib).
   Permission is granted to use, modify, and / or redistribute at will.
*/

/* This is an example implementation of _PDCLIB_flushbuffer() fit for
   use with POSIX kernels.
*/

#include <stdio.h>
#include <string.h>

#ifndef REGTEST
#include <_PDCLIB_glue.h>

#include </usr/include/errno.h>

typedef long ssize_t;
extern ssize_t write( int fd, const void * buf, size_t count );

/* The number of attempts to complete an output buffer flushing before giving
 *    up.
 *    */
#define _PDCLIB_IO_RETRIES 1

/* What the system should do after an I/O operation did not succeed, before   */
/* trying again. (Empty by default.)                                          */
#define _PDCLIB_IO_RETRY_OP( stream )

int _PDCLIB_flushbuffer( struct _PDCLIB_file_t * stream )
{
    if ( ! ( stream->status & _PDCLIB_FBIN ) )
    {
        /* TODO: Text stream conversion here */
    }
    /* No need to handle buffers > INT_MAX, as PDCLib doesn't allow them */
    _PDCLIB_size_t written = 0;
    int rc;
    /* Keep trying to write data until everything is written, an error
       occurs, or the configured number of retries is exceeded.
    */
    for ( unsigned int retries = _PDCLIB_IO_RETRIES; retries > 0; --retries )
    {
        rc = (int)write( stream->handle, stream->buffer + written, stream->bufidx - written );
        if ( rc < 0 )
        {
            /* Write error */
            switch ( errno )
            {
                /* See <_PDCLIB_config.h>. There should be differenciated errno
                   handling here, possibly even a 1:1 mapping; but that is up
                   to the individual platform.
                */
                case EBADF:
                case EFAULT:
                case EFBIG:
                case EINTR:
                case EINVAL:
                case EIO:
                case ENOSPC:
                case EPIPE:
                    _PDCLIB_errno = _PDCLIB_ERROR;
                    break;
                default:
                    /* This should be something like EUNKNOWN. */
                    _PDCLIB_errno = _PDCLIB_ERROR;
                    break;
            }
            stream->status |= _PDCLIB_ERRORFLAG;
            /* Move unwritten remains to begin of buffer. */
            stream->bufidx -= written;
            memmove( stream->buffer, stream->buffer + written, stream->bufidx );
            return EOF;
        }
        written += (_PDCLIB_size_t)rc;
        stream->pos.offset += rc;
        if ( written == stream->bufidx )
        {
            /* Buffer written completely. */
            stream->bufidx = 0;
            return 0;
        }
    }
    /* Number of retries exceeded. You probably want a different errno value
       here.
    */
    _PDCLIB_errno = _PDCLIB_ERROR;
    stream->status |= _PDCLIB_ERRORFLAG;
    /* Move unwritten remains to begin of buffer. */
    stream->bufidx -= written;
    memmove( stream->buffer, stream->buffer + written, stream->bufidx );
    return EOF;
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

