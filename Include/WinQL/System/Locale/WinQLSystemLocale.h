//WinQLSystemLocale.h

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

//WinQL System Locale object

#ifndef WINQL_SYSTEM_LOCALE_H_3
#define WINQL_SYSTEM_LOCALE_H_3

#include "WinQL/Application/ErrorSystem/WinQLErrorSystem.h"
#include "WinQL/CodeServices/Locale/WinQLLocale.h"
#include "WinQL/CodeServices/WinQLPolicy.h"
#include "WinQL/CodeServices/WinQLSharedRef.h"

//--------------------------------------------------------------------------------
namespace nsWin32
{
	//--------------------------------------------------------------------------------
	class __QOR_INTERFACE( __WINQL ) CSystemLocale : public CLocale
	{

		QOR_PP_WINQL_SHARED;

	public:

		__QOR_DECLARE_OCLASS_ID( CSystemLocale );

		//--------------------------------------------------------------------------------
		enum SysGeoClass 
		{
			Nation  = 16,
			Region  = 14,
		};

		CSystemLocale();
		virtual ~CSystemLocale();
		unsigned short GetDefaultLangID();
		unsigned long GetDefaultLCID();
		int GetDefaultLocaleName( CWStringRef strLocaleName );
		bool EnumLocalesEx( Locale_EnumProcEx lpLocaleEnumProcEx, unsigned long dwFlags, Cmp_long_ptr lParam, void* lpReserved );
		bool EnumLocales( Locale_EnumProc lpLocaleEnumProc, unsigned long dwFlags );
		bool EnumLanguageGroups( LanguageGroup_EnumProc pLangGroupEnumProc, unsigned long dwFlags, Cmp_long_ptr lParam );
		bool EnumGeoIDs( unsigned long GeoClass, unsigned long ParentGeoId, Geo_EnumProc lpGeoEnumProc );
		bool EnumCodePages( CodePage_EnumProc lpCodePageEnumProc, unsigned long dwFlags );
		nsWin32::CCodePage* CodePage( unsigned int uiPageIndex );
		bool LocaleChanged();
		void SetLocaleChanged();

	protected:

		nsCodeQOR::CTMap< unsigned long, nsWin32::CCodePage*, CWinQLPolicy, nsCodeQOR::mem_traits< nsCodeQOR::CTMapPair < unsigned long, nsWin32::CCodePage* > >::CTAllocator > m_MapCodePages;
		nsCodeQOR::CTArray< nsWin32::CCodePage*, CWinQLPolicy, nsCodeQOR::mem_traits< nsWin32::CCodePage* >::CTAllocator > m_apCodePages;
		nsCodeQOR::CTArray< nsWin32::CCodePage*, CWinQLPolicy, nsCodeQOR::mem_traits< nsWin32::CCodePage* >::CTAllocator > m_apGeoLocations;
		nsCodeQOR::CTArray< nsWin32::CCodePage*, CWinQLPolicy, nsCodeQOR::mem_traits< nsWin32::CCodePage* >::CTAllocator > m_apLanguageGroups;
		nsCodeQOR::CTArray< nsWin32::CCodePage*, CWinQLPolicy, nsCodeQOR::mem_traits< nsWin32::CCodePage* >::CTAllocator > m_apLocales;

	private:

		bool m_bLocaleChanged;

		static bool __QCMP_STDCALLCONVENTION EnumAllCodePagesProc (TCHAR* strCodePage);
		bool m_bCodePagesEnumerated;

		bool AddCodePage( unsigned int uiCodePage );
	};

}//nsWin32

#endif//WINQL_SYSTEM_LOCALE_H_3
