//WinQLExePageAllocator.h

// Copyright Querysoft Limited 2015
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

//Allocate aligned pages of Read/Write/Execute memory from the OS

#ifndef WINQL_EXEPAGEALLOCATOR_H_1
#define WINQL_EXEPAGEALLOCATOR_H_1

#include "WinQL/WinQL.h"
#include "CodeQOR/Modules/ProcessBase.h"

//--------------------------------------------------------------------------------
namespace nsWin32
{
	//------------------------------------------------------------------------------
	struct __QCMP_LOCAL VirtualMemoryLocal
	{
		VirtualMemoryLocal() __QCMP_THROW;

		static Cmp_uint_ptr roundUpToPowerOf2(Cmp_uint_ptr base);

		Cmp_uint_ptr alignment;
		Cmp_uint_ptr pageSize;
	};

	//--------------------------------------------------------------------------------
	class __QOR_INTERFACE( __WINQL ) CExePageAllocator
	{
	public:

		__QOR_DECLARE_OCLASS_ID(CExePageAllocator);

		CExePageAllocator();
		virtual ~CExePageAllocator();

		virtual void* Alloc( nsCodeQOR::CProcessBase* pProcess, Cmp_uint_ptr length, Cmp_uint_ptr* allocated, bool canExecute );
		virtual void Free( nsCodeQOR::CProcessBase* pProcess, void* addr, Cmp_uint_ptr /* length */ );
		virtual Cmp_uint_ptr GetAlignment() __QCMP_THROW;
		virtual Cmp_uint_ptr GetPageSize() __QCMP_THROW;

	private:

		VirtualMemoryLocal m_vm;
	};

}//nsWin32

#endif//WINQL_EXEPAGEALLOCATOR_H_1

