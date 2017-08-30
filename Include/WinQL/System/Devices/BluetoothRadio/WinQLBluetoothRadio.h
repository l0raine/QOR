//WinQLBluetoothRadio.h

// Copyright Querysoft Limited 2013, 2016, 2017
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

//Win32 Bluetooth Radio Device

#ifndef WINQL_BLUETOOTHRADIO_H_3
#define WINQL_BLUETOOTHRADIO_H_3

#include "CompilerQOR.h"

#ifdef	__QCMP_OPTIMIZEINCLUDE
#pragma	__QCMP_OPTIMIZEINCLUDE
#endif//__QCMP_OPTIMIZEINCLUDE

#include "WinQL/System/Devices/Interfaces/WinQLDeviceInterface.h"
#include "WinQL/System/Devices/WinQLIODevice.h"
#include "WinQL/Application/Comms/Bluetooth/WinQLBluetoothRemoteDevice.h"
#include "WinQL/System/Devices/WinQLNotification.h"

__QOR_DECLARE_REF(nsWin32, __WINQL, CBluetoothRadio, CTExtRef);

//--------------------------------------------------------------------------------
namespace nsWin32
{
	//--------------------------------------------------------------------------------
	class __QOR_INTERFACE( __WINQL ) CBluetoothRadio : public CDeviceInterface
	{
	public:

		__QOR_DECLARE_REF_TYPE(CBluetoothRadio);

		//--------------------------------------------------------------------------------
		struct Info
		{
			unsigned long dwSize;						// Size, in bytes, of this entire data structure
			BluetoothAddress address;					// Address of the local radio
			wchar_t szName[ BluetoothMaxNameSize ];		// Name of the local radio
			unsigned long ulClassofDevice;				// Class of device for the local radio
			unsigned short lmpSubversion;				// lmpSubversion, manufacturer specifc.
			unsigned short manufacturer;				// Manufacturer of the radio, BTH_MFG_Xxx value.  For the most up to date
														// list, goto the Bluetooth specification website and get the Bluetooth
														// assigned numbers document.
		};

		__QOR_DECLARE_OCLASS_ID( CBluetoothRadio );

		static nsCodeQOR::CTExternalRegEntry< CBluetoothRadio > RegEntry;
		static nsCodeQOR::mxGUID GUID_BLUETOOTH_HCI_EVENT;
		static nsCodeQOR::mxGUID GUID_BLUETOOTH_L2CAP_EVENT;
		static nsCodeQOR::mxGUID GUID_BLUETOOTH_RADIO_IN_RANGE;
		static nsCodeQOR::mxGUID GUID_BLUETOOTH_RADIO_OUT_OF_RANGE;

		CBluetoothRadio();
		CBluetoothRadio( CDeviceHandle::ref_type hExisting );
		CBluetoothRadio( const CBluetoothRadio& src );
		CBluetoothRadio& operator = ( const CBluetoothRadio& src );
		virtual ~CBluetoothRadio();

		void SetHandle(CDeviceHandle::ref_type hExisting);
		void AuthenticateDevice( COSWindow::refType ParentWindow, CBluetoothRemoteDevice::ref_type Device, CWString strPassKey );
		void AuthenticateDeviceEx( COSWindow::refType ParentWindow, CBluetoothRemoteDevice::ref_type Device, BluetoothOutOfBandData* pbtOobData, CBluetoothRemoteDevice::Authentication_Requirements AuthentRequirements );
		bool EnableDiscovery( bool bEnabled );
		bool EnableIncomingConnections( bool bEnabled );
		unsigned long EnumerateInstalledServices( CBluetoothRemoteDevice::ref_type Device, nsCodeQOR::__mxGUID** ppGuidServices );
		void GetDeviceInfo( CBluetoothRemoteDevice::ref_type Device );
		bool IsConnectable( void );
		bool IsDiscoverable( void );
		void SendAuthenticationResponse( CBluetoothRemoteDevice::Info* pDeviceInfo, CWString strPassKey );
		void SendAuthenticationResponseEx( void* pResponse );
		void SetLocalServiceInfo( nsCodeQOR::mxGUID* pClassGuid, unsigned long ulInstance, const BluetoothLocalServiceInfo* pServiceInfoIn );
		void SetServiceState( CBluetoothRemoteDevice::ref_type Device, nsCodeQOR::__mxGUID* pGuidService , unsigned long ulServiceFlags );
		void EnableNotifications( CHandle& hRecipient, bool bEnable );
		void Open(void);
		void Close(void);
		void* GetSessionHandle(void);

	protected:

		bool OpenDevice( void );
		void GetInfo( void );
		void SetupNotificationFilter( void );

		Info m_Info;

		CNotificationFilter m_NotificationFilter;
		bool m_bNotificationsEnabled;
		CDeviceNotification::ref_type Notification;
		CIODeviceFile::ref_type m_Session;

	private:

		nsWinQAPI::CBthProps& m_Library;

	};

}//nsWin32

#endif//WINQL_BLUETOOTHRADIO_H_3
