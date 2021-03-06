//Observer.h

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

//Observer pattern template helpers

#ifndef CODEQOR_OBSERVER_H_3
#define CODEQOR_OBSERVER_H_3

#include "CompilerQOR.h"

#ifdef	__QCMP_OPTIMIZEINCLUDE
#pragma	__QCMP_OPTIMIZEINCLUDE
#endif//__QCMP_OPTIMIZEINCLUDE

#include "CodeQOR.h"
#include "CodeQOR/DataStructures/TArray.h"

//--------------------------------------------------------------------------------
namespace nsCodeQOR
{
	//--------------------------------------------------------------------------------
	class __QOR_INTERFACE( __CODEQOR ) CChainLink
	{
	public:

		//--------------------------------------------------------------------------------
		CChainLink() : m_pPrev( 0 ), m_pNext( 0 )
		{
		}

		//--------------------------------------------------------------------------------
		CChainLink( const CChainLink& src )
		{
			m_pPrev = src.m_pPrev;
			m_pNext = src.m_pNext;
		}

		//--------------------------------------------------------------------------------
		virtual ~CChainLink()
		{
		}
	
		//--------------------------------------------------------------------------------
		CChainLink& operator = ( const CChainLink& src )
		{
			if( &src != this )
			{
				m_pPrev = src.m_pPrev;
				m_pNext = src.m_pNext;
			}
			return *this;
		}

		//--------------------------------------------------------------------------------
		CChainLink*& Prev( void )
		{
			return m_pPrev;
		}

		//--------------------------------------------------------------------------------
		CChainLink*& Next( void )
		{
			return m_pNext;
		}

		//--------------------------------------------------------------------------------
		static void Add( CChainLink*& pFirst, CChainLink* pNew )
		{
			if( pNew )
			{
				if( pFirst != 0 )
				{
					pFirst->Prev() = pNew;
					pNew->Next() = pFirst;					
				}

				pFirst = pNew;
			}
		}

		//--------------------------------------------------------------------------------
		static void Remove( CChainLink*& pFirst, CChainLink* pOld )
		{
			if( pFirst == pOld )
			{
				pFirst = pOld->Next();
			}

			if( pOld )
			{
				if( pOld->Prev() )
				{
					pOld->Prev()->Next() = pOld->Next();
				}

				if( pOld->Next() )
				{
					pOld->Next()->Prev() = pOld->Prev();
				}
			}
		}

		//--------------------------------------------------------------------------------
		template< class TDerived >
		static void Walk( CChainLink* pFirst, void(*pFunc)(TDerived*) )
		{
			while( pFirst != 0 )
			{
				TDerived* pDerived = dynamic_cast< TDerived* >( pFirst );
				if( pDerived )
				{
					(pFunc)(pDerived);
				}
				pFirst = pFirst->Next();
			}
		}

	protected:

		CChainLink* m_pPrev;
		CChainLink* m_pNext;
	};

	//--------------------------------------------------------------------------------
	//Abstract concept base for observers
	template< class TObserved >
	class CAbstractObserver : public CChainLink
	{
	public:

		//--------------------------------------------------------------------------------
		CAbstractObserver() : CChainLink()
		{
		}

		//--------------------------------------------------------------------------------
		CAbstractObserver( const CAbstractObserver& src ) : CChainLink( src )
		{
		}

		//--------------------------------------------------------------------------------
		virtual ~CAbstractObserver()
		{
		}

		//--------------------------------------------------------------------------------
		CAbstractObserver& operator = ( const CAbstractObserver& src )
		{
			CChainLink::operator = ( src );
			return *this;
		}

		virtual void Update( TObserved& Observered ) = 0;

	};

	//--------------------------------------------------------------------------------
	//Observer concept proxy
	//Proxies observer interface on anything that supports it
	template< class TObserved, class TImpl >
	class CProxyObserver : public CAbstractObserver< TObserved >
	{
	public:

		//--------------------------------------------------------------------------------
		CProxyObserver( TImpl& Impl ) : m_Impl( Impl )
		{
		}

		//--------------------------------------------------------------------------------
		CProxyObserver( const CProxyObserver& src ) : CAbstractObserver< TObserved >( src ), m_Impl( src.m_Impl )
		{
		}

		//--------------------------------------------------------------------------------
		virtual ~CProxyObserver()
		{
		}

		//--------------------------------------------------------------------------------
		CProxyObserver& operator = ( const CProxyObserver& src )
		{
			CAbstractObserver< TObserved >::operator=( src );
			return *this;
		}

		//--------------------------------------------------------------------------------
		virtual void Update( TObserved& Observed )
		{
			m_Impl.Update( Observed );
		}

	protected:

		TImpl& m_Impl;
	};

	//--------------------------------------------------------------------------------
	//Oservable property. Add as a public member to make a class observable
	template< class TObserved >
	class CObservable
	{
	public:

		//--------------------------------------------------------------------------------
		CObservable( TObserved& Observed ) : m_Observed( Observed )
		{
			m_pFirst = 0;
		}

		//--------------------------------------------------------------------------------
		CObservable( const CObservable& src ) : m_Observed( src.m_Observed )
		{
			*this = src;
		}

		//--------------------------------------------------------------------------------
		CObservable& operator = ( const CObservable& src )
		{
			if( &src != this )
			{
				m_pFirst = src.m_pFirst;
			}
			return *this;
		}

		//--------------------------------------------------------------------------------
		virtual ~CObservable()
		{
		}

		//--------------------------------------------------------------------------------
		void Update( void )
		{
			CAbstractObserver< TObserved >* it = dynamic_cast< CAbstractObserver< TObserved >* >( m_pFirst );
			while( it != 0 )
			{
				it->Update( m_Observed );
				it = (CAbstractObserver< TObserved >*)(it->Next());
			}
		}

		//--------------------------------------------------------------------------------
		void AddObserver( CChainLink* pNew )
		{
			CAbstractObserver< TObserved >::Add( m_pFirst, pNew );
		}

		//--------------------------------------------------------------------------------
		void RemoveObserver( CChainLink* pOld )
		{
			CAbstractObserver< TObserved >::Remove( m_pFirst, pOld );
		}

	protected:

		TObserved& m_Observed;

		CChainLink* m_pFirst;
	};

}//nsCodeQOR

#endif//CODEQOR_OBSERVER_H_3
