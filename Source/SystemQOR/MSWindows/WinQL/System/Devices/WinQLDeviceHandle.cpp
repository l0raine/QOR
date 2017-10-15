//WinQLDeviceHandle.cpp

// Copyright Querysoft Limited 2013, 2017
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

#include "WinQL/CodeServices/WinQLPolicy.h"
#include "WinQL/Application/Threading/WinQLCriticalSection.h"
#include "WinQL/Application/ErrorSystem/WinQLError.h"
#include "WinQL/System/Devices/WinQLDeviceHandle.h"
#include "WinQL/Application/Threading/WinQLThread.h"
#include "WinQL/Application/Resources/WinQLResourceManager.h"
#include "WinQAPI/Kernel32.h"

//--------------------------------------------------------------------------------
namespace nsWin32
{
	using namespace nsWinQAPI;

	__QOR_IMPLEMENT_OCLASS_LUID( CDeviceHandle );

	//--------------------------------------------------------------------------------
	CDeviceHandle::CDeviceHandle() : CHandle( 0 )
	{
		_WINQ_FCONTEXT( "CDeviceHandle::CDeviceHandle" );
	}

	//--------------------------------------------------------------------------------
	CDeviceHandle::CDeviceHandle( void* h ) : CHandle( h )
	{
		_WINQ_FCONTEXT( "CDeviceHandle::CDeviceHandle" );
	}

	//--------------------------------------------------------------------------------
	CDeviceHandle::CDeviceHandle( int h ) : CHandle( h )
	{
		_WINQ_FCONTEXT( "CDeviceHandle::CDeviceHandle" );
	}

	//--------------------------------------------------------------------------------
	CDeviceHandle::CDeviceHandle( const CDeviceHandle& src ) : CHandle( src.ptr() )
	{
		_WINQ_FCONTEXT( "CDeviceHandle::CDeviceHandle" );
	}

	//--------------------------------------------------------------------------------
	CDeviceHandle::CDeviceHandle(CDeviceHandle&& move) : CHandle(std::move(move.ptr()))
	{
		_WINQ_FCONTEXT("CDeviceHandle::CDeviceHandle");
	}

	//--------------------------------------------------------------------------------
	CDeviceHandle& CDeviceHandle::operator = ( const CDeviceHandle& src )
	{
		_WINQ_FCONTEXT( "CDeviceHandle::operator =" );

		if( &src != this )
		{
			m_h = src.ptr();
		}

		return *this;
	}

	//--------------------------------------------------------------------------------
	CDeviceHandle& CDeviceHandle::operator = ( CDeviceHandle&& move)
	{
		_WINQ_FCONTEXT("CDeviceHandle::operator =");

		if (&move != this)
		{
			m_h = move.ptr();
			move.m_h = 0;
		}

		return *this;
	}

	//--------------------------------------------------------------------------------
	CDeviceHandle::~CDeviceHandle()
	{
		_WINQ_FCONTEXT( "CDeviceHandle::~CDeviceHandle" );
		Close();
	}

	//--------------------------------------------------------------------------------
	void* CDeviceHandle::Use() const
	{
		_WINQ_FCONTEXT( "CDeviceHandle::Use" );
		return ptr();
	}


	__QOR_IMPLEMENT_OCLASS_LUID(CStdHandle);

	//--------------------------------------------------------------------------------
	CStdHandle::CStdHandle(void* h) : CDeviceHandle(h)
	{
		_WINQ_FCONTEXT("CStdHandle::CStdHandle");
	}

	//--------------------------------------------------------------------------------
	CStdHandle::CStdHandle(unsigned long nStdHandle) : CDeviceHandle( CKernel32::GetStdHandle( nStdHandle ))
	{
		_WINQ_FCONTEXT("CStdHandle::CStdHandle");
	}
	
	//--------------------------------------------------------------------------------
	CStdHandle::CStdHandle(const CStdHandle& src) : CDeviceHandle( src.ptr() )
	{
		_WINQ_FCONTEXT("CStdHandle::CStdHandle");
	}

	//--------------------------------------------------------------------------------
	CStdHandle::CStdHandle(CStdHandle&& move) : CDeviceHandle(std::move(move.ptr()))
	{
		_WINQ_FCONTEXT("CStdHandle::CStdHandle");
	}

	//--------------------------------------------------------------------------------
	CStdHandle& CStdHandle::operator = (const CStdHandle& src)
	{
		_WINQ_FCONTEXT("CStdHandle::operator =");

		if (&src != this)
		{
			m_h = src.ptr();
		}

		return *this;
	}

	//--------------------------------------------------------------------------------
	CStdHandle& CStdHandle::operator = (CStdHandle&& move)
	{
		_WINQ_FCONTEXT("CStdHandle::operator =");

		if (&move != this)
		{
			m_h = move.ptr();
			move.m_h = 0;
		}

		return *this;
	}
	
	//--------------------------------------------------------------------------------
	CStdHandle::~CStdHandle()
	{	
		_WINQ_FCONTEXT("CStdHandle::~CStdHandle");
		m_h = nullptr; //Don't close, nullify, as it's a Standard Handle
	}

}//nsWin32
