/* ----------------------------------------------------------------------------
 * $Id$
 * ----------------------------------------------------------------------------
 * Public Domain C Library - http://pdclib.sourceforge.net
 * This code is Public Domain. Use, modify, and redistribute at will.
 * ----------------------------------------------------------------------------
 * Signal handling
 * --------------------------------------------------------------------------*/

#ifndef _SIGNAL_H
#define _SIGNAL_H _SIGNAL_H

#ifndef _NULL
#include "__intern.h"
#endif

/* TODO: Documentation */

/* ----------------------------------------------------------------------------
 * MACROS
 * --------------------------------------------------------------------------*/

#define SIGABRT _SIGABRT
#define SIGFPE  _SIGFPE
#define SIGILL  _SIGILL
#define SIGINT  _SIGINT
#define SIGSEGV _SIGSEGV
#define SIGTERM _SIGTERM
#define SIG_DFL _SIG_DFL
#define SIG_ERR _SIG_ERR
#define SIG_IGN _SIG_IGN

/* ----------------------------------------------------------------------------
 * TYPEDEFS
 * --------------------------------------------------------------------------*/

#ifndef _SIG_ATOMIC_T
#define _SIG_ATOMIC_T _SIG_ATOMIC_T
typedef __sig_atomic_t sig_atomic_t;
#endif /* _SIG_ATOMIC_T

/* ----------------------------------------------------------------------------
 * FUNCTIONS
 * --------------------------------------------------------------------------*/

int raise( int sig );                                        /* TODO */
void ( * signal( int sig, void ( *func )( int ) ) ) ( int ); /* TODO */

#endif /* _SIGNAL_H */
