//WinQLBluetoothRemoteDevice.h

// Copyright Querysoft Limited 2013, 2016
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

//Win32 Bluetooth Remote Device

#ifndef WINQL_COMMS_BLUETOOTHREMOTEDEVICE_H_3
#define WINQL_COMMS_BLUETOOTHREMOTEDEVICE_H_3

#ifdef	__QCMP_OPTIMIZEINCLUDE
#pragma	__QCMP_OPTIMIZEINCLUDE
#endif//__QCMP_OPTIMIZEINCLUDE

#include "WinQL/WinQL.h"
#include "WinQL/CodeServices/WinQLPolicy.h"
#include "WinQL/Definitions/Constants.h"
#include "WinQL/System/Clock/WinQLTime.h"
#include "WinQL/GUI/Window.h"

//--------------------------------------------------------------------------------
namespace nsWinQAPI
{
	class __QOR_INTERFACE( __WINQAPI ) CBthProps;
}//nsWinQAPI

//--------------------------------------------------------------------------------
namespace nsWin32
{
	class __QOR_INTERFACE( __WINQL ) CBluetoothRadio;
	class __QOR_INTERFACE( __WINQL ) CBluetoothClient;

	typedef Cmp_unsigned__int64 BluetoothAddr;//BTH_ADDR;

	//--------------------------------------------------------------------------------
	struct BluetoothAddress 
	{
		union 
		{
			BluetoothAddr	ullLong;       //  easier to compare again BLUETOOTH_NULL_ADDRESS
			byte			rgBytes[ 6 ];   //  easier to format when broken out
		};
	};

	//--------------------------------------------------------------------------------
	struct BluetoothLocalServiceInfo
	{
		int Enabled;                        //  If TRUE, the enable the services

		BluetoothAddress   btAddr;                         //  If service is to be advertised for a particular remote device

		wchar_t szName[ BluetoothMaxServiceNameSize ];    //  SDP Service Name to be advertised.
		wchar_t szDeviceString[ BluetoothDeviceNameSize ]; //  Local device name (if any) like COM4 or LPT1
	};

	//--------------------------------------------------------------------------------
	struct BluetoothOutOfBandData
	{
		unsigned char C[16];
		unsigned char R[16];
	};

	//--------------------------------------------------------------------------------
	struct BluetoothPinInfo
	{
		unsigned char pin[ BluetoothMaxPINSize ];
		unsigned char pinLength;
	};

	//--------------------------------------------------------------------------------
	struct BluetoothNumericComparisonInfo
	{
		unsigned long NumericValue;
	};

	//--------------------------------------------------------------------------------
	struct BluetoothPasskeyInfo
	{
		unsigned long passkey;
	};

	//--------------------------------------------------------------------------------
	struct BluetoothHCIEventInfo
	{
		BluetoothAddr bthAddress;
		unsigned char connectionType;
		unsigned char connected;
	};

	//--------------------------------------------------------------------------------
	struct BluetoothL2CAPEventInfo
	{
		BluetoothAddr	bthAddress;
		unsigned short	psm;
		unsigned char	connected;
		unsigned char	initiated;
	};

	//--------------------------------------------------------------------------------
	struct ClassOfDevice
	{
	public:

		//--------------------------------------------------------------------------------
		enum eMajorClasses
		{
			Miscellaneous					= 0x00,
			Computer						= 0x01,
			Phone							= 0x02,
			LANAccess						= 0x03,
			Audio							= 0x04,
			Peripheral						= 0x05,
			Imaging							= 0x06,
			Wearable						= 0x07,
			Toy								= 0x08,
			Health							= 0x09,
			Unclassified					= 0x1F,
		};

		//--------------------------------------------------------------------------------
		enum eComputerMinorClasses
		{
			Computer_Unclassified			= 0x00,
			Computer_Desktop				= 0x01,
			Computer_Server					= 0x02,
			Computer_Laptop					= 0x03,
			Computer_Handheld				= 0x04,
			Computer_Palm					= 0x05,
			Computer_Wearable				= 0x06,
		};

		//--------------------------------------------------------------------------------
		enum ePhoneMinorClasses
		{
			Phone_Unclassified				= 0x00,
			Phone_Cellular					= 0x01,
			Phone_Cordless					= 0x02,
			Phone_Smart						= 0x03,
			Phone_WiredModem				= 0x04,
		};

		//--------------------------------------------------------------------------------
		enum eAudioMinorClass
		{
			Audio_Unclassified				= 0x00,
			Audio_Headset					= 0x01,
			Audio_HandsFree					= 0x02,
			Audio_HeadsetHandsFree			= 0x03,
			Audio_Microphone				= 0x04,
			Audio_Loudspeaker				= 0x05,
			Audio_Headphones				= 0x06,
			Audio_PortableAudio				= 0x07,
			Audio_CasrAudio					= 0x08,
			Audio_SetTopBox					= 0x09,
			Audio_HiFiAudio					= 0x0A,
			Audio_VCR						= 0x0B,
			Audio_VideoCamera				= 0x0C,
			Audio_Camcorder					= 0x0D,
			Audio_VideoMonitor				= 0x0E,
			Audio_VideoDisplayLoudspeaker	= 0x0F,
			Audio_VideoDisplayConferencing	= 0x10,
			Audio_GamingToy					= 0x12,
		};

		//--------------------------------------------------------------------------------
		enum ePeripheralMinorClass
		{
			Peripheral_KeyboardMask			= 0x10,
			Peripheral_PointerMask			= 0x20,
			Peripheral_NoCategory			= 0x00,
			Peripheral_Joystick				= 0x01,
			Peripheral_Gamepad				= 0x02,
			Peripheral_RemoteControl		= 0x03,
			Peripheral_Sensing				= 0x04
		};

		//--------------------------------------------------------------------------------
		enum eImagingMinorClass
		{
			Imaging_DisplayMask				= 0x04,
			Imaging_CameraMask				= 0x08,
			Imaging_ScannerMask				= 0x10,
			Imaging_PrinterMask				= 0x20,
		};

		//--------------------------------------------------------------------------------
		enum eWearableMinorClass
		{
			Wearable_WristWatch				= 0x01,
			Wearable_Pager					= 0x02,
			Wearable_Jacket					= 0x03,
			Wearable_Helmet					= 0x04,
			Wearable_Glasses				= 0x05,
		};

		//--------------------------------------------------------------------------------
		enum eToyMinorClass
		{
			Toy_Robot						= 0x01,
			Toy_Vehicle						= 0x02,
			Toy_DollActionFigure			= 0x03,
			Toy_Controller					= 0x04,
			Toy_Game						= 0x05,
		};

		//--------------------------------------------------------------------------------
		enum eHealthMinorClass
		{
			Health_BloodPressureMonitor		= 0x01,
			Health_Thermometer				= 0x02,
			Health_WeighingScale			= 0x03,
			Health_GlucoseMeter				= 0x04,
			Health_PulseOximeter			= 0x05,
			Health_HeartPulseMonitor		= 0x06,
			Health_DataDisplay				= 0x07,
			Health_StepCounter				= 0x08,
		};

		//--------------------------------------------------------------------------------
		enum eService
		{
			Service_Limited					= 0x0001,
			Service_Positioning				= 0x0008,
			Service_Networking				= 0x0010,
			Service_Rendering				= 0x0020,
			Service_Capturing				= 0x0040,
			Service_ObjectXfer				= 0x0080,
			Service_Audio					= 0x0100,
			Service_Telephony				= 0x0200,
			Service_Information				= 0x0400,
		};

		unsigned long ulClassofDevice;

		__QCMP_STATIC_CONSTANT( int, FORMAT_BIT_OFFSET		= 0 );
		__QCMP_STATIC_CONSTANT( int, MINOR_BIT_OFFSET		= 2 );
		__QCMP_STATIC_CONSTANT( int, MAJOR_BIT_OFFSET		= 8 * 1 );
		__QCMP_STATIC_CONSTANT( int, SERVICE_BIT_OFFSET		= 8 * 1 + 5 );

		__QCMP_STATIC_CONSTANT( unsigned long, FORMAT_MASK	= 0x000003 );
		__QCMP_STATIC_CONSTANT( unsigned long, MINOR_MASK	= 0x0000FC );
		__QCMP_STATIC_CONSTANT( unsigned long, MAJOR_MASK	= 0x001F00 );
		__QCMP_STATIC_CONSTANT( unsigned long, SERVICE_MASK	= 0xFFE000 );

		//--------------------------------------------------------------------------------
		void Reset( void )
		{
			ulClassofDevice = 0;
		}

		//--------------------------------------------------------------------------------
		unsigned char GetFormat( void )
		{
			return ( (ulClassofDevice) & FORMAT_MASK >> FORMAT_BIT_OFFSET );
		}

		//--------------------------------------------------------------------------------
		unsigned char GetMinor( void )
		{
			return ( ( (ulClassofDevice) & MINOR_MASK ) >> MINOR_BIT_OFFSET );
		}

		//--------------------------------------------------------------------------------
		unsigned char GetMajor( void )
		{
			return ( ( (ulClassofDevice) & MAJOR_MASK ) >> MAJOR_BIT_OFFSET );
		}

		//--------------------------------------------------------------------------------
		unsigned short GetService( void )
		{
			return static_cast< unsigned short >( ( (ulClassofDevice) & SERVICE_MASK ) >> SERVICE_BIT_OFFSET );
		}
	};

	class __QOR_INTERFACE( __WINQL ) CAuthenticateBluetoothSession;		//forward declaration

	//--------------------------------------------------------------------------------
	//Our representation of somebody else's device on the other end of Bluetooth comms
	class __QOR_INTERFACE( __WINQL ) CBluetoothRemoteDevice
	{
	public:
		
		typedef nsCodeQOR::CTLRef< CBluetoothRemoteDevice > refType;

		//--------------------------------------------------------------------------------
		enum Authentication_Method
		{
			BLUETOOTH_AUTHENTICATION_METHOD_LEGACY     = 0x1,
			BLUETOOTH_AUTHENTICATION_METHOD_OOB,
			BLUETOOTH_AUTHENTICATION_METHOD_NUMERIC_COMPARISON,
			BLUETOOTH_AUTHENTICATION_METHOD_PASSKEY_NOTIFICATION,
			BLUETOOTH_AUTHENTICATION_METHOD_PASSKEY
		};

		//--------------------------------------------------------------------------------
		enum IO_Capability
		{
			BLUETOOTH_IO_CAPABILITY_DISPLAYONLY    = 0x00,
			BLUETOOTH_IO_CAPABILITY_DISPLAYYESNO    = 0x01,   
			BLUETOOTH_IO_CAPABILITY_KEYBOARDONLY    = 0x02,
			BLUETOOTH_IO_CAPABILITY_NOINPUTNOOUTPUT = 0x03,
			BLUETOOTH_IO_CAPABILITY_UNDEFINED       = 0xff
		};

		//--------------------------------------------------------------------------------
		enum Authentication_Requirements
		{
			MITMProtectionNotRequired               = 0x00,
			MITMProtectionRequired                  = 0x01,
			MITMProtectionNotRequiredBonding        = 0x02,
			MITMProtectionRequiredBonding           = 0x03,
			MITMProtectionNotRequiredGeneralBonding = 0x04,
			MITMProtectionRequiredGeneralBonding    = 0x05,
			MITMProtectionNotDefined                = 0xff
		};

		//--------------------------------------------------------------------------------
		enum eConnectionType
		{
			ACL = 1,
			SCO = 2,
		};

		//--------------------------------------------------------------------------------
		enum ePSM
		{
			PSM_SDP						= 0x0001,
			PSM_RFCOMM					= 0x0003,
			PSM_TCS_BIN					= 0x0005,
			PSM_TCS_BIN_CORDLESS		= 0x0007,
			PSM_BNEP					= 0x000F,
			PSM_HID_CONTROL				= 0x0011,
			PSM_AVCTP					= 0x0017,
			PSM_AVDTP					= 0x0019,
			PSM_UDI_C_PLANE				= 0x001D,
		};

		//--------------------------------------------------------------------------------
		struct Info
		{
			unsigned long dwSize;							//  size, in bytes, of this structure - must be the sizeof(BLUETOOTH_DEVICE_INFO)
			BluetoothAddress Address;						//  Bluetooth address
			ClassOfDevice ulClassofDevice;					//  Bluetooth "Class of Device"
			int fConnected;									//  Device connected/in use
			int fRemembered;								//  Device remembered
			int fAuthenticated;								//  Device authenticated/paired/bonded
			SystemTime  stLastSeen;							//  Last time the device was seen
			SystemTime  stLastUsed;							//  Last time the device was used for other than RNR, inquiry, or SDP
			wchar_t   szName[ BluetoothMaxNameSize ];		//  Name of the device
		};

		//--------------------------------------------------------------------------------
		struct ShortInfo
		{
			unsigned long flags;
			BluetoothAddr address;
			ClassOfDevice  classOfDevice;
			char     name[ BluetoothMaxNameSize ];
		};

		//--------------------------------------------------------------------------------
		enum eInfoFlags
		{
			BDIF_Address		= 0x00000001,
			BDIF_COD			= 0x00000002,
			BDIF_Name			= 0x00000004,
			BDIF_Paired			= 0x00000008,
			BDIF_Personal		= 0x00000010,
			BDIF_Connected		= 0x00000020,
			BDIF_ShortName		= 0x00000040,
			BDIF_Visible			= 0x00000080,
			BDIF_SSPSupported		= 0x00000100,
			BDIF_SSPPaired			= 0x00000200,
			BDIF_SSP_MITMProtected	= 0x00000400,
			BDIF_RSSI				= 0x00001000,
			BDIF_EIR				= 0x00002000,
		};

		//--------------------------------------------------------------------------------
		struct Authentication_CallbackParams
		{
			Info						deviceInfo;
			Authentication_Method		authenticationMethod;
			IO_Capability				ioCapability;
			Authentication_Requirements authenticationRequirements;

			union
			{
				unsigned long	Numeric_Value;
				unsigned long	Passkey;
			};
		};

		__QOR_DECLARE_OCLASS_ID( CBluetoothRemoteDevice );

		CBluetoothRemoteDevice();
		virtual ~CBluetoothRemoteDevice();

		//--------------------------------------------------------------------------------
		refType Ref( void )
		{
			return refType( this, false );
		}

		static refType Prototype( void );

		void Update( void );
		Info* GetInfo( void );

		void Authenticate( COSWindow::refType ParentWindow, CWString strPassKey );
		unsigned long AuthenticateEx( COSWindow::refType ParentWindow, BluetoothOutOfBandData* pbtOobData, Authentication_Requirements AuthentRequirements );
		bool DisplayProperties( COSWindow::refType ParentWindow );
		void EnumerateInstalledServices( void );
		
		void Remove( void );		

		void OnConnect( eConnectionType ConnectionType );
		void OnDisconnect( void );
		void OnL2CAPEvent( BluetoothL2CAPEventInfo* pEventInfo, CBluetoothRadio* Radio );
		void OnL2CAPDisconnect( ePSM PSM, bool bInitiated );
		void OnL2CAPConnect( ePSM PSM, bool bInitiated );
		void OnEstablishCODMiscellaneous();
		void OnEstablishCODComputer( void );
		void OnEstablishCODPhone( void );
		void OnEstablishCODLANAccess( void );
		void OnEstablishCODAudio( void );
		void OnEstablishCODPeripheral( void );
		void OnEstablishCODImaging( void );
		void OnEstablishCODWearable( void );
		void OnEstablishCODToy( void );
		void OnEstablishCODHealth( void );
		void OnEstablishCODUnclassified( void );
		void OnEstablishCOD( void );
		void OnInRange( ShortInfo& Info, unsigned long ulPreviousFlags, CBluetoothRadio* Radio );
		void OnOutOfRange( void );
		bool OnAuthenticationRequest( Authentication_CallbackParams* pAuthCallbackParams, CAuthenticateBluetoothSession& AuthenticationSession );
		bool OnLegacyAuthenticationRequest( Authentication_CallbackParams* pAuthCallbackParams, CAuthenticateBluetoothSession& AuthenticationSession );
		bool OnOutOfBandAuthenticationRequest( Authentication_CallbackParams* pAuthCallbackParams, CAuthenticateBluetoothSession& AuthenticationSession );
		bool OnNumericComparisonAuthenticationRequest( Authentication_CallbackParams* pAuthCallbackParams, CAuthenticateBluetoothSession& AuthenticationSession );
		bool OnPasskeyNotificationAuthenticationRequest( CBluetoothRemoteDevice::Authentication_CallbackParams* pAuthCallbackParams, CAuthenticateBluetoothSession& AuthenticationSession );
		bool OnPassKeyAuthenticationRequest( CBluetoothRemoteDevice::Authentication_CallbackParams* pAuthCallbackParams, CAuthenticateBluetoothSession& AuthenticationSession );

		nsCodeQOR::mxGUID* GetServices( unsigned long& ulCountServices );
		CBluetoothClient** GetServiceClients( void );

	private:

		void Reset( void );
		
		nsWinQAPI::CBthProps& m_Library;
		Info m_Info;		
		nsCodeQOR::mxGUID* m_pGuidServices;
		CBluetoothClient** m_pServiceClients;
		unsigned long m_ulCountServices;

		CBluetoothRemoteDevice( const CBluetoothRemoteDevice& );
		CBluetoothRemoteDevice& operator = ( const CBluetoothRemoteDevice& );
	};

	//--------------------------------------------------------------------------------
	struct BluetoothRadioInRange
	{
		CBluetoothRemoteDevice::ShortInfo deviceInfo;
		unsigned long previousDeviceFlags;
	};

}//nsWin32

#endif//WINQL_COMMS_BLUETOOTHREMOTEDEVICE_H_3
