//WinQLExePageAllocator.cpp

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

#include "WinQL/WinQL.h"
#include "WinQL/Application/Threading/WinQLCriticalSection.h"
#include "SystemQOR.h"
#include <assert.h>
#include "WinQL/Application/Memory/WinQLExePageAllocator.h"
#include "WinQL/Application/Process/WinQLProcess.h"
#include "WinQAPI/Kernel32.h"

//--------------------------------------------------------------------------------
namespace nsWin32
{
	__QOR_IMPLEMENT_OCLASS_LUID(CExePageAllocator);

	//------------------------------------------------------------------------------
	static bool isAligned(Cmp_uint_ptr base, Cmp_uint_ptr alignment)
	{
		return base % alignment == 0;
	}

	//------------------------------------------------------------------------------
	static Cmp_uint_ptr roundUp(Cmp_uint_ptr base, Cmp_uint_ptr pageSize)
	{
		Cmp_uint_ptr over = base % pageSize;
		return base + (over > 0 ? pageSize - over : 0);
	}

	//------------------------------------------------------------------------------
	VirtualMemoryLocal::VirtualMemoryLocal() __QCMP_THROW
	{
		::SYSTEM_INFO info;
		nsWinQAPI::CKernel32::GetSystemInfo( &info );
		alignment = info.dwAllocationGranularity;
		pageSize = roundUpToPowerOf2(info.dwPageSize);
	}

	//------------------------------------------------------------------------------
	// Implementation is from "Hacker's Delight" by Henry S. Warren, Jr.,
	// figure 3-3, page 48, where the function is called clp2.
	Cmp_uint_ptr VirtualMemoryLocal::roundUpToPowerOf2( Cmp_uint_ptr base )
	{
		base -= 1;

		base = base | ( base >> 1 );
		base = base | ( base >> 2 );
		base = base | ( base >> 4 );
		base = base | ( base >> 8 );
		base = base | ( base >> 16 );

#	if ( QOR_ARCH_WORDSIZE == 64 )
		if( sizeof( Cmp_uint_ptr ) >= 8 )
		{
			base = base | (base >> 32);
		}
#	endif

		return base + 1;
	}

	//------------------------------------------------------------------------------
	static VirtualMemoryLocal& vm() __QCMP_THROW
	{
		static VirtualMemoryLocal vm;
		return vm;
	};

	//--------------------------------------------------------------------------------
	CExePageAllocator::CExePageAllocator()
	{
		__QCS_FCONTEXT( "CExePageAllocator::CExePageAllocator" );
	}

	//--------------------------------------------------------------------------------
	CExePageAllocator::~CExePageAllocator()
	{
		__QCS_FCONTEXT( "CExePageAllocator::~CExePageAllocator" );
	}

	//--------------------------------------------------------------------------------
	void* CExePageAllocator::Alloc( nsCodeQOR::CProcessBase* pProcess, Cmp_uint_ptr length, Cmp_uint_ptr* allocated, bool canExecute )
	{
		// VirtualAlloc rounds allocated size to page size automatically.
		Cmp_uint_ptr msize = roundUp( length, vm().pageSize );

		CProcess* pWinProcess = dynamic_cast< CProcess* >( pProcess );

		if( pWinProcess )
		{
			// Windows XP SP2 / Vista allow Data Execution Prevention (DEP).
			//nsWin32::nsCodeServices::CVirtualHelper VirtualHelper;
			unsigned short protect = canExecute ? PAGE_EXECUTE_READWRITE : PAGE_READWRITE;
			void* mbase = nsWinQAPI::CKernel32::VirtualAllocEx( nsWinQAPI::CKernel32::GetCurrentProcess(), 0, msize, MEM_COMMIT | MEM_RESERVE, protect);
			if( mbase == 0 )
			{
				return 0;
			}

			assert( isAligned( reinterpret_cast< Cmp_uint_ptr >( mbase ), vm().alignment ) );

			if( allocated )
			{
				*allocated = msize;
			}
			return mbase;
		}
		return 0;
	}

	//--------------------------------------------------------------------------------
	void CExePageAllocator::Free( nsCodeQOR::CProcessBase* pProcess, void* addr, Cmp_uint_ptr /* length */ )
	{
		CProcess* pWinProcess = dynamic_cast< CProcess* >( pProcess );

		if( pWinProcess )
		{
			nsWinQAPI::CKernel32::VirtualFreeEx( pWinProcess->ProcessHandle().Use(), addr, 0, MEM_RELEASE );
		}
	}

	//------------------------------------------------------------------------------
	Cmp_uint_ptr CExePageAllocator::GetAlignment() __QCMP_THROW
	{
		return vm().alignment;
	}

	//------------------------------------------------------------------------------
	Cmp_uint_ptr CExePageAllocator::GetPageSize() __QCMP_THROW
	{
		return vm().pageSize;
	}
}//nsWin32
