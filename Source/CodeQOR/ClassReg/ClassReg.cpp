//ClassReg.cpp

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

#include "CompilerQOR.h"
#include "CodeQOR/ClassReg/ClassReg.h"
#include "string.h"

//--------------------------------------------------------------------------------
namespace nsCodeQOR
{
	//--------------------------------------------------------------------------------
	__QOR_INTERFACE( __CODEQOR ) bool IsEqualmxGUID( mxGUID& rguid1, mxGUID& rguid2 )
	{
	   return (
		  ( (unsigned long *) &rguid1 )[ 0 ] == ( (unsigned long *) &rguid2 )[ 0 ] &&
		  ( (unsigned long *) &rguid1 )[ 1 ] == ( (unsigned long *) &rguid2 )[ 1 ] &&
		  ( (unsigned long *) &rguid1 )[ 2 ] == ( (unsigned long *) &rguid2 )[ 2 ] &&
		  ( (unsigned long *) &rguid1 )[ 3 ] == ( (unsigned long *) &rguid2 )[ 3 ] );
	}

	//--------------------------------------------------------------------------------
	__QOR_INTERFACE( __CODEQOR ) bool operator == ( mxGUID& guidOne, mxGUID& guidOther )
	{
		return IsEqualmxGUID( guidOne, guidOther) ? true : false;
	}

	//--------------------------------------------------------------------------------
	__QOR_INTERFACE( __CODEQOR ) bool operator != ( const mxGUID& guidOne, const mxGUID& guidOther)
	{
		return !( guidOne == guidOther );
	}

	//--------------------------------------------------------------------------------
	__QOR_INTERFACE( __CODEQOR ) bool operator < ( const mxGUID& guidOne, const mxGUID& guidOther)
	{
		return strncmp( (const char*)(&guidOne), (const char*)(&guidOther), sizeof( mxGUID ) ) < 0 ? true : false;
	}

}//nsCodeQOR

