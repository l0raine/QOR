//BuildOpts.h

// Copyright Querysoft Limited 2016
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


//Definitions needed to construct an MSVC 2015 command line

#define QOR_PP_BUILD_COMPILER_EXECUTABLE				cl.exe
#define QOR_PP_BUILD_LINKER_EXECUTABLE					link.exe
#define QOR_PP_BUILD_LIB_EXECUTABLE						lib.exe
#if( QOR_ARCH == QOR_ARCH_X86_32 )
#	define QOR_PP_BUILD_ASSEMBLER_EXECUTABLE				ml.exe
#elif( QOR_ARCH == QOR_ARCH_X86_64 )
#	define QOR_PP_BUILD_ASSEMBLER_EXECUTABLE				ml64.exe
#endif

#ifndef	QOR_PP_BUILD_CMP_INTRINSICS_ENABLE
#	define QOR_PP_BUILD_CMP_INTRINSICS_ENABLE			__QCS_NO_
#endif

#include "BuildCmpCmdLine.h"
#include "BuildLnkCmdLine.h"


#define QOR_PP_BUILD_LINK_OBJLISTNAME( _MODULE_NAME )	QOR_PP_CAT( QOR_PP_CAT( QOR_PP_CONFIG_INT_DIR, _MODULE_NAME ), objlist.txt )

#define QOR_PP_BUILD_LINK_PREPARE_OBJLIST( _MODULE_NAME ) \
														echo ??/n > QOR_PP_BUILD_LINK_OBJLISTNAME( _MODULE_NAME )

#define QOR_PP_BUILD_LINK_EXPORT_OBJNAME( r, _MODULE_NAME, _, _X ) \
														echo QOR_PP_CAT( QOR_PP_CAT( QOR_PP_CONFIG_INT_DIR,_MODULE_NAME/ ), QOR_PP_CAT( _X,.obj )) >> QOR_PP_BUILD_LINK_OBJLISTNAME( _MODULE_NAME )

#include "BuildLibCmdLine.h"
#include "BuildAsmCmdLine.h"
