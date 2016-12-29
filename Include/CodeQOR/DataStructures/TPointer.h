//TPointer.h

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

//A managed object pointer

#ifndef CODEQOR_TPOINTER_H_2
#define CODEQOR_TPOINTER_H_2

#include "CompilerQOR.h"

#ifdef	__QCMP_OPTIMIZEINCLUDE
#pragma	__QCMP_OPTIMIZEINCLUDE
#endif//__QCMP_OPTIMIZEINCLUDE

//--------------------------------------------------------------------------------
namespace nsCodeQOR
{
	template< typename T > class TBox;

	//--------------------------------------------------------------------------------
	//A smart pointer template that encapsulates a boxed item
	//This is the generic type for all 'managed' object pointers
	template< typename T >
	class TPointer
	{
	public:

		//--------------------------------------------------------------------------------
		TPointer( TBox< T >* p ) : m_p( p )
		{
			m_p->AddRef();
		}

		//--------------------------------------------------------------------------------
		TPointer( const TPointer< T >& src ) : m_p( src.m_p )
		{
			m_p->AddRef();
		}

		//--------------------------------------------------------------------------------
		TPointer< T >& operator = ( const TPointer< T >& src )
		{
			m_p->Release();
			m_p = src.m_p;
			m_p->AddRef();
		}

		//--------------------------------------------------------------------------------
		virtual ~TPointer()
		{
			m_p->Release();
		}

		//--------------------------------------------------------------------------------
		T* operator -> ( void )
		{
			return m_p->operator->();
		}

		//--------------------------------------------------------------------------------
		T& operator * ( void )
		{
			return *( m_p->operator->() );
		}

		//--------------------------------------------------------------------------------
		T& operator []( unsigned int uiIndex )
		{
			return m_p->operator[]( uiIndex );
		}

	protected:

		//--------------------------------------------------------------------------------
		TBox< T >* Box( void )
		{
			return m_p;
		}

		TBox< T >* m_p;

	};

}//nsCodeQOR

#endif//CODEQOR_TPOINTER_H_2