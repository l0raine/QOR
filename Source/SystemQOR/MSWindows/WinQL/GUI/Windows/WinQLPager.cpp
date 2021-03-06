//WinQLPager.cpp

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
__QCMP_WARNING_PUSH
__QCMP_WARNING_DISABLE( __QCMP_WARN_THIS_USED_IN_BASE_INIT_LIST, "Safe usafe: stored in member for later use" );
#include "WinQL/GUI/Windows/Pager.h"
__QCMP_WARNING_POP

#if		( _WIN32_IE >= 0x0400 )

//--------------------------------------------------------------------------------
namespace nsWin32
{

	__QOR_IMPLEMENT_OCLASS_LUID( CPagerClass );

	//--------------------------------------------------------------------------------
	CPagerClass::CPagerClass() : m_ComCtrl32( CCommonCtrl::CCPAGESCROLLER_CLASS )
	{ 
		_WINQ_FCONTEXT( "CPagerClass::CPagerClass" );
	}

	//--------------------------------------------------------------------------------
	CPagerClass::~CPagerClass()
	{ 
		_WINQ_FCONTEXT( "CPagerClass::~CPagerClass" );
	}

	//--------------------------------------------------------------------------------
	bool CPagerClass::Preregistered()
	{ 
		_WINQ_FCONTEXT( "CPagerClass::Preregistered" );
		return true; 
	}

	//--------------------------------------------------------------------------------
	const TCHAR* CPagerClass::Name()
	{ 
		_WINQ_FCONTEXT( "CPagerClass::Name" );
		return _TXT( "SysPager" ); 
	}

	
	
	
	
	
	__QOR_IMPLEMENT_OCLASS_LUID( CPagerFactory );

	//--------------------------------------------------------------------------------
	CPagerFactory::CPagerFactory() : CWindowFactory()
	{
		_WINQ_FCONTEXT( "CPagerFactory::CPagerFactory" );
	}

	//--------------------------------------------------------------------------------
	CPager* CPagerFactory::Create()
	{
		_WINQ_FCONTEXT( "CPagerFactory::Instance" );
		return new CPager;//PreCreateWindow< CPager, CPagerClass >();
	}

	//--------------------------------------------------------------------------------
	CPagerFactory::~CPagerFactory()
	{
		_WINQ_FCONTEXT( "CPagerFactory::~CPagerFactory" );
	}
			
	//--------------------------------------------------------------------------------
	bool CPagerFactory::GetVertical()
	{
		_WINQ_FCONTEXT( "CPagerFactory::GetVertical" );
		return !GetStyleBits( PGS_HORZ );
	}

	//--------------------------------------------------------------------------------
	void CPagerFactory::SetVertical( bool bFlag )
	{
		_WINQ_FCONTEXT( "CPagerFactory::SetVertical" );
		SetStyleBits( PGS_HORZ, !bFlag );
	}

	//--------------------------------------------------------------------------------
	bool CPagerFactory::GetHorizontal()
	{
		_WINQ_FCONTEXT( "CPagerFactory::GetHorizontal" );
		return GetStyleBits( PGS_HORZ );
	}

	//--------------------------------------------------------------------------------
	void CPagerFactory::SetHorizontal( bool bFlag )
	{
		_WINQ_FCONTEXT( "CPagerFactory::SetHorizontal" );
		SetStyleBits( PGS_HORZ, bFlag );
	}

	//--------------------------------------------------------------------------------
	bool CPagerFactory::GetAutoScroll()
	{
		_WINQ_FCONTEXT( "CPagerFactory::GetAutoScroll" );
		return GetStyleBits( PGS_AUTOSCROLL );
	}

	//--------------------------------------------------------------------------------
	void CPagerFactory::SetAutoScroll( bool bFlag )
	{
		_WINQ_FCONTEXT( "CPagerFactory::SetAutoScroll" );
		SetStyleBits( PGS_AUTOSCROLL, bFlag );
	}

	//--------------------------------------------------------------------------------
	bool CPagerFactory::GetDragAndDrop()
	{
		_WINQ_FCONTEXT( "CPagerFactory::GetDragAndDrop" );
		return GetStyleBits( PGS_DRAGNDROP );
	}

	//--------------------------------------------------------------------------------
	void CPagerFactory::SetDragAndDrop( bool bFlag )
	{
		_WINQ_FCONTEXT( "CPagerFactory::SetDragAndDrop" );
		SetStyleBits( PGS_DRAGNDROP, bFlag );
	}
	
	
	
	
	__QOR_IMPLEMENT_OCLASS_LUID( CPager );

	//--------------------------------------------------------------------------------
	CPager::CPager() : CWinCtrlWindow()
	{	
		_WINQ_FCONTEXT( "CPager::CPager" );
	}

	//--------------------------------------------------------------------------------
	CPager::~CPager()
	{
		_WINQ_FCONTEXT( "CPager::~CPager" );
	}
	
	//--------------------------------------------------------------------------------
	long CPager::OnNotify( NotificationMessageHeader* pHdr )
	{
		_WINQ_FCONTEXT( "CPager::OnNotify" );
		long lResult = 0;

		if( pHdr != 0 )
		{
			switch ( pHdr->m_uiCode )
			{
			case NM_RELEASEDCAPTURE:
				{
					OnReleasedCapture( pHdr );
				}
				break;
			case PGN_CALCSIZE:
				{
					OnCalcSize( reinterpret_cast< NMPGCALCSIZE* >( pHdr ) );
				}
				break;
			case PGN_HOTITEMCHANGE:
				{
					lResult = static_cast< long >( OnHotItemChange( reinterpret_cast< NMPGHOTITEM* >( pHdr ) ) ? 1 : 0 );
				}
				break;
			default:
				{
					lResult = OnUnknownNotification( pHdr );
				}
				break;
			}
		}
		return lResult;
	}

	//--------------------------------------------------------------------------------
	void CPager::OnReleasedCapture( NotificationMessageHeader* pHdr )
	{
		_WINQ_FCONTEXT( "CPager::OnReleasedCapture" );
	}

	//--------------------------------------------------------------------------------
	void CPager::OnCalcSize( NMPGCALCSIZE* pCalcSize )
	{
		_WINQ_FCONTEXT( "CPager::OnCalcSize" );
	}

	//--------------------------------------------------------------------------------
	bool CPager::OnHotItemChange( NMPGHOTITEM* pHotItem )
	{
		_WINQ_FCONTEXT( "CPager::OnHotItemChange" );
		bool bResult = true;
		return bResult;
	}

	//--------------------------------------------------------------------------------
	long CPager::OnUnknownNotification( NotificationMessageHeader* pHdr )
	{
		_WINQ_FCONTEXT( "CPager::OnUnknownNotification" );
		long lResult = 0;
		return lResult;
	}

	//--------------------------------------------------------------------------------
	void CPager::ForwardMouse( bool bForward )
	{
		_WINQ_FCONTEXT( "CPager::ForwardMouse" );
		m_Win32MsgHandler.Send( Ref(), (unsigned int) PGM_FORWARDMOUSE, 
			static_cast< Cmp_uint_ptr >( bForward ? 1 : 0 ), 0 );
	}

	//--------------------------------------------------------------------------------
	unsigned long CPager::GetBkColour()
	{
		_WINQ_FCONTEXT( "CPager::GetBkColour" );
		unsigned long Result = static_cast< unsigned long >(
			m_Win32MsgHandler.Send( Ref(), (unsigned int) PGM_GETBKCOLOR, 0, 0 ) ); 
		return Result;
	}

	//--------------------------------------------------------------------------------
	long CPager::GetBorderPixels()
	{
		_WINQ_FCONTEXT( "CPager::GetBorderPixels" );
		long lResult = m_Win32MsgHandler.Send( Ref(), (unsigned int) PGM_GETBORDER, 0, 0 );
		return lResult;
	}

	//--------------------------------------------------------------------------------
	long CPager::GetButtonSizePixels()
	{
		_WINQ_FCONTEXT( "CPager::GetButtonSizePixels" );
		long lResult = m_Win32MsgHandler.Send( Ref(), (unsigned int) PGM_GETBUTTONSIZE, 0, 0 );
		return lResult;
	}

	//--------------------------------------------------------------------------------
	long CPager::GetButtonState( int iButton )
	{
		_WINQ_FCONTEXT( "CPager::GetButtonState" );
		long lResult = m_Win32MsgHandler.Send( Ref(), (unsigned int) PGM_GETBUTTONSTATE, 0, static_cast< Cmp_long_ptr >( iButton ) );
		return lResult;
	}

	//--------------------------------------------------------------------------------
	void CPager::GetDropTarget( IDropTarget** pIDropTarget )
	{
		_WINQ_FCONTEXT( "CPager::GetDropTarget" );
		m_Win32MsgHandler.Send( Ref(), (unsigned int) PGM_GETDROPTARGET, 0, reinterpret_cast< Cmp_long_ptr >( pIDropTarget ) );
	}

	//--------------------------------------------------------------------------------
	long CPager::GetPosScrollPixels()
	{
		_WINQ_FCONTEXT( "CPager::GetPosScrollPixels" );
		long lResult = m_Win32MsgHandler.Send( Ref(), (unsigned int) PGM_GETPOS, 0, 0 );
		return lResult;
	}

	//--------------------------------------------------------------------------------
	void CPager::RecalcSize()
	{
		_WINQ_FCONTEXT( "CPager::RecalcSize" );
		m_Win32MsgHandler.Send( Ref(), (unsigned int) PGM_RECALCSIZE, 0, 0 );
	}

	//--------------------------------------------------------------------------------
	unsigned long CPager::SetBkColour( unsigned long clrBk )
	{
		_WINQ_FCONTEXT( "CPager::SetBkColour" );
		unsigned long Prev = static_cast< unsigned long >( m_Win32MsgHandler.Send( Ref(), (unsigned int) PGM_SETBKCOLOR, 0, static_cast< Cmp_long_ptr >( clrBk ) ) );
		return Prev;
	}

	//--------------------------------------------------------------------------------
	long CPager::SetBorderPixels( int iBorderSize )
	{
		_WINQ_FCONTEXT( "CPager::SetBorderPixels" );
		long lResult = m_Win32MsgHandler.Send( Ref(), (unsigned int) PGM_SETBORDER, 0, static_cast< Cmp_long_ptr >( iBorderSize ) );
		return lResult;
	}

	//--------------------------------------------------------------------------------
	long CPager::SetButtonPixels( int iSize )
	{
		_WINQ_FCONTEXT( "CPager::SetButtonPixels" );
		long lResult = m_Win32MsgHandler.Send( Ref(), (unsigned int) PGM_SETBUTTONSIZE, 0, static_cast< Cmp_long_ptr >( iSize ) );
		return lResult;
	}

	//--------------------------------------------------------------------------------
	void CPager::SetChild( CWindowHandle::refType hChild )
	{
		_WINQ_FCONTEXT( "CPager::SetChild" );
		m_Win32MsgHandler.Send( Ref(), (unsigned int) PGM_SETCHILD, 0, reinterpret_cast< Cmp_long_ptr >( hChild->Use() ) );
	}

	//--------------------------------------------------------------------------------
	void CPager::SetPosScrollPixels( int iPos )
	{
		_WINQ_FCONTEXT( "CPager::SetPosScrollPixels" );
		m_Win32MsgHandler.Send( Ref(), (unsigned int) PGM_SETPOS, 0, static_cast< Cmp_long_ptr >( iPos ) );
	}

}//nsWin32

#endif//( _WIN32_IE >= 0x0400 )
