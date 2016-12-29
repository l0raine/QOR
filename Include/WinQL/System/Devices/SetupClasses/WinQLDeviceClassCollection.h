//WinQLDeviceClassCollection.h

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

//Win32 Device Class Collection

#ifndef WINQL_DEVICECLASSCOLLECTION_H_3
#define WINQL_DEVICECLASSCOLLECTION_H_3

#ifdef	__QCMP_OPTIMIZEINCLUDE
#pragma	__QCMP_OPTIMIZEINCLUDE
#endif//__QCMP_OPTIMIZEINCLUDE

#include "WinQL/Definitions/Data.h"
#include "WinQL/Definitions/IO.h"
#include "WinQL/System/Devices/WinQLDevice.h"
#include "WinQL/System/Devices/WinQLDeviceHandle.h"
#include "WinQL/System/Devices/SetupClasses/WinQLDeviceSetupClass.h"
#include "WinQL/CodeServices/Text/WinString.h"
#include "WinQL/System/Devices/Instances/WinQLDeviceCollection.h"

//--------------------------------------------------------------------------------
namespace nsWin32
{
	/*
	//--------------------------------------------------------------------------------
	class __QOR_INTERFACE( __WINQL ) CDeviceInstanceCM : public CTDeviceCollection< nsCodeQOR::mxGUID, nsMammut::CModelItem >
	{
		friend class CDeviceInstanceEnumerator;

	public:

		__QOR_DECLARE_OCLASS_ID( CDeviceInstanceCM );

		CDeviceInstanceCM(const mxTCHAR* szMachineName = 0 );
		CDeviceInstanceCM( const CDeviceInstanceCM& src );
		CDeviceInstanceCM& operator = ( const CDeviceInstanceCM& src );
		virtual ~CDeviceInstanceCM();
	};
	*/
	/*
	//--------------------------------------------------------------------------------
	class __QOR_INTERFACE( __WINQL ) CDeviceSetupClassCM : public CTDeviceCollection< nsCodeQOR::mxGUID, CDeviceSetupClassModel >
	{
		friend class CDeviceSetupClassEnumerator;

	public:

		__QOR_DECLARE_OCLASS_ID( CDeviceSetupClassCM );

		CDeviceSetupClassCM( unsigned long uFlags = 0, const mxTCHAR* szMachineName  = 0 );
		CDeviceSetupClassCM( const CDeviceSetupClassCM& src );
		CDeviceSetupClassCM& operator = ( const CDeviceSetupClassCM& src );
		virtual ~CDeviceSetupClassCM();

	protected:

		unsigned long m_ulFlags;		

	};
	*/
	/*
	//--------------------------------------------------------------------------------
	class __QOR_INTERFACE( __WINQL ) CDeviceClassCollection
	{
		friend class CDeviceClass;

	public:

		__QOR_DECLARE_OCLASS_ID( CDeviceClassCollection );

		CDeviceClassCollection( unsigned long ulFlags = 0, const mxTCHAR* szMachineName = 0 );
		CDeviceClassCollection( const CDeviceClassCollection& src );
		CDeviceClassCollection& operator = ( const CDeviceClassCollection& src );
		~CDeviceClassCollection();

		unsigned long Size( void );
		bool IsRemote( void );
		bool IsLocal( void );

		nsCodeQOR::CTLRef< CDeviceClass > operator[]( const CTString& strClass );
		nsCodeQOR::CTLRef< CDeviceClass > operator[]( nsCodeQOR::mxGUID* pGUID );
		nsCodeQOR::CTLRef< CDeviceClass > operator[]( unsigned long ulIndex );

	protected:

		void RegisterAClass( nsCodeQOR::__mxGUID, CDeviceClass* pDeviceClass );
		CDeviceSetupClass::refType FindClass( nsCodeQOR::__mxGUID );

		nsCodeQOR::CTArray< nsCodeQOR::__mxGUID, CWinQLPolicy > m_ArrayGuids;
		nsCodeQOR::CTMap< nsCodeQOR::__mxGUID, CDeviceClass* > m_MapClasses;
		bool m_bRemote;
		const mxTCHAR* m_szMachineName;

	private:

		nsWinQAPI::CSetupAPI& m_Library;
	};
	*/
}//nsWin32

#endif//WINQL_DEVICECLASSCOLLECTION_H_3