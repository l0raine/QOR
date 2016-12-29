//WinQLServiceControlManager.cpp

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

#include "WinQL/System/ProcessManager/WinQLServiceControlManager.h"
#include "WinQAPI/AdvAPI32.h"

//--------------------------------------------------------------------------------
namespace nsWin32
{
	using namespace nsWinQAPI;

	__QOR_IMPLEMENT_OCLASS_LUID( CServiceControlManager );

	//--------------------------------------------------------------------------------
	CServiceControlManager::CServiceControlManager() : m_AdvAPI32Library( CAdvAPI32::Instance() )
	{
		_WINQ_FCONTEXT( "CServiceControlManager::CServiceControlManager" );
	}

	//--------------------------------------------------------------------------------
	CServiceControlManager::~CServiceControlManager()
	{
		_WINQ_FCONTEXT( "CServiceControlManager::~CServiceControlManager" );
	}

	//--------------------------------------------------------------------------------
	bool CServiceControlManager::StartCtrlDispatcher( const SERVICE_TABLE_ENTRY* pServiceTable )
	{
		_WINQ_FCONTEXT( "CServiceControlManager::StartCtrlDispatcher" );

		bool bResult = m_AdvAPI32Library.StartServiceCtrlDispatcher( reinterpret_cast< const ::SERVICE_TABLE_ENTRY* >( pServiceTable ) ) ? true : false;
		return bResult;
	}

	//--------------------------------------------------------------------------------
	ServiceStatusHandle CServiceControlManager::RegisterCtrlHandler( CTString& strServiceName, LPHANDLER_FUNCTION pHandlerProc )
	{
		_WINQ_FCONTEXT( "CServiceControlManager::RegisterCtrlHandler" );

		ServiceStatusHandle Result = reinterpret_cast< ServiceStatusHandle >( m_AdvAPI32Library.RegisterServiceCtrlHandler( strServiceName.GetNullableBuffer(), reinterpret_cast< ::LPHANDLER_FUNCTION >( pHandlerProc ) ) );
		strServiceName.ReleaseBuffer();

		return Result;
	}

	//--------------------------------------------------------------------------------
	ServiceStatusHandle CServiceControlManager::RegisterCtrlHandler( CTString& strServiceName, LPHANDLER_FUNCTION_EX pHandlerProc, void* pContext )
	{
		_WINQ_FCONTEXT( "CServiceControlManager::RegisterCtrlHandler" );

		ServiceStatusHandle Result = reinterpret_cast< ServiceStatusHandle >( m_AdvAPI32Library.RegisterServiceCtrlHandlerEx( strServiceName.GetNullableBuffer(), reinterpret_cast< ::LPHANDLER_FUNCTION_EX >( pHandlerProc ), pContext ) );
		strServiceName.ReleaseBuffer();

		return Result;
	}

	//--------------------------------------------------------------------------------
	bool CServiceControlManager::SetBits( ServiceStatusHandle hServiceStatus, unsigned long ulServiceBits, bool bSetBitsOn, bool bUpdateImmediately )
	{
		_WINQ_FCONTEXT( "CServiceControlManager::SetBits" );
		bool bResult = m_AdvAPI32Library.SetServiceBits( reinterpret_cast< ::SERVICE_STATUS_HANDLE >( hServiceStatus ), ulServiceBits, bSetBitsOn ? TRUE : FALSE, bUpdateImmediately ? TRUE : FALSE ) ? true : false;
		return bResult;
	}

	//--------------------------------------------------------------------------------
	bool CServiceControlManager::SetStatus( ServiceStatusHandle hServiceStatus, LPSERVICE_STATUS lpServiceStatus )
	{
		_WINQ_FCONTEXT( "CServiceControlManager::SetStatus" );
		bool bResult = m_AdvAPI32Library.SetServiceStatus( reinterpret_cast< ::SERVICE_STATUS_HANDLE >( hServiceStatus ), reinterpret_cast< ::LPSERVICE_STATUS >( lpServiceStatus ) ) ? true : false;
		return bResult;
	}

	//--------------------------------------------------------------------------------
	CServiceControlSession::refType CServiceControlManager::OpenSession( CTString& strMachine, CTString& strDatabaseName, unsigned long ulDesiredAccess )
	{
		_WINQ_FCONTEXT( "CServiceControlManager::OpenSession" );
		CServiceControlSession::refType result( new CServiceControlSession( *this, strMachine.GetNullableBuffer(), strDatabaseName.GetNullableBuffer(), ulDesiredAccess ), true );
		
		strMachine.ReleaseBuffer();
		strDatabaseName.ReleaseBuffer();

		return result;
	}

	//--------------------------------------------------------------------------------
	ServiceControlHandle CServiceControlManager::OpenSCManagerT( const TCHAR* pMachineName, const TCHAR* pDatabaseName, unsigned long ulDesiredAccess )
	{
		_WINQ_FCONTEXT( "CServiceControlManager::OpenSCManager" );
		ServiceControlHandle Result = reinterpret_cast< ServiceControlHandle >( m_AdvAPI32Library.OpenSCManager( pMachineName, pDatabaseName, ulDesiredAccess ) );
		return Result;
	}

	//--------------------------------------------------------------------------------
	bool CServiceControlManager::CloseServiceHandle( ServiceControlHandle hSCObject )
	{
		_WINQ_FCONTEXT( "CServiceControlManager::CloseServiceHandle" );
		bool bResult = m_AdvAPI32Library.CloseServiceHandle( reinterpret_cast< ::SC_HANDLE >( hSCObject ) ) ? true : false;
		return bResult;
	}

	//--------------------------------------------------------------------------------
	void* CServiceControlManager::LockServiceDatabase( ServiceControlHandle hSCManager )
	{
		_WINQ_FCONTEXT( "CServiceControlManager::LockServiceDatabase" );
		void* pResult = m_AdvAPI32Library.LockServiceDatabase( reinterpret_cast< ::SC_HANDLE >( hSCManager ) );
		return pResult;
	}

	//--------------------------------------------------------------------------------
	bool CServiceControlManager::UnlockServiceDatabase( void* ScLock )
	{
		_WINQ_FCONTEXT( "CServiceControlManager::UnlockServiceDatabase" );
		bool bResult = m_AdvAPI32Library.UnlockServiceDatabase( ScLock ) ? true : false;
		return bResult;
	}

}//nsWin32

