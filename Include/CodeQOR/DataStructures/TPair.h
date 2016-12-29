//TPair.h

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

//Pair class template

#ifndef CODEQOR_DATASTRUCTS_TPAIR_H_1
#define CODEQOR_DATASTRUCTS_TPAIR_H_1

#ifdef	__QCMP_OPTIMIZEINCLUDE
#pragma	__QCMP_OPTIMIZEINCLUDE
#endif//__QCMP_OPTIMIZEINCLUDE

//--------------------------------------------------------------------------------
namespace nsCodeQOR
{
	//--------------------------------------------------------------------------------
	//A pair of instances TFirst and TSecond accessed via First() and Second()
	//For comparison purposes a pair is equivalent to its first item only if compared with a TFirst
	template< class TFirst, class TSecond >
	class CTPair
	{

	public:

		typedef CTPair<TFirst, TSecond> type;

		//--------------------------------------------------------------------------------
		CTPair(){}

		//--------------------------------------------------------------------------------
		//Construct from first and second items
		CTPair( const TFirst& afirst, const TSecond& asecond )
		{
			m_first = afirst;
			m_second = asecond;
		}

		//--------------------------------------------------------------------------------
		//copy construct from a pair of identical type
		CTPair( const CTPair<TFirst, TSecond>& srcPair )
		{
			type& Pair = const_cast< type& >( srcPair );
			m_first = Pair.First();
			m_second = Pair.Second();
		}

		//--------------------------------------------------------------------------------
		virtual ~CTPair()
		{
		}

		//--------------------------------------------------------------------------------
		//return a reference to m_first
		const TFirst& First() const
		{
			return m_first;
		}

		//--------------------------------------------------------------------------------
		//return a reference to m_first
		TFirst& First()
		{
			return m_first;
		}

		//--------------------------------------------------------------------------------
		//return a reference to m_second
		const TSecond& Second() const
		{
			return m_second;
		}

		//--------------------------------------------------------------------------------
		//return a reference to m_second
		TSecond& Second()
		{
			return m_second;
		}

		//--------------------------------------------------------------------------------
		//Assignment operator from a pair of identical type
		CTPair< TFirst, TSecond >& operator =( const CTPair< TFirst, TSecond >& aPair)
		{
			CTPair< TFirst, TSecond >& Pair( const_cast< CTPair< TFirst, TSecond >& >( aPair ) );
			m_first = Pair.First();
			m_second = Pair.Second();
			return *this;
		}

		//--------------------------------------------------------------------------------
		//Not equal operator override for comparison with a TFirst
		bool operator != ( const TFirst& afirst )
		{
			return ( afirst == m_first ) ? false : true;
		}

		//--------------------------------------------------------------------------------
		//Not equal operator override for comparison with a pair of identical type
		bool operator != ( CTPair< TFirst, TSecond >& aPair )
		{
			return aPair.First() != m_first || aPair.Second() != m_second;
		}

		//--------------------------------------------------------------------------------
		//Equal operator override for comparison with a TFirst
		bool operator == ( const TFirst& afirst )
		{
			return afirst == m_first;
		}

		//--------------------------------------------------------------------------------
		//Equal operator override for comparison with a pair of identical type
		bool operator == ( const CTPair< TFirst, TSecond >& aPair ) const
		{
			return aPair.m_first == m_first && aPair.m_second == m_second;
		}

		//NOTE: > and < operators have no certain semantics for comparison of pairs with pairs so they are not overriden

		//--------------------------------------------------------------------------------
		//Greater than operator override for comparison with a TFirst
		bool operator > ( const TFirst& afirst )
		{
			return m_first < afirst;
		}

		//--------------------------------------------------------------------------------
		//Less than operator override for comparison with a TFirst
		bool operator < ( const TFirst& afirst )
		{
			return afirst < m_first;
		}

	protected:

		TFirst m_first;
		TSecond m_second;
	};

}//nsCodeQOR

#endif//CODEQOR_DATASTRUCTS_TPAIR_H_1