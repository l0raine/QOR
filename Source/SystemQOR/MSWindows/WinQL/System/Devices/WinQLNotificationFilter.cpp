//WinQLNotificationFilter.cpp

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
#include "WinQL/CodeServices/Handles/WinQLHandle.h"
#include "WinQL/System/Devices/WinQLNotificationFilter.h"
#include "WinQL/Application/Threading/WinQLThread.h"
#include "WinQL/Application/Resources/WinQLResourceManager.h"
#include "WinQAPI/User32.h"

//--------------------------------------------------------------------------------
namespace nsWin32
{
	using namespace nsWinQAPI;

	//--------------------------------------------------------------------------------
	CNotificationFilter::CNotificationFilter(  eNotificationType NotifyType ) : m_NotifyType( NotifyType ), m_bAllClasses( false ) 
	{
	}

	//--------------------------------------------------------------------------------
	CNotificationFilter::~CNotificationFilter()
	{
	}

	//--------------------------------------------------------------------------------
	bool CNotificationFilter::GetAllClasses( void )
	{
		return m_bAllClasses;
	}

	//--------------------------------------------------------------------------------
	void CNotificationFilter::SetAllClasses( bool bAll )
	{
		m_bAllClasses = bAll;
	}

	//--------------------------------------------------------------------------------
	void CNotificationFilter::AddInterfaceFilter( nsCodeQOR::mxGUID* pGUID )
	{
		sDeviceBroadcastDeviceInterace DevInterface;

		DevInterface.ulSize = sizeof( sDeviceBroadcastDeviceInterace );
		DevInterface.ulDeviceType = eNotifyInterface;
		memcpy( &DevInterface.guid, pGUID, sizeof( nsCodeQOR::mxGUID ) );
	
		m_VecInterfaceFilters.push_back( DevInterface );
	}

	//--------------------------------------------------------------------------------
	void CNotificationFilter::AddHandleFilter( void* DeviceHandle, nsCodeQOR::mxGUID* pEventGUID )
	{
		sDeviceBroadcastHandle DevHandle;

		DevHandle.ulSize = sizeof( sDeviceBroadcastHandle );
		DevHandle.ulDeviceType = eNotifyHandle;
		DevHandle.DeviceHandle = DeviceHandle;
		DevHandle.NotificationHandle = 0;
		DevHandle.NameOffset = 0;
		DevHandle.data[ 0 ] = 0;
		memcpy( &DevHandle.EventGUID, pEventGUID, sizeof( nsCodeQOR::mxGUID ) );

		m_VecHandleFilters.push_back( DevHandle );
	}

	//--------------------------------------------------------------------------------
	std::vector< sDeviceBroadcastDeviceInterace >& CNotificationFilter::InterfaceFilters( void )
	{
		return m_VecInterfaceFilters;
	}

	//--------------------------------------------------------------------------------
	std::vector< sDeviceBroadcastHandle >& CNotificationFilter::HandleFilters( void )
	{
		return m_VecHandleFilters;
	}

	//--------------------------------------------------------------------------------
	CNotificationFilter::eNotificationType CNotificationFilter::NotifyType( void )
	{
		return m_NotifyType;
	}

}//nsWin32
