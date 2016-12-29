//WinString.h

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

//WinQL String class

#ifndef WINQL_CS_TXT_STRING_H_1
#define WINQL_CS_TXT_STRING_H_1

#include "CodeQOR/Text/Char.h"
#include <stdarg.h>
#include "WinQL/Application/ErrorSystem/WinQLFunctionContext.h"

//--------------------------------------------------------------------------------
namespace nsWin32
{

	//--------------------------------------------------------------------------------
	template< class _tChar, class _tRawAllocator = nsCodeQOR::CDefaultSource >
	class CString : public nsCodeQOR::CTString< _tChar, _tRawAllocator >
	{
		friend class nsCodeQOR::CTCRef< nsWin32::CString< _tChar, _tRawAllocator > >;
		typedef nsCodeQOR::CTString< _tChar, _tRawAllocator > BaseName;

	protected:

		//--------------------------------------------------------------------------------
		struct sWinHeader
		{
			unsigned long ulLocaleID;			
			unsigned short usAlloc;
			unsigned short usLen;
			unsigned short usHeaderSize;
		};

	public:

		typedef _tChar char_type;
		typedef nsCodeQOR::CTCRef< CString< _tChar, _tRawAllocator > > ref_type;

        //--------------------------------------------------------------------------------
        CString() : BaseName()
        {
        }

		//--------------------------------------------------------------------------------
		CString( _tChar* cpString ) : BaseName( cpString )
		{
		}

		//--------------------------------------------------------------------------------
        CString( const _tChar* cpString, unsigned short usSrcLen = 0 ) : BaseName( cpString, usSrcLen )
        {
		}

		//--------------------------------------------------------------------------------
		CString( const _tChar* cpString, unsigned short usSrcLen, unsigned short usInitialBufferSize ) : BaseName( cpString, usSrcLen, usInitialBufferSize )
		{
		}

		//--------------------------------------------------------------------------------
		CString( const CString< _tChar >& Src ) : BaseName( Src )
		{
		}

		//--------------------------------------------------------------------------------
		CString& operator = ( const CString< _tChar >& Src )
		{
			if( &Src != this )
			{
				BaseName::operator = ( Src );
			}
			return *this;
		}

		//--------------------------------------------------------------------------------
		CString& operator = ( nsCodeQOR::CTLRef< _tChar > Src )
		{
			BaseName::operator = ( Src );
			return *this;
		}

		//--------------------------------------------------------------------------------
		//TODO: Use proper collation ordering
		bool operator == ( const CString< _tChar >& Src ) const
		{
			bool bResult = ( BaseName::Len() == Src.Len() ) ? true : false;

			if( bResult && BaseName::Len() > 0 )
			{
				bResult = ( memcmp( operator const _tChar *(), Src.operator const _tChar *(), BaseName::Len() ) == 0 );
			}
			return bResult;
		}

        //--------------------------------------------------------------------------------
        operator const _tChar* ( void ) const
        {
            return BaseName::operator const _tChar*();
        }

        //--------------------------------------------------------------------------------
		//TODO: Use proper collation ordering
        bool operator < ( const CString< _tChar >& Src ) const
        {
            bool bResult = false;
			//
			return bResult;
        }

        //--------------------------------------------------------------------------------
        virtual ~CString()
        {
        }

        //--------------------------------------------------------------------------------
        nsCodeQOR::CTCRef< CString< _tChar > > operator()( void )
        {
			nsCodeQOR::CTCRef< CString< _tChar > > ref( this );
			return ref;
        }

		//--------------------------------------------------------------------------------
		virtual unsigned short ClassHeaderByteSize( void ) const
		{
			return sizeof( sWinHeader );
		}

		//--------------------------------------------------------------------------------
		virtual void HeaderOnResize( byte* pOld, byte* pNew )
		{
			sWinHeader* pOldHeader = reinterpret_cast< sWinHeader* >( pOld - sizeof( sWinHeader ) );
			sWinHeader* pNewHeader = reinterpret_cast< sWinHeader* >( pNew - sizeof( sWinHeader ) );
			if( pOld )
			{
				pNewHeader->ulLocaleID = pOldHeader->ulLocaleID;
			}
			else
			{
				pNewHeader->ulLocaleID = 0xDFDFDFDF;
			}
		}

		//--------------------------------------------------------------------------------
		nsCodeQOR::CTLRef< _tChar > DetachBuffer( void )
		{
			_tRawAllocator allocator;
			_tChar* pDetachedBuffer = reinterpret_cast< _tChar* >( allocator.Source( sizeof( _tChar ) * InternalLen() ) );
			memcpy( pDetachedBuffer, BaseName::m_p, BaseName::InternalLen() );
			BaseName::SetSize( 0 );
			nsCodeQOR::CTLRef< _tChar > Result( pDetachedBuffer, true );
			return Result;
		}

	};

	typedef CString< char > CAStringBase;

	class __QOR_INTERFACE( __WINQL ) CWString;
	class __QOR_INTERFACE( __WINQL ) CAString;

#	if ( __QOR_UNICODE )
	typedef CWString CTString;
#else
	typedef CAString CTString;
#endif

	//--------------------------------------------------------------------------------
	class __QOR_INTERFACE( __WINQL ) CAString : public CAStringBase
	{
		typedef CAStringBase BaseName;

	public:

		CAString();

		CAString( nsCodeQOR::CTLRef< char > Src );
		CAString( const CAString& src );
		CAString( const char*, unsigned short usLen = 0 );
		virtual ~CAString();
		CAString& operator = ( const CAString& src );
		CAString& operator = ( nsCodeQOR::CTLRef< char > Src );

        //--------------------------------------------------------------------------------
        operator const char* ( void ) const
        {
            return BaseName::operator const char*();
        }

        //--------------------------------------------------------------------------------
        bool operator < ( const CAString& Cmp ) const
        {
			if( BaseName::Len() == 0 && Cmp.Len() > 0 )
			{
				return true;
			}
			if( BaseName::Len() >= 0 && Cmp.Len() == 0 )
			{
				return false;
			}

			bool bResult = ( strcmp( operator const char *(), Cmp.operator const char *() ) < 0 ) ? true : false;
			return bResult;
        }

		nsCodeQOR::CTLRef< char > DetachBufffer( void );

		int Format( CAString& Fmt, va_list arglist );
		int Format( const char* szFmt, va_list arglist );
		int FormatV( CAString& Fmt, ... );
		int FormatV( const char* szFmt, ... );
		CAString toAString( void ) const;
		nsWin32::CTString toTString( void ) const;
		CWString toWString( void ) const;
		CAString& toUpper( void );
		CAString& toLower( void );
		static CAString& TheEmptyString( void );

		//--------------------------------------------------------------------------------
		ref_type Ref( void )
		{
			return ref_type( this );
		}

	};

	typedef CString< wchar_t > CWStringBase;

	//--------------------------------------------------------------------------------
	class __QOR_INTERFACE( __WINQL ) CWString : public CWStringBase
	{
		typedef CWStringBase BaseName;

	public:

		CWString();
		CWString( const CWString& src );
		CWString( const wchar_t*, unsigned short usLen = 0 );
		virtual ~CWString();
		CWString& operator = ( const CWString& src );
		CWString& operator = ( const wchar_t* src );
		CWString& operator = ( const nsCodeQOR::CTLRef< wchar_t >& Src );
		bool operator == ( const CWString& Cmp ) const;
		bool operator < ( const CWString& Cmp ) const;

        //--------------------------------------------------------------------------------
        operator const wchar_t* ( void ) const
        {
            return BaseName::operator const wchar_t*();
        }

		int Format( CWString& Fmt, va_list arglist );
		int Format( const wchar_t* szFmt, va_list arglist );
		int FormatV( CWString& Fmt, ... );
		int FormatV( const wchar_t* szFmt, ... );
		nsWin32::CTString toTString( void ) const;
		CAString toAString( void ) const;
		CWString toWString( void ) const;
		CWString& toUpper( void );
		CWString& toLower( void );
		static CWString& TheEmptyString( void );

		//--------------------------------------------------------------------------------
		ref_type Ref( void )
		{
			return ref_type( this );
		}
	};

	typedef CAString::ref_type CAStringRef;
	typedef CWString::ref_type CWStringRef;
	typedef CTString::ref_type CTStringRef;

}//nsWin32

#endif//WINQL_CS_TXT_STRING_H_1