//WinQLSyncHandle.h

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

//WinQL Synchronisation Handle object wrapper

#ifndef WINQL_CS_SYNCHANDLE_H_1
#define WINQL_CS_SYNCHANDLE_H_1

#include "CompilerQOR.h"

#ifdef	__QCMP_OPTIMIZEINCLUDE
#pragma	__QCMP_OPTIMIZEINCLUDE
#endif//__QCMP_OPTIMIZEINCLUDE

#include "CodeQOR/DataStructures/TCRef.h"
#include "WinQL/CodeServices/Handles/WinQLHandle.h"

//--------------------------------------------------------------------------------
namespace nsWin32
{
	class __QOR_INTERFACE( __WINQL ) CSyncHandle;
}

//--------------------------------------------------------------------------------
namespace nsCodeQOR
{
	template<>
	struct reference_type< nsWin32::CSyncHandle >
	{
	public:

		typedef nsCodeQOR::CTCRef< nsWin32::CSyncHandle > type;
	};
}

//--------------------------------------------------------------------------------
namespace nsWin32
{
	//--------------------------------------------------------------------------------
	class __QOR_INTERFACE( __WINQL ) CSyncHandle : public CHandle
	{
	public:

		__QOR_DECLARE_OCLASS_ID( CSyncHandle );
		__QOR_DECLARE_REF_TYPE( CSyncHandle );

		CSyncHandle();
		CSyncHandle( void* h, bool bCanBeSignaled = false );
		virtual ~CSyncHandle();
		CSyncHandle( const CSyncHandle& );
		CSyncHandle( CSyncHandle::ref_type src );
		CSyncHandle& operator = ( const CSyncHandle& );
		CSyncHandle& operator = ( void* pOSHandle );

		ref_type Ref( void )
		{
			return ref_type( this );
		}

		bool operator == ( const CSyncHandle& cmp )
		{
			return CHandle::operator==( cmp );
		}

		void* Use( void );

		unsigned long AddRef( void );
		unsigned long Release( void );

		bool CanBeSignaled( void ) const;
		void SetCanBeSignaled( bool bSignalable );

	protected:

		CHandle m_SourceProcess;
		unsigned long m_ulRefCount;//TODO: Should be an atmoic value
		bool m_bCanBeSignaled;
	};

	//--------------------------------------------------------------------------------
	class __QOR_INTERFACE( __WINQL ) CThreadHandle : public CSyncHandle
	{
	public:

		__QOR_DECLARE_OCLASS_ID( CThreadHandle );

		CThreadHandle();
		CThreadHandle( void* h );
		virtual ~CThreadHandle();
		CThreadHandle( const CThreadHandle& );
		CThreadHandle& operator = ( const CThreadHandle& );
		CThreadHandle& operator = ( void* pOSHandle );
	};

	//--------------------------------------------------------------------------------
	class __QOR_INTERFACE( __WINQL ) CSyncHandleSet
	{
	public:

		__QOR_DECLARE_OCLASS_ID( CSyncHandleSet );

		CSyncHandleSet();
		CSyncHandleSet( const CSyncHandleSet& );
		~CSyncHandleSet();
		CSyncHandleSet& operator = ( const CSyncHandleSet& );

		unsigned long Add( CSyncHandle& Handle );
		unsigned long Remove( CSyncHandle& Handle );
		unsigned long Count( void );

		void** Use( void );

		//------------------------------------------------------------------------------
		CSyncHandle*& operator[]( unsigned long k ) const
		{
			return m_ArraySyncHandles[ k ];		//TODO: This should throw if k is out of range
		}

	private:

		nsCodeQOR::CTArray< void* > m_UseArray;
		nsCodeQOR::CTArray< CSyncHandle* > m_ArraySyncHandles;
	};

}//nsWin32

#endif//WINQL_CS_SYNCHANDLE_H_1
