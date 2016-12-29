//WinQLProcThreadAttribList.cpp

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

//

#include <limits.h>
#include "CodeQOR/ErrorSystem/Error.h"
#include "AppocritaQOR/Controller.h"
#include "../Source/SystemQOR/MSWindows/WinQAPI/include/ErrorDomain.h"
#include "../Source/SystemQOR/MSWindows/WinQAPI/include/DynamicLibrary.h"
#include "WinQL/Application/ErrorSystem/WinQLError.h"
#include "WinQL/Application/Process/WinQLProcess.h"
#include "WinQL/Application/Process/WinQLJob.h"
#include "WinQL/Application/Threading/WinQLThread.h"
#include "WinQAPI/Kernel32.h"
#include "WinQAPI/User32.h"
#include "WinQAPI/PSAPI.h"

//------------------------------------------------------------------------------
namespace nsWin32
{
	using namespace nsWinQAPI;

	//--Process Thread Attribute List-------------------------------------------------

	__QOR_IMPLEMENT_OCLASS_LUID( CProcessThreadAttributeList );

	//--------------------------------------------------------------------------------
	CProcessThreadAttributeList::CProcessThreadAttributeList( unsigned long dwAttributeCount, int* pbResult )
	{
		_WINQ_FCONTEXT( "CProcessThreadAttributeList::CProcessThreadAttributeList" );
		m_Size = 0;
		m_pAttributeList = 0;
		BOOL bResult = FALSE;
		__QOR_PROTECT
		{
			bResult = CKernel32::InitializeProcThreadAttributeList( 0, dwAttributeCount, 0, &m_Size );
			if( bResult == TRUE )
			{
				m_pAttributeList = reinterpret_cast<LPPROC_THREAD_ATTRIBUTE_LIST>( new unsigned char[ m_Size ] );
				bResult = CKernel32::InitializeProcThreadAttributeList( reinterpret_cast< ::LPPROC_THREAD_ATTRIBUTE_LIST >( m_pAttributeList ), dwAttributeCount, 0, &m_Size );
			}

			if( pbResult != 0 )
			{
				*pbResult = bResult;
			}
		}__QOR_ENDPROTECT
	}

	//--------------------------------------------------------------------------------
	CProcessThreadAttributeList::~CProcessThreadAttributeList()
	{
		_WINQ_FCONTEXT( "CProcessThreadAttributeList::~CProcessThreadAttributeList" );
		__QOR_PROTECT
		{
			if( m_pAttributeList != 0 )
			{					
				CKernel32::DeleteProcThreadAttributeList( reinterpret_cast< ::LPPROC_THREAD_ATTRIBUTE_LIST >( m_pAttributeList ) );
				//delete m_pAttributeList;
			}
		}__QOR_ENDPROTECT
	}

	//--------------------------------------------------------------------------------
	bool CProcessThreadAttributeList::Update( Cmp_ulong_ptr Attribute, void* lpValue, Cmp_ulong_ptr cbSize )
	{
		_WINQ_FCONTEXT( "CProcessThreadAttributeList::Update" );
		bool bResult = false;
		__QOR_PROTECT
		{
			bResult = CKernel32::UpdateProcThreadAttribute( reinterpret_cast< ::LPPROC_THREAD_ATTRIBUTE_LIST >( m_pAttributeList ), 0, Attribute, lpValue, cbSize, 0, 0 ) ? true : false;
		}__QOR_ENDPROTECT
		return bResult;
	}

}//nsWin32
