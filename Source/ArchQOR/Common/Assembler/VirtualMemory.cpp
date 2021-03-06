//MemoryManager.cpp

// Copyright (c) 2008-2010, Petr Kobalicek <kobalicek.petr@gmail.com>
// Copyright (c) Querysoft Limited 2012, 2015
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

#include "ArchQOR.h"
#include "ArchQOR/Common/Assembler/VirtualMemory.h"
#include <string.h>
#include <assert.h>
#include "CodeQOR/Tracing/FunctionContextBase.h"

//------------------------------------------------------------------------------
namespace nsArch
{
	CExePageAllocator CVirtualMemory::s_OSPageAllocator;

	//------------------------------------------------------------------------------
	__QOR_IMPLEMENT_OCLASS_LUID(CVirtualMemory);

	//------------------------------------------------------------------------------
	void* CVirtualMemory::alloc(Cmp_uint_ptr length, Cmp_uint_ptr* allocated, bool canExecute) __QCMP_THROW
	{
		__QCS_FCONTEXT("CVirtualMemory::alloc");
		return s_OSPageAllocator.Alloc( nsCodeQOR::CProcessBase::ThisProcess(), length, allocated, canExecute );
	}

	//------------------------------------------------------------------------------
	void CVirtualMemory::free(void* addr, Cmp_uint_ptr length) __QCMP_THROW
	{
		__QCS_FCONTEXT("CVirtualMemory::free");
		s_OSPageAllocator.Free( nsCodeQOR::CProcessBase::ThisProcess(), addr, length );
	}

}//nsArch
