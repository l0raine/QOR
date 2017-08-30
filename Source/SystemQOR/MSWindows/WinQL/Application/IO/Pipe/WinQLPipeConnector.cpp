//WinQLPipeConnector.cpp

// Copyright Querysoft Limited 2013, 2016, 2017
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

#include "WinQL/Application/IO/Pipe/WinQLPipeConnector.h"
#include "WinQL/Application/Threading/WinQLEvent.h"

//--------------------------------------------------------------------------------
namespace nsWin32
{
	__QOR_IMPLEMENT_OCLASS_LUID( CPipeConnector );

	//--------------------------------------------------------------------------------
	CPipeConnector::CPipeConnector( nsBluefoot::CConnectionPool* pPool ) : nsBluefoot::CPlug( pPool )
	{
		_WINQ_FCONTEXT( "CPipeConnector::CPipeConnector" );
		m_pSecurity = 0;
		m_strServerName = CTString( _TXT( "." ) );
		m_ulAccess = nsWin32::Generic_Read | nsWin32::Generic_Write;
		m_ulShareMode = 0;
		m_ulFlags = 0;
		m_ulConnectionTimeout = DefaultClientConnectionTimeout;
	}

	//--------------------------------------------------------------------------------
	CPipeConnector::~CPipeConnector()
	{
		_WINQ_FCONTEXT( "CPipeConnector::~CPipeConnector" );
		if( m_bConnected )
		{
			Disconnect();
		}		
	}

	//--------------------------------------------------------------------------------
	void CPipeConnector::SetConnectionTimeout( unsigned long ulTimeoutMilliseconds )
	{
		_WINQ_FCONTEXT( "CPipeConnector::SetConnectionTimeout" );
		m_ulConnectionTimeout = ulTimeoutMilliseconds;
	}

	//--------------------------------------------------------------------------------
	unsigned long CPipeConnector::GetConnectionTimeout( void )
	{
		_WINQ_FCONTEXT( "CPipeConnector::GetConnectionTimeout" );
		return m_ulConnectionTimeout;
	}

	//--------------------------------------------------------------------------------
	bool CPipeConnector::Connect()
	{
		_WINQ_FCONTEXT( "CPipeConnector::Connect" );

		unsigned long ulError = 0;
		CTime Time;
		unsigned long ulInitialTickCount = Time.GetTickCount();
		do
		{
			m_bConnected = m_Pipe.Open( m_strServerName, m_strPipeName, m_ulAccess, m_ulShareMode, m_pSecurity, m_ulFlags );

			if( !m_bConnected )
			{
				ulError = m_ErrorHelper.GetLastError();
			}

		}while( !m_bConnected && ( ulError == nsWin32::ErrorPipeBusy ) && ( ( Time.GetTickCount() - ulInitialTickCount ) < m_ulConnectionTimeout ) );

		if( !AsyncConnection() )
		{
			m_bConnected ? OnConnected() : OnConnectionError();
		}
		return m_bConnected;
	}

	//--------------------------------------------------------------------------------
	void CPipeConnector::Disconnect()
	{
		_WINQ_FCONTEXT( "CPipeConnector::Disconnect" );
		bool bClosed = m_Pipe.Close();
		m_bConnected = false;
		if( !AsyncConnection() )
		{
			bClosed ? OnDisconnected() : OnDisconnectionError();
		}
	}

	//--------------------------------------------------------------------------------
	bool CPipeConnector::HandlePendingConnectionResult( bool bConnected )
	{
		_WINQ_FCONTEXT( "CPipeConnector::HandlePendingConnectionResult" );

		bool bPendingIO = false;

		// Overlapped ConnectNamedPipe should return zero. 
		if( bConnected ) 
		{
			//printf("ConnectNamedPipe failed with %d.\n", GetLastError()); 
			return false;
		}

		switch( m_ErrorHelper.GetLastError() ) 
		{ 
		// The overlapped connection in progress. 
		case ErrorIOPending: 
			bPendingIO = true; 
			break; 
   
		// Client is already connected, so signal an event.    
		case ErrorPipeConnected: 
			{
				OVERLAPPED* pOverlapped = reinterpret_cast< OVERLAPPED* >( GetSyncObject() );
				CSyncHandle tmpHandle( pOverlapped->hEvent, true ); 
				CEvent tmpEvent( tmpHandle );
				if( tmpEvent.Set() ) 
				{
					tmpHandle.Drop();
					break; 
				}
			}   
		// If an error occurs during the connect operation... 
		default: 
			{
				//printf("ConnectNamedPipe failed with %d.\n", GetLastError());
				return false;
			}
		} 

		return bPendingIO;		
	}

	//--------------------------------------------------------------------------------
	void CPipeConnector::SetServerName( CTString& strServerName )
	{
		_WINQ_FCONTEXT( "CPipeConnector::SetServerName" );
		m_strServerName = strServerName;
	}

	//--------------------------------------------------------------------------------
	void CPipeConnector::SetPipeName( CTString& strPipeName )
	{
		_WINQ_FCONTEXT( "CPipeConnector::SetPipeName" );
		m_strPipeName = strPipeName;
	}

	//--------------------------------------------------------------------------------
	void CPipeConnector::SetDesiredAccess( unsigned long ulDesiredAccess )
	{
		_WINQ_FCONTEXT( "CPipeConnector::SetDesiredAccess" );
		m_ulAccess = ulDesiredAccess;
	}

	//--------------------------------------------------------------------------------
	void CPipeConnector::SetShareMode( unsigned long ulShareMode )
	{
		_WINQ_FCONTEXT( "CPipeConnector::SetShareMode" );
		m_ulShareMode = ulShareMode;
	}

	//--------------------------------------------------------------------------------
	void CPipeConnector::SetFlags( unsigned long ulFlags )
	{
		_WINQ_FCONTEXT( "CPipeConnector::SetFlags" );
		m_ulFlags = ulFlags;
	}

	//--------------------------------------------------------------------------------
	void CPipeConnector::SetSecurity( SECURITY_ATTRIBUTES* pSecurity )
	{
		_WINQ_FCONTEXT( "CPipeConnector::SetSecurity" );
		m_pSecurity = pSecurity;
	}

	//--------------------------------------------------------------------------------
	CTString CPipeConnector::GetServerName( void )
	{
		_WINQ_FCONTEXT( "CPipeConnector::GetServerName" );
		return m_strServerName;
	}

	//--------------------------------------------------------------------------------
	unsigned long CPipeConnector::GetAccessMode( void )
	{
		_WINQ_FCONTEXT( "CPipeConnector::GetAccessMode" );
		return m_ulAccess;
	}

	//--------------------------------------------------------------------------------
	unsigned long CPipeConnector::GetShareMode( void )
	{
		_WINQ_FCONTEXT( "CPipeConnector::GetShareMode" );
		return m_ulShareMode;
	}

	//--------------------------------------------------------------------------------
	unsigned long CPipeConnector::GetFlags( void )
	{
		_WINQ_FCONTEXT( "CPipeConnector::GetFlags" );
		return m_ulFlags;
	}

	//--------------------------------------------------------------------------------
	SECURITY_ATTRIBUTES* CPipeConnector::GetSecurity( void )
	{
		_WINQ_FCONTEXT( "CPipeConnector::GetSecurity" );
		return m_pSecurity;
	}

}//nsWin32


