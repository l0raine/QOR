//FlyStrap.h

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

//Approximately a 'point cut' class in AOP terminology

#ifndef CODEQOR_FLYSTRAP_H_1
#define CODEQOR_FLYSTRAP_H_1

#include "FlyStrapBase.h"

#ifdef	__QCMP_OPTIMIZEINCLUDE
#pragma	__QCMP_OPTIMIZEINCLUDE
#endif//__QCMP_OPTIMIZEINCLUDE

//--------------------------------------------------------------------------------
namespace nsCodeQOR
{
	class __QOR_INTERFACE( __CODEQOR ) CCallContextBase;

	//--------------------------------------------------------------------------------
	class __QOR_INTERFACE( __CODEQOR ) CFlyStrap : public CFlyStrapBase
	{
	public:

		__QOR_DECLARE_OCLASS_ID( CFlyStrap );

		CFlyStrap();
		CFlyStrap( CFlyStrapBase* );
		virtual ~CFlyStrap();
	
		virtual bool PreCondition( CCallContextBase* pCall, CFunctionContextBase* pFunction );		
		virtual bool OnAssignmentCondition( CCallContextBase* pCall );
		virtual bool PostCondition( CCallContextBase* pCall );
		virtual bool Pre( CCallContextBase* pCall, CFunctionContextBase* pFunction );
		virtual bool OnReturnAssignment( CCallContextBase* pCall );
		virtual bool Post( CCallContextBase* pCall );

		//--------------------------------------------------------------------------------
		template< class T > void Strap()
		{
			CFlyStrapBase* pJoinPoint = 0;
			CClassInstanceFactory* pFactory = ThisModule().ClassReg().GetFactory( T::ClassID() );
			if( pFactory != 0 )
			{
				pJoinPoint = dynamic_cast< CFlyStrapBase* >( reinterpret_cast< T* >( pFactory->Instance() ) );	//get the instance pointer on creation				
			}
			else
			{
				pJoinPoint = 0;
			}

			if( pJoinPoint )
			{
				pJoinPoint->StrapOn( this );
			}
		}


		bool CallPre( CCallContextBase* pCall, CFunctionContextBase* pFunction );
		bool CallOnReturnAssignment( CCallContextBase* pCall );
		bool CallPost( CCallContextBase* pCall );
		
	};

}//nsCodeQOR

#endif//CODEQOR_FLYSTRAP_H_1
