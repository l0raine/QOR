//WinQLPipeSink.cpp

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

#include "WinQL/Application/IO/Pipe/WinQLPipeSink.h"
#include "WinQL/Application/IO/Pipe/WinQLPipeConnector.h"

//--------------------------------------------------------------------------------
namespace nsWin32
{

	__QOR_IMPLEMENT_OCLASS_LUID( CPipeSink );

	//--------------------------------------------------------------------------------
	CPipeSink::CPipeSink(  CPipeConnector* pPipeConnector ) : CIOSink( pPipeConnector )
	{
		_WINQ_FCONTEXT( "CPipeSink::CPipeSink" );
	}

	//--------------------------------------------------------------------------------
	CPipeSink::~CPipeSink()
	{
		_WINQ_FCONTEXT( "CPipeSink::~CPipeSink" );
	}

	//--------------------------------------------------------------------------------
	bool CPipeSink::Write( unsigned long& ulNumberOfUnitsWritten, unsigned long ulNumberOfUnitsToWrite)
	{
		_WINQ_FCONTEXT( "CPipeSink::Write" );
		bool bResult = false;
		CPipeConnector* pPipeConnector = dynamic_cast< CPipeConnector* >( m_pIOSinkConnector );
		if( pPipeConnector && pPipeConnector->IsConnected() )
		{			
			byte* pBuffer = GetSource()->GetBuffer()->ReadRequest(ulNumberOfUnitsToWrite);
			unsigned long ulUnitSize = GetSource()->GetBuffer()->GetUnitSize();
			if( pPipeConnector->AsyncConnection() )
			{
				bResult = pPipeConnector->Pipe().Write( (const void*)(pBuffer), ulNumberOfUnitsToWrite * ulUnitSize,
					reinterpret_cast< OVERLAPPED* >( pPipeConnector->GetSyncObject() ), (LPOVERLAPPED_COMPLETION_ROUTINE)(&COverlappedHandler::OnOverlappedWriteCompleted) );
				ulNumberOfUnitsWritten = 0;

				if( !bResult )
				{
					WriteError.Signal();
				}

			}
			else
			{
				bResult = pPipeConnector->Pipe().Write( (const void*)(pBuffer), ulNumberOfUnitsToWrite * ulUnitSize, ulNumberOfUnitsWritten, 0 );
				if (bResult && (ulNumberOfUnitsWritten > 0))
				{
					ulNumberOfUnitsWritten /= ulUnitSize;
				}
				GetSource()->GetBuffer()->ReadAcknowledge(ulNumberOfUnitsWritten);

				bResult ? WriteSuccess.Signal() : WriteError.Signal();
			}
		}
		return bResult;
	}

	//--------------------------------------------------------------------------------
	bool CPipeSink::Flush( void )
	{
		_WINQ_FCONTEXT( "CPipeSink::Flush" );
		bool bResult = true;
		CPipeConnector* pPipeConnector = dynamic_cast< CPipeConnector* >( m_pIOSinkConnector );
		if( pPipeConnector && pPipeConnector->IsConnected() )
		{
			bResult = pPipeConnector->Pipe().Flush();
		}
		return bResult;
	}

}//nsWin32


