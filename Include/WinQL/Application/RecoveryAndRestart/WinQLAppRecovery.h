//WinQLAppRecovery.h

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

//Win32 Application Recovery class

#ifndef WINQL_APPRECOVERY_H_3
#define WINQL_APPRECOVERY_H_3

#ifdef	__QCMP_OPTIMIZEINCLUDE
#pragma	__QCMP_OPTIMIZEINCLUDE
#endif//__QCMP_OPTIMIZEINCLUDE

#include "WinQL/WinQL.h"

//--------------------------------------------------------------------------------
namespace nsWin32
{
	class __QOR_INTERFACE( __WINQL ) CWaitableTimer;

	typedef unsigned long ( __QCMP_STDCALLCONVENTION* APPLICATION_RECOVERY_CALLBACK )( void* pvParameter );

	//--------------------------------------------------------------------------------
	class __QOR_INTERFACE( __WINQL ) CAppRecovery
	{

	public:

		//--------------------------------------------------------------------------------
		typedef nsCodeQOR::CTLRef< CAppRecovery > refType;

		__QOR_DECLARE_OCLASS_ID( CAppRecovery );

		CAppRecovery( unsigned long ulRecoveryPingInterval = 1000 );
		~CAppRecovery();

		virtual bool Recover( void );
		virtual void Cancel( void );

		//--------------------------------------------------------------------------------
		refType Ref( void )
		{
			return refType( this, false );
		}

	protected:

		void ApplicationRecoveryFinished( bool bSuccess );
		long ApplicationRecoveryInProgress( int* pbCanceled );
		long GetApplicationRecoveryCallback( void* hProcess, nsWin32::APPLICATION_RECOVERY_CALLBACK* pRecoveryCallback, void** ppvParameter, unsigned long* dwPingInterval, unsigned long* dwFlags );
		long RegisterApplicationRecoveryCallback( nsWin32::APPLICATION_RECOVERY_CALLBACK pRecoveryCallback, void* pvParameter, unsigned long dwPingInterval, unsigned long dwFlags );
		long UnregisterApplicationRecoveryCallback( void );

		void ProcessRecover( void );
		
		static unsigned long __QCMP_STDCALLCONVENTION RecoveryCallback( void* pvParameter );
		static void __QCMP_STDCALLCONVENTION RecoveryPingCallback( void* pArg, unsigned long ulTimerLowValue, unsigned long ulTimerHighValue );

	protected:

		void CancelRecovery( void );

	private:

		unsigned long m_ulRecoveryPingInterval;
		CWaitableTimer* m_pTimer;
	};

}//nsWin32

#endif//WINQL_APPRESTART_H_2
