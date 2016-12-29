//IWorkflow.h

// Copyright Querysoft Limited 2016
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

//Abstract Workflow Interface

#include "CompilerQOR.h"

#ifdef	__QCMP_OPTIMIZEINCLUDE
#pragma __QCMP_OPTIMIZEINCLUDE
#endif//__QCMP_OPTIMIZEINCLUDE

#ifndef _APPOCRITAQOR_IWORKFLOW_H_
#define _APPOCRITAQOR_IWORKFLOW_H_

#include "AppocritaQOR/IApplication.h"
#include "AppocritaQOR/IState.h"

//------------------------------------------------------------------------------
namespace nsQOR
{
	//------------------------------------------------------------------------------
	class __QOR_INTERFACE( __APPOCRITA ) IWorkflow
	{
	public:

		__QOR_IMPL_REF( IWorkflow );

		IWorkflow(){};
		virtual ~IWorkflow(){};
		IWorkflow( const IWorkflow& src ){};
		IWorkflow& operator = ( const IWorkflow& src ){ return *this; }

		virtual void SetApplication( IApplication::ref_type Application ) = 0;
		virtual IState::ref_type CurrentState( void ) const = 0;
		virtual void SetState( IState::ref_type pNewState, IEvent::ref_type pEvent ) = 0;
		virtual void PushState( IState::ref_type pNewState, IEvent::ref_type pEvent ) = 0;
		virtual void PopState( IEvent::ref_type pEvent ) = 0;
		virtual IState::ref_type InitialState( void ) const = 0;
		virtual bool DefaultHandleEvent( IEvent::ref_type pEvent ) = 0;
		virtual void OnIdle(void) = 0;
	};
}//nsQOR

#endif//_APPOCRITAQOR_IWORKFLOW_H_
