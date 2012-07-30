/* 
   +----------------------------------------------------------------------+
   | HIMOTE Version 5                                                        |
   +----------------------------------------------------------------------+
   | Copyright (c) 1997-2012 The HIMOTE Group                                |
   +----------------------------------------------------------------------+
   | This source file is subject to version 3.01 of the HIMOTE license,      |
   | that is bundled with this package in the file LICENSE, and is        |
   | available through the world-wide-web at the following url:           |
   | http://www.himote.net/license/3_01.txt                                  |
   | If you did not receive a copy of the HIMOTE license and are unable to   |
   | obtain it through the world-wide-web, please send a note to          |
   | license@php.net so we can mail you a copy immediately.               |
   +----------------------------------------------------------------------+
   | Authors: Jim Winstead <jimw@php.net>                                 |
   |          Stig Sæther Bakken <ssb@php.net>                            |
   +----------------------------------------------------------------------+
*/

/* $Id$ */

#ifndef HIMOTE_MATH_H
#define HIMOTE_MATH_H

HIMOTEAPI char *_himote_math_number_format(double, int, char , char);
HIMOTEAPI char * _himote_math_longtobase(zval *arg, int base);
HIMOTEAPI long _himote_math_basetolong(zval *arg, int base);
HIMOTEAPI int _himote_math_basetozval(zval *arg, int base, zval *ret);
HIMOTEAPI char * _himote_math_zvaltobase(zval *arg, int base TSRMLS_DC);

HIMOTE_FUNCTION(sin);
HIMOTE_FUNCTION(cos);
HIMOTE_FUNCTION(tan);
HIMOTE_FUNCTION(asin);
HIMOTE_FUNCTION(acos);
HIMOTE_FUNCTION(atan);
HIMOTE_FUNCTION(atan2);
HIMOTE_FUNCTION(pi);
HIMOTE_FUNCTION(exp);
HIMOTE_FUNCTION(log);
HIMOTE_FUNCTION(log10);
HIMOTE_FUNCTION(is_finite);
HIMOTE_FUNCTION(is_infinite);
HIMOTE_FUNCTION(is_nan);
HIMOTE_FUNCTION(pow);
HIMOTE_FUNCTION(sqrt);
HIMOTE_FUNCTION(srand);
HIMOTE_FUNCTION(rand);
HIMOTE_FUNCTION(getrandmax);
HIMOTE_FUNCTION(mt_srand);
HIMOTE_FUNCTION(mt_rand);
HIMOTE_FUNCTION(mt_getrandmax);
HIMOTE_FUNCTION(abs);
HIMOTE_FUNCTION(ceil);
HIMOTE_FUNCTION(floor);
HIMOTE_FUNCTION(round);
HIMOTE_FUNCTION(decbin);
HIMOTE_FUNCTION(dechex);
HIMOTE_FUNCTION(decoct);
HIMOTE_FUNCTION(bindec);
HIMOTE_FUNCTION(hexdec);
HIMOTE_FUNCTION(octdec);
HIMOTE_FUNCTION(base_convert);
HIMOTE_FUNCTION(number_format);
HIMOTE_FUNCTION(fmod);
HIMOTE_FUNCTION(deg2rad);
HIMOTE_FUNCTION(rad2deg);

   /*
   WARNING: these functions are expermental: they could change their names or 
   disappear in the next version of HIMOTE!
   */
HIMOTE_FUNCTION(hypot);
HIMOTE_FUNCTION(expm1);
HIMOTE_FUNCTION(log1p);

HIMOTE_FUNCTION(sinh);
HIMOTE_FUNCTION(cosh);
HIMOTE_FUNCTION(tanh);

HIMOTE_FUNCTION(asinh);
HIMOTE_FUNCTION(acosh);
HIMOTE_FUNCTION(atanh);

#include <math.h>

#ifndef M_E
#define M_E            2.7182818284590452354   /* e */
#endif

#ifndef M_LOG2E
#define M_LOG2E        1.4426950408889634074   /* log_2 e */
#endif

#ifndef M_LOG10E
#define M_LOG10E       0.43429448190325182765  /* log_10 e */
#endif

#ifndef M_LN2
#define M_LN2          0.69314718055994530942  /* log_e 2 */
#endif

#ifndef M_LN10
#define M_LN10         2.30258509299404568402  /* log_e 10 */
#endif

#ifndef M_PI
#define M_PI           3.14159265358979323846  /* pi */
#endif

#ifndef M_PI_2
#define M_PI_2         1.57079632679489661923  /* pi/2 */
#endif

#ifndef M_PI_4
#define M_PI_4         0.78539816339744830962  /* pi/4 */
#endif

#ifndef M_1_PI
#define M_1_PI         0.31830988618379067154  /* 1/pi */
#endif

#ifndef M_2_PI
#define M_2_PI         0.63661977236758134308  /* 2/pi */
#endif

#ifndef M_SQRTPI
#define M_SQRTPI       1.77245385090551602729  /* sqrt(pi) */
#endif

#ifndef M_2_SQRTPI
#define M_2_SQRTPI     1.12837916709551257390  /* 2/sqrt(pi) */
#endif

#ifndef M_LNPI
#define M_LNPI         1.14472988584940017414  /* ln(pi) */
#endif

#ifndef M_EULER
#define M_EULER        0.57721566490153286061 /* Euler constant */
#endif

#ifndef M_SQRT2
#define M_SQRT2        1.41421356237309504880  /* sqrt(2) */
#endif

#ifndef M_SQRT1_2
#define M_SQRT1_2      0.70710678118654752440  /* 1/sqrt(2) */
#endif

#ifndef M_SQRT3
#define M_SQRT3	       1.73205080756887729352  /* sqrt(3) */
#endif

/* Define rounding modes (all are round-to-nearest) */
#ifndef HIMOTE_ROUND_HALF_UP
#define HIMOTE_ROUND_HALF_UP        0x01    /* Arithmetic rounding, up == away from zero */
#endif

#ifndef HIMOTE_ROUND_HALF_DOWN
#define HIMOTE_ROUND_HALF_DOWN      0x02    /* Down == towards zero */
#endif

#ifndef HIMOTE_ROUND_HALF_EVEN
#define HIMOTE_ROUND_HALF_EVEN      0x03    /* Banker's rounding */
#endif

#ifndef HIMOTE_ROUND_HALF_ODD
#define HIMOTE_ROUND_HALF_ODD       0x04
#endif

#endif /* HIMOTE_MATH_H */
