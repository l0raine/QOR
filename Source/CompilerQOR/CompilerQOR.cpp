//CompilerQOR.cpp

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


//Implements the CCompiler class and CompilerQOR Module identity

#ifndef NDEBUG													//Debug build
#	define __QCMP_REPORTCONIG				1					//Report configuration items during compilation where supported
#	define __QCMP_REPORTDEFECITS			1					//Report developer TODO: items during compilation where supported
#endif

#include "CompilerQOR.h"
#include "ArchQOR.h"

#ifdef _USRDLL													//Only needed for shared library builds
#	include "CodeQOR/DataTypes/GUID.h"
#	include "CodeQOR/Modules/LoadableModuleBase.h"
#	include "SystemQOR/SharedBootStrap.h"
#endif

//Pull in any intrinsics from the compiler as extern C function prototypes
#ifdef __QCMP_INTRINSICS_HEADER
__QCMP_STARTLINKAGE_C
#	include __QCMP_INTRINSICS_HEADER
__QCMP_ENDLINKAGE_C
#endif

//--------------------------------------------------------------------------------
namespace nsCompiler
{

//Implement the builtin wrappers within the CCompiler clas
#ifdef __QCMP_BUILTINS_INC
#	include __QCMP_BUILTINS_INC
#endif

//Implement the intrinsic wrappers within the CCompiler class
#ifdef __QCMP_INTRINSICS_INC
#	include __QCMP_INTRINSICS_INC
#endif

    //--------------------------------------------------------------------------------
    CCompiler::CCompiler()
    {
    }

    //--------------------------------------------------------------------------------
    CCompiler::CCompiler( const CCompiler& /*src*/ )
    {
    }

    //--------------------------------------------------------------------------------
    CCompiler& CCompiler::operator = ( const CCompiler& /*src*/ )
    {
		return *this;
    }

    //--------------------------------------------------------------------------------
    CCompiler::~CCompiler()
    {
    }

    //--------------------------------------------------------------------------------
    const char* CCompiler::Name( void )
    {
		return __QCMP_COMPILER_NAME;
    }

	static CCompiler theCompiler;

}//nsCompiler

//--------------------------------------------------------------------------------
//If the Compiler defines an unbuiltins header then include it here in the global namespace
#ifdef __QCMP_UNBUILTINS_HEADER
#	include __QCMP_UNBUILTINS_HEADER
#endif

//------------------------------------------------------------------------------
__QCMP_STARTLINKAGE_C

	//------------------------------------------------------------------------------
	__QCMP_EXPORT nsCompiler::CCompiler* TheCompiler( void )
	{
		return &nsCompiler::theCompiler;
	}

__QCMP_ENDLINKAGE_C

//------------------------------------------------------------------------------
//Only for shared library builds as one of a network of shared libraries
#ifndef QOR_MONOLITHIC
#ifdef _USRDLL


__QCMP_STARTLINKAGE_C

	extern int _cdecl QORStaticInit( void );

	//------------------------------------------------------------------------------
	__QCMP_EXPORT int _cdecl QORinit( void )
	{
		QORStaticInit();
		return 1;
	}

	//------------------------------------------------------------------------------
	//This gives the Compiler QOR library a unique identity
	//NOTE: The prototype for this function is delibrately ommitted. The client must explicitly request this entry point at runtime to identify this module.
	__QCMP_EXPORT nsCodeQOR::mxGUID* QORidentity( void )
	{
		static nsCodeQOR::mxGUID CompilerQOR = { 0x8519f0c2, 0xd864, 0x4477, { 0xbb, 0x36, 0xa0, 0xed, 0xbc, 0x0b, 0xb5, 0x05 } };
		return &CompilerQOR;
	}

__QCMP_ENDLINKAGE_C

	//------------------------------------------------------------------------------
	//This gives the Compiler QOR library a singleton representing the module at runtime
	nsCodeQOR::CLoadableModuleBase& __QCMP_LOCAL ThisModule( void )
	{
		static nsCodeQOR::CLoadableModuleBase CompilerQORModule( "Querysoft Open Runtime compiler compatability library (CompilerQOR)" );
		return CompilerQORModule;
	}

#endif//_USRDLL
#endif//QOR_MONOLITHIC
