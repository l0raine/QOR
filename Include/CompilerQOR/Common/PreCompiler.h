// PreCompiler.h

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

//early inclusion header shared between prebuild config stage and CompilerQOR

#ifndef QOR_PRECOMPILER_H_1
#define QOR_PRECOMPILER_H_1

#undef __QCMP_COMPILER									//undefine the compiler here
#undef __QCMP_COMPILER_INCLUDE							//undefine the compiler header file

#include "CompilerQOR/Common/PreConfig.h"				//Preprocessor definitions for configuration header
#include "CompilerQOR/Common/CompilerFeatures.h"		//Define feature macros so specific compiler deficiencies can be declared
#include "CompilerQOR/Common/Compilers.h"				//Determine the available compiler definitions

#include "CompilerQOR/Common/CompilerSelection.h"		//Select by detection the compiler in use

#ifdef __QCMP_COMPILER									//If compiler is determined
#	include "CompilerQOR/Preprocessor/Preprocessor.h"	//Include preprocessor definitions now we know which preprocessor they will be for													
#	include "CompilerQOR/Common/CompilerPath.h"			//Determine the paths for the compiler headers
#else													//Otherwise we guess that the unknown compiler supports #error as that's the best we can do
#	error The compiler in use could not be identified. Build terminating at PreCompiler.h
#endif//__QCMP_COMPILER

#ifdef QOR_CONFIG_HEADER								//If a configuration file is defined
//__QCMP_MESSAGE( QOR_PP_STRINGIZE(QOR_CONFIG_HEADER) )
#	include QOR_PP_STRINGIZE(QOR_PP_CAT(QOR_CONFIG_HEADER,Config.h))		//include it here
#else
#	include "DefaultConfig.h"
#endif


#endif//QOR_PRECOMPILER_H_1
