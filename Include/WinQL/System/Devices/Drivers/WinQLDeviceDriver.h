//WinQLDeviceDriver.h

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

//Win32 Device Driver

#ifndef WINQL_DEVICEDRIVER_H_3
#define WINQL_DEVICEDRIVER_H_3

#include "CompilerQOR.h"

#ifdef	__QCMP_OPTIMIZEINCLUDE
#pragma __QCMP_OPTIMIZEINCLUDE
#endif//__QCMP_OPTIMIZEINCLUDE

#include "CodeQOR/DataStructures/TRef.h"
#include "WinQL/CodeServices/Handles/WinQLHandle.h"

__QOR_DECLARE_REF(nsWin32, __WINQL, CDeviceDriver, CTRef);

//--------------------------------------------------------------------------------
namespace nsWin32
{
	//--------------------------------------------------------------------------------
	class __QOR_INTERFACE( __WINQL ) CDeviceDriver
	{
	public:

		__QOR_DECLARE_REF_TYPE(CDeviceDriver);
		__QOR_DECLARE_OCLASS_ID(CDeviceDriver);

		CDeviceDriver();
		virtual ~CDeviceDriver();

	private:

		CTString m_ID;
		/*
		typedef struct {
  DWORD     cbSize;
  DWORD     DriverType;
  ULONG_PTR Reserved;
  TCHAR     Description[LINE_LEN];
  TCHAR     MfgName[LINE_LEN];
  TCHAR     ProviderName[LINE_LEN];
  FILETIME  DriverDate;
  DWORDLONG DriverVersion;
} SP_DRVINFO_DATA, *PSP_DRVINFO_DATA;
*/

/*
typedef struct _SP_DRVINFO_DETAIL_DATA {
  DWORD     cbSize;
  FILETIME  InfDate;
  DWORD     CompatIDsOffset;
  DWORD     CompatIDsLength;
  ULONG_PTR Reserved;
  TCHAR     SectionName[LINE_LEN];
  TCHAR     InfFileName[MAX_PATH];
  TCHAR     DrvDescription[LINE_LEN];
  TCHAR     HardwareID[ANYSIZE_ARRAY];
} SP_DRVINFO_DETAIL_DATA, *PSP_DRVINFO_DETAIL_DATA;

*/
	};

}//nsWin32

#endif//WINQL_DEVICEDRIVER_H_3
