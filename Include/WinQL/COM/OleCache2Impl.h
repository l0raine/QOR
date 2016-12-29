//OleCache2Impl.h

// Copyright Querysoft Limited 2013, 2015
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

#ifndef WINQL_COM_OLECACHE2IMPL_H_3
#define WINQL_COM_OLECACHE2IMPL_H_3

#ifdef	__QCMP_OPTIMIZEINCLUDE
#pragma	__QCMP_OPTIMIZEINCLUDE
#endif//__QCMP_OPTIMIZEINCLUDE

#include "WinQL/Definitions/Constants.h"
#include "WinQL/Definitions/Security.h"
#include "WinQL/Definitions/Interfaces.h"
#include "WinQL/COM/TInterfaceMember.h"

//--------------------------------------------------------------------------------
namespace nsWin32
{
	//--------------------------------------------------------------------------------
	class __QOR_INTERFACE( __WINQL_COM ) COleCacheImpl : public CInterfaceImplBase< IOleCache >
	{
	public:

		__QOR_DECLARE_COMCLASS_ID( COleCacheImpl );

		COleCacheImpl( CIUnknownImplBase<>* pImpl );
		virtual ~COleCacheImpl();

		virtual long __QCMP_STDCALLCONVENTION Cache( FormatEtc* pformatetc, unsigned long advf, unsigned long* pdwConnection );
		virtual long __QCMP_STDCALLCONVENTION Uncache( unsigned long dwConnection );
		virtual long __QCMP_STDCALLCONVENTION EnumCache( IEnumSTATDATA** ppenumSTATDATA );
		virtual long __QCMP_STDCALLCONVENTION InitCache( IDataObject* pDataObject );
		virtual long __QCMP_STDCALLCONVENTION SetData( FormatEtc* pformatetc, StgMedium* pmedium, int fRelease );

	private:

		COleCacheImpl();
		COleCacheImpl( const COleCacheImpl& );
		COleCacheImpl& operator = ( const COleCacheImpl& );
	};

	//--------------------------------------------------------------------------------
	class __QOR_INTERFACE( __WINQL_COM ) COleCache2Impl : public CInterfaceImplBase< IOleCache2, COleCacheImpl >
	{
	public:

		__QOR_DECLARE_COMCLASS_ID( COleCache2Impl );

		COleCache2Impl( CIUnknownImplBase<>* pImpl );
		virtual ~COleCache2Impl();

		virtual long __QCMP_STDCALLCONVENTION SaveObject( void );
		virtual long __QCMP_STDCALLCONVENTION GetMoniker( unsigned long dwAssign, unsigned long dwWhichMoniker, IMoniker** ppmk );
		virtual long __QCMP_STDCALLCONVENTION GetContainer( IOleContainer** ppContainer );
		virtual long __QCMP_STDCALLCONVENTION ShowObject( void );
		virtual long __QCMP_STDCALLCONVENTION OnShowWindow( int fShow );
		virtual long __QCMP_STDCALLCONVENTION RequestNewObjectLayout( void );

	private:

		COleCache2Impl();
		COleCache2Impl( const COleCache2Impl& );
		COleCache2Impl& operator = ( const COleCache2Impl& );
	};

}//nsWin32

#endif//WINQL_COM_OLECACHE2IMPL_H_3
