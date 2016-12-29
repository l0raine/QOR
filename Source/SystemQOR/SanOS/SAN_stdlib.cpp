//SAN_stdlib.cpp

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

#include "SystemQOR.h"

#if		(QOR_SYS_OS == QOR_SYS_SANOS)

#include "SystemQOR/SanOS/SAN_stdlib.h"
#include "SystemQOR/SharedBootStrap.h"
#include "SanQL/CodeServices/Process.h"

//--------------------------------------------------------------------------------
namespace nsSanOS
{
	//--------------------------------------------------------------------------------
	__QOR_INTERFACE( __QSYS )  int MBCurMax( void )
	{
		return 1;
	}
	/*
	//--------------------------------------------------------------------------------
	__QOR_INTERFACE( __QSYS ) int MBCurMax_l( locale_t l )
	{
		return 1;//TODO: Fix this
	}
	*/
	__QOR_IMPLEMENT_OCLASS_LUID( Cstdlib );

	//--------------------------------------------------------------------------------
	__QCMP_NORETURN void Cstdlib::abort( void )
	{
		//_WINQ_FCONTEXT( "Cstdlib::abort" );
		_exit( 3 );
	}

	//--------------------------------------------------------------------------------
	int Cstdlib::atexit( void (*pFunc)(void) )
	{
		//_WINQ_FCONTEXT( "Cstdlib::atexit" );

		if( g_pBootStrap )
		{
			return g_pBootStrap->atexit( pFunc );
		}
		return 0;
	}

	//--------------------------------------------------------------------------------
	void* Cstdlib::calloc( size_t nNum, size_t nSize )
	{
		//_WINQ_FCONTEXT( "Cstdlib::calloc" );
		void* pvBlk = 0;
		__QCS_PROTECT
		{
			// ensure that (nSize * nNum) does not overflow
			//if( nNum == 0 || ( nSize < ( _HEAP_MAXREQ / nNum ) ) )
			{
				nSize *= nNum;
				pvBlk = this->malloc( nSize );//try to malloc the requested space
				if( pvBlk != 0 )
				{
					memset( pvBlk, 0, nSize );// If malloc() succeeded, initialize the allocated space to zeros.
				}
			}
			/*
			else
			{
				errno = ENOMEM;
			}
			*/
		}__QCS_ENDPROTECT

		return pvBlk;
	}

	//--------------------------------------------------------------------------------
	void Cstdlib::exit( int status )
	{
		//_WINQ_FCONTEXT( "Cstdlib::exit" );
		doexit( status, 0, 0 );
	}

	//--------------------------------------------------------------------------------
	void Cstdlib::_exit( int status )
	{
		//_WINQ_FCONTEXT( "Cstdlib::_exit" );
		doexit( status, 1, 0 ); // quick term, kill process
	}

	//--------------------------------------------------------------------------------
	void Cstdlib::free( void* ptr )
	{
		//_WINQ_FCONTEXT( "Cstdlib::free" );
		__QCS_PROTECT
		{
			//m_ProcessHeap.Free( 0, ptr );
		}__QCS_ENDPROTECT
	}

	//--------------------------------------------------------------------------------
	void* Cstdlib::malloc( size_t size )
	{
		//_WINQ_FCONTEXT( "Cstdlib::malloc" );
		void* pAlloc = 0;
		__QCS_PROTECT
		{
			nsSanOS::CProcess* pProcess = nsSanOS::CProcess::ThisProcess();
			if( pProcess )
			{
				//pProcess->MemoryManager();
			}
			//pAlloc = m_ProcessHeap.Alloc( 0, size );
		}__QCS_ENDPROTECT
		return pAlloc;
	}

	//--------------------------------------------------------------------------------
	void* Cstdlib::realloc( void* ptr, size_t size )
	{
		//_WINQ_FCONTEXT( "Cstdlib::realloc" );
		void* pAlloc = 0;
		__QCS_PROTECT
		{
			if( ptr == 0 )
			{
				//pAlloc = m_ProcessHeap.Alloc( 0, size );
			}
			else
			{
				//pAlloc = m_ProcessHeap.ReAlloc( 0, ptr, size );
			}
		}__QCS_ENDPROTECT
		return pAlloc;
	}

}//nsSanOS

#endif//(QOR_SYS_OS == QOR_SYS_SANOS)