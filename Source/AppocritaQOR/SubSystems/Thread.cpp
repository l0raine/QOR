//Thread.cpp

// Copyright Querysoft Limited 2016
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

//Thread implementation

#include "CodeQOR/Instancing/TInstancePtr.h"
#include "CodeQOR/Tracing/TraceFlyer.h"
#include "CodeQOR/Tracing/FunctionContextBase.h"
#include "AppocritaQOR/AppocritaQOR.h"
#include "AppocritaQOR/SubSystems/Thread.h"
#include "AppocritaQOR/SubSystems/IThreading.h"
#include "AppocritaQOR/SubSystems/Threading.h"
#include "AppocritaQOR/SubSystem.h"
#include "AppocritaQOR/Application.h"

//------------------------------------------------------------------------------
namespace nsQOR
{

	__QOR_IMPLEMENT_OCLASS_LUID( IThread );

	//--------------------------------------------------------------------------------
	IThread::IThread()
	{
	}

	//--------------------------------------------------------------------------------
	IThread::IThread( const IThread& src )
	{
		*this = src;
	}

	//--------------------------------------------------------------------------------
	IThread& IThread::operator=( IThread const & src )
	{
		if( &src != this )
		{
		}
		return *this;
	}

	//--------------------------------------------------------------------------------
	IThread::~IThread()
	{
	}

	__QOR_IMPLEMENT_OCLASS_LUID( CThread );

	IThread::ref_type CThread::m_spMainThread = 0;

	//--------------------------------------------------------------------------------
	IThread::ref_type CThread::GetCurrent( void )
	{
		if( !TheApplication().IsNull() && !TheApplication()->GetRole().IsNull() )
		{
			nsQOR::CThreading* pThreading = TheApplication()->GetRole()->GetSubSystem( IThreading::ClassID() ).As< nsQOR::CThreading >();
			if( pThreading )
			{
				return pThreading->GetCurrent();
			}
		}
		return m_spMainThread;
	}

	//--------------------------------------------------------------------------------
	CThread::CThread()
	{
		m_pBaseFContext = 0;
		m_pBaseErrorDomain = 0;
		m_pBaseExceptionContext = 0;
		m_ulRecursionCount = 0;
		m_bTraceEnabled = false;
		if( m_spMainThread.IsNull() )
		{
			m_spMainThread.Attach( this, false );
		}
	}

	//--------------------------------------------------------------------------------
	CThread::CThread( const CThread& src )
	{
		if( &src != this )
		{
			*this = src;
		}
	}

	//--------------------------------------------------------------------------------
	CThread& CThread::operator=( CThread const & src )
	{
		m_pBaseFContext = src.m_pBaseFContext;
		m_pBaseErrorDomain = 0;//TODO:
							   //m_iDefaultProcessingThrow = src.m_iDefaultProcessingThrow;
							   //m_DummyExceptData = src.m_DummyExceptData;
							   //m_pDummyFrameInfoChain = src.m_pDummyFrameInfoChain;
		return *this;
	}

	//--------------------------------------------------------------------------------
	CThread::~CThread()
	{
	}

	//--------------------------------------------------------------------------------
	nsCodeQOR::CFunctionContextBase* CThread::RegisterFunctionContext( nsCodeQOR::CFunctionContextBase* pFContext )
	{
		nsCodeQOR::CFunctionContextBase* pParent = m_pBaseFContext;
		m_pBaseFContext = pFContext;
		if( m_bTraceEnabled && pParent && !pParent->Locked() )
		{
			nsCodeQOR::CTInstancePtr< nsCodeQOR::CTraceFlyer > pTraceFlyer;
			if( !pTraceFlyer.IsNull() )
			{
				pTraceFlyer->Trace( const_cast<char*>( pFContext->Name() ) );
			}
		}
		return pParent;
	}

	//--------------------------------------------------------------------------------
	void CThread::UnregisterFunctionContext( nsCodeQOR::CFunctionContextBase* pFContext, nsCodeQOR::CFunctionContextBase* pParent )
	{
		m_pBaseFContext = pParent;
		if( m_pBaseFContext )
		{
			m_pBaseFContext->Lock();
		}
	}

	//--------------------------------------------------------------------------------
	nsCodeQOR::CFunctionContextBase* CThread::FunctionContext( void )
	{
		return m_pBaseFContext;
	}

	//--------------------------------------------------------------------------------
	nsCodeQOR::CBaseErrorDomain*& CThread::ErrorDomain( void )
	{
		return m_pBaseErrorDomain;
	}

	//--------------------------------------------------------------------------------
	nsCodeQOR::CExceptionContextBase* CThread::ExceptionContext( void )
	{
		return m_pBaseExceptionContext;
	}

	//--------------------------------------------------------------------------------
	unsigned long CThread::IncrementRecursionCount()
	{
		return m_ulRecursionCount++;
	}

	//--------------------------------------------------------------------------------
	unsigned long CThread::DecrementRecursionCount()
	{
		return m_ulRecursionCount--;
	}

	//--------------------------------------------------------------------------------
	unsigned long CThread::RecursionCount()
	{
		return m_ulRecursionCount;
	}

	//--------------------------------------------------------------------------------
	bool CThread::InErrorSystem()
	{
		return RecursionCount() > 0;
	}

	//--------------------------------------------------------------------------------
	void CThread::LeaveErrorSystem( void )
	{
		DecrementRecursionCount();
	}

	//--------------------------------------------------------------------------------
	void CThread::EnterErrorSystem( void )
	{
		IncrementRecursionCount();
	}

	//------------------------------------------------------------------------------
	unsigned int CThread::TlsAlloc( void )
	{
		m_aThreadLocalStorage.AcquireAccess();
		unsigned int uiResult = m_aThreadLocalStorage.Size();
		void* pNothing = 0;
		m_aThreadLocalStorage.Append( pNothing );
		m_aThreadLocalStorage.ReleaseAccess();
		return uiResult;
	}

	//------------------------------------------------------------------------------
	bool CThread::TlsFree( unsigned int uiTlsIndex )
	{
		m_aThreadLocalStorage.AcquireAccess();
		m_aThreadLocalStorage[ uiTlsIndex ] = 0;
		m_aThreadLocalStorage.ReleaseAccess();
		return true;
	}

	//------------------------------------------------------------------------------
	void* CThread::TlsGetValue( unsigned int uiTlsIndex )
	{
		void* pResult = 0;
		m_aThreadLocalStorage.AcquireAccess();
		pResult = m_aThreadLocalStorage[ uiTlsIndex ];
		m_aThreadLocalStorage.ReleaseAccess();
		return pResult;
	}

	//------------------------------------------------------------------------------
	bool CThread::TlsSetValue( unsigned int uiTlsIndex, void* lpTlsValue )
	{
		m_aThreadLocalStorage.AcquireAccess();
		m_aThreadLocalStorage[ uiTlsIndex ] = lpTlsValue;
		m_aThreadLocalStorage.ReleaseAccess();
		return true;
	}

	//------------------------------------------------------------------------------
	nsCodeQOR::CTMap< nsCodeQOR::mxGUID*, void* >& CThread::ClassThreadMap()
	{
		return m_ClassThreadMap;
	}

	//------------------------------------------------------------------------------
	CEventManager& CThread::LocalEventManager()
	{
		return *m_pLocalEventManager;
	}

	//------------------------------------------------------------------------------
	void CThread::SetTraceEnabled( bool bEnabled )
	{
		m_bTraceEnabled = bEnabled;
	}

	//------------------------------------------------------------------------------
	bool CThread::GetTraceEnabled( void )
	{
		return m_bTraceEnabled;
	}

	//------------------------------------------------------------------------------
	void CThread::SetCodePage( nsCodeQOR::CCodePage* pCodePage )
	{
		m_pCodePage = pCodePage;
	}

	//------------------------------------------------------------------------------
	nsCodeQOR::CCodePage* CThread::GetCodePage( void )
	{
		return m_pCodePage;
	}

	//------------------------------------------------------------------------------
	bool CThread::IsAFiber( void )
	{
		return false;
	}

	//------------------------------------------------------------------------------
	bool CThread::IsGUIThread( bool bConvert )
	{
		return false;
	}
}//nsQOR
