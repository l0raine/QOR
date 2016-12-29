//CodeGenerator.cpp

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

//Generic code generator

#include "ArchQOR.h"
#include "ArchQOR/Common/Assembler/CodeGenerator.h"
#include "ArchQOR/Common/Assembler/Assembler.h"
#include "ArchQOR/Common/Assembler/MemoryManager.h"
#include "ArchQOR/Common/Assembler/MemoryMarker.h"
#include "CodeQOR/Tracing/FunctionContextBase.h"

//------------------------------------------------------------------------------
namespace nsArch
{
	//------------------------------------------------------------------------------
	__QOR_IMPLEMENT_OCLASS_LUID(CCodeGeneratorBase);

	//------------------------------------------------------------------------------
	CCodeGeneratorBase::CCodeGeneratorBase()
	{
		__QCS_MEMBER_FCONTEXT("CCodeGeneratorBase::CCodeGeneratorBase");
	}

	//------------------------------------------------------------------------------
	CCodeGeneratorBase::~CCodeGeneratorBase()
	{
		__QCS_MEMBER_FCONTEXT("CCodeGeneratorBase::~CCodeGeneratorBase");
	}

	//------------------------------------------------------------------------------
	CCodeGeneratorBase* CCodeGeneratorBase::getGlobal()
	{
		__QCS_FCONTEXT("CCodeGeneratorBase::getGlobal");
		static CJitCodeGenerator global;
		return &global;
	}


	//------------------------------------------------------------------------------
	__QOR_IMPLEMENT_OCLASS_LUID(CJitCodeGenerator);

	//------------------------------------------------------------------------------
	CJitCodeGenerator::CJitCodeGenerator() : m_pMemoryManager(0), m_pMemoryMarker(0), m_uiallocType( MEMORY_ALLOC_FREEABLE )
	{
		__QCS_MEMBER_FCONTEXT("CJitCodeGenerator::CJitCodeGenerator");
	}

	//------------------------------------------------------------------------------
	CJitCodeGenerator::~CJitCodeGenerator()
	{
		__QCS_MEMBER_FCONTEXT("CJitCodeGenerator::~CJitCodeGenerator");
	}

	//------------------------------------------------------------------------------
	Cmp_unsigned__int32 CJitCodeGenerator::generate( void** dest, CAbstractAssembler* assembler )
	{
		__QCS_MEMBER_FCONTEXT("CJitCodeGenerator::generate");

		// Disallow empty code generation.
		Cmp_uint_ptr codeSize = assembler->getCodeSize();
		if( codeSize == 0 )
		{
			*dest = 0;
			return nsArch::ERROR_NO_FUNCTION;
		}

		// Switch to global memory manager if not provided.
		CMemoryManager* memmgr = getMemoryManager();
		if( memmgr == 0 )
		{
			memmgr = CMemoryManager::getGlobal();
		}

		void* p = memmgr->alloc( codeSize, getAllocType() );
		if( p == 0 )
		{
			*dest = 0;
			return ERROR_NO_VIRTUAL_MEMORY;
		}

		// Relocate the code.
		Cmp_uint_ptr relocatedSize = assembler->relocCode( p );

		// Return unused memory to mamory-manager.
		if( relocatedSize < codeSize )
		{
			memmgr->shrink( p, relocatedSize );
		}

		// Mark memory if MemoryMarker provided.
		if( m_pMemoryMarker )
		{
			m_pMemoryMarker->mark( p, relocatedSize );
		}

		// Return the code.
		*dest = p;
		return ERROR_NONE;
	}

}//nsArch