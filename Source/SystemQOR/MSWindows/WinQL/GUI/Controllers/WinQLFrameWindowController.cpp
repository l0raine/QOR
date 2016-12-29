//WinQLFrameWindowController.cpp

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
__QCMP_WARNING_DISABLE( __QCMP_WARN_THIS_USED_IN_BASE_INIT_LIST, "Safe usage: stored in member for later use" )
#include "WinQL/GUI/Windows/FrameWindow.h"
#include "WinQL/GUI/Controllers/FrameMenuController.h"
#include "WinQL/GUI/Controllers/FrameNCController.h"
#include "WinQL/GUI/Controllers/FrameRenderingController.h"
#include "WinQL/GUI/Controllers/FrameScrollController.h"
#include "WinQL/GUI/Controllers/FrameWindowController.h"
__QCMP_WARNING_POP

//--------------------------------------------------------------------------------
namespace nsWin32
{
	__QOR_IMPLEMENT_OCLASS_LUID( CFrameWindowController );

	//--------------------------------------------------------------------------------
	CFrameWindowController::CFrameWindowController( nsMammut::CModel* pModelItem, nsQOR::CController::ref_type Parent ) : CInteractiveWindowController( pModelItem, Parent )
	{
		_WINQ_FCONTEXT( "CFrameWindowController::CFrameWindowController" );
	}

	//--------------------------------------------------------------------------------
	CFrameWindowController::~CFrameWindowController()
	{
		_WINQ_FCONTEXT( "CFrameWindowController::~CFrameWindowController" );
	}

	//--------------------------------------------------------------------------------
	void CFrameWindowController::SetModel( nsMammut::CModel* pModelItem )
	{
		_WINQ_FCONTEXT( "CFrameWindowController::SetModel" );

		NonClient.Configure( &FrameNCController() );
		Rendering.Configure( &FrameRenderingController() );
		Scroll.Configure( &FrameScrollController() );
		Menu.Configure( &FrameMenuController() );

		CInteractiveWindowController::SetModel( pModelItem );						
	}

	//--------------------------------------------------------------------------------
	bool CFrameWindowController::ProcessMessage( COSWindow& Window, Cmp_long_ptr& lResult, unsigned int uMsg, Cmp_uint_ptr wParam, Cmp_long_ptr lParam )
	{
		_WINQ_FCONTEXT( "CFrameWindowController::ProcessMessage" );

		bool bProcessed = ProcessHook( Window, lResult, uMsg, wParam, lParam );

		bProcessed = CInteractiveWindowController::ProcessMessage( Window, lResult, uMsg, wParam, lParam );

		if( !bProcessed )
		{
			bProcessed = HandleMessage( Window, lResult, uMsg, wParam, lParam );
		}
		return bProcessed;
	}

	//--------------------------------------------------------------------------------
	bool CFrameWindowController::HandleMessage( COSWindow& Window, Cmp_long_ptr& lResult, unsigned int uMsg, Cmp_uint_ptr wParam, Cmp_long_ptr lParam )
	{
		_WINQ_FCONTEXT( "CFrameWindowController::HandleMessage" );

		bool bHandled = false;

		switch ( uMsg )
		{
		case COSWindow::wmQueryEndSession:
			{
				bool bLoggingOff = ( lParam & COSWindow::EndSessionLogOff ) > 0 ? true : false;
				lResult = OnQueryEndSession( bLoggingOff ) ? 1 : 0;
				bHandled = true;
			}
			break;
		case COSWindow::wmEndSession:
			{
				bool bEnd = wParam ? true : false;
				bool bLoggingOff = ( lParam & COSWindow::EndSessionLogOff ) > 0 ? true : false;
				OnEndSession( bEnd, bLoggingOff );
				lResult = 0;
				bHandled = true;
			}
			break;
		};

		return bHandled;
	}


	//--------------------------------------------------------------------------------
	long CFrameWindowController::OnCreate(  COSWindow& Window, CreateStruct* pCreateStruct )
	{
		_WINQ_FCONTEXT( "CFrameWindowController::OnCreate" );
		long lResult = CInteractiveWindowController::OnCreate( pCreateStruct );
		//Create any special clients by calling virtual funcs here

		//TODO: Recalc layout
		return lResult;
	}

	//--------------------------------------------------------------------------------
	long CFrameWindowController::OnDestroy( COSWindow& Window, unsigned int uMsg, Cmp_uint_ptr wParam, Cmp_long_ptr lParam )
	{
		_WINQ_FCONTEXT( "CFrameWindowController::OnDestroy" );
		//Destroy dependent stuff and help stuff here
		long lResult = CInteractiveWindowController::OnDestroy( Window, uMsg, wParam, lParam );
		return lResult;
	}

	//--------------------------------------------------------------------------------
	long CFrameWindowController::OnActivate( COSWindow& Window, unsigned int uMsg, Cmp_uint_ptr wParam, Cmp_long_ptr lParam )
	{
		_WINQ_FCONTEXT( "CFrameWindowController::OnActivate" );
		long lResult = CInteractiveWindowController::OnActivate( Window, uMsg, wParam, lParam );
		return lResult;
	}

	//--------------------------------------------------------------------------------
	void CFrameWindowController::OnEnable( bool bEnable )
	{
		_WINQ_FCONTEXT( "CFrameWindowController::OnEnable" );
		//Handle modal disabled state and enable/disable locking

		if( bEnable == true )
		{
			//If Enable is locked on force a WM_NCACTIVATE for this frame and 
			//any floating windows it owns
		}
	}

	//--------------------------------------------------------------------------------
	void CFrameWindowController::OnClose( COSWindow& Window )
	{
		_WINQ_FCONTEXT( "CFrameWindowController::OnClose" );
		//Check with the use contents whether we can close
		//If this is th emain frame intiate an appwide saveall

		Window.Destroy();
	}

	//--------------------------------------------------------------------------------
	bool CFrameWindowController::OnQueryEndSession( bool bLoggingOff )
	{
		_WINQ_FCONTEXT( "CFrameWindowController::OnQueryEndSession" );
		//If this is the main frame then initiate an app wide saveall
		return true;
	}

	//--------------------------------------------------------------------------------
	void CFrameWindowController::OnEndSession( bool bEnd, bool bLoggingOff )
	{
		_WINQ_FCONTEXT( "CFrameWindowController::OnEndSession" );
		if( bEnd )
		{
			//If this is the main frame then initiate an app wide closedown
		}
	}

}//nsWin32
