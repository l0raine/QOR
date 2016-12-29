
/* @(#)s_ilogb.c 5.1 93/09/24 */
/*
 * ====================================================
 * Copyright (C) 1993 by Sun Microsystems, Inc. All rights reserved.
 *
 * Developed at SunPro, a Sun Microsystems, Inc. business.
 * Permission to use, copy, modify, and distribute this
 * software is freely granted, provided that this notice
 * is preserved.
 * ====================================================
 */
//Conversion to float by Ian Lance Taylor, Cygnus Support, ian@cygnus.com.
/*
FUNCTION
       <<ilogb>>, <<ilogbf>>---get exponent of floating-point number
INDEX
    ilogb
INDEX
    ilogbf

ANSI_SYNOPSIS
    #include <math.h>
        int ilogb(double <[val]>);
        int ilogbf(float <[val]>);

TRAD_SYNOPSIS
    #include <math.h>
        int ilogb(<[val]>)
        double <[val]>;

        int ilogbf(<[val]>)
        float <[val]>;


DESCRIPTION

    All nonzero, normal numbers can be described as <[m]> *
    2**<[p]>.  <<ilogb>> and <<ilogbf>> examine the argument
    <[val]>, and return <[p]>.  The functions <<frexp>> and
    <<frexpf>> are similar to <<ilogb>> and <<ilogbf>>, but also
    return <[m]>.

RETURNS

<<ilogb>> and <<ilogbf>> return the power of two used to form the
floating-point argument.  If <[val]> is <<0>>, they return <<-
INT_MAX>> (<<INT_MAX>> is defined in limits.h).  If <[val]> is
infinite, or NaN, they return <<INT_MAX>>.

PORTABILITY
    Neither <<ilogb>> nor <<ilogbf>> is required by ANSI C or by
    the System V Interface Definition (Issue 2).  */

/* ilogb(double x)
 * return the binary exponent of non-zero x
 * ilogb(0) = 0x80000001
 * ilogb(inf/NaN) = 0x7fffffff (no signal is raised)
 */

#include "SystemQOR/Posix/Basemath.h"
#include <limits.h>

//------------------------------------------------------------------------------
namespace nsBaseCRT
{
    //------------------------------------------------------------------------------
    int Cmath::ilogbf( float x )
    {
        Cmp_signed__int32 hx,ix;

        get_float_word( hx, x );
        hx &= 0x7fffffff;
        if( uword_is_zero( hx ) )
        {
            return - INT_MAX;	// ilogb(0) = 0x80000001
        }

        if( uword_is_subnormal( hx ) )
        {
            for( ix = -126, hx <<= 8; hx > 0; hx <<= 1 )
            {
                ix -=1;
            }
            return ix;
        }
        else if( !uword_isfinite( hx ) )
        {
            return INT_MAX;
        }
        else
        {
            return ( hx >> 23 ) - 127;
        }
    }

#ifdef _DOUBLE_IS_32BITS

    //------------------------------------------------------------------------------
    int Cmath::ilogb( double x )
    {
        return ilogbf( (float)x );
    }

#else

    //------------------------------------------------------------------------------
    int Cmath::ilogb( double x )
    {
        Cmp_signed__int32 hx,lx,ix;

        extract_words( hx, lx, x );
        hx &= 0x7fffffff;
        if( hx < 0x00100000 )
        {
            if( ( hx | lx ) == 0 )
            {
                return - INT_MAX;	// ilogb(0) = 0x80000001
            }
            else			/* subnormal x */
            {
                if( hx == 0 )
                {
                    for( ix = -1043; lx > 0; lx <<= 1 )
                    {
                        ix -= 1;
                    }
                }
                else
                {
                    for( ix = -1022, hx <<= 11; hx > 0; hx <<= 1 )
                    {
                        ix -=1;
                    }
                }
                return ix;
            }
        }
        else if( hx < 0x7ff00000 )
        {
            return (hx >> 20 ) - 1023;
        }
        else
        {
            return INT_MAX;
        }
    }

#endif /* _DOUBLE_IS_32BITS */

};//namespace nsBaseCRT