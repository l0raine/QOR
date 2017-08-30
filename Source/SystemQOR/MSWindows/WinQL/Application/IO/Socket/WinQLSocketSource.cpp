//WinQLSocketSource.cpp

// Copyright Querysoft Limited 2013, 2016
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

#include "WinQL/Application/IO/Socket/WinQLSocketSource.h"
#include "WinQL/Application/IO/Socket/WinQLSocketConnector.h"
#include "WinQL/Application/IO/WinQLIOSink.h"
#include "WinQL/Application/ErrorSystem/WinQLFunctionContext.h"

//--------------------------------------------------------------------------------
namespace nsWin32
{

	__QOR_IMPLEMENT_OCLASS_LUID( CSocketSource );

	//--------------------------------------------------------------------------------
	CSocketSource::CSocketSource( CSocketConnector* pSocketConnector ) : CIOSource( pSocketConnector )
	{
		_WINQ_FCONTEXT( "CSocketSource::CSocketSource" );
	}

	//--------------------------------------------------------------------------------
	CSocketSource::~CSocketSource()
	{
		_WINQ_FCONTEXT( "CSocketSource::~CSocketSource" );
	}

	//--------------------------------------------------------------------------------
	bool CSocketSource::Read( unsigned long ulUnitSize )
	{
		_WINQ_FCONTEXT( "CSocketSource::Read" );

		unsigned long ulNumberOfUnitsToRead = m_pBuffer->WriteCapacity();
		unsigned long ulNumberOfUnitsRead = 0;
		return ulNumberOfUnitsToRead == 0 ? false : Read( ulNumberOfUnitsToRead, ulNumberOfUnitsRead, ulUnitSize );
	}

	//--------------------------------------------------------------------------------
	bool CSocketSource::Read( unsigned long ulNumberOfUnitsToRead, unsigned long& ulNumberOfUnitsRead, unsigned long ulUnitSize )
	{
		_WINQ_FCONTEXT( "CSocketSource::Read" );
		bool bResult = false;
		CSocketConnector* pSocketConnector = dynamic_cast< CSocketConnector* >( m_pIOSourceConnector );
		if( pSocketConnector && pSocketConnector->IsConnected() )
		{
			byte* pBuffer = m_pBuffer->WriteRequest( ulNumberOfUnitsToRead );
			WSABuf WSABuffer;
			WSABuffer.buf = reinterpret_cast< char* >( pBuffer );
			WSABuffer.len = ulNumberOfUnitsToRead * ulUnitSize;
			unsigned long ulFlags = 0;

			if( pSocketConnector->AsyncConnection() )
			{				
				int iResult = pSocketConnector->Socket().Receive( &WSABuffer, 1, 0, &ulFlags, reinterpret_cast< OVERLAPPED* >( pSocketConnector->GetSyncObject() ),
					reinterpret_cast< fpWSAOverlappedCompletionRoutine >( &COverlappedHandler::OnOverlappedSocketReadCompleted ) ); 

				bResult = ( iResult == 0 ? true : false );

				if( !bResult && pSocketConnector->Protocol() )
				{
					unsigned long ulLastError = pSocketConnector->Socket().GetLastError();
					pSocketConnector->Protocol().As<nsBluefoot::CProtocol>()->OnReadError();
				}
			}
			else
			{				
				if( pSocketConnector->Socket().Receive( &WSABuffer, 1, &ulNumberOfUnitsRead, &ulFlags, 0 , 0 ) == 0 )
				{
					ulNumberOfUnitsRead /= ulUnitSize;
					m_pBuffer->WriteAcknowledge( ulNumberOfUnitsRead );
					if( ulNumberOfUnitsRead > 0 )
					{
						unsigned long ulNumberOfUnitsWritten = 0;
						//m_pSink->Write( ulNumberOfUnitsRead, ulNumberOfUnitsWritten, m_pBuffer->ReadRequest( ulNumberOfUnitsRead ), ulUnitSize );
						m_pBuffer->ReadAcknowledge( ulNumberOfUnitsWritten );
						bResult = true;
					}
					else
					{
						bResult = false;
					}
				}

				if( pSocketConnector->Protocol() )
				{
					if( bResult )
					{
						pSocketConnector->Protocol().As<nsBluefoot::CProtocol>()->OnReadSuccess( ulNumberOfUnitsRead );
					}
					else
					{
						pSocketConnector->Protocol().As<nsBluefoot::CProtocol>()->OnReadError();
					}
				}
			}
		}
		return bResult;
	}

	//--------------------------------------------------------------------------------
	bool CSocketSource::IsAtEnd( void )
	{
		_WINQ_FCONTEXT( "CSocketSource::IsAtEnd" );
		bool bResult = false;
		return bResult;
	}

}//nsWin32


