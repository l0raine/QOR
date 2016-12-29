//BfXmlAttributes.h

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

// SAX Attributes

#ifndef BLUEFOOT_XML_SAX_ATTRIBUTES_H_3
#define BLUEFOOT_XML_SAX_ATTRIBUTES_H_3

#ifdef	__QCMP_OPTIMIZEINCLUDE
#pragma	__QCMP_OPTIMIZEINCLUDE
#endif//__QCMP_OPTIMIZEINCLUDE

//
#include "CompilerQOR.h"
#include "CodeQOR/Text/TString.h"
#include <vector>

//------------------------------------------------------------------------------
namespace nsBluefoot
{
	//------------------------------------------------------------------------------
	class __QOR_INTERFACE( __BLUEFOOTQOR ) CXmlAttributes
	{
	public:

		__QOR_DECLARE_OCLASS_ID( CXmlAttributes );

		CXmlAttributes();
		virtual ~CXmlAttributes();

		int Index( const nsCodeQOR::CUCS2String& qName ) const;
		//int index( const QLatin1String& qName) const;
		int Index( const nsCodeQOR::CUCS2String& uri, const nsCodeQOR::CUCS2String& localPart) const;
		int Length() const;

		//------------------------------------------------------------------------------
		__QCMP_INLINE int Count() const
		{
			return Length();
		}

		nsCodeQOR::CUCS2String LocalName( int index ) const;
		nsCodeQOR::CUCS2String QName( int index ) const;
		nsCodeQOR::CUCS2String Uri( int index ) const;
		nsCodeQOR::CUCS2String Type( int index ) const;
		nsCodeQOR::CUCS2String Type( const nsCodeQOR::CUCS2String& qName ) const;
		nsCodeQOR::CUCS2String Type( const nsCodeQOR::CUCS2String& uri, const nsCodeQOR::CUCS2String& localName ) const;
		nsCodeQOR::CUCS2String Value( int index ) const;
		nsCodeQOR::CUCS2String Value( const nsCodeQOR::CUCS2String& qName ) const;
		//std::string value( const QLatin1String& qName ) const;
		nsCodeQOR::CUCS2String Value( const nsCodeQOR::CUCS2String& uri, const nsCodeQOR::CUCS2String& localName ) const;

		void Clear();
		void Append( const nsCodeQOR::CUCS2String& qName, const nsCodeQOR::CUCS2String& uri, const nsCodeQOR::CUCS2String& localPart, const nsCodeQOR::CUCS2String& value );

	private:

		//------------------------------------------------------------------------------
		struct Attribute 
		{
			nsCodeQOR::CUCS2String qname, uri, localname, value;
		};

		typedef std::vector< Attribute > AttributeList;
		AttributeList m_AttList;

		//CXmlAttributesPrivate* d;
	};

}//nsBluefoot

#endif//BLUEFOOT_XML_SAX_ATTRIBUTES_H_3