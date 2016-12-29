//System.cpp

// Copyright Querysoft Limited 2015, 2016
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

#include "SystemQOR.h"
#include "SystemQOR/System.h"
#include "CodeQOR/DataTypes/GUID.h"
#include "CodeQOR/Tracing/FunctionContextBase.h"

//------------------------------------------------------------------------------
namespace nsQOR
{
	static ISystem* theSystem = nullptr;

	__QOR_IMPLEMENT_OCLASS_GUID( CSystem, 0xa6eb5841, 0x95ca, 0x4008, 0xb8, 0x4f, 0xb8, 0xd0, 0x6b, 0xbf, 0xb6, 0x14 );	// {A6EB5841-95CA-4008-B84F-B8D06BBFB614}

	//------------------------------------------------------------------------------
	ISystem::ISystem()
	{
		theSystem = this;
	}

	//------------------------------------------------------------------------------
	CSystem::CSystem()
	{
		__QCS_MEMBER_FCONTEXT( "CSystem::CSystem" );

		nsCodeQOR::CClassInstanceFactory* pFactory = ThisModule().ExternalClassReg().GetFactory( CSystem::ClassID() );
		if( pFactory )
		{
			m_Impl.Attach( reinterpret_cast<ISystem*>( pFactory->Instance() ), true );
		}
	}

	//------------------------------------------------------------------------------
	CSystem::~CSystem()
	{
		__QCS_MEMBER_FCONTEXT( "CSystem::~CSystem" );
	}

	//------------------------------------------------------------------------------
	void CSystem::Setup( IApplication& Application )
	{
		__QCS_MEMBER_FCONTEXT( "CSystem::Setup" );
		m_Impl->Setup( Application );
	}

	//------------------------------------------------------------------------------
	void CSystem::Shutdown( IApplication& Application )
	{
		__QCS_MEMBER_FCONTEXT( "CSystem::Shutdown" );
		m_Impl->Shutdown( Application );
	}

}//nsQOR

 //------------------------------------------------------------------------------
__QCMP_EXPORT nsQOR::ISystem::ref_type TheSystem( void )
{
	return nsQOR::theSystem->Ref();
}
