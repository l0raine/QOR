//StringSink.h

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

#ifndef BLUEFOOT_SINKS_STRING_H_3
#define BLUEFOOT_SINKS_STRING_H_3

#ifdef	__QCMP_OPTIMIZEINCLUDE
#pragma	__QCMP_OPTIMIZEINCLUDE
#endif//__QCMP_OPTIMIZEINCLUDE

//Defines a Sink for a Bluefoot pipeline

#include "BluefootQOR/BFSink.h"
#include "CodeQOR/Text/TString.h"
#include "CodeQOR/Text/Char.h"

//------------------------------------------------------------------------------
namespace nsBluefoot
{
	//------------------------------------------------------------------------------
	template< typename _tChar > 
	class __QOR_INTERFACE( __BLUEFOOTQOR ) CStringSink : public CSink
	{
	public:

		//------------------------------------------------------------------------------
		CStringSink()
		{
		}

		//------------------------------------------------------------------------------
		virtual ~CStringSink()
		{
		}

		//------------------------------------------------------------------------------
		CStringSink( const CStringSink& src )
		{
			*this = src;
		}

		//------------------------------------------------------------------------------
		CStringSink& operator = (const CStringSink& src)
		{
			if( &src != this )
			{
				m_strSink = src.m_strSink;
			}
			return *this;
		}

		//------------------------------------------------------------------------------
		virtual bool Write( unsigned long& ulUnitsWritten, unsigned long ulUnitsToWrite = 1 )
		{
			bool bResult = false;
			unsigned long ulUnitsRead = 0;
			if( GetMode() == ePull )
			{			
				GetSource()->Read( ulUnitsRead, ulUnitsToWrite );
				bResult = ulUnitsRead > 0 ? true : false;
			}
			
			_tChar* pTChar = reinterpret_cast< _tChar* >( GetSource()->GetBuffer()->ReadRequest( ulUnitsToWrite ) );
			if( ulUnitsToWrite > 0 )
			{
				bResult = bResult || true;
				m_strSink.Append( const_cast< const _tChar* >( pTChar ), static_cast< unsigned short >( ulUnitsToWrite ) );
				ulUnitsWritten = ulUnitsToWrite;
				GetSource()->GetBuffer()->ReadAcknowledge( ulUnitsWritten );
			}
			return bResult;
		}

		//------------------------------------------------------------------------------
		nsCodeQOR::CTString< _tChar >& GetData( void )
		{
			return m_strSink;
		}

	protected:

		nsCodeQOR::CTString< _tChar > m_strSink;

	};

	typedef CStringSink< nsCodeQOR::CChar8 > ANSIStringSink;
	typedef CStringSink< nsCodeQOR::CChar16 > UTF16StringSink;
	typedef CStringSink< nsCodeQOR::CChar32 > CUCS4StringSink;

}//nsBluefoot

#endif//BLUEFOOT_SINKS_STRING_H_3
