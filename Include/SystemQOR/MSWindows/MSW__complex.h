//MSW_complex.h

// Copyright Querysoft Limited 2013
//
// Permission is hereby granted, free of charge, to any person or organization
// obtaining a copy of the software and accompanying documentation covered by
// this license (the "Software") to use, reproduce, display, distribute,
// execute, and transmit the Software, and to prepare derivative works of the
// Software, and to permit third-parties to whom the Software is furnished to
// do so, all subject to the following:
// 
// The copyright notices in the Software and this entire statement, including
// the above license grant, this restriction and the following disclaimer,
// must be included in all copies of the Software, in whole or in part, and
// all derivative works of the Software, unless such copies or derivative
// works are solely in the form of machine-executable object code generated by
// a source language processor.
// 
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE, TITLE AND NON-INFRINGEMENT. IN NO EVENT
// SHALL THE COPYRIGHT HOLDERS OR ANYONE DISTRIBUTING THE SOFTWARE BE LIABLE
// FOR ANY DAMAGES OR OTHER LIABILITY, WHETHER IN CONTRACT, TORT OR OTHERWISE,
// ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
// DEALINGS IN THE SOFTWARE.

//MSWindows overrides for complex

#ifndef SYSTEMQOR_MSW_COMPLEX_H_1
#define SYSTEMQOR_MSW_COMPLEX_H_1

#include "SystemQOR/Posix/Basecomplex.h"

//--------------------------------------------------------------------------------
namespace nsWin32
{
	//--------------------------------------------------------------------------------
	class __QOR_INTERFACE( __QSYS ) Ccomplex : public nsBaseCRT::Ccomplex
	{
	public:

		Ccomplex();
		virtual ~Ccomplex();

        virtual double_complex cacos( double_complex z );
        virtual float_complex cacosf( float_complex z );
        virtual long_double_complex cacosl( long_double_complex z );
        virtual double_complex casin( double_complex z );
        virtual float_complex casinf(float_complex z);
        virtual long_double_complex casinl(long_double_complex z);
        virtual double_complex catan( double_complex z );
        virtual float_complex catanf( float_complex z );
        virtual long_double_complex catanl( long_double_complex z );
        virtual double_complex ccos( double_complex z );
        virtual float_complex ccosf( float_complex z );
        virtual long_double_complex ccosl( long_double_complex z );
        virtual double_complex csin( double_complex z );
        virtual float_complex csinf(float_complex z);
        virtual long_double_complex csinl(long_double_complex z);
        virtual double_complex ctan(double_complex z);
        virtual float_complex ctanf(float_complex z);
		virtual long_double_complex ctanl(long_double_complex z);
        virtual double_complex cacosh(double_complex z);
        virtual float_complex cacoshf( float_complex z );
        virtual long_double_complex cacoshl( long_double_complex z );
        virtual double_complex casinh( double_complex z );
        virtual float_complex casinhf( float_complex z );
        virtual long_double_complex casinhl( long_double_complex z );
        virtual double_complex catanh(double_complex z);
        virtual float_complex catanhf(float_complex z);
        virtual long_double_complex catanhl(long_double_complex z);
        virtual double_complex ccosh(double_complex z);
        virtual float_complex ccoshf( float_complex z );
        virtual long_double_complex ccoshl( long_double_complex z );
        virtual double_complex csinh( double_complex z );
        virtual float_complex csinhf(float_complex z);
        virtual long_double_complex csinhl( long_double_complex z );
        virtual double_complex ctanh( double_complex z );
        virtual float_complex ctanhf( float_complex z );
        virtual long_double_complex ctanhl(long_double_complex z);
        virtual double_complex cexp(double_complex z);
        virtual float_complex cexpf(float_complex z);
        virtual long_double_complex cexpl(long_double_complex z);
        virtual double_complex clog(double_complex z);
        virtual float_complex clogf(float_complex z);
        virtual long_double_complex clogl(long_double_complex z);
        virtual double cabs( double_complex z );
        virtual float cabsf(float_complex z);
        virtual long double cabsl(long_double_complex z);
        virtual double_complex cpow( double_complex x, double_complex y );
        virtual float_complex cpowf(float_complex x, float_complex y);
        virtual long_double_complex cpowl(long_double_complex x, long_double_complex y);
        virtual double_complex csqrt( double_complex z );
        virtual float_complex csqrtf( float_complex z );
        virtual long_double_complex csqrtl( long_double_complex z );
        virtual double carg( double_complex z );
        virtual float cargf(float_complex z);
        virtual long double cargl(long_double_complex z);
        virtual double cimag( double_complex z );
        virtual float cimagf( float_complex z );
        virtual long double cimagl( long_double_complex z );
        virtual double_complex conj(double_complex z);
        virtual float_complex conjf(float_complex z);
        virtual long_double_complex conjl(long_double_complex z);
        virtual double_complex cproj(double_complex z);
        virtual float_complex cprojf( float_complex z );
        virtual long_double_complex cprojl(long_double_complex z);
        virtual double creal( double_complex z );
        virtual float crealf( float_complex z );
        virtual long double creall( long_double_complex z );

	};

}//nsWin32


#endif//SYSTEMQOR_MSW_COMPLEX_H_1
