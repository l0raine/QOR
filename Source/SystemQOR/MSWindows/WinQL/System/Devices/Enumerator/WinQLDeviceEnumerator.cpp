//WinQLDeviceEnumerator.cpp

// Copyright Querysoft Limited 2013, 2015
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
#include "WinQL/Application/ErrorSystem/WinQLError.h"
#include "WinQL/CodeServices/Text/WinString.h"
#include "WinQL/System/Devices/Enumerator/WinQLDeviceEnumerator.h"
#include "WinQL/System/Devices/Instances/WinQLDeviceInstance.h"
#include "WinQL/System/WinQLSystem.h"
#include "WinQAPI/SetupAPI.h"

//--------------------------------------------------------------------------------
namespace nsWin32
{
	using namespace nsWinQAPI;

	//--------------------------------------------------------------------------------
	__QOR_IMPLEMENT_OCLASS_LUID( CDeviceEnumerator );

	//--------------------------------------------------------------------------------
	CDeviceEnumerator::CDeviceEnumerator( CTString& strEnumID ) : m_Library( CSetupAPI::Instance() )
	,	m_strID( strEnumID ), m_ArrayDeviceInstances(), m_bEnumerated( false )
	{
		_WINQ_FCONTEXT( "CDeviceEnumerator::CDeviceEnumerator" );		
	}

	//--------------------------------------------------------------------------------
	CTString CDeviceEnumerator::ID(void)
	{
		return m_strID;
	}

	//--------------------------------------------------------------------------------
	CDeviceEnumerator::~CDeviceEnumerator()
	{
		_WINQ_FCONTEXT( "CDeviceEnumerator::~CDeviceEnumerator" );
	}

	//--------------------------------------------------------------------------------
	nsCodeQOR::CTArray< CDeviceInstance*, CWinQLPolicy >& CDeviceEnumerator::Instances()
	{
		_WINQ_FCONTEXT( "CDeviceEnumerator::Instances" );
		return m_ArrayDeviceInstances;
	}

	//--------------------------------------------------------------------------------
	unsigned int CDeviceEnumerator::Enumerate( void )
	{
		_WINQ_FCONTEXT( "CDeviceEnumerator::Enumerate" );
		unsigned int uiIndex = m_ArrayDeviceInstances.Size();
		if( !m_bEnumerated )
		{
			m_InfoSet.Attach( new CDeviceInfoSet( m_strID ), true );
			nsCodeQOR::mxGUID nullGUID = { 0x00000000, 0x0000, 0x0000, { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 } };			
			do
			{
				unsigned long ulError = 0;
				unsigned long ulResult = (unsigned long)(-1);
				m_DevInfo.cbSize = sizeof( ::SP_DEVINFO_DATA );
				m_DevInfo.ClassGuid = nullGUID;
				m_DevInfo.DevInst = 0;
				m_DevInfo.Reserved = 0;

				if( m_Library.SetupDiEnumDeviceInfo( reinterpret_cast< ::HDEVINFO >( m_InfoSet->Handle().Use() ), uiIndex, reinterpret_cast< ::PSP_DEVINFO_DATA >( &m_DevInfo ) ) )
				{
					ulResult = m_DevInfo.DevInst;
					if( ulResult > 0 && ulResult != (unsigned long)(-1) )
					{
						CTString strDeviceID;
						if( m_Library.CM_Get_Device_ID_Ex( static_cast< ::DEVINST >( m_DevInfo.DevInst ), strDeviceID.GetBufferSetLength( MaxDeviceIDLen + 1), MaxDeviceIDLen, 0, 0 ) != CR_SUCCESS )
						{
							ulError = ::GetLastError();
						}
						else
						{
							strDeviceID.ValidateBuffer();
							//Get the device instance ID and device data and add it to the global instance map
							CTString strDeviceInstance;
							unsigned long ulInstanceSize = 0;
							m_Library.SetupDiGetDeviceInstanceId( reinterpret_cast< ::HDEVINFO >( m_InfoSet->Handle().Use() ), reinterpret_cast< ::PSP_DEVINFO_DATA >( &m_DevInfo ), 0, 0, &ulInstanceSize );
							if( ulInstanceSize > 0 )
							{							
								m_Library.SetupDiGetDeviceInstanceId( m_InfoSet->Handle().Use(), reinterpret_cast< ::PSP_DEVINFO_DATA >( &m_DevInfo ), 
									strDeviceInstance.GetBufferSetLength( static_cast< unsigned short >( ulInstanceSize + 1 ) ), ulInstanceSize, &ulInstanceSize );
								strDeviceInstance.ValidateBuffer( static_cast< unsigned short >( ulInstanceSize ) );
							}
							else
							{
								ulError = ::GetLastError();
							}

							CDeviceInstance* pDeviceInstance = TheSystem().As< nsWin32::CSystem >()->Devices(QOR_PP_SHARED_OBJECT_ACCESS).DeviceFromID( strDeviceInstance );
						
							if( pDeviceInstance == 0 )
							{
								pDeviceInstance = new CDeviceInstance( strDeviceID, m_InfoSet, m_DevInfo, uiIndex );
							}
							else
							{
								pDeviceInstance->AttachInfoSet( m_InfoSet, uiIndex );
							}

							m_ArrayDeviceInstances.Append( pDeviceInstance );
						}
						
						uiIndex++;
					}
					else
					{
						ulError = ::GetLastError();
						m_bEnumerated = true;
					}
				}
				else
				{
					ulError = ::GetLastError();
					m_bEnumerated = true;
				}
			}while( !m_bEnumerated );
		}
		return uiIndex;
	}

}//nsWin32
