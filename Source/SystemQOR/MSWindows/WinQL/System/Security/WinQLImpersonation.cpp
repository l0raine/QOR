//WinQLImpersonation.cpp

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

#include "WinQL/Application/ErrorSystem/WinQLError.h"
#include "WinQL/System/Security/WinQLImpersonation.h"
#include "WinQL/Application/Threading/WinQLThread.h"
#include "WinQAPI/AdvAPI32.h"

using namespace nsWinQAPI;

//--------------------------------------------------------------------------------
namespace nsWin32
{
	__QOR_IMPLEMENT_OCLASS_LUID( CImpersonationSession );

	//--------------------------------------------------------------------------------
	CImpersonationSession::CImpersonationSession() : m_AdvAPI32Library( CAdvAPI32::Instance() )
	{
		_WINQ_FCONTEXT( "CImpersonationSession::CImpersonationSession" );
		m_bInSession = false;
	}

	//--------------------------------------------------------------------------------
	CImpersonationSession::~CImpersonationSession()
	{
		_WINQ_FCONTEXT( "CImpersonationSession::~CImpersonationSession" );
		if( m_bInSession )
		{
			__QOR_PROTECT
			{
				m_AdvAPI32Library.RevertToSelf();
			}__QOR_ENDPROTECT
		}
	}

			
	//--Self Impersonation Session----------------------------------------------------

	__QOR_IMPLEMENT_OCLASS_LUID( CSelfImpersonationSession );

	//--------------------------------------------------------------------------------
	CSelfImpersonationSession::CSelfImpersonationSession( nsWin32::SECURITY_IMPERSONATION_LEVEL ImpersonationLevel ) : CImpersonationSession()
	{
		_WINQ_FCONTEXT( "CSelfImpersonationSession::CSelfImpersonationSession" );
		__QOR_PROTECT
		{
			m_bInSession = m_AdvAPI32Library.ImpersonateSelf( static_cast< ::SECURITY_IMPERSONATION_LEVEL >( ImpersonationLevel ) ) ? true : false;
		}__QOR_ENDPROTECT
	}

	//--------------------------------------------------------------------------------
	CSelfImpersonationSession::~CSelfImpersonationSession()
	{
		_WINQ_FCONTEXT( "CSelfImpersonationSession::~CSelfImpersonationSession" );
	}


	//--Named Pipe Client Impersonation Session---------------------------------------

	__QOR_IMPLEMENT_OCLASS_LUID( CNamedPipeClientImpersonationSession );

	//--------------------------------------------------------------------------------
	CNamedPipeClientImpersonationSession::CNamedPipeClientImpersonationSession( void* hNamedPipe ) : CImpersonationSession()
	{
		_WINQ_FCONTEXT( "CNamedPipeClientImpersonationSession::CNamedPipeClientImpersonationSession" );
		__QOR_PROTECT
		{
			m_bInSession = m_AdvAPI32Library.ImpersonateNamedPipeClient( hNamedPipe ) ? true : false;
		}__QOR_ENDPROTECT
	}

	//--------------------------------------------------------------------------------
	CNamedPipeClientImpersonationSession::~CNamedPipeClientImpersonationSession()
	{
		_WINQ_FCONTEXT( "CNamedPipeClientImpersonationSession::~CNamedPipeClientImpersonationSession" );
	}


	//--Logged On User Impersonation Session---------------------------------------

	__QOR_IMPLEMENT_OCLASS_LUID( CLoggedOnUserImpersonationSession );

	//--------------------------------------------------------------------------------
	CLoggedOnUserImpersonationSession::CLoggedOnUserImpersonationSession( CHandle& hToken ) : CImpersonationSession()
	{
		_WINQ_FCONTEXT( "CLoggedOnUserImpersonationSession::CLoggedOnUserImpersonationSession" );
		__QOR_PROTECT
		{
			m_bInSession = m_AdvAPI32Library.ImpersonateLoggedOnUser( hToken.Use() ) ? true : false;
		}__QOR_ENDPROTECT
	}

	//--------------------------------------------------------------------------------
	CLoggedOnUserImpersonationSession::~CLoggedOnUserImpersonationSession()
	{
		_WINQ_FCONTEXT( "CLoggedOnUserImpersonationSession::~CLoggedOnUserImpersonationSession" );
	}


	//--Anonymous Impersonation Session---------------------------------------

	__QOR_IMPLEMENT_OCLASS_LUID( CAnonymousImpersonationSession );

	//--------------------------------------------------------------------------------
	CAnonymousImpersonationSession::CAnonymousImpersonationSession( CThread& Thread ) : CImpersonationSession()
	{
		_WINQ_FCONTEXT( "CAnonymousImpersonationSession::CAnonymousImpersonationSession" );
		__QOR_PROTECT
		{
			m_bInSession = m_AdvAPI32Library.ImpersonateAnonymousToken( Thread.Handle()->Use() ) ? true : false;
		}__QOR_ENDPROTECT
	}

	//--------------------------------------------------------------------------------
	CAnonymousImpersonationSession::~CAnonymousImpersonationSession()
	{
		_WINQ_FCONTEXT( "CAnonymousImpersonationSession::~CAnonymousImpersonationSession" );
	}

}//nsWin32