//MMC.cpp

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

#include "WinQAPI/WinQAPI.h"
#include "SystemQOR.h"
#include "WinQAPI/Kernel32.h"
#include "WinQAPI/MMCAPI.h"
#include "../Source/SystemQOR/MSWindows/WinQAPI/include/ReturnCheck.h"

//--------------------------------------------------------------------------------
namespace nsWinQAPI
{

	//--------------------------------------------------------------------------------
	long CMMC::MMCFreeNotifyHandle( Cmp_long_ptr lNotifyHandle )
	{
		_WINQ_FCONTEXT( "CMMC::MMCFreeNotifyHandle" );
		long hResult = 0;
		_WINQ_USESAPI( MMCFreeNotifyHandle );
		hResult = Call< long, Cmp_long_ptr >( pFunc, lNotifyHandle );
		return hResult;
	}

	//--------------------------------------------------------------------------------
	long CMMC::MMCPropertyChangeNotify( Cmp_long_ptr lNotifyHandle, Cmp_long_ptr param )
	{
		_WINQ_FCONTEXT( "CMMC::MMCPropertyChangeNotify" );
		long hResult = 0;
		_WINQ_USESAPI( MMCPropertyChangeNotify );
		hResult = Call< long, Cmp_long_ptr, Cmp_long_ptr >( pFunc, lNotifyHandle, param );
		return hResult;
	}

	//--------------------------------------------------------------------------------
	long CMMC::MMCPropertyHelp( LPOLESTR pszHelpTopic )
	{
		_WINQ_FCONTEXT( "CMMC::MMCPropertyHelp" );
		long hResult = 0;
		_WINQ_USESAPI( MMCPropertyHelp );
		hResult = Call< long, LPOLESTR >( pFunc, pszHelpTopic );
		return hResult;
	}

	//--------------------------------------------------------------------------------
	long CMMC::MMCPropPageCallback( void* vpsp )
	{
		_WINQ_FCONTEXT( "CMMC::MMCPropPageCallback" );
		long hResult = 0;
		_WINQ_USESAPI( MMCPropPageCallback );
		hResult = Call< long, void* >( pFunc, vpsp );
		return hResult;
	}

}//nsWinQAPI

