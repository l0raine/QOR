//WinQLUSBHostController.cpp

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

#include "SystemQOR/System.h"
#include "WinQL/CodeServices/WinQLPolicy.h"
#include "WinQL/Application/Threading/WinQLCriticalSection.h"
#include "WinQL/Definitions/Constants.h"
#include "WinQL/Application/ErrorSystem/WinQLError.h"
#include "WinQL/CodeServices/Text/WinString.h"
#include "WinQL/System/Devices/USB/WinQLUSBHostController.h"
#include "WinQL/System/Devices/USB/WinQLUSBHub.h"
#include "WinQL/System/Devices/Interfaces/WinQLDeviceInterfaceClass.h"
#include "WinQL/System/WinQLSystem.h"

//--------------------------------------------------------------------------------
namespace nsWin32
{
	__QOR_IMPLEMENT_OCLASS_GUID( CUSBHostController, 0x3ABF6F2D, 0x71C4, 0x462A, 0x8A, 0x92, 0x1E, 0x68, 0x61, 0xE6, 0xAF, 0x27 );
	
	nsCodeQOR::CTExternalRegEntry< CUSBHostController > CUSBHostController::RegEntry;

	//--------------------------------------------------------------------------------
	CUSBHostController::CUSBHostController() : CDeviceInterface()
	{
		_WINQ_FCONTEXT( "CUSBHostController::CUSBHostController" );
	}

	//--------------------------------------------------------------------------------
	CUSBHostController::~CUSBHostController()
	{
		_WINQ_FCONTEXT( "CUSBHostController::~CUSBHostController" );
	}

	//--------------------------------------------------------------------------------
	CWString CUSBHostController::GetHCDDriverKeyName()
	{
		auto Session = Open(Generic_Write, File_Share_Write, Open_Existing);
		CWString strKeyName;
		bool                    success = false;
		unsigned long			nBytes = 0;
		USB_HCD_DRIVERKEY_NAME  driverKeyName = {0};
		PUSB_HCD_DRIVERKEY_NAME driverKeyNameW = NULL;
		
		memset( &driverKeyName, 0, sizeof( USB_HCD_DRIVERKEY_NAME ) );

		// Get the length of the name of the driver key of the HCD
		success = Session->Control( 
			__WINQL_DEVICE_CONTROL_CODE( File_Device_USB, HCD_GET_DRIVERKEY_NAME, Method_Buffered, File_Any_Access ), &driverKeyName, sizeof(driverKeyName), &driverKeyName, sizeof(driverKeyName), &nBytes, NULL );

		// Allocate space to hold the driver key name
		nBytes = driverKeyName.ActualLength;

		driverKeyNameW = reinterpret_cast< PUSB_HCD_DRIVERKEY_NAME >( new byte[ nBytes ] );

		// Get the name of the driver key of the device attached to the specified port.
		success = Session->Control( 
			__WINQL_DEVICE_CONTROL_CODE( File_Device_USB, HCD_GET_DRIVERKEY_NAME, Method_Buffered, File_Any_Access ), driverKeyNameW, nBytes, driverKeyNameW, nBytes, &nBytes, NULL );

		strKeyName.Append( &driverKeyNameW->DriverKeyName[ 0 ] );
		delete driverKeyNameW;
		return strKeyName;
	}

	//--------------------------------------------------------------------------------
	/*
	CUSBHostController::PUSB_DEVICE_PNP_STRINGS  CUSBHostController::DriverNameToDeviceProperties( CWString& strDriverKeyName )
	{
		HDEVINFO        deviceInfo = INVALID_HANDLE_VALUE;
		SP_DEVINFO_DATA deviceInfoData = {0};
		ULONG           len;
		BOOL            status;
		PUSB_DEVICE_PNP_STRINGS DevProps = NULL;
		DWORD           lastError;

		// Allocate device propeties structure
		DevProps = (PUSB_DEVICE_PNP_STRINGS) ALLOC(sizeof(USB_DEVICE_PNP_STRINGS));


		nsCodeQOR::CTLRef< CDeviceInstance > refInstance = GetInstance();


		status = GetDeviceProperty( deviceInfo, &deviceInfoData, SPDRP_DEVICEDESC, &DevProps->DeviceDesc );
    
		GetDeviceProperty( deviceInfo, &deviceInfoData, SPDRP_HARDWAREID, &DevProps->HwId );

		GetDeviceProperty( deviceInfo, &deviceInfoData, SPDRP_SERVICE, &DevProps->Service );

		GetDeviceProperty( deviceInfo, &deviceInfoData, SPDRP_CLASS, &DevProps->DeviceClass );
	
	Done:


		if (status == FALSE)
		{
			if (DevProps != NULL)
			{
				FreeDeviceProperties(&DevProps);
			}
		}
		return DevProps;
	}
	*/

	//--------------------------------------------------------------------------------
	CUSBHub* CUSBHostController::GetRootHub()
	{
		_WINQ_FCONTEXT( "CUSBHostController::GetRootHub" );

		CTString strRootHub = GetRootHubName().toTString();

		CUSBHub* pHub = TheSystem().As< nsWin32::CSystem >()->Devices( QOR_PP_SHARED_OBJECT_ACCESS )().USBHubFromName( strRootHub );

		return pHub;
	}

	//--------------------------------------------------------------------------------
	CWString CUSBHostController::GetRootHubName()
	{
		_WINQ_FCONTEXT( "CUSBHostController::GetRootHubName" );
		bool                success = false;
		unsigned long		nBytes = 0;
		USB_ROOT_HUB_NAME   rootHubName;
		PUSB_ROOT_HUB_NAME  rootHubNameW = NULL;
		CWString strTooHubName;

		auto Session = Open(Generic_Write, File_Share_Write, Open_Existing);

		// Get the length of the name of the Root Hub attached to the Host Controller
		
		success = Session->Control( 
			__WINQL_DEVICE_CONTROL_CODE( File_Device_USB, HCD_GET_ROOT_HUB_NAME, Method_Buffered, File_Any_Access ), 0, 0, &rootHubName, sizeof(rootHubName), &nBytes, 0 );

		//Allocate space to hold the Root Hub name
		
		nBytes = rootHubName.ActualLength;

		rootHubNameW = reinterpret_cast< PUSB_ROOT_HUB_NAME >( new byte[ nBytes ] );

		// Get the name of the Root Hub attached to the Host Controller
		success = Session->Control( 
			__WINQL_DEVICE_CONTROL_CODE( File_Device_USB, HCD_GET_ROOT_HUB_NAME, Method_Buffered, File_Any_Access ), 0, 0, rootHubNameW, nBytes, &nBytes, 0 );

		strTooHubName.Append( rootHubNameW->RootHubName );

		// All done, free the uncoverted Root Hub name and return the converted Root Hub name
		delete rootHubNameW;
		return strTooHubName;
	}

	//--------------------------------------------------------------------------------
	void CUSBHostController::GetHostControllerInfo( PUSBHOSTCONTROLLERINFO hcInfo )
	{
		USBUSER_CONTROLLER_INFO_0	UsbControllerInfo;
		//unsigned long				dwError = 0;
		unsigned long               dwBytes = 0;
		bool                        bSuccess = false;

		memset(&UsbControllerInfo, 0, sizeof(UsbControllerInfo));

		// set the header and request sizes
		UsbControllerInfo.Header.UsbUserRequest = USBUSER_GET_CONTROLLER_INFO_0;
		UsbControllerInfo.Header.RequestBufferLength = sizeof(UsbControllerInfo);

		auto Session = Open(Generic_Write, File_Share_Write, Open_Existing);

		// Query for the USB_CONTROLLER_INFO_0 structure
		
		bSuccess = Session->Control( 
			__WINQL_DEVICE_CONTROL_CODE( File_Device_USB, HCD_USER_REQUEST, Method_Buffered, File_Any_Access ), &UsbControllerInfo, sizeof(UsbControllerInfo), &UsbControllerInfo, sizeof(UsbControllerInfo), &dwBytes, NULL);
			
		memcpy( &hcInfo->ControllerInfo, &UsbControllerInfo.Info0, sizeof(USB_CONTROLLER_INFO_0));// copy the data into our USB Host Controller's info structure
	}

	//--------------------------------------------------------------------------------
	void CUSBHostController::EnumerateRootHub()
	{
		Open( Generic_Write, File_Share_Write, Open_Existing );

		USBHOSTCONTROLLERINFO Info;

		memset( &Info, 0, sizeof( USBHOSTCONTROLLERINFO ) );
		Info.DeviceInfoType = HostControllerInfo;
		CWString strDriverKeyName = GetHCDDriverKeyName();
		
		Info.DriverKey = strDriverKeyName.GetBuffer();

		/*
		CDeviceInstance::ref_type refInstance = GetInstance();
		if( !refInstance.IsNull() )
		{
			CTString strDeviceID = refInstance->DeviceID();
			//strDeviceID.Scan( _TXT( "PCI\\VEN_%x&DEV_%x&SUBSYS_%x&REV_%x", &Info.VendorID, &Info.DeviceID, &Info.SubSysID, &Info.Revision ) );
		}
		*/


		Info.DriverKey = 0;
		strDriverKeyName.ReleaseBuffer();
		//Close();
	}
}//nsWin32

