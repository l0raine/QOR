//SuperHVersion.h

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

#include "ArchQOR/Common/Endian.h"
#include "SuperHDefinitions.h"

//Determine SuperH architecture variant and version
//Wordsize Endianness and Name

#if( QOR_ARCH == QOR_ARCH_SUPERH )

#	undef QOR_ARCH_ENDIAN		//Bi-endian

#   if !defined(BOOST_ARCH_SH) && (defined(__SH5__))
#       define QOR_ARCH_SUPERH_VERSION BOOST_VERSION_NUMBER(5,0,0)
#		define QOR_ARCH_WORDSIZE	64
#   endif
#   if !defined(BOOST_ARCH_SH) && (defined(__SH4__))
#       define QOR_ARCH_SUPERH_VERSION BOOST_VERSION_NUMBER(4,0,0)
#		define QOR_ARCH_WORDSIZE	32
#   endif
#   if !defined(BOOST_ARCH_SH) && (defined(__sh3__) || defined(__SH3__))
#       define QOR_ARCH_SUPERH_VERSION BOOST_VERSION_NUMBER(3,0,0)
#		define QOR_ARCH_WORDSIZE	32
#   endif
#   if !defined(BOOST_ARCH_SH) && (defined(__sh2__))
#       define QOR_ARCH_SUPERH_VERSION BOOST_VERSION_NUMBER(2,0,0)
#		define QOR_ARCH_WORDSIZE	32
#   elif (defined(__sh1__))
#       define QOR_ARCH_SUPERH_VERSION BOOST_VERSION_NUMBER(1,0,0)
#		define QOR_ARCH_WORDSIZE	32
#   else
#       define QOR_ARCH_SUPERH_VERSION QOR_PP_VERSION_NUMBER(0,0,1)
#endif

#	define QOR_ARCH_NAME		"SuperH " QOR_PP_STRINGIZE(QOR_ARCH_SUPERH_VERSION)

#endif