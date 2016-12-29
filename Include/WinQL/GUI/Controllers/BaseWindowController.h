//BaseWindowController.h

// Copyright Querysoft Limited 2013, 2015
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

//GUI Base Controller for Windows windows

#ifndef WINQL_GUI_CONTROLLER_BASE_H_3
#define WINQL_GUI_CONTROLLER_BASE_H_3

#include "CodeQOR/Instancing/STMember.h"
#include "AppocritaQOR/Controller.h"
#include "WinQL/GUI/Controllers/Parts/StyleController.h"
#include "WinQL/GUI/Controllers/Parts/BaseTextController.h"
#include "WinQL/GUI/Controllers/Parts/OwnerController.h"
#include "WinQL/GUI/Controllers/Parts/TimerController.h"
#include "WinQL/GUI/Controllers/Parts/UserController.h"
#include "WinQL/GUI/Controllers/Parts/DeviceChangeController.h"

//--------------------------------------------------------------------------------
namespace nsWin32
{
    class __QOR_INTERFACE( __WINQL_GUI ) COSWindow;
	class __QOR_INTERFACE( __WINQL_GUI ) CWindowView;
	struct CreateStruct;

    //--------------------------------------------------------------------------------
	class __QOR_INTERFACE( __WINQL_GUI ) CBaseWindowController : public nsQOR::CController
	{
	public:

		__QOR_DECLARE_OCLASS_ID( CBaseWindowController );

		CBaseWindowController( nsMammut::CModel* pModel = 0, nsQOR::CController::ref_type Parent = 0 );
		virtual ~CBaseWindowController();

		virtual void SetModel( nsMammut::CModel* pModelItem );

        //--------------------------------------------------------------------------------
        template< class TView > void CreateView( nsQOR::CController* pController = 0 )
        {
            TView* pView = new TView();
            pView->SetModel( m_pModel );
            pView->SetController( pController ? pController : this->GetChildController( pView ) );
            pView->Animate( 0 );
        }

		virtual CBaseWindowController* HookController( CBaseWindowController* pController );
		bool ProcessHook( COSWindow& Window, Cmp_long_ptr& lResult, unsigned int uMsg, Cmp_uint_ptr wParam, Cmp_long_ptr lParam );
		virtual bool ProcessMessage( COSWindow& Window, Cmp_long_ptr& lResult, unsigned int uMsg, Cmp_uint_ptr wParam, Cmp_long_ptr lParam );
		bool HandleMessage( COSWindow& Window, Cmp_long_ptr& lResult, unsigned int uMsg, Cmp_uint_ptr wParam, Cmp_long_ptr lParam );
		virtual long OnCreate( CreateStruct* pCreateStruct );
		virtual long OnDestroy( COSWindow& Window, unsigned int uMsg, Cmp_uint_ptr wParam, Cmp_long_ptr lParam );
		virtual long OnActivate( COSWindow& Window, unsigned int uMsg, Cmp_uint_ptr wParam, Cmp_long_ptr lParam );
		virtual long OnMouseActivate( COSWindow& Window, unsigned int uMsg, Cmp_uint_ptr wParam, Cmp_long_ptr lParam );
		virtual void OnEnable( COSWindow& Window, bool bEnable );
		virtual void OnClose( COSWindow& Window );
		virtual void OnSystemError( COSWindow& Window, Cmp_long_ptr& lResult, unsigned int uMsg, Cmp_uint_ptr wParam, Cmp_long_ptr lParam );
		virtual void OnSysCommand( COSWindow& Window, unsigned int uMsg, Cmp_uint_ptr wParam, Cmp_long_ptr lParam );

		nsCodeQOR::CSTMember< CStyleController > Style;
		nsCodeQOR::CSTMember< CUserController > User;
		nsCodeQOR::CSTMember< CBaseTextController > BaseText;
		nsCodeQOR::CSTMember< COwnerController > Owner;
		nsCodeQOR::CSTMember< CTimerController > Timer;
		nsCodeQOR::CSTMember< CDeviceChangeController > DeviceChange;

		nsCodeQOR::CSTMember< CWindowView > View;

	protected:

		CBaseWindowController* m_pNextHookController;

	};

}//nsWin32

#endif//WINQL_GUI_CONTROLLER_BASE_H_3
