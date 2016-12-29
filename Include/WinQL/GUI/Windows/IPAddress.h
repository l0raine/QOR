//IPAddress.h

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

//IPAddress Common Control Window

#ifndef WINQL_GUI_WND_CCTRL_IPADDRESS_H_3
#define WINQL_GUI_WND_CCTRL_IPADDRESS_H_3

#include "WinQL/GUI/Views/WindowView.h"
#include "WinQL/GUI/Windows/WinCtrlWindow.h"
#include "MammutQOR/Model.h"
#include "WinQL/GUI/CommonCtrl.h"
#include "WinQL/GUI/WindowFactory.h"

//--------------------------------------------------------------------------------
namespace nsWin32
{
#if		( _WIN32_IE >= 0x0400 )

	//--------------------------------------------------------------------------------
	class __QOR_INTERFACE( __WINQL_GUI ) CIPAddressClass : public CWindowClass
	{
	public:

		__QOR_DECLARE_OCLASS_ID( CIPAddressClass );

		CIPAddressClass();
		~CIPAddressClass();
		virtual bool Preregistered();
		const TCHAR* Name();

	private:

		CCommonCtrl m_ComCtrl32;

		CIPAddressClass( const CIPAddressClass& );
		CIPAddressClass& operator = ( const CIPAddressClass& );
	};


	//--------------------------------------------------------------------------------
	class __QOR_INTERFACE( __WINQL_GUI ) CIPAddress : public CWinCtrlWindow
	{
	public:

		//Notifications
		__QCMP_STATIC_CONSTANT( int, EN_SETFOCUS         = 0x0100 );
		__QCMP_STATIC_CONSTANT( int, EN_KILLFOCUS        = 0x0200 );
		__QCMP_STATIC_CONSTANT( int, EN_CHANGE           = 0x0300 );

		__QCMP_STATIC_CONSTANT( int, IPN_FIRST           = (0U-860U) );      // internet address
		__QCMP_STATIC_CONSTANT( int, IPN_LAST            = (0U-879U) );      // internet address

		__QCMP_STATIC_CONSTANT( int, IPN_FIELDCHANGED    = (IPN_FIRST - 0) );

		//Messages
		__QCMP_STATIC_CONSTANT( int, IPM_CLEARADDRESS	= (COSWindow::wmUser+100) );// no parameters
		__QCMP_STATIC_CONSTANT( int, IPM_SETADDRESS		= (COSWindow::wmUser+101) );// lparam = TCP/IP address
		__QCMP_STATIC_CONSTANT( int, IPM_GETADDRESS		= (COSWindow::wmUser+102) );// lresult = # of non black fields.  lparam = LPDWORD for TCP/IP address
		__QCMP_STATIC_CONSTANT( int, IPM_SETRANGE		= (COSWindow::wmUser+103) );// wparam = field, lparam = range
		__QCMP_STATIC_CONSTANT( int, IPM_SETFOCUS		= (COSWindow::wmUser+104) );// wparam = field
		__QCMP_STATIC_CONSTANT( int, IPM_ISBLANK			= (COSWindow::wmUser+105) );// no parameters

		//--------------------------------------------------------------------------------
		typedef struct tagNMIPADDRESS : public NotificationMessageHeader
		{
			//NMHDR hdr;
			int iField;
			int iValue;
		} NMIPADDRESS, *LPNMIPADDRESS;

		__QOR_DECLARE_OCLASS_ID( CIPAddress );

		CIPAddress();
		~CIPAddress();
		virtual void OnCommand( unsigned short wCtrlID, unsigned short wCode );

		virtual void OnChange();
		virtual void OnSetFocus();
		virtual void OnKillFocus();
		virtual void OnUnknownCommand( unsigned short wCode );

		virtual long OnNotify( NotificationMessageHeader* pHdr );

		virtual void OnFieldChanged( NMIPADDRESS* pHdr );
		virtual long OnUnknownNotification( NotificationMessageHeader* pHdr );

		void ClearAddress();
		long GetAddress( unsigned long& dwAddress );
		bool IsBlank();
		void SetAddress( unsigned long dwAddress );
		void SetFieldFocus( int nField );
		bool SetRange( int nField, unsigned short wRange );

	};

	//--------------------------------------------------------------------------------
	class __QOR_INTERFACE( __WINQL_GUI ) CIPAddressFactory : public CWindowFactory
	{
	public:

		__QOR_DECLARE_OCLASS_ID( CIPAddressFactory );

		CIPAddressFactory();
		~CIPAddressFactory();
		virtual CIPAddress* Create();

		/*
		bool GetHorizontal()
		{
			return GetStyleBits( HDS_HORZ );
		}

		//--------------------------------------------------------------------------------
		void SetHorizontal( bool bFlag )
		{
			SetStyleBits( HDS_HORZ, !bFlag );
		}
		*/

	private:

		CIPAddressFactory( const CIPAddressFactory& );
		CIPAddressFactory& operator = ( const CIPAddressFactory& );
 
	};

#endif//( _WIN32_IE >= 0x0400 )

}//nsWin32

#endif//WINQL_GUI_WND_CCTRL_IPADDRESS_H_3