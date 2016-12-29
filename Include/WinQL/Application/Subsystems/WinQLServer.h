//WinQLServer.h

// Copyright Querysoft Limited 2016
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

//WinQL Server Subsystem

#ifndef WINQL_SUBSYS_SERVER_H_1
#define WINQL_SUBSYS_SERVER_H_1

#include "CompilerQOR.h"

#ifdef	__QCMP_OPTIMIZEINCLUDE
#pragma	__QCMP_OPTIMIZEINCLUDE
#endif//__QCMP_OPTIMIZEINCLUDE

#include "AppocritaQOR/Application.h"
#include "AppocritaQOR/SubSystem.h"
#include "BluefootQOR/BfConnectionPool.h"
#include "WinQL/CodeServices/Handles/WinQLHandle.h"
#include "WinQL/Application/Threading/WinQLCriticalSection.h"
#include "WinQL/Application/Threading/WinQLSynchronization.h"
#include "WinQL/Application/ErrorSystem/WinQLErrorHandling.h"
#include "WinQL/Application/Threading/WinQLEvent.h"

//--------------------------------------------------------------------------------
namespace nsWin32
{
	class __QOR_INTERFACE( __WINQL ) CWin32Application;
	class __QOR_INTERFACE( __WINQL ) CServer;

	//--------------------------------------------------------------------------------
	class __QOR_INTERFACE( __WINQL ) CServerEvent : public CEvent
	{
	public:

		CServerEvent( CServer& Server, SECURITY_ATTRIBUTES* lpEventAttributes = 0, const TCHAR* lpName = 0, unsigned long dwFlags = 0, unsigned long dwDesiredAccess = 0, bool* pbAlreadyExists = 0 );
		virtual ~CServerEvent();
		virtual void OnSignaled( void );

	protected:

		CServer& m_Server;
	};

	//--------------------------------------------------------------------------------
	class __QOR_INTERFACE( __WINQL ) CServer : public nsQOR::CSubSystem
	{
	public:

		__QOR_DECLARE_OCLASS_ID( CServer );

		__QOR_IMPL_REF( CServer );

		static nsCodeQOR::CTExternalRegEntry< CServer > RegEntry;

		CServer();
		~CServer();

		virtual void Setup( nsQOR::IApplication& Applicaton );
		virtual void Shutdown( nsQOR::IApplication& Application );

		virtual void SetupConnection( nsBluefoot::CBFPlug::refPlugType& refConnector );		//override to set device specific properties for the Connector
		virtual nsBluefoot::CBFPlug::refPlugType CreateConnection( void );					//override to create new device specific pending client connections
		virtual bool OnListenResult( bool );												//override to custom process listen result 
		virtual bool Listen( void );														//override to customize Servers listen for new client connections		
		virtual void Stop( void );															//call to break main loop on next event

		void SetConnectionPool( nsBluefoot::CBFConnectionPool::refType refConnectionPool );	//Attach a connection pool to allow the server to request new connections from a pool
		nsBluefoot::CBFConnectionPool::refType GetConnectionPool( void );

		void OnSignaled( void );

	protected:

		bool m_bPendingIO;																	//Is IO pending
		CServerEvent m_ConnectEvent;														//Event for signalling connections
		OVERLAPPED m_Overlapped;															//Windows sync object for handling async connections
		CErrorHelper m_ErrorHelper;

		nsBluefoot::CBFPlug::refPlugType m_refPendingIOConnection;							//Precreated connection for the next client
		nsBluefoot::CBFConnectionPool::refType m_refConnectionPool;							//Connection pool from which to source connections

		nsQOR::CApplication::ref_type m_Application;

	};

}//nsWin32

#endif//WINQL_SUBSYS_SERVER_H_1
