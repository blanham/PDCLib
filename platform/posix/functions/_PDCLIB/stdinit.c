/* $Id$ */

/* _PDCLIB_stdinit

   This file is part of the Public Domain C Library (PDCLib).
   Permission is granted to use, modify, and / or redistribute at will.
*/

/* This is an example initialization of stdin, stdout and stderr to the integer
   file descriptors 0, 1, and 2, respectively. This applies for a great variety
   of operating systems, including POSIX compliant ones.
*/

#include <stdio.h>
#include <locale.h>
#include <limits.h>

#ifndef REGTEST

/* In a POSIX system, stdin / stdout / stderr are equivalent to the (int) file
   descriptors 0, 1, and 2 respectively.
*/
/* TODO: This is proof-of-concept, requires finetuning. */
static char _PDCLIB_sin_buffer[BUFSIZ];
static char _PDCLIB_sout_buffer[BUFSIZ];
static char _PDCLIB_serr_buffer[BUFSIZ];

static unsigned char _PDCLIB_sin_ungetbuf[_PDCLIB_UNGETCBUFSIZE];
static unsigned char _PDCLIB_sout_ungetbuf[_PDCLIB_UNGETCBUFSIZE];
static unsigned char _PDCLIB_serr_ungetbuf[_PDCLIB_UNGETCBUFSIZE];

extern _PDCLIB_fileops_t _PDCLIB_fileops;
static struct _PDCLIB_file_t _PDCLIB_serr = { &_PDCLIB_fileops, { .sval = 2 }, 0, _PDCLIB_serr_buffer, BUFSIZ, 0, 0, { 0, 0 }, 0, _PDCLIB_serr_ungetbuf, _IONBF | _PDCLIB_FWRITE | _PDCLIB_STATIC, NULL, NULL };
static struct _PDCLIB_file_t _PDCLIB_sout = { &_PDCLIB_fileops, { .sval = 1 }, 0, _PDCLIB_sout_buffer, BUFSIZ, 0, 0, { 0, 0 }, 0, _PDCLIB_sout_ungetbuf, _IOLBF | _PDCLIB_FWRITE | _PDCLIB_STATIC, NULL, &_PDCLIB_serr };
static struct _PDCLIB_file_t _PDCLIB_sin  = { &_PDCLIB_fileops, { .sval = 0 }, 0, _PDCLIB_sin_buffer, BUFSIZ, 0, 0, { 0, 0 }, 0, _PDCLIB_sin_ungetbuf, _IOLBF | _PDCLIB_FREAD | _PDCLIB_STATIC, NULL, &_PDCLIB_sout };

struct _PDCLIB_file_t * stdin  = &_PDCLIB_sin;
struct _PDCLIB_file_t * stdout = &_PDCLIB_sout;
struct _PDCLIB_file_t * stderr = &_PDCLIB_serr;

/* FIXME: This approach is a possible attack vector. */
struct _PDCLIB_file_t * _PDCLIB_filelist = &_PDCLIB_sin;

/* "C" locale - defaulting to ASCII-7.
   1 kByte (+ 4 byte) of <ctype.h> data.
   Each line: flags, lowercase, uppercase, collation.
*/
static struct _PDCLIB_ctype_t _ctype[] = {
    { /* EOF */    0,    0,    0,    0 },
    { /* NUL */ _PDCLIB_CTYPE_CNTRL,                                             0x00, 0x00, 0x00 },
    { /* SOH */ _PDCLIB_CTYPE_CNTRL,                                             0x01, 0x01, 0x01 },
    { /* STX */ _PDCLIB_CTYPE_CNTRL,                                             0x02, 0x02, 0x02 },
    { /* ETX */ _PDCLIB_CTYPE_CNTRL,                                             0x03, 0x03, 0x03 },
    { /* EOT */ _PDCLIB_CTYPE_CNTRL,                                             0x04, 0x04, 0x04 },
    { /* ENQ */ _PDCLIB_CTYPE_CNTRL,                                             0x05, 0x05, 0x05 },
    { /* ACK */ _PDCLIB_CTYPE_CNTRL,                                             0x06, 0x06, 0x06 },
    { /* BEL */ _PDCLIB_CTYPE_CNTRL,                                             0x07, 0x07, 0x07 },
    { /*  BS */ _PDCLIB_CTYPE_CNTRL,                                             0x08, 0x08, 0x08 },
    { /*  HT */ _PDCLIB_CTYPE_CNTRL | _PDCLIB_CTYPE_BLANK | _PDCLIB_CTYPE_SPACE, 0x09, 0x09, 0x09 },
    { /*  LF */ _PDCLIB_CTYPE_CNTRL | _PDCLIB_CTYPE_SPACE,                       0x0A, 0x0A, 0x0A },
    { /*  VT */ _PDCLIB_CTYPE_CNTRL | _PDCLIB_CTYPE_SPACE,                       0x0B, 0x0B, 0x0B },
    { /*  FF */ _PDCLIB_CTYPE_CNTRL | _PDCLIB_CTYPE_SPACE,                       0x0C, 0x0C, 0x0C },
    { /*  CR */ _PDCLIB_CTYPE_CNTRL | _PDCLIB_CTYPE_SPACE,                       0x0D, 0x0D, 0x0D },
    { /*  SO */ _PDCLIB_CTYPE_CNTRL,                                             0x0E, 0x0E, 0x0E },
    { /*  SI */ _PDCLIB_CTYPE_CNTRL,                                             0x0F, 0x0F, 0x0F },
    { /* DLE */ _PDCLIB_CTYPE_CNTRL,                                             0x10, 0x10, 0x10 },
    { /* DC1 */ _PDCLIB_CTYPE_CNTRL,                                             0x11, 0x11, 0x11 },
    { /* DC2 */ _PDCLIB_CTYPE_CNTRL,                                             0x12, 0x12, 0x12 },
    { /* DC3 */ _PDCLIB_CTYPE_CNTRL,                                             0x13, 0x13, 0x13 },
    { /* DC4 */ _PDCLIB_CTYPE_CNTRL,                                             0x14, 0x14, 0x14 },
    { /* NAK */ _PDCLIB_CTYPE_CNTRL,                                             0x15, 0x15, 0x15 },
    { /* SYN */ _PDCLIB_CTYPE_CNTRL,                                             0x16, 0x16, 0x16 },
    { /* ETB */ _PDCLIB_CTYPE_CNTRL,                                             0x17, 0x17, 0x17 },
    { /* CAN */ _PDCLIB_CTYPE_CNTRL,                                             0x18, 0x18, 0x18 },
    { /*  EM */ _PDCLIB_CTYPE_CNTRL,                                             0x19, 0x19, 0x19 },
    { /* SUB */ _PDCLIB_CTYPE_CNTRL,                                             0x1A, 0x1A, 0x1A },
    { /* ESC */ _PDCLIB_CTYPE_CNTRL,                                             0x1B, 0x1B, 0x1B },
    { /*  FS */ _PDCLIB_CTYPE_CNTRL,                                             0x1C, 0x1C, 0x1C },
    { /*  GS */ _PDCLIB_CTYPE_CNTRL,                                             0x1D, 0x1D, 0x1D },
    { /*  RS */ _PDCLIB_CTYPE_CNTRL,                                             0x1E, 0x1E, 0x1E },
    { /*  US */ _PDCLIB_CTYPE_CNTRL,                                             0x1F, 0x1F, 0x1F },
    { /*  SP */ _PDCLIB_CTYPE_BLANK | _PDCLIB_CTYPE_SPACE,                       0x20, 0x20, 0x20 },
    { /* '!' */ _PDCLIB_CTYPE_GRAPH | _PDCLIB_CTYPE_PUNCT,                       0x21, 0x21, 0x21 },
    { /* '"' */ _PDCLIB_CTYPE_GRAPH | _PDCLIB_CTYPE_PUNCT,                       0x22, 0x22, 0x22 },
    { /* '#' */ _PDCLIB_CTYPE_GRAPH | _PDCLIB_CTYPE_PUNCT,                       0x23, 0x23, 0x23 },
    { /* '$' */ _PDCLIB_CTYPE_GRAPH | _PDCLIB_CTYPE_PUNCT,                       0x24, 0x24, 0x24 },
    { /* '%' */ _PDCLIB_CTYPE_GRAPH | _PDCLIB_CTYPE_PUNCT,                       0x25, 0x25, 0x25 },
    { /* '&' */ _PDCLIB_CTYPE_GRAPH | _PDCLIB_CTYPE_PUNCT,                       0x26, 0x26, 0x26 },
    { /* ''' */ _PDCLIB_CTYPE_GRAPH | _PDCLIB_CTYPE_PUNCT,                       0x27, 0x27, 0x27 },
    { /* '(' */ _PDCLIB_CTYPE_GRAPH | _PDCLIB_CTYPE_PUNCT,                       0x28, 0x28, 0x28 },
    { /* ')' */ _PDCLIB_CTYPE_GRAPH | _PDCLIB_CTYPE_PUNCT,                       0x29, 0x29, 0x29 },
    { /* '*' */ _PDCLIB_CTYPE_GRAPH | _PDCLIB_CTYPE_PUNCT,                       0x2A, 0x2A, 0x2A },
    { /* '+' */ _PDCLIB_CTYPE_GRAPH | _PDCLIB_CTYPE_PUNCT,                       0x2B, 0x2B, 0x2B },
    { /* ',' */ _PDCLIB_CTYPE_GRAPH | _PDCLIB_CTYPE_PUNCT,                       0x2C, 0x2C, 0x2C },
    { /* '-' */ _PDCLIB_CTYPE_GRAPH | _PDCLIB_CTYPE_PUNCT,                       0x2D, 0x2D, 0x2D },
    { /* '.' */ _PDCLIB_CTYPE_GRAPH | _PDCLIB_CTYPE_PUNCT,                       0x2E, 0x2E, 0x2E },
    { /* '/' */ _PDCLIB_CTYPE_GRAPH | _PDCLIB_CTYPE_PUNCT,                       0x2F, 0x2F, 0x2F },
    { /* '0' */ _PDCLIB_CTYPE_GRAPH | _PDCLIB_CTYPE_DIGIT | _PDCLIB_CTYPE_XDIGT, 0x30, 0x30, 0x30 },
    { /* '1' */ _PDCLIB_CTYPE_GRAPH | _PDCLIB_CTYPE_DIGIT | _PDCLIB_CTYPE_XDIGT, 0x31, 0x31, 0x31 },
    { /* '2' */ _PDCLIB_CTYPE_GRAPH | _PDCLIB_CTYPE_DIGIT | _PDCLIB_CTYPE_XDIGT, 0x32, 0x32, 0x32 },
    { /* '3' */ _PDCLIB_CTYPE_GRAPH | _PDCLIB_CTYPE_DIGIT | _PDCLIB_CTYPE_XDIGT, 0x33, 0x33, 0x33 },
    { /* '4' */ _PDCLIB_CTYPE_GRAPH | _PDCLIB_CTYPE_DIGIT | _PDCLIB_CTYPE_XDIGT, 0x34, 0x34, 0x34 },
    { /* '5' */ _PDCLIB_CTYPE_GRAPH | _PDCLIB_CTYPE_DIGIT | _PDCLIB_CTYPE_XDIGT, 0x35, 0x35, 0x35 },
    { /* '6' */ _PDCLIB_CTYPE_GRAPH | _PDCLIB_CTYPE_DIGIT | _PDCLIB_CTYPE_XDIGT, 0x36, 0x36, 0x36 },
    { /* '7' */ _PDCLIB_CTYPE_GRAPH | _PDCLIB_CTYPE_DIGIT | _PDCLIB_CTYPE_XDIGT, 0x37, 0x37, 0x37 },
    { /* '8' */ _PDCLIB_CTYPE_GRAPH | _PDCLIB_CTYPE_DIGIT | _PDCLIB_CTYPE_XDIGT, 0x38, 0x38, 0x38 },
    { /* '9' */ _PDCLIB_CTYPE_GRAPH | _PDCLIB_CTYPE_DIGIT | _PDCLIB_CTYPE_XDIGT, 0x39, 0x39, 0x39 },
    { /* ':' */ _PDCLIB_CTYPE_GRAPH | _PDCLIB_CTYPE_PUNCT,                       0x3A, 0x3A, 0x3A },
    { /* ';' */ _PDCLIB_CTYPE_GRAPH | _PDCLIB_CTYPE_PUNCT,                       0x3B, 0x3B, 0x3B },
    { /* '<' */ _PDCLIB_CTYPE_GRAPH | _PDCLIB_CTYPE_PUNCT,                       0x3C, 0x3C, 0x3C },
    { /* '=' */ _PDCLIB_CTYPE_GRAPH | _PDCLIB_CTYPE_PUNCT,                       0x3D, 0x3D, 0x3D },
    { /* '>' */ _PDCLIB_CTYPE_GRAPH | _PDCLIB_CTYPE_PUNCT,                       0x3E, 0x3E, 0x3E },
    { /* '?' */ _PDCLIB_CTYPE_GRAPH | _PDCLIB_CTYPE_PUNCT,                       0x3F, 0x3F, 0x3F },
    { /* '@' */ _PDCLIB_CTYPE_GRAPH | _PDCLIB_CTYPE_PUNCT,                       0x40, 0x40, 0x40 },
    { /* 'A' */ _PDCLIB_CTYPE_GRAPH | _PDCLIB_CTYPE_ALPHA | _PDCLIB_CTYPE_UPPER | _PDCLIB_CTYPE_XDIGT, 0x41, 0x61, 0x41 },
    { /* 'B' */ _PDCLIB_CTYPE_GRAPH | _PDCLIB_CTYPE_ALPHA | _PDCLIB_CTYPE_UPPER | _PDCLIB_CTYPE_XDIGT, 0x42, 0x62, 0x42 },
    { /* 'C' */ _PDCLIB_CTYPE_GRAPH | _PDCLIB_CTYPE_ALPHA | _PDCLIB_CTYPE_UPPER | _PDCLIB_CTYPE_XDIGT, 0x43, 0x63, 0x43 },
    { /* 'D' */ _PDCLIB_CTYPE_GRAPH | _PDCLIB_CTYPE_ALPHA | _PDCLIB_CTYPE_UPPER | _PDCLIB_CTYPE_XDIGT, 0x44, 0x64, 0x44 },
    { /* 'E' */ _PDCLIB_CTYPE_GRAPH | _PDCLIB_CTYPE_ALPHA | _PDCLIB_CTYPE_UPPER | _PDCLIB_CTYPE_XDIGT, 0x45, 0x65, 0x45 },
    { /* 'F' */ _PDCLIB_CTYPE_GRAPH | _PDCLIB_CTYPE_ALPHA | _PDCLIB_CTYPE_UPPER | _PDCLIB_CTYPE_XDIGT, 0x46, 0x66, 0x46 },
    { /* 'G' */ _PDCLIB_CTYPE_GRAPH | _PDCLIB_CTYPE_ALPHA | _PDCLIB_CTYPE_UPPER, 0x47, 0x67, 0x47 },
    { /* 'H' */ _PDCLIB_CTYPE_GRAPH | _PDCLIB_CTYPE_ALPHA | _PDCLIB_CTYPE_UPPER, 0x48, 0x68, 0x48 },
    { /* 'I' */ _PDCLIB_CTYPE_GRAPH | _PDCLIB_CTYPE_ALPHA | _PDCLIB_CTYPE_UPPER, 0x49, 0x69, 0x49 },
    { /* 'J' */ _PDCLIB_CTYPE_GRAPH | _PDCLIB_CTYPE_ALPHA | _PDCLIB_CTYPE_UPPER, 0x4A, 0x6A, 0x4A },
    { /* 'K' */ _PDCLIB_CTYPE_GRAPH | _PDCLIB_CTYPE_ALPHA | _PDCLIB_CTYPE_UPPER, 0x4B, 0x6B, 0x4B },
    { /* 'L' */ _PDCLIB_CTYPE_GRAPH | _PDCLIB_CTYPE_ALPHA | _PDCLIB_CTYPE_UPPER, 0x4C, 0x6C, 0x4C },
    { /* 'M' */ _PDCLIB_CTYPE_GRAPH | _PDCLIB_CTYPE_ALPHA | _PDCLIB_CTYPE_UPPER, 0x4D, 0x6D, 0x4D },
    { /* 'N' */ _PDCLIB_CTYPE_GRAPH | _PDCLIB_CTYPE_ALPHA | _PDCLIB_CTYPE_UPPER, 0x4E, 0x6E, 0x4E },
    { /* 'O' */ _PDCLIB_CTYPE_GRAPH | _PDCLIB_CTYPE_ALPHA | _PDCLIB_CTYPE_UPPER, 0x4F, 0x6F, 0x4F },
    { /* 'P' */ _PDCLIB_CTYPE_GRAPH | _PDCLIB_CTYPE_ALPHA | _PDCLIB_CTYPE_UPPER, 0x50, 0x70, 0x50 },
    { /* 'Q' */ _PDCLIB_CTYPE_GRAPH | _PDCLIB_CTYPE_ALPHA | _PDCLIB_CTYPE_UPPER, 0x51, 0x71, 0x51 },
    { /* 'R' */ _PDCLIB_CTYPE_GRAPH | _PDCLIB_CTYPE_ALPHA | _PDCLIB_CTYPE_UPPER, 0x52, 0x72, 0x52 },
    { /* 'S' */ _PDCLIB_CTYPE_GRAPH | _PDCLIB_CTYPE_ALPHA | _PDCLIB_CTYPE_UPPER, 0x53, 0x73, 0x53 },
    { /* 'T' */ _PDCLIB_CTYPE_GRAPH | _PDCLIB_CTYPE_ALPHA | _PDCLIB_CTYPE_UPPER, 0x54, 0x74, 0x54 },
    { /* 'U' */ _PDCLIB_CTYPE_GRAPH | _PDCLIB_CTYPE_ALPHA | _PDCLIB_CTYPE_UPPER, 0x55, 0x75, 0x55 },
    { /* 'V' */ _PDCLIB_CTYPE_GRAPH | _PDCLIB_CTYPE_ALPHA | _PDCLIB_CTYPE_UPPER, 0x56, 0x76, 0x56 },
    { /* 'W' */ _PDCLIB_CTYPE_GRAPH | _PDCLIB_CTYPE_ALPHA | _PDCLIB_CTYPE_UPPER, 0x57, 0x77, 0x57 },
    { /* 'X' */ _PDCLIB_CTYPE_GRAPH | _PDCLIB_CTYPE_ALPHA | _PDCLIB_CTYPE_UPPER, 0x58, 0x78, 0x58 },
    { /* 'Y' */ _PDCLIB_CTYPE_GRAPH | _PDCLIB_CTYPE_ALPHA | _PDCLIB_CTYPE_UPPER, 0x59, 0x79, 0x59 },
    { /* 'Z' */ _PDCLIB_CTYPE_GRAPH | _PDCLIB_CTYPE_ALPHA | _PDCLIB_CTYPE_UPPER, 0x5A, 0x7A, 0x5A },
    { /* '[' */ _PDCLIB_CTYPE_GRAPH | _PDCLIB_CTYPE_PUNCT,                       0x5B, 0x5B, 0x5B },
    { /* '\' */ _PDCLIB_CTYPE_GRAPH | _PDCLIB_CTYPE_PUNCT,                       0x5C, 0x5C, 0x5C },
    { /* ']' */ _PDCLIB_CTYPE_GRAPH | _PDCLIB_CTYPE_PUNCT,                       0x5D, 0x5D, 0x5D },
    { /* '^' */ _PDCLIB_CTYPE_GRAPH | _PDCLIB_CTYPE_PUNCT,                       0x5E, 0x5E, 0x5E },
    { /* '_' */ _PDCLIB_CTYPE_GRAPH | _PDCLIB_CTYPE_PUNCT,                       0x5F, 0x5F, 0x5F },
    { /* '`' */ _PDCLIB_CTYPE_GRAPH | _PDCLIB_CTYPE_PUNCT,                       0x60, 0x60, 0x60 },
    { /* 'a' */ _PDCLIB_CTYPE_GRAPH | _PDCLIB_CTYPE_ALPHA | _PDCLIB_CTYPE_LOWER | _PDCLIB_CTYPE_XDIGT, 0x41, 0x61, 0x61 },
    { /* 'b' */ _PDCLIB_CTYPE_GRAPH | _PDCLIB_CTYPE_ALPHA | _PDCLIB_CTYPE_LOWER | _PDCLIB_CTYPE_XDIGT, 0x42, 0x62, 0x62 },
    { /* 'c' */ _PDCLIB_CTYPE_GRAPH | _PDCLIB_CTYPE_ALPHA | _PDCLIB_CTYPE_LOWER | _PDCLIB_CTYPE_XDIGT, 0x43, 0x63, 0x63 },
    { /* 'd' */ _PDCLIB_CTYPE_GRAPH | _PDCLIB_CTYPE_ALPHA | _PDCLIB_CTYPE_LOWER | _PDCLIB_CTYPE_XDIGT, 0x44, 0x64, 0x64 },
    { /* 'e' */ _PDCLIB_CTYPE_GRAPH | _PDCLIB_CTYPE_ALPHA | _PDCLIB_CTYPE_LOWER | _PDCLIB_CTYPE_XDIGT, 0x45, 0x65, 0x65 },
    { /* 'f' */ _PDCLIB_CTYPE_GRAPH | _PDCLIB_CTYPE_ALPHA | _PDCLIB_CTYPE_LOWER | _PDCLIB_CTYPE_XDIGT, 0x46, 0x66, 0x66 },
    { /* 'g' */ _PDCLIB_CTYPE_GRAPH | _PDCLIB_CTYPE_ALPHA | _PDCLIB_CTYPE_LOWER, 0x47, 0x67, 0x67 },
    { /* 'h' */ _PDCLIB_CTYPE_GRAPH | _PDCLIB_CTYPE_ALPHA | _PDCLIB_CTYPE_LOWER, 0x48, 0x68, 0x68 },
    { /* 'i' */ _PDCLIB_CTYPE_GRAPH | _PDCLIB_CTYPE_ALPHA | _PDCLIB_CTYPE_LOWER, 0x49, 0x69, 0x69 },
    { /* 'j' */ _PDCLIB_CTYPE_GRAPH | _PDCLIB_CTYPE_ALPHA | _PDCLIB_CTYPE_LOWER, 0x4A, 0x6A, 0x6A },
    { /* 'k' */ _PDCLIB_CTYPE_GRAPH | _PDCLIB_CTYPE_ALPHA | _PDCLIB_CTYPE_LOWER, 0x4B, 0x6B, 0x6B },
    { /* 'l' */ _PDCLIB_CTYPE_GRAPH | _PDCLIB_CTYPE_ALPHA | _PDCLIB_CTYPE_LOWER, 0x4C, 0x6C, 0x6C },
    { /* 'm' */ _PDCLIB_CTYPE_GRAPH | _PDCLIB_CTYPE_ALPHA | _PDCLIB_CTYPE_LOWER, 0x4D, 0x6D, 0x6D },
    { /* 'n' */ _PDCLIB_CTYPE_GRAPH | _PDCLIB_CTYPE_ALPHA | _PDCLIB_CTYPE_LOWER, 0x4E, 0x6E, 0x6E },
    { /* 'o' */ _PDCLIB_CTYPE_GRAPH | _PDCLIB_CTYPE_ALPHA | _PDCLIB_CTYPE_LOWER, 0x4F, 0x6F, 0x6F },
    { /* 'p' */ _PDCLIB_CTYPE_GRAPH | _PDCLIB_CTYPE_ALPHA | _PDCLIB_CTYPE_LOWER, 0x50, 0x70, 0x70 },
    { /* 'q' */ _PDCLIB_CTYPE_GRAPH | _PDCLIB_CTYPE_ALPHA | _PDCLIB_CTYPE_LOWER, 0x51, 0x71, 0x71 },
    { /* 'r' */ _PDCLIB_CTYPE_GRAPH | _PDCLIB_CTYPE_ALPHA | _PDCLIB_CTYPE_LOWER, 0x52, 0x72, 0x72 },
    { /* 's' */ _PDCLIB_CTYPE_GRAPH | _PDCLIB_CTYPE_ALPHA | _PDCLIB_CTYPE_LOWER, 0x53, 0x73, 0x73 },
    { /* 't' */ _PDCLIB_CTYPE_GRAPH | _PDCLIB_CTYPE_ALPHA | _PDCLIB_CTYPE_LOWER, 0x54, 0x74, 0x74 },
    { /* 'u' */ _PDCLIB_CTYPE_GRAPH | _PDCLIB_CTYPE_ALPHA | _PDCLIB_CTYPE_LOWER, 0x55, 0x75, 0x75 },
    { /* 'v' */ _PDCLIB_CTYPE_GRAPH | _PDCLIB_CTYPE_ALPHA | _PDCLIB_CTYPE_LOWER, 0x56, 0x76, 0x76 },
    { /* 'w' */ _PDCLIB_CTYPE_GRAPH | _PDCLIB_CTYPE_ALPHA | _PDCLIB_CTYPE_LOWER, 0x57, 0x77, 0x77 },
    { /* 'x' */ _PDCLIB_CTYPE_GRAPH | _PDCLIB_CTYPE_ALPHA | _PDCLIB_CTYPE_LOWER, 0x58, 0x78, 0x78 },
    { /* 'y' */ _PDCLIB_CTYPE_GRAPH | _PDCLIB_CTYPE_ALPHA | _PDCLIB_CTYPE_LOWER, 0x59, 0x79, 0x79 },
    { /* 'z' */ _PDCLIB_CTYPE_GRAPH | _PDCLIB_CTYPE_ALPHA | _PDCLIB_CTYPE_LOWER, 0x5A, 0x7A, 0x7A },
    { /* '{' */ _PDCLIB_CTYPE_GRAPH | _PDCLIB_CTYPE_PUNCT,                       0x7B, 0x7B, 0x7B },
    { /* '|' */ _PDCLIB_CTYPE_GRAPH | _PDCLIB_CTYPE_PUNCT,                       0x7C, 0x7C, 0x7C },
    { /* '}' */ _PDCLIB_CTYPE_GRAPH | _PDCLIB_CTYPE_PUNCT,                       0x7D, 0x7D, 0x7D },
    { /* '~' */ _PDCLIB_CTYPE_GRAPH | _PDCLIB_CTYPE_PUNCT,                       0x7E, 0x7E, 0x7E },
    { /* DEL */ _PDCLIB_CTYPE_CNTRL,                                             0x7F, 0x7F, 0x7F },
    { 0x00, 0x80, 0x80, 0x80 },
    { 0x00, 0x81, 0x81, 0x81 },
    { 0x00, 0x82, 0x82, 0x82 },
    { 0x00, 0x83, 0x83, 0x83 },
    { 0x00, 0x84, 0x84, 0x84 },
    { 0x00, 0x85, 0x85, 0x85 },
    { 0x00, 0x86, 0x86, 0x86 },
    { 0x00, 0x87, 0x87, 0x87 },
    { 0x00, 0x88, 0x88, 0x88 },
    { 0x00, 0x89, 0x89, 0x89 },
    { 0x00, 0x8A, 0x8A, 0x8A },
    { 0x00, 0x8B, 0x8B, 0x8B },
    { 0x00, 0x8C, 0x8C, 0x8C },
    { 0x00, 0x8D, 0x8D, 0x8D },
    { 0x00, 0x8E, 0x8E, 0x8E },
    { 0x00, 0x8F, 0x8F, 0x8F },
    { 0x00, 0x90, 0x90, 0x90 },
    { 0x00, 0x91, 0x91, 0x91 },
    { 0x00, 0x92, 0x92, 0x92 },
    { 0x00, 0x93, 0x93, 0x93 },
    { 0x00, 0x94, 0x94, 0x94 },
    { 0x00, 0x95, 0x95, 0x95 },
    { 0x00, 0x96, 0x96, 0x96 },
    { 0x00, 0x97, 0x97, 0x97 },
    { 0x00, 0x98, 0x98, 0x98 },
    { 0x00, 0x99, 0x99, 0x99 },
    { 0x00, 0x9A, 0x9A, 0x9A },
    { 0x00, 0x9B, 0x9B, 0x9B },
    { 0x00, 0x9C, 0x9C, 0x9C },
    { 0x00, 0x9D, 0x9D, 0x9D },
    { 0x00, 0x9E, 0x9E, 0x9E },
    { 0x00, 0x9F, 0x9F, 0x9F },
    { 0x00, 0xA0, 0xA0, 0xA0 },
    { 0x00, 0xA1, 0xA1, 0xA1 },
    { 0x00, 0xA2, 0xA2, 0xA2 },
    { 0x00, 0xA3, 0xA3, 0xA3 },
    { 0x00, 0xA4, 0xA4, 0xA4 },
    { 0x00, 0xA5, 0xA5, 0xA5 },
    { 0x00, 0xA6, 0xA6, 0xA6 },
    { 0x00, 0xA7, 0xA7, 0xA7 },
    { 0x00, 0xA8, 0xA8, 0xA8 },
    { 0x00, 0xA9, 0xA9, 0xA9 },
    { 0x00, 0xAA, 0xAA, 0xAA },
    { 0x00, 0xAB, 0xAB, 0xAB },
    { 0x00, 0xAC, 0xAC, 0xAC },
    { 0x00, 0xAD, 0xAD, 0xAD },
    { 0x00, 0xAE, 0xAE, 0xAE },
    { 0x00, 0xAF, 0xAF, 0xAF },
    { 0x00, 0xB0, 0xB0, 0xB0 },
    { 0x00, 0xB1, 0xB1, 0xB1 },
    { 0x00, 0xB2, 0xB2, 0xB2 },
    { 0x00, 0xB3, 0xB3, 0xB3 },
    { 0x00, 0xB4, 0xB4, 0xB4 },
    { 0x00, 0xB5, 0xB5, 0xB5 },
    { 0x00, 0xB6, 0xB6, 0xB6 },
    { 0x00, 0xB7, 0xB7, 0xB7 },
    { 0x00, 0xB8, 0xB8, 0xB8 },
    { 0x00, 0xB9, 0xB9, 0xB9 },
    { 0x00, 0xBA, 0xBA, 0xBA },
    { 0x00, 0xBB, 0xBB, 0xBB },
    { 0x00, 0xBC, 0xBC, 0xBC },
    { 0x00, 0xBD, 0xBD, 0xBD },
    { 0x00, 0xBE, 0xBE, 0xBE },
    { 0x00, 0xBF, 0xBF, 0xBF },
    { 0x00, 0xC0, 0xC0, 0xC0 },
    { 0x00, 0xC1, 0xC1, 0xC1 },
    { 0x00, 0xC2, 0xC2, 0xC2 },
    { 0x00, 0xC3, 0xC3, 0xC3 },
    { 0x00, 0xC4, 0xC4, 0xC4 },
    { 0x00, 0xC5, 0xC5, 0xC5 },
    { 0x00, 0xC6, 0xC6, 0xC6 },
    { 0x00, 0xC7, 0xC7, 0xC7 },
    { 0x00, 0xC8, 0xC8, 0xC8 },
    { 0x00, 0xC9, 0xC9, 0xC9 },
    { 0x00, 0xCA, 0xCA, 0xCA },
    { 0x00, 0xCB, 0xCB, 0xCB },
    { 0x00, 0xCC, 0xCC, 0xCC },
    { 0x00, 0xCD, 0xCD, 0xCD },
    { 0x00, 0xCE, 0xCE, 0xCE },
    { 0x00, 0xCF, 0xCF, 0xCF },
    { 0x00, 0xD0, 0xD0, 0xD0 },
    { 0x00, 0xD1, 0xD1, 0xD1 },
    { 0x00, 0xD2, 0xD2, 0xD2 },
    { 0x00, 0xD3, 0xD3, 0xD3 },
    { 0x00, 0xD4, 0xD4, 0xD4 },
    { 0x00, 0xD5, 0xD5, 0xD5 },
    { 0x00, 0xD6, 0xD6, 0xD6 },
    { 0x00, 0xD7, 0xD7, 0xD7 },
    { 0x00, 0xD8, 0xD8, 0xD8 },
    { 0x00, 0xD9, 0xD9, 0xD9 },
    { 0x00, 0xDA, 0xDA, 0xDA },
    { 0x00, 0xDB, 0xDB, 0xDB },
    { 0x00, 0xDC, 0xDC, 0xDC },
    { 0x00, 0xDD, 0xDD, 0xDD },
    { 0x00, 0xDE, 0xDE, 0xDE },
    { 0x00, 0xDF, 0xDF, 0xDF },
    { 0x00, 0xE0, 0xE0, 0xE0 },
    { 0x00, 0xE1, 0xE1, 0xE1 },
    { 0x00, 0xE2, 0xE2, 0xE2 },
    { 0x00, 0xE3, 0xE3, 0xE3 },
    { 0x00, 0xE4, 0xE4, 0xE4 },
    { 0x00, 0xE5, 0xE5, 0xE5 },
    { 0x00, 0xE6, 0xE6, 0xE6 },
    { 0x00, 0xE7, 0xE7, 0xE7 },
    { 0x00, 0xE8, 0xE8, 0xE8 },
    { 0x00, 0xE9, 0xE9, 0xE9 },
    { 0x00, 0xEA, 0xEA, 0xEA },
    { 0x00, 0xEB, 0xEB, 0xEB },
    { 0x00, 0xEC, 0xEC, 0xEC },
    { 0x00, 0xED, 0xED, 0xED },
    { 0x00, 0xEE, 0xEE, 0xEE },
    { 0x00, 0xEF, 0xEF, 0xEF },
    { 0x00, 0xF0, 0xF0, 0xF0 },
    { 0x00, 0xF1, 0xF1, 0xF1 },
    { 0x00, 0xF2, 0xF2, 0xF2 },
    { 0x00, 0xF3, 0xF3, 0xF3 },
    { 0x00, 0xF4, 0xF4, 0xF4 },
    { 0x00, 0xF5, 0xF5, 0xF5 },
    { 0x00, 0xF6, 0xF6, 0xF6 },
    { 0x00, 0xF7, 0xF7, 0xF7 },
    { 0x00, 0xF8, 0xF8, 0xF8 },
    { 0x00, 0xF9, 0xF9, 0xF9 },
    { 0x00, 0xFA, 0xFA, 0xFA },
    { 0x00, 0xFB, 0xFB, 0xFB },
    { 0x00, 0xFC, 0xFC, 0xFC },
    { 0x00, 0xFD, 0xFD, 0xFD },
    { 0x00, 0xFE, 0xFE, 0xFE },
    { 0x00, 0xFF, 0xFF, 0xFF }
};

struct lconv _PDCLIB_lconv = { 
    /* _PDCLIB_ctype      */ _ctype + 1,
    /* _PDCLIB_errno_texts */
    {
        /* no error */ (char *)"",
        /* ERANGE   */ (char *)"ERANGE (Range error)",
        /* EDOM     */ (char *)"EDOM (Domain error)",
        /* EILSEQ   */ (char *)"EILSEQ (Illegal sequence)"
    },
    /* decimal_point      */ (char *)".",
    /* thousands_sep      */ (char *)"",
    /* grouping           */ (char *)"",
    /* mon_decimal_point  */ (char *)"",
    /* mon_thousands_sep  */ (char *)"",
    /* mon_grouping       */ (char *)"",
    /* positive_sign      */ (char *)"",
    /* negative_sign      */ (char *)"",
    /* currency_symbol    */ (char *)"",
    /* int_curr_symbol    */ (char *)"",
    /* frac_digits        */ CHAR_MAX,
    /* p_cs_precedes      */ CHAR_MAX,
    /* n_cs_precedes      */ CHAR_MAX,
    /* p_sep_by_space     */ CHAR_MAX,
    /* n_sep_by_space     */ CHAR_MAX,
    /* p_sign_posn        */ CHAR_MAX,
    /* n_sign_posn        */ CHAR_MAX,
    /* int_frac_digits    */ CHAR_MAX,
    /* int_p_cs_precedes  */ CHAR_MAX,
    /* int_n_cs_precedes  */ CHAR_MAX,
    /* int_p_sep_by_space */ CHAR_MAX,
    /* int_n_sep_by_space */ CHAR_MAX,
    /* int_p_sign_posn    */ CHAR_MAX,
    /* int_n_sign_posn    */ CHAR_MAX,
};

#endif

#ifdef TEST
#include <_PDCLIB_test.h>

int main( void )
{
    /* Testing covered by several other testdrivers using stdin / stdout / 
       stderr.
    */
    return TEST_RESULTS;
}

#endif
