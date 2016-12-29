//MallocSpy.h

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

#ifndef WINQL_COM_MALLOCSPY_H_3
#define WINQL_COM_MALLOCSPY_H_3

#include "WinQL/Definitions/Constants.h"
#include "WinQL/Definitions/Security.h"
#include "WinQL/Definitions/Data.h"
#include "WinQL/Definitions/Interfaces.h"
#include "WinQL/COM/ServerObjectBase.h"
#include "CodeQOR/DataStructures/TArray.h"
#include "WinQL/Application/ErrorSystem/WinQLDebugging.h"
#include "WinQL/CodeServices/WinQLPolicy.h"

//--------------------------------------------------------------------------------
namespace nsWin32
{
	//--------------------------------------------------------------------------------
	class __QOR_INTERFACE( __WINQL_COM ) CMallocSpy : public CServerObjectBase< IMallocSpy >
	{
	public:

		__QOR_DECLARE_COMCLASS_ID( CMallocSpy );

		CMallocSpy();
		virtual ~CMallocSpy();

		virtual Cmp_ulong_ptr __QCMP_STDCALLCONVENTION PreAlloc( Cmp_ulong_ptr cbRequest );
		virtual void* __QCMP_STDCALLCONVENTION PostAlloc( void* pActual );
		virtual void* __QCMP_STDCALLCONVENTION PreFree( void* pRequest, int fSpyed );
		virtual void __QCMP_STDCALLCONVENTION PostFree( int fSpyed );
		virtual Cmp_ulong_ptr __QCMP_STDCALLCONVENTION PreRealloc( void* pRequest, Cmp_ulong_ptr cbRequest, void** ppNewRequest, int fSpyed );
		virtual void* __QCMP_STDCALLCONVENTION PostRealloc( void* pActual, int fSpyed );
		virtual void* __QCMP_STDCALLCONVENTION PreGetSize( void* pRequest, int fSpyed );
		virtual Cmp_ulong_ptr __QCMP_STDCALLCONVENTION PostGetSize( Cmp_ulong_ptr cbActual, int fSpyed );
		virtual void* __QCMP_STDCALLCONVENTION PreDidAlloc( void* pRequest, int fSpyed );
		virtual int __QCMP_STDCALLCONVENTION PostDidAlloc( void* pRequest, int fSpyed, int fActual );
		virtual void __QCMP_STDCALLCONVENTION PreHeapMinimize( void );
		virtual void __QCMP_STDCALLCONVENTION PostHeapMinimize( void );

		virtual long AddToList( void* pv );
		virtual long RemoveFromList( void* pv );
		virtual long DumpLeaks( void );
		virtual void Reset( void );

	protected:

		__QCMP_STATIC_CONSTANT( int, ROUNDUP_AMOUNT = 8 );

#define		ROUNDUP_(size,amount)		( ( ( unsigned long )( size ) + ( (amount)-1 ) ) & ~( ( unsigned long )(amount)-1 ) )
#define		ROUNDUP(size)				ROUNDUP_(size, ROUNDUP_AMOUNT)

		__QCMP_STATIC_CONSTANT( unsigned long, ulHeadSize = sizeof( unsigned long ) );
		__QCMP_STATIC_CONSTANT( size_t, lengthSize = sizeof( size_t ) );
		__QCMP_STATIC_CONSTANT( unsigned long, ulIdSize = sizeof( unsigned long ) );
		__QCMP_STATIC_CONSTANT( unsigned long, ulFileNameSize = sizeof( TCHAR* ) );
		__QCMP_STATIC_CONSTANT( unsigned long, ulLineNumberSize = sizeof( unsigned long ) );
		__QCMP_STATIC_CONSTANT( unsigned long, ulTailSize = sizeof( unsigned char ) );

		__QCMP_STATIC_CONSTANT( unsigned long, ulHeaderSize = ROUNDUP( ulHeadSize + lengthSize + ulIdSize + ulFileNameSize + ulLineNumberSize ) );
		__QCMP_STATIC_CONSTANT( unsigned long, ulFooterSize = ulTailSize );
		__QCMP_STATIC_CONSTANT( unsigned char, cHeadSign = '{' );
		__QCMP_STATIC_CONSTANT( unsigned char, cTailSign = '}' );
		__QCMP_STATIC_CONSTANT( unsigned char, cAllocSign = '$' );
		__QCMP_STATIC_CONSTANT( unsigned char, cFreeSign = 'Z' );

		template< typename t > unsigned char* Head_Offset( t pActual ){ return (unsigned char*)( pActual ); }
		template< typename t > unsigned char* Tail_Offset( t pActual ){ return ( Users_Offset( pActual ) + Buffer_Length( pActual ) ); }
		template< typename t > unsigned char* Users_Offset( t pActual ){ return ( Head_Offset( pActual ) + ulHeaderSize ); }
		template< typename t > unsigned char* Header_Offset( t pRequest ){ return ( (unsigned char*)( pRequest ) - ulHeaderSize ); }
		template< typename t > unsigned char* Length_Offset( t pActual ){ return ( Head_Offset( pActual ) + ulHeaderSize ); }
		template< typename t > size_t& Buffer_Length( t pActual ){ return ( *(size_t*)Length_Offset( pActual ) ); }
		template< typename t > unsigned char* Id_Offset( t pActual ){ return ( Length_Offset( pActual ) + lengthSize ); }
		template< typename t > unsigned long& Buffer_Id( t pActual ){ return ( *(unsigned long*)Id_Offset( pActual ) ); }
		template< typename t > unsigned char* FileName_Offset( t pActual ){ return ( Id_Offset( pActual ) + ulIdSize ); }
		template< typename t > wchar_t*& Buffer_FileName( t pActual ){ return ( *(wchar_t**)FileName_Offset( pActual ) ); }
		template< typename t > unsigned char* LineNumber_Offset( t pActual ){ return ( FileName_Offset( pActual ) + ulFileNameSize ); }
		template< typename t > unsigned long& Buffer_LineNumber( t pActual ){ return ( *(unsigned long*)LineNumber_Offset( pActual ) ); }
		template< typename t > unsigned long& Head_Signature( t pActual ){ return ( *(unsigned long*)Head_Offset( pActual ) ); }
		template< typename t > unsigned char& Tail_Signature( t pActual ){ return ( *(unsigned char*)Tail_Offset( pActual ) ); }

		size_t m_BytesRequested;
		unsigned long m_ulAllocationCount;

		nsCodeQOR::CTArray< void*, CWinQLPolicy > m_ListAllocs;

	private:

		int m_ItemIndex;			
		unsigned long m_ulBreakID;
		nsWin32::CDebuggingHelper m_DebugHelper;

		CMallocSpy( const CMallocSpy& );
		CMallocSpy& operator = ( const CMallocSpy& );
	};

}//nsWin32

#endif//WINQL_COM_MALLOCSPY_H_3
