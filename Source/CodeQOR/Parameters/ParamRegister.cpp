//ParamRegister.cpp

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

//Intercept the assignment of return values

#include "CompilerQOR.h"
#include "CodeQOR/Tracing/FunctionContextBase.h"
#include "CodeQOR/Parameters/ParamRegister.h"
#include "CodeQOR/Modules/ProcessBase.h"
#include "AppocritaQOR/SubSystems/Thread.h"

//--------------------------------------------------------------------------------
namespace nsParamChecking
{
	//--------------------------------------------------------------------------------
	CFunctionContextLock::CFunctionContextLock()
	{
		m_ulLevel = 100;
		m_pCallContext = 0;
		m_pFunctionContext = 0;
		m_pParentCallContext = 0;
		nsCodeQOR::CProcessBase* pProcess = nsCodeQOR::CProcessBase::ThisProcess();
		if( nsCodeQOR::CFunctionContextBase::Booted( false ) && pProcess && pProcess->ThreadContext() )
		{
			m_pFunctionContext = pProcess->ThreadContext()->FunctionContext();
			
			if( m_pFunctionContext )
			{
				m_ulLevel = m_pFunctionContext->Lock();
				m_pCallContext = m_pFunctionContext->CallContext();
				if( m_pFunctionContext->GetParent() )
				{
					m_pParentCallContext = m_pFunctionContext->GetParent()->CallContext();
				}
			}
		}
	}
	
	//--------------------------------------------------------------------------------
	nsCodeQOR::CCallContextBase* CFunctionContextLock::CallContextPtr( void )
	{
		return m_pCallContext;
	}
		
	//--------------------------------------------------------------------------------
	nsCodeQOR::CCallContextBase* CFunctionContextLock::ParentCallContextPtr( void )
	{
		return m_pParentCallContext;
	}

	//--------------------------------------------------------------------------------
	unsigned long CFunctionContextLock::Level( void )
	{
		return m_ulLevel;
	}
		
	//--------------------------------------------------------------------------------
	CFunctionContextLock::~CFunctionContextLock()
	{
		if( m_pFunctionContext != 0 )
		{
			m_pFunctionContext->Unlock();
		}
	}
	
	//--------------------------------------------------------------------------------
	CReturnRegister::~CReturnRegister()
	{
	}

	//--------------------------------------------------------------------------------
	void CReturnRegister::OnAssignment( void )
	{
		nsQOR::IThread::ref_type pThreadContext = nsQOR::CThread::GetCurrent();
		if( pThreadContext )
		{
			nsCodeQOR::CFunctionContextBase* pFunctionContext = ( pThreadContext.IsNull() ) ? 0 : pThreadContext->FunctionContext();
			nsCodeQOR::CFunctionContextBase* pParent = ( pFunctionContext == 0 ) ? 0 : pFunctionContext->GetParent();
			nsCodeQOR::CCallContextBase* pCallContext = ( pParent == 0 ) ? 0 : pParent->CallContext();

			if( pCallContext != 0 )
			{
				pFunctionContext->Lock();
				pCallContext->OnReturnAssignment();
				pFunctionContext->Unlock();
			}
		}
	}

}//nsParamChecking
