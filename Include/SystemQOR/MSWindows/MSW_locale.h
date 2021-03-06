//MSW_locale.h

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

//MSWindows overrides for locale

#ifndef SYSTEMQOR_MSW_LOCALE_H_3
#define SYSTEMQOR_MSW_LOCALE_H_3

#include "SystemQOR/Posix/Baselocale.h"
#include "WinQL/WinQL.h"
#include "WinQL/Application/Threading/WinQLCriticalSection.h"
#include "WinQL/CodeServices/Locale/WinQLSetLoc.h"
#include "WinQL/CodeServices/Locale/WinQLThreadLocaleInfo.h"

//--------------------------------------------------------------------------------
namespace nsWin32
{
	//--------------------------------------------------------------------------------
	class __QOR_INTERFACE( __QSYS ) Clocale : public nsBaseCRT::Clocale
	{
	public:

		__QCMP_STATIC_CONSTANT( unsigned int, CodePage_Ansi = 0 );
		__QCMP_STATIC_CONSTANT( unsigned int, Sort_Default = 0 );

		Clocale();
		virtual ~Clocale();

		virtual locale_t duplocale( locale_t l );
		virtual void freelocale( locale_t l );
		virtual lconv* localeconv(void);
		virtual locale_t newlocale( int, const char*, locale_t );
		virtual char* setlocale( int category, const char* locale );
		virtual locale_t uselocale( locale_t l );
		virtual lconv* localeconv_l( locale_t l );
		
		void crtInit( void );
		void crtCleanup( void );

	private:

		static const char _first_127char[];
		nsWin32::CCriticalSection m_SetLocaleSection;
		
		nsWin32::CThreadLocaleInfo* __updatetlocinfo(void);
		char* _setlocale_nolock( nsWin32::CThreadLocaleInfo* ploci, int _category, const char* _locale );
		nsWin32::CThreadLocaleInfo* _updatetlocinfoEx_nolock( nsWin32::CThreadLocaleInfo** pptlocid, nsWin32::CThreadLocaleInfo* ptlocis );
		char* _setlocale_set_cat( nsWin32::CThreadLocaleInfo* ploci, int category, const char* locale );
		char* _expandlocale ( char* expr, char* output, size_t sizeInChars, LC_ID* id, unsigned int* cp, int category );
		int __lc_strtolc ( nsWin32::CLC_STRINGS* names, const char* locale );
		void __lc_lctostr( char* locale, size_t sizeInBytes, const nsWin32::CLC_STRINGS* names );
		void _strcats( char* outstr, size_t sizeInBytes, int n, ... );		
		
		Clocale( const Clocale& );
		Clocale& operator = ( const Clocale& );
	};

}//nsWin32


#endif//SYSTEMQOR_MSW_LOCALE_H_3

