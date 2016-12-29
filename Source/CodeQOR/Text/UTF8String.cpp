//UTF8String.cpp

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

#include "CompilerQOR.h"
#include "CodeQOR/Text/UTF8String.h"
#include "CodeQOR/Text/UTF16String.h"
#include "CodeQOR/Text/UTF32String.h"
#include "AppocritaQOR/Event.h"

//------------------------------------------------------------------------------
namespace nsCodeQOR
{
	//--------------------------------------------------------------------------------
	CUTF8Char CUTF8String::begin( void )
	{
		CUTF8Char it( m_String.GetBuffer() );
		m_String.ReleaseBuffer();
		return it;
	}

	//--------------------------------------------------------------------------------
	CUTF8Char CUTF8String::end( void )
	{
		CUTF8Char it( m_String.GetBuffer() + m_String.Len() );
		m_String.ReleaseBuffer();
		return it;
	}

	//--------------------------------------------------------------------------------
	void CUTF8String::CountChars()
	{
		m_bEncodingValidated = false;
		CUTF8Char it = begin();
		while( ++it != end() && !it.IsInvalid() )
		{
			m_usCharCount++;
		}
		if( !it.IsInvalid() )
		{
			m_bEncodingValidated = true;
		}
	}

	//--------------------------------------------------------------------------------
	CUTF8Char CUTF8String::CharAt( unsigned short usPos )
	{
		CUTF8Char Ch( m_String.GetBuffer() );
		m_String.ReleaseBuffer();
		while( usPos-- )
		{
			++Ch;
		}
		return Ch;
	}

    //--------------------------------------------------------------------------------
    CUTF8String::CUTF8String() : m_String()
    {
		m_String.SetCodePage( CCodePage::eUTF8 );
		m_usCharCount = 0;
		m_bEncodingValidated = true;
    }

	//--------------------------------------------------------------------------------
    CUTF8String::CUTF8String( const CChar8* cpString, unsigned short usSrcLen ) : m_String( cpString, usSrcLen )
    {
		m_String.SetCodePage( CCodePage::eUTF8 );
		CountChars();
    }

    //--------------------------------------------------------------------------------
    CUTF8String::CUTF8String( const CChar8* cpString, unsigned short usSrcLen, unsigned short usInitialBufferSize ) : m_String( cpString, usSrcLen, usInitialBufferSize )
    {
		m_String.SetCodePage( CCodePage::eUTF8 );
		CountChars();
    }

	//--------------------------------------------------------------------------------
	CUTF8String::CUTF8String( const CUTF8String& Src ) : m_String( Src.m_String ), m_usCharCount( Src.m_usCharCount ), m_bEncodingValidated( Src.m_bEncodingValidated )
	{
	}

	//--------------------------------------------------------------------------------
	CUTF8String::CUTF8String( const CUTF16String& Src ) : m_String(), m_usCharCount( 0 ), m_bEncodingValidated( true )
	{
		CChar8 utf8[ 4 ];
		CUTF8Char Ch;
		CUTF16String& vSrc( const_cast< CUTF16String& >( Src ) );
		CUTF16Char SrcIt = vSrc.begin();
		Ch.Attach( utf8 );
		while( SrcIt != vSrc.end() )
		{
			unsigned int uiCodePoint = SrcIt.ToCodePoint();
			utf8[ 0 ].m = 0;
			utf8[ 1 ].m = 0;
			utf8[ 2 ].m = 0;
			utf8[ 3 ].m = 0;
			if( uiCodePoint < 0x80 )
			{
				utf8[ 0 ] = static_cast< byte >( uiCodePoint );
				Append( CUTF8String( Ch ) );
			}
			else if( uiCodePoint < 0x7FF )
			{
				utf8[ 0 ] = static_cast< byte >( ( uiCodePoint >> 6 ) + 0xC0 );
				utf8[ 1 ] = static_cast< byte >( ( uiCodePoint & 0x3F ) + 0x80 );
				Append( CUTF8String( Ch ) );				
			}
			else if( uiCodePoint < 0xFFFF )
			{
				utf8[ 0 ] = static_cast< byte >( ( uiCodePoint >> 12 ) + 0xE0 );
				utf8[ 1 ] = static_cast< byte >( ( ( uiCodePoint >> 6 ) & 0x3F ) + 0x80 );
				utf8[ 2 ] = static_cast< byte >( ( uiCodePoint & 0x3F ) + 0x80 );
				Append( CUTF8String( Ch ) );
			}
			else if( uiCodePoint < 0x10FFFF )
			{
				utf8[ 0 ] = static_cast< byte >( ( uiCodePoint >> 18 ) + 0xF0 );
				utf8[ 1 ] = static_cast< byte >( ( ( uiCodePoint >> 12 ) & 0x3F ) + 0x80 );
				utf8[ 2 ] = static_cast< byte >( ( ( uiCodePoint >> 6 ) & 0x3F ) + 0x80 );
				utf8[ 3 ] = static_cast< byte >( ( uiCodePoint & 0x3F ) + 0x80 );
				Append( CUTF8String( Ch ) );
			}

			++SrcIt;
		}
	}

	//--------------------------------------------------------------------------------
	CUTF8String::CUTF8String( const CUTF32String& Src ) : m_String(), m_usCharCount( 0 ), m_bEncodingValidated( true )
	{
		CChar8 utf8[ 4 ];
		CUTF8Char Ch;
		CUTF32String& vSrc( const_cast< CUTF32String& >( Src ) );
		CChar32* SrcIt = vSrc.begin();
		Ch.Attach( utf8 );
		while( SrcIt != vSrc.end() )
		{
			unsigned int uiCodePoint = ( *SrcIt ).m;
			utf8[ 0 ].m = 0;
			utf8[ 1 ].m = 0;
			utf8[ 2 ].m = 0;
			utf8[ 3 ].m = 0;
			if( uiCodePoint < 0x80 )
			{
				utf8[ 0 ] = static_cast< byte >( uiCodePoint );
				Append( CUTF8String( Ch ) );
			}
			else if( uiCodePoint < 0x7FF )
			{
				utf8[ 0 ] = static_cast< byte >( ( uiCodePoint >> 6 ) + 0xC0 );
				utf8[ 1 ] = static_cast< byte >( ( uiCodePoint & 0x3F ) + 0x80 );
				Append( CUTF8String( Ch ) );				
			}
			else if( uiCodePoint < 0xFFFF )
			{
				utf8[ 0 ] = static_cast< byte >( ( uiCodePoint >> 12 ) + 0xE0 );
				utf8[ 1 ] = static_cast< byte >( ( ( uiCodePoint >> 6 ) & 0x3F ) + 0x80 );
				utf8[ 2 ] = static_cast< byte >( ( uiCodePoint & 0x3F ) + 0x80 );
				Append( CUTF8String( Ch ) );
			}
			else if( uiCodePoint < 0x10FFFF )
			{
				utf8[ 0 ] = static_cast< byte >( ( uiCodePoint >> 18 ) + 0xF0 );
				utf8[ 1 ] = static_cast< byte >( ( ( uiCodePoint >> 12 ) & 0x3F ) + 0x80 );
				utf8[ 2 ] = static_cast< byte >( ( ( uiCodePoint >> 6 ) & 0x3F ) + 0x80 );
				utf8[ 3 ] = static_cast< byte >( ( uiCodePoint & 0x3F ) + 0x80 );
				Append( CUTF8String( Ch ) );
			}

			++SrcIt;
		}
	}

    //--------------------------------------------------------------------------------
    CUTF8String::CUTF8String( nsCodeQOR::CTLRef< CChar8 > Src ) : m_String( Src )
    {
		m_String.SetCodePage( CCodePage::eUTF8 );
		CountChars();
    }

	//--------------------------------------------------------------------------------
	CUTF8String::CUTF8String( CChar8 c ) : m_String( c )
	{
		m_String.SetCodePage( CCodePage::eUTF8 );
		CountChars();
	}

	//--------------------------------------------------------------------------------
	CUTF8String::CUTF8String( CTString< CChar8, CDefaultSource >::ref_type Src ) : m_String( Src )
	{
		if( GetCodePage() != CCodePage::eUTF8 )
		{
			operator = ( CUTF32String( *this ).ToUTF8String() );
		}
	}

    //--------------------------------------------------------------------------------
    CUTF8String::CUTF8String( const CTString< CChar8, CDefaultSource >& Src ) : m_String( Src )
    {
		if( GetCodePage() != CCodePage::eUTF8 )
		{
			operator = ( CUTF32String( *this ).ToUTF8String() );
		}
    }

	//--------------------------------------------------------------------------------
	CUTF8String& CUTF8String::operator = ( const CUTF8String& Src )
	{
		if( &Src != this )
		{
			m_String = Src.m_String;
			m_usCharCount = Src.m_usCharCount;
			m_bEncodingValidated = Src.m_bEncodingValidated;
		}
		return *this;
	}

    //--------------------------------------------------------------------------------
    CUTF8String& CUTF8String::operator = ( const CTString< CChar8, CDefaultSource >& Src )
    {
		m_String = Src;
		if( GetCodePage() != CCodePage::eUTF8 )
		{
			operator = ( CUTF32String( *this ).ToUTF8String() );
		}
        return *this;
    }

	//--------------------------------------------------------------------------------
	CUTF8String& CUTF8String::operator = ( CTString< CChar8, CDefaultSource >::ref_type Src )
	{
		m_String = Src;
		if( GetCodePage() != CCodePage::eUTF8 )
		{
			operator = ( CUTF32String( *this ).ToUTF8String() );
		}
		return *this;
	}

	//--------------------------------------------------------------------------------
	CUTF8String& CUTF8String::operator = ( CChar8 c )
	{
		operator = ( CTString< CChar8, CDefaultSource >( c ) );
		CountChars();
		return *this;
	}
		
	//--------------------------------------------------------------------------------
	unsigned short CUTF8String::GetCodePage() const
	{
		return m_String.GetCodePage();
	}

    //--------------------------------------------------------------------------------
	//Returns UTF8 character count
    unsigned short CUTF8String::Length() const
    {
		return m_usCharCount;
    }

	//--------------------------------------------------------------------------------
	bool CUTF8String::IsEmpty( void ) const
	{
		return m_String.IsEmpty();
	}

    //--------------------------------------------------------------------------------
    //Two Strings are equal if they contain equal data
    bool CUTF8String::operator == ( const CTString< CChar8, CDefaultSource >& Src ) const
    {
		return m_String == Src;
    }

    //--------------------------------------------------------------------------------
    bool CUTF8String::operator < ( const CTString< CChar8, CDefaultSource >& Cmp ) const
    {
		return m_String < Cmp;
    }

    //--------------------------------------------------------------------------------
    CUTF8String::~CUTF8String()
    {
    }

	//--------------------------------------------------------------------------------
	CUTF8Char CUTF8String::At( unsigned short usPos )
	{
		CUTF8Char it = begin();
		it += usPos;
		return it;
	}

	//--------------------------------------------------------------------------------
	bool CUTF8String::ValidateReference( CUTF8Char Ch )
	{
		if( Ch.IsNull() )
		{
			return false;
		}

		CChar8* pBuffer = m_String.GetBuffer();
		bool bResult = ( Ch.ptr() >= pBuffer && Ch.ptr() < ( pBuffer + m_String.Len() ) && !Ch.IsInvalid() );
		m_String.ReleaseBuffer();
		return bResult;
	}

	//--------------------------------------------------------------------------------
	bool CUTF8String::Set( unsigned short usPos, CUTF8Char ch )
	{
		bool bResult = false;
		CUTF8Char Ref = CharAt( usPos );
		if( ValidateReference( Ref ) )
		{
			short sShift = Ref.Len() - ch.Len();

			if( sShift > 0 )
			{
				m_String.Remove( static_cast< unsigned short >( Ref.ptr() - m_String.GetBuffer() ), sShift );	
				m_String.ReleaseBuffer();
			}		
			else if( sShift < 0 )
			{
				CUTF8String strInsert( const_cast< CChar8* >( ch.ptr() ), static_cast< unsigned short >( 0 - sShift ) );
			}
			memcpy( Ref.ptr(), ch.ptr(), Ref.Len() - sShift );
			bResult = true;
		}
		return bResult;
	}

	//--------------------------------------------------------------------------------
	CUTF8String& CUTF8String::Insert(  unsigned short usPos, CUTF8String& Src )
	{
		if( usPos > m_usCharCount )
		{
			usPos = m_usCharCount;
		}
		CUTF8Char Ref = CharAt( usPos );
		m_String.Insert( static_cast< unsigned short >( Ref.ptr() - m_String.GetBuffer() ), Src.m_String );
		m_String.ReleaseBuffer();
		CountChars();
		return *this;
	}

	//--------------------------------------------------------------------------------
	CUTF8String& CUTF8String::Remove( unsigned short usPos, unsigned short usCount )
	{
		CUTF8Char Begin = CharAt( usPos );
		CUTF8Char End = CharAt( usPos + usCount );

		m_String.Remove( static_cast< unsigned short >( Begin.ptr() - m_String.GetBuffer() ), static_cast< unsigned short >( End.ptr() - Begin.ptr() ) );
		m_String.ReleaseBuffer();
		CountChars();
		return *this;
	}

	//--------------------------------------------------------------------------------
	CUTF8String& CUTF8String::Clear( void )
	{
		m_String.Clear();
		m_usCharCount = 0;
		m_bEncodingValidated = true;
		return *this;
	}

    //--------------------------------------------------------------------------------
	CUTF8String& CUTF8String::Append( CChar8 ch )
	{
		return Append( const_cast< const CChar8* >( &ch ), 1 );
	}

	//--------------------------------------------------------------------------------
    CUTF8String& CUTF8String::Append( const CChar8* cpString, unsigned short usSrcLen )
    {
		m_String.Append( cpString, usSrcLen );
		CountChars();
        return *this;
    }

	//--------------------------------------------------------------------------------
	CUTF8String& CUTF8String::Append( const CUTF8String& Str )
	{
		return Append( Str.m_String, Str.m_String.Len() );
	}

	//--------------------------------------------------------------------------------
	CUTF8String CUTF8String::Left( unsigned short usLen )
	{
		CUTF8Char Pos = CharAt( usLen );
		CUTF8String Result( m_String.Left( static_cast< unsigned short >( Pos.ptr() - m_String.GetBuffer() ) ) );
		m_String.ReleaseBuffer();
		return Result;
	}

	//--------------------------------------------------------------------------------
	CUTF8String CUTF8String::Right( unsigned short usLen )
	{
		CUTF8Char Pos = CharAt( m_usCharCount - usLen );
		CUTF8Char End = --end();
		return CUTF8String( m_String.Right( static_cast< unsigned short >( End.ptr() - Pos.ptr() ) ) );
	}

	//--------------------------------------------------------------------------------
	CUTF8String CUTF8String::Mid( unsigned short usPos, short usLen )
	{
		CUTF8Char Begin = CharAt( usPos );
		CUTF8Char End( Begin );
		End += usLen;
		return CUTF8String( m_String.Mid( static_cast< unsigned short >( Begin.ptr() - m_String.GetBuffer() ), static_cast< unsigned short >( End.ptr() - Begin.ptr() ) ) );
	}

	//--------------------------------------------------------------------------------
	CUTF8String CUTF8String::TrimLeft()
	{
		CTrimLeftFunctor F;
		return ProcessByChar( F, 0 );
	}

	//--------------------------------------------------------------------------------
	CUTF8String CUTF8String::TrimRight()
	{		
		CTrimRightFunctor F;
		return ReverseProcessByChar( F, m_usCharCount );
	}


	//--------------------------------------------------------------------------------
	//Process the string through a functor one character at a time
	CUTF8String CUTF8String::ProcessByChar( CCharProcessorFunctor& ProcessFunctor, unsigned short usPos )
	{
		CUTF8String strResult;
		CUTF8Char Pos = CharAt( usPos );
		while( Pos != end() && ProcessFunctor( strResult, Pos ) == eProcessResultMore )
		{
			++Pos;
		}
		return strResult;
	}

	//--------------------------------------------------------------------------------
	//Process the string through a functor one character at a time in reverse
	CUTF8String CUTF8String::ReverseProcessByChar( CCharProcessorFunctor& ProcessFunctor, unsigned short usPos )
	{
		CUTF8String strResult;
		CUTF8Char Pos = CharAt( usPos );
		while( Pos.ptr() >= begin() && ProcessFunctor( strResult, Pos ) == eProcessResultMore )
		{
			--Pos;
		}
		return strResult;
	}

	//--------------------------------------------------------------------------------
	//Process the string through a functor to find the beginning and end of substrings and then process each substring through a second functor
	//This can be used as the basis for tokenizing a string, the beginning of language parsing.
	void CUTF8String::ProcessForSubString( CCharProcessorFunctor& CharFunctor, CStringProcessorFunctor& StringFunctor, unsigned short usPos )
	{
		CUTF8String strResult;
		CUTF8Char Pos = CharAt( usPos );
		do
		{				
			strResult.Clear();
			while( Pos.ptr() != end() && CharFunctor( strResult, Pos ) != eProcessResultBegin )
			{
				++Pos;
			}
			
			while( Pos.ptr() != end() && CharFunctor( strResult, Pos ) == eProcessResultMore )
			{
			}
		}while( StringFunctor( strResult ) != eProcessResultEnd );
	}

	//--------------------------------------------------------------------------------
	//Reserve memory for the string in advance if you plan to make many small appends
	void CUTF8String::Reserve( unsigned short usCharCount )
	{
		m_String.Reserve( usCharCount * eUTF8MaxBytes );
	}

	//--------------------------------------------------------------------------------
	unsigned short CUTF8String::BufferByteCount( void )
	{
		return m_String.Len();
	}

	//--------------------------------------------------------------------------------
	CUTF32String CUTF8String::ToUTF32String( void )
	{
		return CUTF32String( *this );
	}

	//--------------------------------------------------------------------------------
	CUTF16String CUTF8String::ToUTF16String( void )
	{
		return CUTF16String( *this );
	}

}//nsCodeQOR

