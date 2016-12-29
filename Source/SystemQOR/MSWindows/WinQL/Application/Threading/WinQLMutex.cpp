//WinQLMutex.cpp

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
#include "WinQL/Application/Threading/WinQLMutex.h"
#include "WinQAPI/Kernel32.h"

//------------------------------------------------------------------------------
namespace nsWin32
{
	using namespace nsWinQAPI;

	// {DA1D30A7-B50E-4C52-8124-F60244407540}
	__QOR_IMPLEMENT_OCLASS_GUID( CMutex, 0xda1d30a7, 0xb50e, 0x4c52, 0x81, 0x24, 0xf6, 0x2, 0x44, 0x40, 0x75, 0x40 );

	//--------------------------------------------------------------------------------
	CMutex::CMutex( unsigned long dwFlags, nsWin32::LPSECURITY_ATTRIBUTES lpMutexAttributes, unsigned long dwDesiredAccess, const TCHAR* lpName, bool* pbAlreadyExists )
	{
		_WINQ_FCONTEXT( "CMutex::CMutex" );
		__QOR_PROTECT
		{
			static DWORD dwMajorVersion = ( DWORD )( LOBYTE( LOWORD( CKernel32::GetVersion() ) ) );
			bool bAlreadyExists = false;
			m_bInitialOwnership = ( dwFlags & CREATE_MUTEX_INITIAL_OWNER );
			m_bOpenClose = false;
#			if ( _WIN32_WINNT >= 0x0600 )
			if( dwMajorVersion >= 6 )
			{
				m_h = CKernel32::CreateMutexEx( reinterpret_cast< ::LPSECURITY_ATTRIBUTES >( lpMutexAttributes ), lpName, dwFlags, dwDesiredAccess, bAlreadyExists );
			}
			else
			{
#			else
			QOR_PP_UNREF( dwDesiredAccess );
#			endif
			m_h = CKernel32::CreateMutex( reinterpret_cast< ::LPSECURITY_ATTRIBUTES >( lpMutexAttributes ), m_bInitialOwnership ? TRUE : FALSE, lpName, bAlreadyExists );
#			if ( _WIN32_WINNT >= 0x0600 )
			}
#			endif
			if( pbAlreadyExists != 0 )
			{
				*pbAlreadyExists = bAlreadyExists;
			}

			if( bAlreadyExists || !m_bInitialOwnership )
			{
				m_bOpenClose = true;
			}

		}__QOR_ENDPROTECT
	}

	//--------------------------------------------------------------------------------
	CMutex::CMutex( const TCHAR* lpName, unsigned long dwDesiredAccess, bool bInheritHandle )
	{
		_WINQ_FCONTEXT( "CMutex::CMutex" );
		__QOR_PROTECT
		{
			m_h = CKernel32::OpenMutex( dwDesiredAccess, bInheritHandle ? TRUE : FALSE, lpName );
			if( m_h != 0 )
			{
				m_bOpenClose = true;
			}
		}__QOR_ENDPROTECT
	}

	//--------------------------------------------------------------------------------
	CMutex::~CMutex()
	{
		_WINQ_FCONTEXT( "CMutex::~CMutex" );
		__QOR_PROTECT
		{
			if( m_bInitialOwnership )
			{
				Release();
			}
			if( m_bOpenClose )
			{
				CKernel32::CloseHandle( m_h );
			}
		}__QOR_ENDPROTECT
	}

	//--------------------------------------------------------------------------------
	bool CMutex::Release()
	{
		_WINQ_FCONTEXT( "CMutex::Release" );
		bool bResult = false;
		__QOR_PROTECT
		{
			bResult = CKernel32::ReleaseMutex( m_h ) ? true : false;
		}__QOR_ENDPROTECT
		return bResult;
	}

	//protected:

	//--------------------------------------------------------------------------------
	const void* CMutex::Handle() const
	{
		_WINQ_FCONTEXT( "CMutex::Handle" );
		return m_h;
	}

	// {4009FD75-F03A-4A75-B840-77863AB3487F}
	__QOR_IMPLEMENT_OCLASS_GUID( CMutexLock, 0x4009fd75, 0xf03a, 0x4a75, 0xb8, 0x40, 0x77, 0x86, 0x3a, 0xb3, 0x48, 0x7f )

	//--------------------------------------------------------------------------------
	CMutexLock::CMutexLock( CMutex& Mutex, unsigned long dwTimeout /*= 0xFFFFFFFF*/, unsigned long* pdwResult /*= 0*/ ) : m_Mutex( Mutex )
	{
		_WINQ_FCONTEXT( "CMutexLock::CMutexLock" );
		__QOR_PROTECT
		{
			//nsWin32::nsSync::CWaitHelper WaitHelper;
			unsigned long dwResult = 0;//WaitHelper.WaitForSingleObject( const_cast< void* >( m_Mutex.Handle() ), dwTimeout );

			if( pdwResult != 0 )
			{
				*pdwResult = dwResult;
			}
		}__QOR_ENDPROTECT
	}

	//--------------------------------------------------------------------------------
	CMutexLock::~CMutexLock()
	{
		_WINQ_FCONTEXT( "CMutexLock::~CMutexLock" );
		m_Mutex.Release();
	}

	// {CCD29EDD-AF31-4B0F-A379-8678A0C1A593}
	__QOR_IMPLEMENT_OCLASS_GUID( CLock, 0xccd29edd, 0xaf31, 0x4b0f, 0xa3, 0x79, 0x86, 0x78, 0xa0, 0xc1, 0xa5, 0x93 )

	//--------------------------------------------------------------------------------
	CLock::CLock( SECURITY_ATTRIBUTES* pMutexAttributes /*= 0*/, unsigned long dwFlags /*= 0*/, unsigned long dwDesiredAccess /*= 0*/, unsigned long* pdwResult /*= 0*/, unsigned long dwTimeout /*= Infinite*/ ) :
	m_Mutex( dwFlags, pMutexAttributes, dwDesiredAccess )
	{
		_WINQ_FCONTEXT( "CLock::CLock" );
		unsigned long dwResult = 0;//m_Mutex.Wait( dwTimeout );
		if( pdwResult != 0 )
		{
			*pdwResult = dwResult;
		}
	}

	//--------------------------------------------------------------------------------
	CLock::~CLock()
	{
		_WINQ_FCONTEXT( "CLock::~CLock" );
		m_Mutex.Release();
	}

}//nsWin32
