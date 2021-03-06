//MSVC.h

// Copyright Querysoft Limited 2015
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

//Set things common to MSVC compilers

#ifndef QCMP_MSVC_H_1
#define QCMP_MSVC_H_1

#pragma warning( disable : 4503 )					// warning: decorated name length exceeded. Turn off as it's a compiler limitation rather than anything to do with the code

//Macro to join things together
#define __QCMP_JOIN( X, Y ) __QCMP_JOINER( X, Y )
#define __QCMP_JOINER( X, Y ) __QCMP_JOINER2( X, Y )
#define __QCMP_JOINER2( X, Y ) X##Y

//MSVC supports an L"text" extension macro to embed wide character strings in ANSI source code
//Turn on the use of this by default if UNICODE is configured
#if ( __QOR_UNICODE )
#	define __QCMP_STRINGIZER(x) __QCMP_JOIN( L, #x )
#	define __QCMP_STRINGIZERA(x) #x
#	ifndef UNICODE
#		define UNICODE
#	endif
#	ifndef _UNICODE
#		define _UNICODE
#	endif
#else
#	define __QCMP_STRINGIZER(x) #x
#	define __QCMP_STRINGIZERA(x) #x
#	undef UNICODE								//Both these symbols are needed because years ago someone at Microsoft 'screwed up'.
#	undef _UNICODE
#endif

//Macros to get strings in the right format from hand coded constants
#define __QCMP_STRINGIZE(x) __QCMP_STRINGIZER(x)
#define __QCMP_STRINGIZEA(x) __QCMP_STRINGIZERA(x)

//Make path by joining path to / to filename
#define __QCMP_PATHIFY(_X,_Y) __QCMP_STRINGIZEA(_X/_Y)
#define __QCMP_PATHIFY3(_X,_Y,_Z) __QCMP_STRINGIZEA(_X/_Y/_Z)
#define __QCMP_PATHIFY4(_X,_Y,_Z,_A) __QCMP_STRINGIZEA(_X/_Y/_Z/_A)
#define __QCMP_PATHIFY5(_X,_Y,_Z,_A,_B) __QCMP_STRINGIZEA(_X/_Y/_Z/_A/_B)
#define __QCMP_PATHIFY6(_X,_Y,_Z,_A,_B,_C) __QCMP_STRINGIZEA(_X/_Y/_Z/_A/_B/C)

//Ensure code location is reported for explicit compilation warnings and errors
#define __QCMP_ERROR( _X ) error( __FILE__ "(" __QCMP_STRINGIZEA(__LINE__) ")" ##_X )
#define __QCMP_WARNING( _X ) message( __FILE__ "(" __QCMP_STRINGIZEA(__LINE__) ")" ##_X )

//MSVC supports nameless struct/union extension 
#define __QCMP_NAMELESS_STRUCT

//SEH
#define __QCMP_TRY				__try
#define __QCMP_EXCEPT( _COND )	__except( _COND )
#define __QCMP_EXCEPT_ALL		__except( ... )
#define __QCMP_FINALLY			__finally
#define __QCMP_RETHROW			throw

//define as template if template is needed in template operator member specifications
#define __QCMP_TEMPLATE_OPERATOR_SPECIFIER

#ifndef _W64
#	define _W64	
#endif

#endif//QCMP_MSVC_H_1
