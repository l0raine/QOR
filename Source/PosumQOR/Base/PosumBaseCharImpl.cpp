//PosumBaseCharImpl.cpp

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

#include "PosumQOR.h"
#include "PosumQOR/Base/PosumBaseCharImpl.h"

#include <ctype.h>

//--------------------------------------------------------------------------------
namespace nsPosum
{
	//--------------------------------------------------------------------------------
	CBaseCharImpl::CBaseCharImpl() : m_C( 0 )
	{
	}

	//--------------------------------------------------------------------------------
	CBaseCharImpl::CBaseCharImpl( unsigned int uiC ) : m_C( uiC )
	{
	}

	//--------------------------------------------------------------------------------
	CBaseCharImpl::CBaseCharImpl( const CBaseCharImpl& src ) : m_C( src.m_C )
	{
	}

	//--------------------------------------------------------------------------------
	CBaseCharImpl& CBaseCharImpl::operator = ( const CBaseCharImpl& src )
	{
		m_C = src.m_C;
		return *this;
	}

	//--------------------------------------------------------------------------------
	CBaseCharImpl& CBaseCharImpl::operator = ( const unsigned int& src )
	{
		m_C = src;
		return *this;
	}

	//--------------------------------------------------------------------------------
	CBaseCharImpl::~CBaseCharImpl()
	{
	}

	//--------------------------------------------------------------------------------
	bool CBaseCharImpl::IsAlphaNumeric( void )
	{
		return isalpha( static_cast<int>( m_C ) ) != 0 ? true : false;
	}

	//--------------------------------------------------------------------------------
	bool CBaseCharImpl::IsAlpha( void )
	{
		return isalpha( static_cast<int>( m_C ) ) != 0 ? true : false;
	}

	//--------------------------------------------------------------------------------
	bool CBaseCharImpl::IsBlank( void )
	{
		return isblank( static_cast<int>( m_C ) ) != 0 ? true : false;
	}

	//--------------------------------------------------------------------------------
	bool CBaseCharImpl::IsControl( void )
	{
		return iscntrl( static_cast<int>( m_C ) ) != 0 ? true : false;
	}

	//--------------------------------------------------------------------------------
	bool CBaseCharImpl::IsDigit( void )
	{
		return isdigit( static_cast<int>( m_C ) ) != 0 ? true : false;
	}

	//--------------------------------------------------------------------------------
	bool CBaseCharImpl::IsGraph( void )
	{
		return isgraph( static_cast<int>( m_C ) ) != 0 ? true : false;
	}

	//--------------------------------------------------------------------------------
	bool CBaseCharImpl::IsLowerCase( void )
	{
		return islower( static_cast<int>( m_C ) ) != 0 ? true : false;
	}

	//--------------------------------------------------------------------------------
	bool CBaseCharImpl::IsPrint( void )
	{
		return isprint( static_cast<int>( m_C ) ) != 0 ? true : false;
	}

	//--------------------------------------------------------------------------------
	bool CBaseCharImpl::IsPunctuation( void )
	{
		return ispunct( static_cast<int>( m_C ) ) != 0 ? true : false;
	}

	//--------------------------------------------------------------------------------
	bool CBaseCharImpl::IsSpace( void )
	{
		return isspace( static_cast<int>( m_C ) ) != 0 ? true : false;
	}

	//--------------------------------------------------------------------------------
	bool CBaseCharImpl::IsUpperCase( void )
	{
		return isupper( static_cast<int>( m_C ) ) != 0 ? true : false;
	}

	//--------------------------------------------------------------------------------
	bool CBaseCharImpl::IsXDigit( void )
	{
		return isxdigit( static_cast<int>( m_C ) ) != 0 ? true : false;
	}

	//--------------------------------------------------------------------------------
	bool CBaseCharImpl::IsASCII( void )
	{
		return isascii( static_cast<int>( m_C ) ) != 0 ? true : false;
	}

	//--------------------------------------------------------------------------------
	bool CBaseCharImpl::IsMultiByteAlphaNumeric( void )
	{
		return _ismbbalnum( m_C ) != 0 ? true : false;
	}

	//--------------------------------------------------------------------------------
	CBaseCharImpl CBaseCharImpl::ToLowerCase( void )
	{
		return CBaseCharImpl( tolower( static_cast<int>( m_C ) ) );
	}

	//--------------------------------------------------------------------------------
	CBaseCharImpl CBaseCharImpl::ToUpperCase( void )
	{
		return CBaseCharImpl( toupper( static_cast<int>( m_C ) ) );
	}

	//--------------------------------------------------------------------------------
	CBaseCharImpl CBaseCharImpl::ToASCII( void )
	{
		return CBaseCharImpl( toascii( static_cast< int >( m_C ) ) );
	}

}//nsPosum
