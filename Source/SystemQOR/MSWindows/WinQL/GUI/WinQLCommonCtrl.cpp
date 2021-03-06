//WinQLCommonCtrl.cpp

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

#include "WinQL/Application/ErrorSystem/WinQLError.h"
__QCMP_WARNING_PUSH
__QCMP_WARNING_DISABLE( __QCMP_WARN_THIS_USED_IN_BASE_INIT_LIST, "Safe usage: stored in member for later use." )
#include "WinQL/GUI/CommonCtrl.h"
__QCMP_WARNING_POP
#include "WinQAPI/User32.h"
#include "WinQAPI/ComCtl32.h"

//--------------------------------------------------------------------------------
namespace nsWin32
{
	using namespace ::nsWinQAPI;

	__QOR_IMPLEMENT_OCLASS_LUID( CCommonCtrl );

	//--------------------------------------------------------------------------------
	CCommonCtrl::CCommonCtrl() : m_ComCtl32Library( CComCtl32::Instance() )
	{
		_WINQ_FCONTEXT( "CCommonCtrl::CCommonCtrl" );
		__QOR_PROTECT
		{
			m_ComCtl32Library.InitCommonControls();
		}__QOR_ENDPROTECT
	}

	//--------------------------------------------------------------------------------
	CCommonCtrl::CCommonCtrl( unsigned long dwICC, int* pbResult ) : m_ComCtl32Library( CComCtl32::Instance() )
	{
		_WINQ_FCONTEXT( "CCommonCtrl::CCommonCtrl" );
		INITCOMMONCONTROLSEX InitStruct;
		InitStruct.dwSize = sizeof( INITCOMMONCONTROLSEX );
		InitStruct.dwICC = dwICC;
		BOOL bResult = FALSE;
		__QOR_PROTECT
		{
			bResult = m_ComCtl32Library.InitCommonControlsEx( &InitStruct );
			if( pbResult != 0 )
			{
				*pbResult = bResult;
			}
		}__QOR_ENDPROTECT
	}

	//--------------------------------------------------------------------------------
	CCommonCtrl::~CCommonCtrl()
	{
		_WINQ_FCONTEXT( "CCommonCtrl::~CCommonCtrl" );
	}

	//--------------------------------------------------------------------------------
	void CCommonCtrl::DrawInsert( COSWindow::refType WndParent, COSWindow::refType LB, int nItem )
	{
		_WINQ_FCONTEXT( "CCommonCtrl::DrawInsert" );
		__QOR_PROTECT
		{
			m_ComCtl32Library.DrawInsert( reinterpret_cast< ::HWND >( WndParent->Handle()->Use() ), reinterpret_cast< ::HWND >( LB->Handle()->Use() ), nItem );
		}__QOR_ENDPROTECT
	}

	//--------------------------------------------------------------------------------
	int CCommonCtrl::LBItemFromPt( COSWindow::refType LB, nsWin32::POINT pt, bool bAutoScroll )
	{
		_WINQ_FCONTEXT( "CCommonCtrl::LBItemFromPt" );
		int iResult = -1;
		__QOR_PROTECT
		{
			iResult = m_ComCtl32Library.LBItemFromPt( reinterpret_cast< ::HWND >( LB->Handle()->Use() ), *( reinterpret_cast< ::POINT* >( &pt ) ), bAutoScroll ? TRUE : FALSE );
		}__QOR_ENDPROTECT
		return iResult;
	}

	//--------------------------------------------------------------------------------
	bool CCommonCtrl::MakeDragList( COSWindow::refType LB )
	{
		_WINQ_FCONTEXT( "CCommonCtrl::MakeDragList" );
		bool bResult = false;
		__QOR_PROTECT
		{
			bResult = m_ComCtl32Library.MakeDragList( reinterpret_cast< ::HWND >( LB->Handle()->Use() ) ) ? true : false;
		}__QOR_ENDPROTECT
		return bResult;
	}

}//nsWIn32
