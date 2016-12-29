//BfFilter.cpp

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

//Implements a Bluefoot pipeline filter element base class

#include "BluefootQOR/BFFilter.h"

//------------------------------------------------------------------------------
namespace nsBluefoot
{
	//------------------------------------------------------------------------------
	CBFFilter::CBFFilter() : m_SinkProxy( *this ), m_SourceProxy( *this )
	{
		m_SinkProxy.SetParent( this );
		m_SourceProxy.SetParent( this );
	}

	//------------------------------------------------------------------------------
	CBFFilter::~CBFFilter()
	{

	}

	//------------------------------------------------------------------------------
	CBFFilter::CBFFilter( const CBFFilter& src ) : m_SinkProxy( *this ), m_SourceProxy( *this )
	{
		*this = src;
	}

	//------------------------------------------------------------------------------
	CBFFilter& CBFFilter::operator = ( const CBFFilter& src )
	{
		if (&src != this)
		{
			m_SinkProxy.SetSource( const_cast< CBFFilter& >( src ).m_SinkProxy.GetSource() );
			m_SourceProxy.SetSink( const_cast< CBFFilter& >( src ).m_SourceProxy.GetSink() );
		}
		return *this;
	}

	//------------------------------------------------------------------------------
	void CBFFilter::SetSource( CBFSource* pSource )
	{
		m_SinkProxy.SetSource( pSource );
	}

	//------------------------------------------------------------------------------
	CBFSource* CBFFilter::GetSource(void)
	{
		return m_SinkProxy.GetSource();
	}

	//------------------------------------------------------------------------------
	bool CBFFilter::Write( unsigned long& ulUnitsWritten, unsigned long ulUnitsToWrite )
	{
		return false;
	}

	//------------------------------------------------------------------------------
	void CBFFilter::SetSink( CBFSink* pSink )
	{
		m_SourceProxy.SetSink( pSink );
	}

	//------------------------------------------------------------------------------
	CBFSink* CBFFilter::GetSink( void )
	{
		return m_SourceProxy.GetSink();
	}

	//------------------------------------------------------------------------------
	bool CBFFilter::Read( unsigned long& ulUnitsRead, unsigned long ulUnitsToRead )
	{
		return false;
	}

	//------------------------------------------------------------------------------
	CBFSource* CBFFilter::AsSource()
	{
		return &m_SourceProxy;
	}

	//------------------------------------------------------------------------------
	CBFSink* CBFFilter::AsSink()
	{
		return &m_SinkProxy;
	}

}//nsBluefoot
