//WinQLDisplay.cpp

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

#include "WinQL/Application/ErrorSystem/WinQLError.h"
#include "CompilerQOR.h"
__QCMP_WARNING_PUSH
__QCMP_WARNING_DISABLE( __QCMP_WARN_THIS_USED_IN_BASE_INIT_LIST, "Safe usage: stored in member for later use" )
#include "WinQL/Application/Graphics/WinQLDisplay.h"
__QCMP_WARNING_POP
#include "WinQL/System/Info/WinQLInfo.h"
#include "WinQAPI/User32.h"

#undef AddMonitor		//Kill the leaked AddMonitor(A/W) definition from Windows headers
#undef EnumMonitors

//--------------------------------------------------------------------------------
namespace nsWin32
{
	using namespace nsWinQAPI;

	__QOR_IMPLEMENT_OCLASS_LUID( CDisplayHelper );

	//--------------------------------------------------------------------------------
	CDisplayHelper::CDisplayHelper() : m_User32Library( CUser32::Instance() )
	{
		_WINQ_FCONTEXT( "CDisplayHelper::CDisplayHelper" );
	}

	//--------------------------------------------------------------------------------
	CDisplayHelper::CDisplayHelper( const CDisplayHelper& src) : m_User32Library(CUser32::Instance())
	{
		_WINQ_FCONTEXT("CDisplayHelper::CDisplayHelper");
	}

	//--------------------------------------------------------------------------------
	CDisplayHelper::CDisplayHelper( CDisplayHelper&& move ) : m_User32Library(CUser32::Instance())
	{
		_WINQ_FCONTEXT("CDisplayHelper::CDisplayHelper");
	}

	//--------------------------------------------------------------------------------
	CDisplayHelper& CDisplayHelper::operator = (const CDisplayHelper& src)
	{
		_WINQ_FCONTEXT("CDisplayHelper::operator =");
		return *this;
	}

	//--------------------------------------------------------------------------------
	CDisplayHelper& CDisplayHelper::operator = ( CDisplayHelper&& move)
	{
		_WINQ_FCONTEXT("CDisplayHelper::operator =");
		return *this;
	}

	//--------------------------------------------------------------------------------
	CDisplayHelper::~CDisplayHelper()
	{
		_WINQ_FCONTEXT( "CDisplayHelper::~CDisplayHelper" );
	}

	//--------------------------------------------------------------------------------
	long CDisplayHelper::ChangeSettings( nsWin32::LPDEVMODE lpDevMode, unsigned long dwflags ) const
	{
		_WINQ_FCONTEXT( "CDisplayHelper::ChangeSettings" );
		LONG lResult = 0;
		__QOR_PROTECT
		{
			lResult = m_User32Library.ChangeDisplaySettings( reinterpret_cast< ::LPDEVMODE >( lpDevMode ), dwflags );
		}__QOR_ENDPROTECT
		return lResult;
	}

	//--------------------------------------------------------------------------------
	long CDisplayHelper::ChangeSettings( const TCHAR* lpszDeviceName, nsWin32::LPDEVMODE lpDevMode, COSWindow::refType Window, unsigned long dwflags, void* lParam ) const
	{
		_WINQ_FCONTEXT( "CDisplayHelper::ChangeSettings" );
		LONG lResult = 0;
		__QOR_PROTECT
		{
			lResult = m_User32Library.ChangeDisplaySettingsEx( lpszDeviceName, reinterpret_cast< ::LPDEVMODE >( lpDevMode ), reinterpret_cast< ::HWND >( Window->Handle()->Use() ), dwflags, lParam );
		}__QOR_ENDPROTECT
		return lResult;
	}

	//--------------------------------------------------------------------------------
	bool CDisplayHelper::EnumDevices( const TCHAR* lpDevice, unsigned long iDevNum, nsWin32::PDISPLAY_DEVICE lpDisplayDevice, unsigned long dwFlags ) const
	{
		_WINQ_FCONTEXT( "CDisplayHelper::EnumDevices" );
		bool bResult = false;
		__QOR_PROTECT
		{
			bResult = m_User32Library.EnumDisplayDevices( lpDevice, iDevNum, reinterpret_cast< ::PDISPLAY_DEVICE >( lpDisplayDevice ), dwFlags ) ? true : false;
		}__QOR_ENDPROTECT
		return bResult;
	}

	//--------------------------------------------------------------------------------
	bool CDisplayHelper::EnumSettings( const TCHAR* lpszDeviceName, unsigned long iModeNum, nsWin32::LPDEVMODE lpDevMode, unsigned long dwFlags ) const
	{				
		_WINQ_FCONTEXT( "CDisplayHelper::EnumSettings" );
		bool bResult = false;
		__QOR_PROTECT
		{
			if( dwFlags == 0 )
			{
				bResult = m_User32Library.EnumDisplaySettings( lpszDeviceName, iModeNum, reinterpret_cast< ::LPDEVMODE >( lpDevMode ) ) ? true : false;
			}
			else
			{
				bResult = m_User32Library.EnumDisplaySettingsEx( lpszDeviceName, iModeNum, reinterpret_cast< ::LPDEVMODE >( lpDevMode ), dwFlags ) ? true : false;
			}
		}__QOR_ENDPROTECT
		return bResult;
	}

	//--------------------------------------------------------------------------------
	bool CDisplayHelper::EnumDisplayMonitors( CDeviceContext::refType dc, const nsWin32::RECT* lprcClip, nsWin32::MONITORENUMPROC lpfnEnum, Cmp_long_ptr dwData ) const
	{
		_WINQ_FCONTEXT( "CDisplayHelper::EnumDisplayMonitors" );
		bool bResult = false;
		__QOR_PROTECT
		{
			bResult = m_User32Library.EnumDisplayMonitors( dc.IsNull() ? 0 : reinterpret_cast< ::HDC >( dc->Handle()->Use() ), reinterpret_cast< const ::RECT* >( lprcClip ), reinterpret_cast< ::MONITORENUMPROC >( lpfnEnum ), dwData ) ? true : false;
		}__QOR_ENDPROTECT
		return bResult;
	}

	//--------------------------------------------------------------------------------
	bool CDisplayHelper::SetProcessDPIAware() const
	{
		_WINQ_FCONTEXT( "CDisplayHelper::SetProcessDPIAware" );
		bool bResult = false;
		__QOR_PROTECT
		{
			bResult = m_User32Library.SetProcessDPIAware() ? true : false;
		}__QOR_ENDPROTECT
		return bResult;
	}

	//--------------------------------------------------------------------------------
	bool CDisplayHelper::GetProcessDefaultLayout( unsigned long* pdwDefaultLayout ) const
	{
		_WINQ_FCONTEXT( "CDisplayHelper::GetProcessDefaultLayout" );
		bool bResult = false;
		__QOR_PROTECT
		{
			bResult = m_User32Library.GetProcessDefaultLayout( pdwDefaultLayout ) ? true : false;
		}__QOR_ENDPROTECT
		return bResult;
	}

	//--------------------------------------------------------------------------------
	bool CDisplayHelper::SetProcessDefaultLayout( unsigned long dwDefaultLayout ) const
	{
		_WINQ_FCONTEXT( "CDisplayHelper::SetProcessDefaultLayout" );
		bool bResult = false;
		__QOR_PROTECT
		{
			bResult = m_User32Library.SetProcessDefaultLayout( dwDefaultLayout ) ? true : false;
		}__QOR_ENDPROTECT
		return bResult;
	}

	//--------------------------------------------------------------------------------
	bool CDisplayHelper::IsProcessDPIAware() const
	{
		_WINQ_FCONTEXT( "CDisplayHelper::IsProcessDPIAware" );
		bool bResult = false;
		__QOR_PROTECT
		{
			bResult = m_User32Library.IsProcessDPIAware() ? true : false;
		}__QOR_ENDPROTECT
		return bResult;
	}



	//--Monitor-----------------------------------------------------------------------

	__QOR_IMPLEMENT_OCLASS_LUID( CMonitorHelper );

#include "CompilerQOR.h"
__QCMP_WARNING_PUSH
__QCMP_WARNING_DISABLE( __QCMP_WARN_THIS_USED_IN_BASE_INIT_LIST, "Safe usage: stored in member for later use" )

	//--------------------------------------------------------------------------------
	CMonitorHelper::CMonitorHelper( const CMonitorHelper& Monitor ) : m_User32Library( CUser32::Instance() )
	,	m_Handle( this, 0 )
	{
		_WINQ_FCONTEXT( "CMonitorHelper::CMonitorHelper" );
		m_Handle = Monitor.m_Handle.AsHandle().ptr();
	}

	//--------------------------------------------------------------------------------
	CMonitorHelper::CMonitorHelper( CMonitorHandle::refType hMonitor ) : m_User32Library( CUser32::Instance() )
	,	m_Handle( this, 0 )
	{
		_WINQ_FCONTEXT( "CMonitorHelper::CMonitorHelper" );
		m_Handle = hMonitor->AsHandle().ptr();
	}

	//--------------------------------------------------------------------------------
	CMonitorHelper::CMonitorHelper( nsWin32::POINT pt, unsigned long dwFlags ) : m_User32Library( CUser32::Instance() )
	,	m_Handle( this, 0 )
	{
		_WINQ_FCONTEXT( "CMonitorHelper::CMonitorHelper" );
		__QOR_PROTECT
		{
			m_Handle = ( m_User32Library.MonitorFromPoint( *(reinterpret_cast< ::POINT* >( &pt ) ), dwFlags ) );
		}__QOR_ENDPROTECT
	}

	//--------------------------------------------------------------------------------
	CMonitorHelper::CMonitorHelper( const nsWin32::RECT* lprc, unsigned long dwFlags ) : m_User32Library( CUser32::Instance() )
	,	m_Handle( this, 0 )
	{
		_WINQ_FCONTEXT( "CMonitorHelper::CMonitorHelper" );
		__QOR_PROTECT
		{
			m_Handle = ( m_User32Library.MonitorFromRect( reinterpret_cast< ::LPCRECT >( lprc ), dwFlags ) );
		}__QOR_ENDPROTECT
	}

	//--------------------------------------------------------------------------------
	CMonitorHelper::CMonitorHelper( COSWindow::refType Window, unsigned long dwFlags ) : m_User32Library( CUser32::Instance() )
	,	m_Handle( this, 0 )
	{
		_WINQ_FCONTEXT( "CMonitorHelper::CMonitorHelper" );
		__QOR_PROTECT
		{
			m_Handle = ( m_User32Library.MonitorFromWindow( reinterpret_cast< ::HWND >( Window->Handle()->Use() ), dwFlags ) );
		}__QOR_ENDPROTECT
	}

__QCMP_WARNING_POP

	//--------------------------------------------------------------------------------
	CMonitorHelper::~CMonitorHelper()
	{
		_WINQ_FCONTEXT( "CMonitorHelper::~CMonitorHelper" );
	}

	//--------------------------------------------------------------------------------
	bool CMonitorHelper::GetInfo( nsWin32::LPMONITORINFO lpmi ) const
	{
		_WINQ_FCONTEXT( "CMonitorHelper::GetInfo" );
		bool bResult = false;
		__QOR_PROTECT
		{
			bResult = m_User32Library.GetMonitorInfo( reinterpret_cast< ::HMONITOR >( m_Handle.Use() ), reinterpret_cast< ::LPMONITORINFO >( lpmi ) ) ? true : false;
		}__QOR_ENDPROTECT
		return bResult;
	}


	//--------------------------------------------------------------------------------

	__QOR_IMPLEMENT_OCLASS_LUID( CDisplay );

	//--------------------------------------------------------------------------------
	CDisplay::CDisplay() : m_bDevicesEnumerated( false ), m_bMonitorsEnumerated( false )
	{
		_WINQ_FCONTEXT( "CDisplay::CDisplay" );
	}

	//--------------------------------------------------------------------------------
	CDisplay::~CDisplay()
	{
		_WINQ_FCONTEXT( "CDisplay::~CDisplay" );
	}

	//--------------------------------------------------------------------------------
	CDisplayDevice::ref_type CDisplay::DefaultDevice()
	{
		_WINQ_FCONTEXT("CDisplay::DefaultDevice");
		if( !m_bDevicesEnumerated )
		{
			EnumDevices();
		}
		return m_Devices[ 0 ];
	}

	//--------------------------------------------------------------------------------
	std::vector< CDisplayDevice::ref_type >::iterator CDisplay::Devices_begin()
	{
		_WINQ_FCONTEXT("CDisplay::Devices_begin");
		if (!m_bDevicesEnumerated)
		{
			EnumDevices();
		}
		return m_Devices.begin();
	}

	//--------------------------------------------------------------------------------
	std::vector< CDisplayDevice::ref_type >::iterator CDisplay::Devices_end()
	{
		_WINQ_FCONTEXT("CDisplay::Devices_end");
		if (!m_bDevicesEnumerated)
		{
			EnumDevices();
		}
		return m_Devices.end();
	}

	//--------------------------------------------------------------------------------
	std::vector< CDisplayMonitor::ref_type >::iterator CDisplay::Monitors_begin(void)
	{
		_WINQ_FCONTEXT("CDisplay::Monitors_begin");
		if (!m_bMonitorsEnumerated)
		{
			EnumAllMonitors();
		}
		return m_Monitors.begin();
	}

	//--------------------------------------------------------------------------------
	std::vector< CDisplayMonitor::ref_type >::iterator CDisplay::Monitors_end(void)
	{
		_WINQ_FCONTEXT("CDisplay::Monitors_end");
		if (!m_bMonitorsEnumerated)
		{
			EnumAllMonitors();
		}
		return m_Monitors.end();
	}

	//--------------------------------------------------------------------------------
	CDisplayMonitor::ref_type CDisplay::MonitorFromPoint( nsWin32::POINT pt, unsigned long dwFlags )
	{
		_WINQ_FCONTEXT("CDisplay::MonitorFromPoint");
		return new_shared_ref<CDisplayMonitor>(pt, dwFlags);
	}

	//--------------------------------------------------------------------------------
	CDisplayMonitor::ref_type CDisplay::MonitorFromRect( const CRectangle* lprc, unsigned long dwFlags )
	{
		_WINQ_FCONTEXT("CDisplay::MonitorFromRect");
		return new_shared_ref<CDisplayMonitor>(lprc, dwFlags);
	}

	//--------------------------------------------------------------------------------
	CDisplayMonitor::ref_type CDisplay::MonitorFromWindow( COSWindow::refType Window, unsigned long dwFlags )
	{
		_WINQ_FCONTEXT("CDisplay::MonitorFromWindow");
		return new_shared_ref<CDisplayMonitor>( Window, dwFlags );
	}

	//--------------------------------------------------------------------------------
	long CDisplay::ChangeSettingsForDefaultDevice( nsWin32::LPDEVMODE lpDevMode, unsigned long dwflags )
	{
		_WINQ_FCONTEXT("CDisplay::ChangeSettingsForDefaultDevice");
		long lResult = 0;
		lResult = m_Win32DisplayHelper.ChangeSettings( lpDevMode, dwflags );
		return lResult;
	}

	//--------------------------------------------------------------------------------
	bool CDisplay::EnumMonitors( CDeviceContext::refType dc, const CRectangle* lprcClip, nsWin32::MONITORENUMPROC lpfnEnum, Cmp_long_ptr dwData )
	{
		_WINQ_FCONTEXT("CDisplay::EnumMonitors");
		bool bResult = false;
		bResult = m_Win32DisplayHelper.EnumDisplayMonitors( dc, lprcClip, lpfnEnum, dwData );
		return bResult;
	}			

	//--------------------------------------------------------------------------------
	bool CDisplay::EnumAllMonitors()
	{
		_WINQ_FCONTEXT( "CDisplay::EnumAllMonitors" );
		bool bResult = false;
		bResult = m_Win32DisplayHelper.EnumDisplayMonitors( 0, 0, reinterpret_cast< nsWin32::MONITORENUMPROC >( &CDisplay::EnumMonitorProc ), reinterpret_cast<Cmp_long_ptr>( this ) );
		m_bMonitorsEnumerated = true;
		return bResult;
	}

	//--------------------------------------------------------------------------------
	bool __QCMP_STDCALLCONVENTION CDisplay::EnumMonitorProc( void* hMonitor, void* phdcMonitor, LPRECT lprcMonitor, Cmp_long_ptr dwData )
	{
		_WINQ_SFCONTEXT( "CDisplay::EnumMonitorProc" );
		bool bResult = false;
		CDisplay* pThis = reinterpret_cast< CDisplay* >( dwData );
		CDeviceContext::refType refDC = CDeviceContext::FromHandle( CDCHandle( 0, phdcMonitor ).Ref() );
		bResult = pThis->AddMonitor( hMonitor, refDC, lprcMonitor );
		return bResult;
	}

	//--------------------------------------------------------------------------------
	bool CDisplay::AddMonitor( void* hMonitor, CDeviceContext::refType dcMonitor, LPRECT lprcMonitor )
	{
		_WINQ_FCONTEXT( "CDisplay::AddMonitor" );
		bool bResult = false;
		CDisplayMonitor::ref_type Monitor = new_shared_ref<CDisplayMonitor>( CMonitorHandle( 0, hMonitor ).Ref() );
		m_Monitors.push_back( Monitor );
		bResult = true;
		return bResult;
	}

	//--------------------------------------------------------------------------------
	bool CDisplay::EnumDevices()
	{
		_WINQ_FCONTEXT( "CDisplay::EnumDevices" );

		CSystemInfo Info;
		unsigned long dwMajorVersion = Info.GetMajorVersion();
		bool bResult = false;

#		if( WINVER >= 0x0500 )
		if( dwMajorVersion > 4 )
		{
			unsigned long iDevNum = 0;
				
			do
			{
				DISPLAY_DEVICE tmpDisplayDevice;
				memset(&tmpDisplayDevice, 0, sizeof(DISPLAY_DEVICE));
				tmpDisplayDevice.cb = sizeof(DISPLAY_DEVICE);				
				bResult = m_Win32DisplayHelper.EnumDevices( 0, iDevNum, &tmpDisplayDevice, CDisplayHelper::_EDD_GET_DEVICE_INTERFACE_NAME );
				if( bResult == true )
				{
					m_Devices.push_back(new_shared_ref<CDisplayDevice>(tmpDisplayDevice));
				}
				iDevNum++;
			}while( bResult == true );
			m_bDevicesEnumerated = true;
		}
		else
		{
#		else
			m_Devices.push_back(new_shared_ref<CDisplayDevice>());
#		endif
#		if( WINVER >= 0x0500 )
		}
#		endif

		return bResult;
	}





	__QOR_IMPLEMENT_OCLASS_LUID( CDisplayDevice )

	//--------------------------------------------------------------------------------
	CDisplayDevice::CDisplayDevice() : m_bInitialised( false )
	{				
		_WINQ_FCONTEXT( "CDisplayDevice::CDisplayDevice" );
		cb = sizeof( nsWin32::DISPLAY_DEVICE );
		DeviceID[0] = 0;
		DeviceKey[0] = 0;
		DeviceName[0] = 0;
		DeviceString[0] = 0;
		StateFlags = 0;
	}

	//--------------------------------------------------------------------------------
	CDisplayDevice::CDisplayDevice( const DISPLAY_DEVICE& src) : m_bInitialised(true)
	{
		_WINQ_FCONTEXT("CDisplayDevice::CDisplayDevice");
		cb = src.cb;
		memcpy(DeviceID, src.DeviceID, sizeof(TCHAR) * 128);
		memcpy(DeviceKey, src.DeviceKey, sizeof(TCHAR) * 128);
		memcpy(DeviceName, src.DeviceName, sizeof(TCHAR) * 32);
		memcpy(DeviceString, src.DeviceString, sizeof(TCHAR) * 128);
		StateFlags = src.StateFlags;
	}

	//--------------------------------------------------------------------------------
	CDisplayDevice::CDisplayDevice( const CDisplayDevice& src )
	{
		_WINQ_FCONTEXT( "CDisplayDevice::CDisplayDevice" );
		*this = src;
	}

	//--------------------------------------------------------------------------------
	CDisplayDevice::CDisplayDevice(CDisplayDevice&& move)
	{
		_WINQ_FCONTEXT("CDisplayDevice::CDisplayDevice");
		*this = std::move(move);
	}
	//--------------------------------------------------------------------------------
	CDisplayDevice::~CDisplayDevice()
	{
		_WINQ_FCONTEXT( "CDisplayDevice::~CDisplayDevice" );
	}

	//--------------------------------------------------------------------------------
	CDisplayDevice& CDisplayDevice::operator=( const CDisplayDevice& Src )
	{
		_WINQ_FCONTEXT( "CDisplayDevice::operator =" );
		cb = Src.cb;
		memcpy( DeviceName, Src.DeviceName, 32 * sizeof( TCHAR ) );
		memcpy( DeviceString, Src.DeviceString, 128 * sizeof( TCHAR ) );
		StateFlags = Src.StateFlags;
		memcpy( DeviceID, Src.DeviceID, 128 * sizeof( TCHAR ) );
		memcpy( DeviceKey, Src.DeviceKey, 128 * sizeof( TCHAR ) );
		return *this;
	}

	//--------------------------------------------------------------------------------
	CDisplayDevice& CDisplayDevice::operator=( CDisplayDevice&& move)
	{
		_WINQ_FCONTEXT("CDisplayDevice::operator =");
		cb = move.cb;
		memcpy(DeviceName, move.DeviceName, 32 * sizeof(TCHAR));
		memcpy(DeviceString, move.DeviceString, 128 * sizeof(TCHAR));
		StateFlags = move.StateFlags;
		memcpy(DeviceID, move.DeviceID, 128 * sizeof(TCHAR));
		memcpy(DeviceKey, move.DeviceKey, 128 * sizeof(TCHAR));
		return *this;
	}

	//--------------------------------------------------------------------------------
	bool CDisplayDevice::EnumSettings( unsigned long iModeNum, nsWin32::LPDEVMODE lpDevMode, unsigned long dwFlags ) const
	{
		_WINQ_FCONTEXT( "CDisplayDevice::EnumSettings" );
		bool bResult = false;
		if( m_bInitialised )
		{
			bResult = m_Win32DisplayHelper.EnumSettings( DeviceName, iModeNum, lpDevMode, dwFlags );
		}
		else
		{
			bResult = m_Win32DisplayHelper.EnumSettings( 0, iModeNum, lpDevMode, 0 );
		}
		return bResult;
	}

	//--------------------------------------------------------------------------------
	long CDisplayDevice::ChangeSettings( nsWin32::LPDEVMODE lpDevMode, COSWindow::refType Window, unsigned long dwflags, void* lParam ) const
	{
		_WINQ_FCONTEXT( "CDisplayDevice::ChangeSettings" );
		return m_Win32DisplayHelper.ChangeSettings( DeviceName, lpDevMode, Window, dwflags, lParam );
	}

	//--------------------------------------------------------------------------------
	CTString CDisplayDevice::GetDeviceID() const
	{
		_WINQ_FCONTEXT( "CDisplayDevice::GetDeviceID" );
		CTString strDeviceID( DeviceID, 128 );
		return strDeviceID;
	}

	//--------------------------------------------------------------------------------
	CTString CDisplayDevice::GetDeviceString() const
	{
		_WINQ_FCONTEXT( "CDisplayDevice::GetDeviceString" );
		CTString strDeviceString( DeviceString, 128 );
		return strDeviceString;
	}



	__QOR_IMPLEMENT_OCLASS_LUID( CDisplayMonitor )

	//--------------------------------------------------------------------------------
	CDisplayMonitor::CDisplayMonitor( const CDisplayMonitor& Monitor ) : m_Win32Monitor( Monitor.m_Win32Monitor )
	{
		_WINQ_FCONTEXT( "CDisplayMonitor::CDisplayMonitor" );
		*( dynamic_cast< nsWin32::MONITORINFO* >( this ) ) = Monitor;
	}

	//--------------------------------------------------------------------------------
	CDisplayMonitor::CDisplayMonitor( CDisplayMonitor&& Monitor) : m_Win32Monitor(std::move(Monitor.m_Win32Monitor))
	{
		_WINQ_FCONTEXT("CDisplayMonitor::CDisplayMonitor");
		*(dynamic_cast< nsWin32::MONITORINFO* >(this)) = std::move(Monitor);
	}

	//--------------------------------------------------------------------------------
	CDisplayMonitor::CDisplayMonitor( CMonitorHandle::refType hMonitor ) : m_Win32Monitor( hMonitor )
	{
		_WINQ_FCONTEXT( "CDisplayMonitor::CDisplayMonitor" );
		cbSize = sizeof( nsWin32::MONITORINFO );
		m_Win32Monitor.GetInfo( this );
	}

	//--------------------------------------------------------------------------------
	CDisplayMonitor::CDisplayMonitor( nsWin32::POINT pt, unsigned long dwFlags ) : m_Win32Monitor( pt, dwFlags )
	{
		_WINQ_FCONTEXT( "CDisplayMonitor::CDisplayMonitor" );
		cbSize = sizeof( nsWin32::MONITORINFO );
		m_Win32Monitor.GetInfo( this );
	}

	//--------------------------------------------------------------------------------
	CDisplayMonitor::CDisplayMonitor( const CRectangle* lprc, unsigned long dwFlags ) : m_Win32Monitor( lprc, dwFlags )
	{
		_WINQ_FCONTEXT( "CDisplayMonitor::CDisplayMonitor" );
		cbSize = sizeof( nsWin32::MONITORINFO );
		m_Win32Monitor.GetInfo( this );
	}

	//--------------------------------------------------------------------------------
	CDisplayMonitor::CDisplayMonitor( COSWindow::refType Window, unsigned long dwFlags ) : m_Win32Monitor( Window, dwFlags )
	{
		_WINQ_FCONTEXT( "CDisplayMonitor::CMonitor" );
		cbSize = sizeof( nsWin32::MONITORINFO );
		m_Win32Monitor.GetInfo( this );
	}

	//--------------------------------------------------------------------------------
	CDisplayMonitor& CDisplayMonitor::operator = (const CDisplayMonitor& src)
	{
		_WINQ_FCONTEXT("CDisplayMonitor::operator =");
		if (&src != this)
		{
			cbSize = src.cbSize;
			rcMonitor = src.rcMonitor;
			rcWork = src.rcWork;
			dwFlags = src.dwFlags;
		}
		return *this;
	}

	//--------------------------------------------------------------------------------
	CDisplayMonitor& CDisplayMonitor::operator = (CDisplayMonitor&& move)
	{
		_WINQ_FCONTEXT("CDisplayMonitor::operator =");
		if (&move != this)
		{
			cbSize = std::move(move.cbSize);
			rcMonitor = std::move(move.rcMonitor);
			rcWork = std::move(move.rcWork);
			dwFlags = std::move(move.dwFlags);
		}
		return *this;
	}

	//--------------------------------------------------------------------------------
	bool CDisplayMonitor::IsPrimary() const
	{
		return ( dwFlags & MONITORINFOF_PRIMARY ) ? true : false;
	}

	//--------------------------------------------------------------------------------
	CDisplayMonitor::~CDisplayMonitor()
	{
		_WINQ_FCONTEXT( "CDisplayMonitor::~CMonitor" );
	}

}//nsWin32
