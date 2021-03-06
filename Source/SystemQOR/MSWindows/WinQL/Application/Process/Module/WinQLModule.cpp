//WinQLModule.cpp

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

//Windows Module 

#include "WinQL/Application/ErrorSystem/WinQLError.h"
#include "WinQL/Application/Process/Module/WinQLModule.h"
#include "WinQAPI/Kernel32.h"

//--------------------------------------------------------------------------------
namespace nsWin32
{
	using namespace nsWinQAPI;

	CWinModuleHandleMap* p_WinModuleHandleMap = 0;

	__QOR_IMPLEMENT_OCLASS_LUID( CWinModule );

	//------------------------------------------------------------------------------
	void CWinModule::Init( void )
	{
		_WINQ_FCONTEXT( "CWinModule::Init" );
		CWinModuleHandleMap* pMap = p_WinModuleHandleMap;

		if( pMap == 0 )
		{
			pMap = new CWinModuleHandleMap;
		}

		if( !( m_Handle.IsNull() ) )
		{
			pMap->Add( m_Handle, this );
		}
		else

		if( p_WinModuleHandleMap == 0 )
		{
			p_WinModuleHandleMap = pMap;
		}
	}

	//------------------------------------------------------------------------------
	void CWinModule::Uninit( void )
	{
		_WINQ_FCONTEXT( "CWinModule::Uninit" );
		if( p_WinModuleHandleMap && !( m_Handle.IsNull() ) )
		{
			p_WinModuleHandleMap->Remove( m_Handle );
		}
	}

	//------------------------------------------------------------------------------
	CWinModule::CWinModule() : m_Handle( 0 )
	{
		_WINQ_FCONTEXT( "CWinModule::CWinModule" );
		m_Handle.Attach( this );
	}

	//--------------------------------------------------------------------------------
	CWinModule::CWinModule( void* pHandle ) : m_Handle( pHandle )
	{
		_WINQ_FCONTEXT( "CWinModule::CWinModule" );
		m_Handle.Attach( this );
	}

	//--------------------------------------------------------------------------------
	CWinModule::CWinModule( CHandle& hModule ) : m_Handle( hModule.ptr() )
	{
		_WINQ_FCONTEXT( "CWinModule::CWinModule" );
		m_Handle.Attach( this );
	}

	//--------------------------------------------------------------------------------
	CWinModule::CWinModule( const CWinModule& src ) : m_Handle( src.m_Handle.ptr() )
	{
		_WINQ_FCONTEXT( "CWinModule::CWinModule" );
		m_Handle.Attach( this );
	}

	//--------------------------------------------------------------------------------
	CWinModule& CWinModule::operator = ( const CWinModule& src )
	{
		_WINQ_FCONTEXT( "CWinModule::operator=" );
		*(m_Handle.pptr()) = src.m_Handle.ptr();
		m_Handle.Attach( this );
		return *this;
	}

	//--------------------------------------------------------------------------------
	CWinModule::~CWinModule()
	{
		_WINQ_FCONTEXT( "CWinModule::~CWinModule" );
	}

	//--------------------------------------------------------------------------------
	CHandle& CWinModule::ModuleHandle( void )
	{
		_WINQ_FCONTEXT( "CWinModule::ModuleHandle" );
		return m_Handle;
	}


	//--------------------------------------------------------------------------------
	CWinModule* CWinModule::FromHandle( CHandle hModule )
	{
		_WINQ_SFCONTEXT( "CWinModule::FromHandle" );
		CWinModule* pResult = 0;
			
		__QOR_PROTECT
		{
			pResult = reinterpret_cast< CWinModule* >( hModule.Object() );

			if( pResult == 0 && p_WinModuleHandleMap != 0 )
			{
				pResult = p_WinModuleHandleMap->FindHandle( hModule );
			}

		}__QOR_ENDPROTECT

		return pResult;
	}

}//nsWin32
