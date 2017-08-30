//WinQLDeviceSetupClassEnumerator.cpp

// Copyright Querysoft Limited 2013, 2017
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

#include "WinQL/CodeServices/WinQLPolicy.h"
#include "WinQL/Application/Threading/WinQLCriticalSection.h"
#include "WinQL/Application/ErrorSystem/WinQLError.h"
#include "WinQL/CodeServices/Text/WinString.h"
#include "WinQL/System/Devices/SetupClasses/WinQLDeviceClassCollection.h"
//#include "WinQL/System/Devices/SetupClasses/WinQLDeviceList.h"
#include "WinQL/System/Devices/SetupClasses/WinQLDeviceSetupClass.h"
#include "WinQL/System/Devices/SetupClasses/WinQLDeviceSetupClassEnumerator.h"
#include "WinQL/Definitions/Constants.h"
#include "WinQL/GUI/Window.h"
#include "WinQL/System/WinQLSystem.h"
#include "WinQAPI/Kernel32.h"
#include "WinQAPI/SetupAPI.h"

//--------------------------------------------------------------------------------
namespace nsWin32
{
	using namespace nsWinQAPI;

	//--------------------------------------------------------------------------------
	__QOR_IMPLEMENT_OCLASS_LUID( CDeviceSetupClassEnumerator );

	//--------------------------------------------------------------------------------
	CDeviceSetupClassEnumerator::CDeviceSetupClassEnumerator() : nsQOR::CController(), CSetupAPIBase()
	{		
	}

	//--------------------------------------------------------------------------------
	CDeviceSetupClassEnumerator::CDeviceSetupClassEnumerator( const CDeviceSetupClassEnumerator& src ) : nsQOR::CController( src ), CSetupAPIBase( src )
	{
	}

	//--------------------------------------------------------------------------------
	CDeviceSetupClassEnumerator& CDeviceSetupClassEnumerator::operator = ( const CDeviceSetupClassEnumerator& src )
	{
		if( &src != this )
		{
			nsQOR::CController::operator = ( src );
		}
		return *this;
	}

	//--------------------------------------------------------------------------------
	CDeviceSetupClassEnumerator::~CDeviceSetupClassEnumerator()
	{
	}

	//--------------------------------------------------------------------------------
	void CDeviceSetupClassEnumerator::Enumerate( void )
	{
		/*
		unsigned long ulRequiredSize = 0;
		CDeviceSetupClassCM& model( m_Model().As< CDeviceSetupClassCM >() );

		bool bRemote = model.IsRemote();
		unsigned long ulFlags = model.m_ulFlags;
		const mxTCHAR* szMachineName = bRemote ? model.m_szMachineName : 0;
			
		m_Library.SetupDiBuildClassInfoListEx( 0, 0, 0, &ulRequiredSize, 0, 0 );

		nsCodeQOR::CTArray< nsCodeQOR::__mxGUID, CWinQLPolicy > ArrayGuids;
		ArrayGuids.SetCapacity( ulRequiredSize );
		m_Library.SetupDiBuildClassInfoListEx( ulFlags, reinterpret_cast< ::LPGUID >( ArrayGuids.GetAddressOfData() ), ulRequiredSize, &ulRequiredSize, szMachineName, 0 );
		ArrayGuids.Validate( ulRequiredSize );

		for( unsigned long ulIndex = 0; ulIndex < ulRequiredSize; ulIndex++ )
		{
			CDeviceSetupClass::refType Ref( *model.find( ArrayGuids[ ulIndex ] ) );
			if( Ref.IsNull() )
			{
				Ref.Attach( new CDeviceSetupClass( &ArrayGuids[ ulIndex ], model.m_szMachineName ), true );
				model.insert( ArrayGuids[ ulIndex ], Ref );
			}			
		}
		*/
	}

}//nsWin32
