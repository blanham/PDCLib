/* ----------------------------------------------------------------------------
 * $Id$
 * ----------------------------------------------------------------------------
 * Public Domain C Library - http://pdclib.sourceforge.net
 * This code is Public Domain. Use, modify, and redistribute at will.
 * ----------------------------------------------------------------------------
 * Mathematics
 * --------------------------------------------------------------------------*/

#ifndef _MATH_H
#define _MATH_H _MATH_H

/* TODO: Documentation */

/* ----------------------------------------------------------------------------
 * DEFINES
 * --------------------------------------------------------------------------*/

#define HUGE_VAL  ((double)0x7FF0000000000000)          /* TODO */
#define HUGE_VALF ((float)0x7F800000)                   /* TODO */
#define HUGE_VALL ((long double)0x7FFF8000000000000000) /* TODO */

#define INFINITY ((float)0x7F800000) /* TODO */
#define NAN      ((float)0x7F800001) /* TODO */

/* The following values are platform dependant, must be personality. */
#if 0
#define FP_FAST_FMA  /* TODO */
#define FP_FAST_FMAF /* TODO */
#define FP_FAST_FMAL /* TODO */
#endif

/* These values are used instead of constants to classify numbers. */
#define FP_UNDEFINED 0
#define FP_INFINITE  1
#define FP_NAN       2
#define FP_NORMAL    3
#define FP_SUBNORMAL 4
#define FP_ZERO      5

#define FP_ILOGB0   /* TODO */
#define FP_ILOGBNAN /* TODO */

#define MATH_ERRNO       1
#define MATH_ERREXCEPT   2

/* should be MATH_ERRNO | MATH_ERREXCEPT if we do exceptions. Do we? It's 
 * nice if this is implementation-wide the same.
 */
#define math_errhandling ((int)MATH_ERRNO)

/* ----------------------------------------------------------------------------
 * TYPEDEFS
 * --------------------------------------------------------------------------*/

typedef double_t
#if FLT_EVAL_METHOD == 0
    double
#elif FLT_EVAL_METHOD == 1
    double
#elif FLT_EVAL_METHOD == 2
    long double
#else
    /* TODO - this is implementation defined and cpu dependant */
#endif
;

typedef float_t
#if FLT_EVAL_METHOD == 0
    float
#elif FLT_EVAL_METHOD == 1
    double
#elif FLT_EVAL_METHOD == 2
    long double
#else
    /* TODO - this is implementation defined and cpu dependant */
#endif
;

/* ----------------------------------------------------------------------------
 * MACROS
 * --------------------------------------------------------------------------*/

#define isgreater( x, y )      /* TODO */
#define isgreaterequal( x, y ) /* TODO */
#define isless( x, y )         /* TODO */
#define islessequal( x, y )    /* TODO */
#define islessgreater( x, y )  /* TODO */
#define isunordered( x, y )    /* TODO */

/* Could somebody clean this macro up? It uses 7 other definitions (below).
 * Also, I suspect this macro to be personality-dependant. Somebody confirm
 * or deny?
 */
#define fp_mef 0x7F800000
#define fp_mff 0x007FFFFF
#define fp_med 0x7FF0000000000000
#define fp_mfd 0x000FFFFFFFFFFFFF
#define fp_mel 0x7FFF8000000000000000
#define fp_mjl 0x00004000000000000000 // the j-bit mask
#define fp_mfl 0x00003FFFFFFFFFFFFFFF

#define fpclassify( x ) ((sizeof(x) == sizeof(float)) ? ( \
                          (((x) & fp_mef) == (fp_mef)) ? ( \
                           (((x) & fp_mff) == (0)) ? ( \
                            FP_INFINITY \
                           ) : ( \
                            FP_NAN \
                           ) \
                          ) : ( \
                           (((x) & fp_mef) == (0)) ? ( \
                            (((x) & fp_mff) == (0)) ? ( \
                             FP_ZERO \
                            ) : ( \
                             FP_DENORMAL \
                            ) \
                           ) : ( \
                            FP_NORMAL \
                           ) \
                          ) \
                         ) : (
                          (sizeof(x) == sizeof(double)) ? ( \
                           (((x) & fp_med) == (fp_med)) ? ( \
                            (((x) & fp_mfd) == (0)) ? ( \
                             FP_INFINITY \
                            ) : ( \
                             FP_NAN \
                            ) \
                           ) : ( \
                            (((x) & fp_med) == (0)) ? ( \
                             (((x) & fp_mfd) == (0)) ? ( \
                              FP_ZERO \
                             ) : ( \
                              FP_DENORMAL \
                             ) \
                            ) : ( \
                             FP_NORMAL \
                            ) \
                           ) \
                          ) : ( \
                           (((x) & fp_mel) == (fp_mel)) ? ( \
                            (((x) & fp_mjl) == (fp_mjl)) ? ( \
                             FP_UNSUPPORTED \
                            ) : ( \
                             (((x) & fp_mfl) == (fp_mfl)) ? ( \
                              FP_NAN \
                             ) : ( \
                              FP_INFINITY \
                             ) \
                            ) \
                           ) : ( \
                            (((x) & fp_mel) == (0)) ? ( \
                             (((x) & fp_mjl) == (fp_mjl)) ? ( \
                              FP_NORMAL \ // or actually, pseudo-denormal
                             ) : ( \
                              (((x) & fp_mfl) == (fp_mfl)) ? ( \
                               FP_DENORMAL \
                              ) : ( \
                               FP_ZERO \
                              ) \
                             ) \
                            ) : ( \
                             (((x) & fp_mjl) == (fp_mjl)) ? ( \
                              FP_NORMAL \
                             ) : ( \
                              FP_UNDEFINED \
                             ) \
                            ) \
                           ) \
                          ) \
                         ) \
                        )

#define isfinite( x )   ((sizeof(x) == sizeof(float)) ? ( \
                          (((x) & fp_mef) == (fp_mef)) ? ( \
                           0 \
                          ) : ( \
                           1 \
                          ) \
                         ) : (
                          (sizeof(x) == sizeof(double)) ? ( \
                           (((x) & fp_med) == (fp_med)) ? ( \
                            0 \
                           ) : ( \
                            1 \
                           ) \
                          ) : ( \
                           (((x) & fp_mel) == (fp_mel)) ? ( \
                            0 \
                           ) : ( \
                            (((x) & fp_mel) == (0)) ? ( \
                             (((x) & fp_mjl) == (fp_mjl)) ? ( \
                              1 \
                             ) : ( \
                              0 \
                             ) \
                            ) : ( \
                             (((x) & fp_mjl) == (fp_mjl)) ? ( \
                              1 \
                             ) : ( \
                              0 \
                             ) \
                            ) \
                           ) \
                          ) \
                         ) \
                        )

#define isinf( x )      ((sizeof(x) == sizeof(float)) ? ( \
                          (((x) & fp_mef) == (fp_mef)) ? ( \
                           (((x) & fp_mff) == (0)) ? ( \
                            1 \
                           ) : ( \
                            0 \
                           ) \
                          ) : ( \
                           0 \
                          ) \
                         ) : ((sizeof(x) == sizeof(double)) ? ( \
                           (((x) & fp_med) == (fp_med)) ? ( \
                            (((x) & fp_mfd) == (0)) ? ( \
                             1 \
                            ) : ( \
                             0 \
                            ) \
                           ) : ( \
                            0 \
                           ) \
                          ) : ( \
                           (((x) & fp_mel) == (fp_mel)) ? ( \
                            (((x) & fp_mjl) == (0)) ? ( \
                             (((x) & fp_mfl) == (fp_mfl)) ? ( \
                              0 \
                             ) : ( \
                              1 \
                             ) \
                            ) : ( \
                             0 \
                            ) \
                           ) : ( \
                            0 \
                           ) \
                          ) \
                         ) \
                        )

#define isnan( x )      ((sizeof(x) == sizeof(float)) ? ( \
                          (((x) & fp_mef) == (fp_mef)) ? ( \
                           (((x) & fp_mff) == (0)) ? ( \
                            0 \
                           ) : ( \
                            1 \
                           ) \
                          ) : ( \
                           0 \
                          ) \
                         ) : ((sizeof(x) == sizeof(double)) ? ( \
                           (((x) & fp_med) == (fp_med)) ? ( \
                            (((x) & fp_mfd) == (0)) ? ( \
                             0 \
                            ) : ( \
                             1 \
                            ) \
                           ) : ( \
                            0 \
                           ) \
                          ) : ( \
                           (((x) & fp_mel) == (fp_mel)) ? ( \
                            (((x) & fp_mjl) == (0)) ? ( \
                             (((x) & fp_mfl) == (fp_mfl)) ? ( \
                              1 \
                             ) : ( \
                              0 \
                             ) \
                            ) : ( \
                             0 \
                            ) \
                           ) : ( \
                            0 \
                           ) \
                          ) \
                         ) \
                        )

#define isnormal( x )   ((sizeof(x) == sizeof(float)) ? ( \
                          (((x) & fp_mef) == (fp_mef)) ? ( \
                           0 \
                          ) : ( \
                           (((x) & fp_mef) == (0)) ? ( \
                            0 \
                           ) : ( \
                            1 \
                           ) \
                          ) \
                         ) : ((sizeof(x) == sizeof(double)) ? ( \
                           (((x) & fp_med) == (fp_med)) ? ( \
                            0 \
                           ) : ( \
                            (((x) & fp_med) == (0)) ? ( \
                             0 \
                            ) : ( \
                             1 \
                            ) \
                           ) \
                          ) : ( \
                           (((x) & fp_mel) == (fp_mel)) ? ( \
                            0 \
                           ) : ( \
                            (((x) & fp_mel) == (0)) ? ( \
                             (((x) & fp_mjl) == (fp_mjl)) ? ( \
                              1 \
                             ) : ( \
                              0 \
                             ) \
                            ) : ( \
                             (((x) & fp_mjl) == (fp_mjl)) ? ( \
                              1 \
                             ) : ( \
                              0 \
                             ) \
                            ) \
                           ) \
                          ) \
                         ) \
                        )

#define signbit( x )    ((sizeof(x) == sizeof(float)) ? ( \
                          (((x) & 0x80000000) == (0)) ? ( \
                           0 \
                          ) : ( \
                           1 \
                          ) \
                         ) : ((sizeof(x) == sizeof(double)) ? ( \
                           (((x) & 0x8000000000000000) == (0)) ? ( \
                            0 \
                           ) : ( \
                            1 \
                           ) \
                          ) : ( \
                           (((x) & 0x80000000000000000000) == (0)) ? ( \
                            0 \
                           ) : ( \
                            1 \
                           ) \
                          ) \
                         ) \
                        )

/* ----------------------------------------------------------------------------
 * FUNCTIONS
 * --------------------------------------------------------------------------*/

/** These functions return the magnitude of x.
 *  @param x The value to find the absolute value of.
 *  @return The absolute value of x.
 *  @see fabsl()
 *  @see fabsf()
 */
double      fabs( double       x );

/** These functions return the magnitude of x.
 *  @param x The value to find the absolute value of.
 *  @return The absolute value of x.
 *  @see fabsl()
 *  @see fabs()
 */
float       fabsf( float       x );

/** These functions return the magnitude of x.
 *  @param x The value to find the absolute value of.
 *  @return The absolute value of x.
 *  @see fabs()
 *  @see fabsf()
 */
long double fabsl( long double x );

/** These functions compute the sine of x (measured in radians).
 *  @param x The value to compute the sine of.
 *  @return The sine of x.
 *  @see sinf()
 *  @see sinl()
 *  @see cos()
 *  @see tan()
 *  @see sinh()
 *  @see asin()
 */
double      sin( double       x );

/** These functions compute the sine of x (measured in radians).
 *  @param x The value to compute the sine of.
 *  @return The sine of x.
 *  @see sin()
 *  @see sinl()
 *  @see cosf()
 *  @see tanf()
 *  @see sinhf()
 *  @see asinf()
 */
float       sinf( float       x );

/** These functions compute the sine of x (measured in radians).
 *  @param x The value to compute the sine of.
 *  @return The sine of x.
 *  @see sinf()
 *  @see sin()
 *  @see cosl()
 *  @see tanl()
 *  @see sinhl()
 *  @see asinl()
 */
long double sinl( long double x );

/** These functions compute the hyperbolic sine of x (measured in radians).
 *  @param x The value to compute the hyperbolic sine of.
 *  @return The hyperbolic sine of x.
 *  @see sinhf()
 *  @see sinhl()
 *  @see sin()
 *  @see cosh()
 *  @see tanh()
 *  @see asinh()
 */
double      sinh( double       x );

/** These functions compute the hyperbolic sine of x (measured in radians).
 *  @param x The value to compute the hyperbolic sine of.
 *  @return The hyperbolic sine of x.
 *  @see sinh()
 *  @see sinhl()
 *  @see sinf()
 *  @see coshf()
 *  @see tanhf()
 *  @see asinhf()
 */
float       sinhf( float       x );

/** These functions compute the hyperbolic sine of x (measured in radians).
 *  @param x The value to compute the hyperbolic sine of.
 *  @return The hyperbolic sine of x.
 *  @see sinh()
 *  @see sinhf()
 *  @see sinl()
 *  @see coshl()
 *  @see tanhl()
 *  @see asinhl()
 */
long double sinhl( long double x );

/** These functions compute the arcsine of x (measured in radians).
 *  @param x The value to compute the arcsine of.
 *  @return The arcsine of x.
 *  @see asinf()
 *  @see asinl()
 *  @see sin()
 *  @see acos()
 *  @see atan()
 *  @see asinh()
 */
double      asin( double       x );

/** These functions compute the arcsine of x (measured in radians).
 *  @param x The value to compute the arcsine of.
 *  @return The arcsine of x.
 *  @see asin()
 *  @see asinl()
 *  @see sinf()
 *  @see acosf()
 *  @see atanf()
 *  @see asinhf()
 */
float       asinf( float       x );

/** These functions compute the arcsine of x (measured in radians).
 *  @param x The value to compute the arcsine of.
 *  @return The arcsine of x.
 *  @see asin()
 *  @see asinf()
 *  @see sinl()
 *  @see acosl()
 *  @see atanl()
 *  @see asinhl()
 */
long double asinl( long double x );

/** These functions compute the hyperbolic arcsine of x (measured in radians).
 *  @param x The value to compute the hyperbolic arcsine of.
 *  @return The hyperbolic arcsine of x.
 *  @see asinhf()
 *  @see asinhl()
 *  @see asin()
 *  @see acosh()
 *  @see atanh()
 *  @see sinh()
 */
double      asinh( double       x );

/** These functions compute the hyperbolic arcsine of x (measured in radians).
 *  @param x The value to compute the hyperbolic arcsine of.
 *  @return The hyperbolic arcsine of x.
 *  @see asinh()
 *  @see asinhl()
 *  @see asinf()
 *  @see acoshf()
 *  @see atanhf()
 *  @see sinhf()
 */
float       asinhf( float       x );

/** These functions compute the hyperbolic arcsine of x (measured in radians).
 *  @param x The value to compute the hyperbolic arcsine of.
 *  @return The hyperbolic arcsine of x.
 *  @see asinh()
 *  @see asinhf()
 *  @see asinl()
 *  @see acoshl()
 *  @see atanhl()
 *  @see sinhl()
 */
long double asinhl( long double x );

/** These functions compute the cosine of x (measured in radians).
 *  @param x The value to compute the cosine of.
 *  @return The cosine of x.
 *  @see cosf()
 *  @see cosl()
 *  @see sin()
 *  @see cosh()
 *  @see tan()
 *  @see acos()
 */
double      cos( double       x );

/** These functions compute the cosine of x (measured in radians).
 *  @param x The value to compute the cosine of.
 *  @return The cosine of x.
 *  @see cos()
 *  @see cosl()
 *  @see sinf()
 *  @see coshf()
 *  @see tanf()
 *  @see acosf()
 */
float       cosf( float       x );

/** These functions compute the cosine of x (measured in radians).
 *  @param x The value to compute the cosine of.
 *  @return The cosine of x.
 *  @see cos()
 *  @see cosf()
 *  @see sinl()
 *  @see coshl()
 *  @see tanl()
 *  @see acosl()
 */
long double cosl( long double x );

/** These functions compute the hyperbolic cosine of x (measured in radians).
 *  @param x The value to compute the hyperbolic cosine of.
 *  @return The hyperbolic cosine of x.
 *  @see coshf()
 *  @see coshl()
 *  @see sinh()
 *  @see cos()
 *  @see tanh()
 *  @see acosh()
 */
double      cosh( double       x );

/** These functions compute the hyperbolic cosine of x (measured in radians).
 *  @param x The value to compute the hyperbolic cosine of.
 *  @return The hyperbolic cosine of x.
 *  @see cosh()
 *  @see coshl()
 *  @see sinhf()
 *  @see cosf()
 *  @see tanhf()
 *  @see acoshf()
 */
float       coshf( float       x );

/** These functions compute the hyperbolic cosine of x (measured in radians).
 *  @param x The value to compute the hyperbolic cosine of.
 *  @return The hyperbolic cosine of x.
 *  @see cosh()
 *  @see coshf()
 *  @see sinhl()
 *  @see cosl()
 *  @see tanhl()
 *  @see acoshl()
 */
long double coshl( long double x );

/** These functions compute the arccosine of x (measured in radians).
 *  @param x The value to compute the arccosine of.
 *  @return The arccosine of x.
 *  @see acosf()
 *  @see acosl()
 *  @see asin()
 *  @see cos()
 *  @see atan()
 *  @see acosh()
 */
double      acos( double       x );

/** These functions compute the arccosine of x (measured in radians).
 *  @param x The value to compute the arccosine of.
 *  @return The arccosine of x.
 *  @see acos()
 *  @see acosl()
 *  @see asinf()
 *  @see cosf()
 *  @see atanf()
 *  @see acoshf()
 */
float       acosf( float       x );

/** These functions compute the arccosine of x (measured in radians).
 *  @param x The value to compute the arccosine of.
 *  @return The arccosine of x.
 *  @see acos()
 *  @see acosf()
 *  @see asinl()
 *  @see cosl()
 *  @see atanl()
 *  @see acoshl()
 */
long double acosl( long double x );

/** These functions compute the hyperbolic arccosine of x (measured in radians).
 *  @param x The value to compute the hyperbolic arccosine of.
 *  @return The hyperbolic arccosine of x.
 *  @see acoshf()
 *  @see acoshl()
 *  @see asinh()
 *  @see cosh()
 *  @see atanh()
 *  @see acos()
 */
double      acosh( double       x );

/** These functions compute the hyperbolic arccosine of x (measured in radians).
 *  @param x The value to compute the hyperbolic arccosine of.
 *  @return The hyperbolic arccosine of x.
 *  @see acosh()
 *  @see acoshl()
 *  @see asinhf()
 *  @see coshf()
 *  @see atanhf()
 *  @see acosf()
 */
float       acoshf( float       x );

/** These functions compute the hyperbolic arccosine of x (measured in radians).
 *  @param x The value to compute the hyperbolic arccosine of.
 *  @return The hyperbolic arccosine of x.
 *  @see acosh()
 *  @see acoshf()
 *  @see asinhl()
 *  @see coshl()
 *  @see atanhl()
 *  @see acosl()
 */
long double acoshl( long double x );

/** These functions compute the tangent of x (measured in radians).
 *  @param x The value to compute the tangent of.
 *  @return The tangent of x.
 *  @see tanf()
 *  @see tanl()
 *  @see sin()
 *  @see cos()
 *  @see tanh()
 *  @see atan()
 */
double      tan( double       x );

/** These functions compute the tangent of x (measured in radians).
 *  @param x The value to compute the tangent of.
 *  @return The tangent of x.
 *  @see tan()
 *  @see tanl()
 *  @see sinf()
 *  @see cosf()
 *  @see tanhf()
 *  @see atanf()
 */
float       tanf( float       x );

/** These functions compute the tangent of x (measured in radians).
 *  @param x The value to compute the tangent of.
 *  @return The tangent of x.
 *  @see tan()
 *  @see tanf()
 *  @see sinl()
 *  @see cosl()
 *  @see tanhl()
 *  @see atanl()
 */
long double tanl( long double x );

/** These functions compute the hyperbolic tangent of x (measured in radians).
 *  @param x The value to compute the hyperbolic tangent of.
 *  @return The hyperbolic tangent of x.
 *  @see tanhf()
 *  @see tanhl()
 *  @see sinh()
 *  @see cosh()
 *  @see tan()
 *  @see atanh()
 */
double      tanh( double       x );

/** These functions compute the hyperbolic tangent of x (measured in radians).
 *  @param x The value to compute the hyperbolic tangent of.
 *  @return The hyperbolic tangent of x.
 *  @see tanh()
 *  @see tanhl()
 *  @see sinhf()
 *  @see coshf()
 *  @see tanf()
 *  @see atanhf()
 */
float       tanhf( float       x );

/** These functions compute the hyperbolic tangent of x (measured in radians).
 *  @param x The value to compute the hyperbolic tangent of.
 *  @return The hyperbolic tangent of x.
 *  @see tanh()
 *  @see tanhf()
 *  @see sinhl()
 *  @see coshl()
 *  @see tanl()
 *  @see atanhl()
 */
long double tanhl( long double x );

/** These functions compute the arctangent of x (measured in radians).
 *  @param x The value to compute the arctangent of.
 *  @return The arctangent of x.
 *  @see atanf()
 *  @see atanl()
 *  @see atan2()
 *  @see asin()
 *  @see acos()
 *  @see tan()
 *  @see atanh()
 */
double      atan( double       x );

/** These functions compute the arctangent of x (measured in radians).
 *  @param x The value to compute the arctangent of.
 *  @return The arctangent of x.
 *  @see atan()
 *  @see atanl()
 *  @see atan2f()
 *  @see asinf()
 *  @see acosf()
 *  @see tanf()
 *  @see atanhf()
 */
float       atanf( float       x );

/** These functions compute the arctangent of x (measured in radians).
 *  @param x The value to compute the arctangent of.
 *  @return The arctangent of x.
 *  @see atan()
 *  @see atanf()
 *  @see atan2l()
 *  @see asinl()
 *  @see acosl()
 *  @see tanl()
 *  @see atanhl()
 */
long double atanl( long double x );

/** These functions compute the hyperbolic arctangent of x (measured in radians).
 *  @param x The value to compute the hyperbolic arctangent of.
 *  @return The hyperbolic arctangent of x.
 *  @see atanhf()
 *  @see atanhl()
 *  @see asinh()
 *  @see acosh()
 *  @see tanh()
 *  @see atan()
 */
double      atanh( double       x );

/** These functions compute the hyperbolic arctangent of x (measured in radians).
 *  @param x The value to compute the hyperbolic arctangent of.
 *  @return The hyperbolic arctangent of x.
 *  @see atanh()
 *  @see atanhl()
 *  @see asinhf()
 *  @see acoshf()
 *  @see tanhf()
 *  @see atanf()
 */
float       atanhf( float       x );

/** These functions compute the hyperbolic arctangent of x (measured in radians).
 *  @param x The value to compute the hyperbolic arctangent of.
 *  @return The hyperbolic arctangent of x.
 *  @see atanh()
 *  @see atanhf()
 *  @see asinhl()
 *  @see acoshl()
 *  @see tanhl()
 *  @see atanl()
 */
long double atanhl( long double x );

/** These functions compute the hyperbolic arctangent of x / y (measured in radians).
 *  They return their answer between pi and -pi.
 *  @param y The first side of the triangle.
 *  @param x The second side of the triangle.
 *  @return The angle between the first and the second side.
 *  @see atan2f()
 *  @see atan2l()
 *  @see atan()
 *  @see asin()
 *  @see acos()
 *  @see atanh()
 *  @see tanh()
 */
double      atan2( double       y, double      x );

/** These functions compute the hyperbolic arctangent of x / y (measured in radians).
 *  They return their answer between pi and -pi.
 *  @param y The first side of the triangle.
 *  @param x The second side of the triangle.
 *  @return The angle between the first and the second side.
 *  @see atan2f()
 *  @see atan2l()
 *  @see atanf()
 *  @see asinf()
 *  @see acosf()
 *  @see atanhf()
 *  @see tanhf()
 */
float       atan2f( float       y, float       x );

/** These functions compute the hyperbolic arctangent of x / y (measured in radians).
 *  They return their answer between pi and -pi.
 *  @param y The first side of the triangle.
 *  @param x The second side of the triangle.
 *  @return The angle between the first and the second side.
 *  @see atan2f()
 *  @see atan2l()
 *  @see atanl()
 *  @see asinl()
 *  @see acosl()
 *  @see atanhl()
 *  @see tanhl()
 */
long double atan2l( long double y, long double x );

/** These functions compute the hypotenuse of a straight triangle.
 *  @param x The length of one side of the triangle.
 *  @param y The length of the other side of the triangle.
 *  @return The length of the hypotenuse, according to h = sqrt(x*x+y*y).
 *  @see hypotf()
 *  @see hypotl()
 */
double      hypot( double       x, double      y );

/** These functions compute the hypotenuse of a straight triangle.
 *  @param x The length of one side of the triangle.
 *  @param y The length of the other side of the triangle.
 *  @return The length of the hypotenuse, according to h = sqrt(x*x+y*y).
 *  @see hypot()
 *  @see hypotl()
 */
float       hypotf( float       x, float       y );

/** These functions compute the hypotenuse of a straight triangle.
 *  @param x The length of one side of the triangle.
 *  @param y The length of the other side of the triangle.
 *  @return The length of the hypotenuse, according to h = sqrt(x*x+y*y).
 *  @see hypot()
 *  @see hypotf()
 */
long double hypotl( long double x, long double y );

/** These functions compute x raised to the power y.
 *  @param x The base of the power.
 *  @param y The exponent of the power.
 *  @return The base raised to the power of the exponent.
 *  @see powf()
 *  @see powl()
 */
double      pow( double       x, double      y );

/** These functions compute x raised to the power y.
 *  @param x The base of the power.
 *  @param y The exponent of the power.
 *  @return The base raised to the power of the exponent.
 *  @see pow()
 *  @see powl()
 */
float       powf( float       x, float       y );

/** These functions compute x raised to the power y.
 *  @param x The base of the power.
 *  @pa am y The exponent of the power.
 *  @return The base raised to the power of the exponent.
 *  @see pow()
 *  @see powf()
 */
long double powl( long double x, long double y );

/** These functions compute the square root of x.
 *  @param x The value to take the square root of.
 *  @return The square root of x.
 *  @see sqrtf()
 *  @see sqrtl()
 */
double      sqrt( double       x );

/** These functions compute the square root of x.
 *  @param x The value to take the square root of.
 *  @return The square root of x.
 *  @see sqrt()
 *  @see sqrtl()
 */
float       sqrtf( float       x );

/** These functions compute the square root of x.
 *  @param x The value to take the square root of.
 *  @return The square root of x.
 *  @see sqrt()
 *  @see sqrtf()
 */
long double sqrtl( long double x );

/* TODO */
double      cbrt( double       x );
float       cbrtf( float       x );
long double cbrtl( long double x );

/* TODO */
double      exp( double       x );
float       expf( float       x );
long double expl( long double x );

/* TODO */
double      exp2( double       x );
float       exp2f( float       x );
long double exp2l( long double x );

/* TODO */
double      expm1( double       x );
float       expm1f( float       x );
long double expm1l( long double x );

/* TODO */
double      frexp( double       x, int * exp );
float       frexpf( float       x, int * exp );
long double frexpl( long double x, int * exp );

/* TODO */
double      ldexp( double       x, int exp );
float       ldexpf( float       x, int exp );
long double ldexpl( long double x, int exp );

/** These functions compute the logarithm (base e) of x.
 *  @param x The value to take the logarithm of.
 *  @return The logarithm of x.
 *  @see logf()
 *  @see logl()
 *  @todo is this really the natural logarithm? wouldn't it be ln()?
 */
double      log( double       x );

/** These functions compute the logarithm (base e) of x.
 *  @param x The value to take the logarithm of.
 *  @return The logarithm of x.
 *  @see log()
 *  @see logl()
 *  @todo is this really the natural logarithm? wouldn't it be ln()?
 */
float       logf( float       x );

/** These functions compute the logarithm (base e) of x.
 *  @param x The value to take the logarithm of.
 *  @return The logarithm of x.
 *  @see log()
 *  @see logf()
 *  @todo is this really the natural logarithm? wouldn't it be ln()?
 */
long double logl( long double x );

/** These functions compute the logarithm (base 10) of x.
 *  @param x The value to take the logarithm of.
 *  @return The logarithm of x.
 *  @see log10f()
 *  @see log10l()
 */
double      log10( double       x );

/** These functions compute the logarithm (base 10) of x.
 *  @param x The value to take the logarithm of.
 *  @return The logarithm of x.
 *  @see log10()
 *  @see log10l()
 */
float       log10f( float       x );

/** These functions compute the logarithm (base 10) of x.
 *  @param x The value to take the logarithm of.
 *  @return The logarithm of x.
 *  @see log10()
 *  @see log10f()
 */
long double log10l( long double x );

/** These functions compute the logarithm (base 2) of x.
 *  @param x The value to take the logarithm of.
 *  @return The logarithm of x.
 *  @see log2f()
 *  @see log2l()
 */
double      log2( double       x );

/** These functions compute the logarithm (base 2) of x.
 *  @param x The value to take the logarithm of.
 *  @return The logarithm of x.
 *  @see log2()
 *  @see log2l()
 */
float       log2f( float       x );

/** These functions compute the logarithm (base 2) of x.
 *  @param x The value to take the logarithm of.
 *  @return The logarithm of x.
 *  @see log2()
 *  @see log2f()
 */
long double log2l( long double x );

/* TODO */
double      logb( double       x );
float       logbf( float       x );
long double logbl( long double x );

/* TODO */
int ilogb( double       x );
int ilogbf( float       x );
int ilogbl( long double x );

/* TODO */
double      log1p( double       x );
float       log1pf( float       x );
long double log1pl( long double x );

/** These functions increase x to the next whole number.
 *  @param x The value to increase.
 *  @return The next whole number after x.
 *  @see ceilf()
 *  @see ceill()
 */
double      ceil( double       x );

/** These functions increase x to the next whole number.
 *  @param x The value to increase.
 *  @return The next whole number after x.
 *  @see ceil()
 *  @see ceill()
 */
float       ceilf( float       x );

/** These functions increase x to the next whole number.
 *  @param x The value to increase.
 *  @return The next whole number after x.
 *  @see ceil()
 *  @see ceilf()
 */
long double ceill( long double x );

/** These functions decrease x to the previous whole number.
 *  @param x The value to decrease.
 *  @return The previous whole number before x.
 *  @see floorf()
 *  @see floorl()
 */
double      floor( double       x );

/** These functions decrease x to the previous whole number.
 *  @param x The value to decrease.
 *  @return The previous whole number before x.
 *  @see floor()
 *  @see floorl()
 */
float       floorf( float       x );

/** These functions decrease x to the previous whole number.
 *  @param x The value to decrease.
 *  @return The previous whole number before x.
 *  @see floor()
 *  @see floorf()
 */
long double floorl( long double x );

/** These functions compute the modulus of x and y.
 *  @param x The value to take the modulus of.
 *  @param y The modulus.
 *  @return The value of x modulus y.
 *  @see fmodf()
 *  @see fmodl()
 */
double      fmod( double       x, double      y );

/** These functions compute the modulus of x and y.
 *  @param x The value to take the modulus of.
 *  @param y The modulus.
 *  @return The value of x modulus y.
 *  @see fmod()
 *  @see fmodl()
 */
float       fmodf( float       x, float       y );

/** These functions compute the modulus of x and y.
 *  @param x The value to take the modulus of.
 *  @param y The modulus.
 *  @return The value of x modulus y.
 *  @see fmod()
 *  @see fmodf()
 */
long double fmodl( long double x, long double y );

/* TODO */
double      modf( double       x, double *      integer );
float       modff( float       x, float *       integer );
long double modfl( long double x, long double * integer );

/** These functions return x with the sign of y.
 *  @param x The value to set the sign of.
 *  @param y The value from which to read the sign.
 *  @return The magnitude of x with the sign of y.
 *  @see copysignf()
 *  @see copysignl()
 */
double      copysign( double       x, double      y );

/** These functions return x with the sign of y.
 *  @param x The value to set the sign of.
 *  @param y The value from which to read the sign.
 *  @return The magnitude of x with the sign of y.
 *  @see copysign()
 *  @see copysignl()
 */
float       copysignf( float       x, float       y );

/** These functions return x with the sign of y.
 *  @param x The value to set the sign of.
 *  @param y The value from which to read the sign.
 *  @return The magnitude of x with the sign of y.
 *  @see copysign()
 *  @see copysignf()
 */
long double copysignl( long double x, long double y );

/* TODO */
double      erf( double       x );
float       erff( float       x );
long double erfl( long double x );

/* TODO */
double      erfc( double       x );
float       erfcf( float       x );
long double erfcl( long double x );

/* TODO */
double      fdim( double       x, double      y );
float       fdimf( float       x, float       y );
long double fdiml( long double x, long double y );

/* TODO */
double      fma( double       x, double      y, double      z );
float       fmaf( float       x, float       y, float       z );
long double fmal( long double x, long double y, long double z );

/** These functions return the largest of the parameters.
 *  @param x The first candidate.
 *  @param y The second candidate.
 *  @return The largest of x and y.
 *  @see fmaxf()
 *  @see fmaxl()
 */
double      fmax( double       x, double      y );

/** These functions return the largest of the parameters.
 *  @param x The first candidate.
 *  @param y The second candidate.
 *  @return The largest of x and y.
 *  @see fmax()
 *  @see fmaxl()
 */
float       fmaxf( float       x, float       y );

/** These functions return the largest of the parameters.
 *  @param x The first candidate.
 *  @param y The second candidate.
 *  @return The largest of x and y.
 *  @see fmax()
 *  @see fmaxf()
 */
long double fmaxl( long double x, long double y );

/** These functions return the smallest of the parameters.
 *  @param x The first candidate.
 *  @param y The second candidate.
 *  @return The smallest of x and y.
 *  @see fminf()
 *  @see fminl()
 */
double      fmin( double       x, double      y );

/** These functions return the smallest of the parameters.
 *  @param x The first candidate.
 *  @param y The second candidate.
 *  @return The smallest of x and y.
 *  @see fmin()
 *  @see fminl()
 */
float       fminf( float       x, float       y );

/** These functions return the smallest of the parameters.
 *  @param x The first candidate.
 *  @param y The second candidate.
 *  @return The smallest of x and y.
 *  @see fmin()
 *  @see fminf()
 */
long double fminl( long double x, long double y );

/* TODO */
long long llrint( double       x );
long long llrintf( float       x );
long long llrintl( long double x );
long lrint( double       x );
long lrintf( float       x );
long lrintl( long double x );
double      rint( double       x );
float       rintf( float       x );
long double rintl( long double x );

/* TODO - These functions return their parameter correctly rounded according
 * to the current rounding settings.
 */
long long llround( double       x );
long long llroundf( float       x );
long long llroundl( long double x );
long lround( double       x );
long lroundf( float       x );
long lroundl( long double x );
double      round( double       x );
float       roundf( float       x );
long double roundl( long double x );

/* TODO - These functions return their parameter with its decimal part
 * truncated.
 */
double      trunc( double       x );
float       truncf( float       x );
long double truncl( long double x );

double      nearbyint( double       x );
float       nearbyintf( float       x );
long double nearbyintl( long double x );

double      nextafter( double       x, double      y );
float       nextafterf( float       x, float       y );
long double nextafterl( long double x, long double y );

/* TODO */
double      nexttoward( double       x, long double y );
float       nexttowardf( float       x, long double y );
long double nexttowardl( long double x, long double y );

/* TODO - These functions divide parameter x by parameter y and return the
 * remainder.
 */
double      remainder( double       x, double      y );
float       remainderf( float       x, float       y );
long double remainderl( long double x, long double y );

/* TODO */
double      remquo( double       x, double      y, int * pquo );
float       remquof( float       x, float       y, int * pquo );
long double remquol( long double x, long double y, int * pquo );

/* TODO */
double      scalbn( double       x, int ex );
float       scalbnf( float       x, int ex );
long double scalbnl( long double x, int ex );

/* TODO */
double      scalbln( double       x, long ex );
float       scalblnf( float       x, long ex );
long double scalblnl( long double x, long ex );

/* TODO */
double      lgamma( double       x );
float       lgammaf( float       x );
long double lgammal( long double x );

/* TODO */
double      tgamma( double       x );
float       tgammaf( float       x );
long double tgammal( long double x );

/* TODO */
double      nan( const char  *str );
float       nanf( const char *str );
long double nanl( const char *str );

#endif /* _MATH_H */
