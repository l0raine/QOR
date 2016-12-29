//BfPlug.cpp

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

//Implements a Bluefoot Plug base class.
//A plug is a connector between a device, file, socket or similar and either one or two pipelines

#include "BluefootQOR/BfPlug.h"
#include "BluefootQOR/BfConnectionPool.h"

//------------------------------------------------------------------------------
namespace nsBluefoot
{
	__QOR_IMPLEMENT_OCLASS_LUID( CBFPlug ); 

	//--------------------------------------------------------------------------------
	CBFPlug::CBFPlug( CBFConnectionPool* pPool ) : m_pSyncObject( 0 ), m_lRefCount( 0 ), m_pPool( pPool )
	{
		//_WINQ_FCONTEXT( "CBFPlug::CBFPlug" );
		m_bConnected = false;
	}

	//--------------------------------------------------------------------------------
	CBFPlug::~CBFPlug()
	{
		//_WINQ_FCONTEXT( "CBFPlug::~CBFPlug" );
		if( m_bConnected )
		{
			Disconnect();
		}		
		m_bConnected = false;
	}

	//--------------------------------------------------------------------------------
	void CBFPlug::Disconnect( void )
	{
	}

	//--------------------------------------------------------------------------------
	//Override for Asynchronous connections with custom pending connection states
	bool CBFPlug::HandlePendingConnectionResult( bool bConnected )
	{
		//_WINQ_FCONTEXT( "CBFPlug::HandlePendingConnectionResult" );
		return bConnected;
	}

	//--------------------------------------------------------------------------------
	void CBFPlug::OnConnected( void )
	{
		//_WINQ_FCONTEXT( "CBFPlug::OnConnected" );
		m_bConnected = true;
		if( !m_refProtocol.IsNull() )
		{
			m_refProtocol.As< CBFProtocol >()->OnConnected();
		}
	}

	//--------------------------------------------------------------------------------
	void CBFPlug::OnConnectionError( void )
	{
		//_WINQ_FCONTEXT( "CBFPlug::OnConnectionError" );
		m_bConnected = false;
		if( !m_refProtocol.IsNull() )
		{
			m_refProtocol.As< CBFProtocol >()->OnConnectionError();
		}
	}

	//--------------------------------------------------------------------------------
	void CBFPlug::OnDisconnected( void )
	{
		//_WINQ_FCONTEXT( "CBFPlug::OnDisconnected" );
		m_bConnected = false;
		if( !m_refProtocol.IsNull() )
		{
			m_refProtocol.As< CBFProtocol >()->OnDisconnected();
		}
	}

	//--------------------------------------------------------------------------------
	void CBFPlug::OnDisconnectionError( void )
	{
		//_WINQ_FCONTEXT( "CBFPlug::OnDisconnectionError" );
		m_bConnected = false;
		if( !m_refProtocol.IsNull() )
		{
			m_refProtocol.As<CBFProtocol>()->OnDisconnectionError();
		}
	}

	//--------------------------------------------------------------------------------
	bool CBFPlug::IsConnected( void )
	{
		//_WINQ_FCONTEXT( "CBFPlug::IsConnected" );
		return m_bConnected;
	}

	//--------------------------------------------------------------------------------
	const bool CBFPlug::AsyncConnection( void ) const
	{
		//_WINQ_FCONTEXT( "CBFPlug::AsyncConnection" );
		return false;
	}

	//--------------------------------------------------------------------------------
	void CBFPlug::SetConnectionProtocol( CBFProtocol::ref_type refProtocol )
	{
		//_WINQ_FCONTEXT( "CBFPlug::SetConnectionProtocol" );
		m_refProtocol = refProtocol;
	}

	//--------------------------------------------------------------------------------
	CBFProtocol::ref_type CBFPlug::Protocol( void )
	{
		//_WINQ_FCONTEXT( "CBFPlug::Protocol" );
		return m_refProtocol->Ref();
	}

	//--------------------------------------------------------------------------------
	void* CBFPlug::GetSyncObject()
	{
		//_WINQ_FCONTEXT( "CBFPlug::GetSyncObject" );
		return m_pSyncObject;
	}

	//--------------------------------------------------------------------------------
	void CBFPlug::SetSyncObject( void* pSyncObject )
	{
		//_WINQ_FCONTEXT( "CBFPlug::SetSyncObject" );
		m_pSyncObject = pSyncObject;
	}

	//--------------------------------------------------------------------------------
	CBFPlug::refPlugType CBFPlug::Ref()
	{
		refPlugType ref( this );
		return ref;
	}
	//--------------------------------------------------------------------------------
	void CBFPlug::AddRef()
	{
		m_lRefCount++;
	}

	//--------------------------------------------------------------------------------
	void CBFPlug::Release()
	{
		if( --m_lRefCount <= 0 )
		{
			if( m_pPool )
			{
				m_pPool->Release( this );
			}
		}
	}

}//nsBluefoot

