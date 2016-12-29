//Char32.cpp

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

//32-bit Character type

#include "CodeQOR/Text/Char32.h"
#include "CodeQOR/Text/Char16.h"
#include "CodeQOR/Text/Char8.h"
#include "CodeQOR/CodePages/CodePage.h"
#include "AppocritaQOR/SubSystems/Thread.h"

//------------------------------------------------------------------------------
namespace nsCodeQOR
{

	//------------------------------------------------------------------------------
	CChar32::CChar32() : CChar()
	{
	}		

	//------------------------------------------------------------------------------
	CChar32::CChar32( unsigned int ch ) : CChar( ch )
	{
	}

	//------------------------------------------------------------------------------
	CChar32::CChar32( int rc )
	{
		m = ( static_cast< unsigned int >( rc ) );
	}

	//------------------------------------------------------------------------------
	CChar32::CChar32( CChar8 ch )
	{
		m = ch.Unicode();
	}

	//------------------------------------------------------------------------------
	CChar32::CChar32( CChar16 ch )
	{
		m = ch.Unicode();
	}

	//------------------------------------------------------------------------------
	CChar32::CChar32( const CChar32& ch )
	{
		m = ch.m;
	}

	//------------------------------------------------------------------------------
	CChar32::CChar32( unsigned short usLowWord, unsigned short usHighWord )
	{
		m = ( unsigned int( ( usHighWord << 16 ) | usLowWord ) );
	}
		
	//------------------------------------------------------------------------------
	CChar32::CChar32( CChar32::eSpecialCharacter sc )
	{
		m = ( static_cast< unsigned int >( sc ) );
	}

	//------------------------------------------------------------------------------
	CChar32 CChar32::MirroredChar() const
	{
		return CChar32( static_cast< unsigned int >( m + UnicodeGetProp( static_cast< ULookupType >( m ) )->mirrorDiff ) );
	}

	//------------------------------------------------------------------------------
	CTString< CChar32 > CChar32::Decomposition() const
	{
		unsigned short buffer[ 3 ];
		int length;
		int tag;
		const unsigned short *d = DecompositionHelper( static_cast< unsigned int >( m ), &length, &tag, buffer );
		return CTString< CChar32 >( (CChar32*) d, static_cast< unsigned short >( length ) );
	}

	//------------------------------------------------------------------------------
	CChar32 CChar32::ToLower() const
	{
		const nsUnicodeTables::Properties* p = UnicodeGetProp( static_cast< ULookupType >( m ) );
		if( !p->lowerCaseSpecial )
		{
			return m + p->lowerCaseDiff;
		}
		return m;
	}

	//------------------------------------------------------------------------------
	CChar32 CChar32::ToUpper() const
	{
		const nsUnicodeTables::Properties* p = UnicodeGetProp( static_cast< ULookupType >( m ) );
		if( !p->upperCaseSpecial )
		{
			return m + p->upperCaseDiff;
		}
		return m;
	}

	//------------------------------------------------------------------------------
	CChar32 CChar32::ToTitleCase() const
	{
		const nsUnicodeTables::Properties* p = UnicodeGetProp( static_cast< ULookupType >( m ) );
		if( !p->titleCaseSpecial )
		{
			return m + p->titleCaseDiff;
		}
		return m;
	}

	//------------------------------------------------------------------------------
	CChar32 CChar32::ToCaseFolded() const
	{
		return m + UnicodeGetProp( m )->caseFoldDiff;
	}

	//------------------------------------------------------------------------------
	const char CChar32::ToAscii() const
	{
		/*
	#ifndef QT_NO_CODEC_FOR_C_STRINGS
		if (QTextCodec::codecForCStrings())
			// #####
			return QTextCodec::codecForCStrings()->fromUnicode(QString(*this)).at(0);
	#endif
	*/
		return m > 0xff ? 0 : char( m );
	}

	//--------------------------------------------------------------------------------
	CChar32 CChar32::FromAscii( char c )
	{
		/*
	#ifndef QT_NO_CODEC_FOR_C_STRINGS
		if (QTextCodec::codecForCStrings())
			// #####
			return QTextCodec::codecForCStrings()->toUnicode(&c, 1).at(0).unicode();
	#endif
	*/
		return CChar32( static_cast< unsigned int >( static_cast< unsigned char >( c ) ) );
	}

	//------------------------------------------------------------------------------
	const unsigned int CChar32::Unicode() const 
	{ 
		return m; 
	}

	//------------------------------------------------------------------------------
	unsigned int& CChar32::Unicode() 
	{ 
		return m; 
	}

	//------------------------------------------------------------------------------
	CChar8 CChar32::ToLocal8Bit( void ) const
	{
		CChar8 c;
		nsQOR::IThread::ref_type pCurrentThread = nsQOR::CThread::GetCurrent();

		if( pCurrentThread->GetCodePage() )
		{
			c = static_cast< unsigned char >( pCurrentThread->GetCodePage()->Encode( m ) );
		}
		else
		{
			c = static_cast< unsigned char >( m );
		}
		return c;
	}

	/*
	//------------------------------------------------------------------------------
    __QOR_INTERFACE( __CODEQOR ) bool operator == ( const CChar32& x0, const CChar32& x1 )
	{
		return x0.m == x1.m;
	}
	*/
	//------------------------------------------------------------------------------
	__QOR_INTERFACE( __CODEQOR ) bool operator != ( const CChar32& x0, const CChar32& x1 )
	{
		return x0.m != x1.m;
	}
	
	//------------------------------------------------------------------------------
	__QOR_INTERFACE( __CODEQOR ) bool operator != ( const CChar32& x0, const int x1 )
	{
		return x0.m != static_cast< unsigned int >( x1 );
	}
	
	//------------------------------------------------------------------------------
	__QOR_INTERFACE( __CODEQOR ) bool operator <= ( const CChar32& x0, const CChar32& x1 )
	{
		return x0.m <= x1.m;
	}

	//------------------------------------------------------------------------------
	__QOR_INTERFACE( __CODEQOR ) bool operator >= ( const CChar32& x0, const CChar32& x1 )
	{
		return x0.m >= x1.m;
	}

	//------------------------------------------------------------------------------
	__QOR_INTERFACE( __CODEQOR ) bool operator < ( const CChar32& x0, const CChar32& x1 )
	{
		return x0.m < x1.m;
	}

	//------------------------------------------------------------------------------
	__QOR_INTERFACE( __CODEQOR ) bool operator > ( const CChar32& x0, const CChar32& x1 )
	{
		return x0.m > x1.m;
	}

}//nsCodeQOR
