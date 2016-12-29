//BfXmlParseException.h

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

// SAX Exception Classes

#ifndef BLUEFOOT_XML_SAX_PARSEEXCEPTION_H_3
#define BLUEFOOT_XML_SAX_PARSEEXCEPTION_H_3

#ifdef	__QCMP_OPTIMIZEINCLUDE
#pragma	__QCMP_OPTIMIZEINCLUDE
#endif//__QCMP_OPTIMIZEINCLUDE

#include "CodeQOR/Text/TString.h"

//------------------------------------------------------------------------------
namespace nsBluefoot
{

	//------------------------------------------------------------------------------
	class __QOR_INTERFACE( __BLUEFOOTQOR ) CXmlParseException
	{
	public:
		
		__QOR_DECLARE_OCLASS_ID( CXmlParseException );

		explicit CXmlParseException( const nsCodeQOR::CUCS2String& name = nsCodeQOR::CUCS2String(), int c = -1, int l = -1, const nsCodeQOR::CUCS2String& p = nsCodeQOR::CUCS2String(), const nsCodeQOR::CUCS2String& s = nsCodeQOR::CUCS2String() );
		CXmlParseException( const CXmlParseException &other );
		CXmlParseException& operator = ( const CXmlParseException &other );
		~CXmlParseException();

		int ColumnNumber() const;
		int LineNumber() const;
		nsCodeQOR::CUCS2String PublicId() const;
		nsCodeQOR::CUCS2String SystemId() const;
		nsCodeQOR::CUCS2String Message() const;

	private:

		nsCodeQOR::CUCS2String m_Msg;
		int m_Column;
		int m_Line;
		nsCodeQOR::CUCS2String m_Pub;
		nsCodeQOR::CUCS2String m_Sys;
	};

}//nsBluefoot

#endif//BLUEFOOT_XML_SAX_PARSEEXCEPTION_H_3
