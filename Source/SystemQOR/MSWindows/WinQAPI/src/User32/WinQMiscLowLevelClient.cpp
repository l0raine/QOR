//WinQMiscLowLevelClient.cpp

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

//Miscellaneous Low Level Client support functions

#include "WinQAPI/User32.h"
#include "ReturnCheck.h"

//--------------------------------------------------------------------------------
namespace nsWinQAPI
{
	//--------------------------------------------------------------------------------
	void CUser32::DisableProcessWindowsGhosting(void)
	{
		_WINQ_FCONTEXT( "CUser32::DisableProcessWindowsGhosting" );
		_WINQ_USESAPI( DisableProcessWindowsGhosting );
		(*pFunc)();
	}

	//--------------------------------------------------------------------------------
	//Obselete do not use
	LRESULT CUser32::SendIMEMessageEx( HWND hwnd, LPARAM lParam )
	{
		_WINQ_FCONTEXT( "CUser32::SendIMEMessageEx" );
		CCheckReturn< LRESULT, CSuccessCheck< > >::TType Result;
		_WINQ_USESAPI( SendIMEMessageEx );
		Result = Call< LRESULT, HWND, LPARAM >( pFunc, hwnd, lParam );
		//TODO: Add IME specific errors
		return Result;
	}

	//--------------------------------------------------------------------------------
	//Obselete do not use
	BOOL CUser32::WINNLSEnableIME( HWND hwnd, BOOL bFlag )
	{
		_WINQ_FCONTEXT( "CUser32::WINNLSEnableIME" );
		_WINQ_USESAPI( WINNLSEnableIME );
		return Call< BOOL, HWND, BOOL >( pFunc, hwnd, bFlag );
	}

}//nsWinQAPI

