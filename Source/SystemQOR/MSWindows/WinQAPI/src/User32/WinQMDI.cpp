//WinQMDI.cpp

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

//Multi Document Interface functions

#include "WinQAPI/User32.h"
#include "../Source/SystemQOR/MSWindows/WinQAPI/include/ReturnCheck.h"

//--------------------------------------------------------------------------------
namespace nsWinQAPI
{
	//--------------------------------------------------------------------------------
	HWND CUser32::CreateMDIWindow( LPCTSTR lpClassName, LPCTSTR lpWindowName, DWORD dwStyle, int X, int Y, int nWidth, int nHeight, HWND hWndParent, HINSTANCE hInstance, LPARAM lParam )
	{
		_WINQ_FCONTEXT( "CUser32::CreateMDIWindow" );
		CCheckReturn< HWND, CCheckNonZero< HWND > >::TType Result;
		_WINQ_USESAPIAW( CreateMDIWindow );
		Result = Call< HWND, LPCTSTR, LPCTSTR, DWORD, int, int, int, int, HWND, HINSTANCE, LPARAM >( pFunc, lpClassName, lpWindowName, dwStyle, X, Y, nWidth, nHeight, hWndParent, hInstance, lParam );
		return Result;
	}

	//--------------------------------------------------------------------------------
	LRESULT CUser32::DefFrameProc( HWND hWnd, HWND hWndMDIClient, UINT uMsg, WPARAM wParam, LPARAM lParam )
	{
		_WINQ_FCONTEXT( "CUser32::DefFrameProc" );
		_WINQ_USESAPI( DefFrameProc );
		return Call< LRESULT, HWND, HWND, UINT, WPARAM, LPARAM >( pFunc, hWnd, hWndMDIClient, uMsg, wParam, lParam );
	}

	//--------------------------------------------------------------------------------
	LRESULT CUser32::DefMDIChildProc( HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam )
	{
		_WINQ_FCONTEXT( "CUser32::DefMDIChildProc" );
		_WINQ_USESAPI( DefMDIChildProc );
		return Call< LRESULT, HWND, UINT, WPARAM, LPARAM >( pFunc, hWnd, uMsg, wParam, lParam );
	}

	//--------------------------------------------------------------------------------
	BOOL CUser32::TranslateMDISysAccel( HWND hWndClient, LPMSG lpMsg )
	{
		_WINQ_FCONTEXT( "CUser32::TranslateMDISysAccel" );
		CCheckReturn< BOOL, CBoolCheck< > >::TType bResult;
		_WINQ_USESAPI( TranslateMDISysAccel );
		bResult = Call< BOOL, HWND, LPMSG >( pFunc, hWndClient, lpMsg );
		return bResult;
	}

}//nsWinQAPI

