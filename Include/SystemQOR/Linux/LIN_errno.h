//LIN_errno.h

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

//Linux overrides for errno

#ifndef SYSTEMQOR_LIN_ERRNO_H_3
#define SYSTEMQOR_LIN_ERRNO_H_3

#include "SystemQOR/Linux/types/errno_types.h"
//#include "SystemQOR/Posix/Baseregex.h"

//--------------------------------------------------------------------------------
namespace nsLinux
{
	//--------------------------------------------------------------------------------
	class __QOR_INTERFACE( __QSYS ) Cerrno //: public nsBaseCRT::Cregex
	{
	public:

		Cerrno(){}
		~Cerrno(){}

#ifdef __GNUC__
		__attribute__((const))
#endif
		virtual int* __errno_location( void );

		virtual void warn(const char *, ...);
		virtual void vwarn(const char *, va_list);
		virtual void warnx(const char *, ...);
		virtual void vwarnx(const char *, va_list);

		_Noreturn virtual void err(int, const char *, ...);
		_Noreturn virtual void verr(int, const char *, va_list);
		_Noreturn virtual void errx(int, const char *, ...);
		_Noreturn virtual void verrx(int, const char *, va_list);

	private:

		Cerrno( const Cerrno& );
		Cerrno& operator = ( const Cerrno& );

	};

}//nsLinux

#endif//SYSTEMQOR_LIN_ERRNO_H_3
