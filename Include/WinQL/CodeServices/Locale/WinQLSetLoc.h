//WinQLSetLoc.h

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

//Win32 Set Locale Data

#ifndef WINQL_CS_TXT_LC_SETLOC_H_3
#define WINQL_CS_TXT_LC_SETLOC_H_3

#include "WinQL/CodeServices/Locale/WinQLLCID.h"
#include "WinQL/CodeServices/Text/WinQLCodePage.h"

// _countof helper
#if !defined(_countof)
#	if !defined(__cplusplus)
#		define _countof( _Array ) ( sizeof( _Array ) / sizeof( _Array[ 0 ] ) )
#	else
		extern "C++"
		{
		template < typename _CountofType, size_t _SizeOfArray >
		char ( *__countof_helper( __QCMP_DECLARE_UNALIGNED _CountofType ( &_Array )[ _SizeOfArray ] ) )[ _SizeOfArray ];
#		define _countof( _Array ) sizeof( *__countof_helper( _Array ) )
		}
#	endif
#endif

//--------------------------------------------------------------------------------
namespace nsWin32
{
	//------------------------------------------------------------------------------
	struct CLC_STRINGS 
	{
		char m_szLanguage[ CLC_ID::MAX_LANG_LEN ];
		char m_szCountry[ CLC_ID::MAX_CTRY_LEN ];
		char m_szCodePage[ CLC_ID::MAX_CP_LEN ];
	};

	class CLocale;
	class CLocaleThreadData;

	//------------------------------------------------------------------------------
	class CLocaleTab
	{
	public:
		char*	szName;
		char	chAbbrev[4];
	};

	//------------------------------------------------------------------------------
	class __QOR_INTERFACE( __WINQL ) CSetLoc
	{
	public:
		
		char*	m_pchLanguage;
		char*	m_pchCountry;
		int		m_iLcidState;
		int		m_iPrimaryLen;
		bool	m_bAbbrevLanguage;
		bool	m_bAbbrevCountry;
		unsigned long	m_lcidLanguage;
		unsigned long	m_lcidCountry;
		CLC_ID	CacheId;
		unsigned int m_uiCacheCodePage;
		char	m_acCacheIn[CLC_ID::MAX_LC_LEN];
		char	m_acCacheOut[CLC_ID::MAX_LC_LEN];	
		CIsCtypeCompatible m_aLCIDC[5];

		bool GetQualifiedLocale( const CLC_STRINGS* lpInStr, CLC_ID* lpOutId, CLC_STRINGS* lpOutStr);

	protected:

		void GetLcidFromLangCountry ();
		static bool __QCMP_STDCALLCONVENTION LangCountryEnumProc(char*);

		void GetLcidFromLanguage ();
		static bool __QCMP_STDCALLCONVENTION LanguageEnumProc(char*);

		void GetLcidFromCountry ();
		static bool __QCMP_STDCALLCONVENTION CountryEnumProc(char*);

		void GetLcidFromDefault ();
		int ProcessCodePage ( char* lpCodePageStr );

		bool TestDefaultLanguage (unsigned long lcid, bool bTestPrimary );
		bool TestDefaultCountry(unsigned long);	

		static const unsigned short s_aLangIdNotDefault[];
		static CLocaleHelper s_LocaleHelper;

	private:

		//--------------------------------------------------------------------------------
		int GetPrimaryLen( char* pchLanguage )
		{
			int     len = 0;
			char    ch;

			ch = *pchLanguage++;
			while ( ( ch >= 'A' && ch <= 'Z' ) || ( ch >= 'a' && ch <= 'z' ) )
			{
				len++;
				ch = *pchLanguage++;
			}

			return len;
		}

		//--------------------------------------------------------------------------------
		static unsigned long LcidFromHexString( const char* szHexString )
		{
			char* lpHexString = const_cast< char* >( szHexString );
			signed char	ch;
			unsigned long	lcid = 0;

			while ( ch = *lpHexString++ )
			{
				if ( ch >= 'a' && ch <= 'f' )
				{
					ch += '9' + 1 - 'a';
				}
				else if ( ch >= 'A' && ch <= 'F' )
				{
					ch += '9' + 1 - 'A';
				}
				lcid = lcid * 0x10 + ch - '0';
			}

			return (unsigned long)lcid;
		}

		bool TranslateName ( const CLocaleTab* lpTable, int iHigh, const char** ppchName );

		static int _stricmp ( const char* dst, const char* src );

		//--------------------------------------------------------------------------------
		static int __ascii_stricmp ( const char* dst, const char* src )
		{
			int f, l;

			do
			{
				if ( ( ( f = (unsigned char)( *( dst++ ) ) ) >= 'A' ) && ( f <= 'Z' ) )
				{
					f -= 'A' - 'a';
				}
				if ( ( ( l = (unsigned char)( *( src++ ) ) ) >= 'A' ) && ( l <= 'Z' ) )
				{
					l -= 'A' - 'a';
				}
			}
			while ( f && ( f == l ) );

			return( f - l );
		}

		static int _stricmp_l ( const char* dst, const char* src, CLocaleThreadData* plocinfo );

		static int _strnicmp ( const char* dst, const char* src, size_t count );
		static int __ascii_strnicmp ( const char* first, const char* last, size_t count );
		static int _strnicmp_l ( const char* dst, const char* src, size_t count, CLocaleThreadData* plocinfo );
		static int _tolower_l ( int c, CLocaleThreadData* plocinfo );
	public:
		static int __crtLCMapStringA( CLocaleThreadData* plocinfo, unsigned long Locale, unsigned long dwMapFlags, const char* lpSrcStr, int cchSrc, CAStringRef lpDestStr, CCodePage& code_page, int bError );
		static int __crtLCMapStringA_stat( CLocaleThreadData* plocinfo, unsigned long Locale, unsigned long dwMapFlags, const char* lpSrcStr, int cchSrc, CAStringRef lpDestStr, CCodePage& code_page, int bError );
		static int _chvalidchk_l( int _Char, int _Flag, CLocaleThreadData* _Locale );
		static int _ischartype_l( int c, int _Flag, CLocaleThreadData* _Locale );
		static int _isleadbyte_l ( int c, CLocaleThreadData* plocinfo );
		static int __ansicp( int lcid );
		static int _isctype_l ( int c, int mask, CLocaleThreadData* plocinfo );		
		static bool __crtGetStringTypeA_stat( CLocaleThreadData* plocinfo, unsigned long dwInfoType, const char* lpSrcStr, int cchSrc, unsigned short* lpCharType, CCodePage& code_page, int lcid, int bError );
		static bool __crtGetStringTypeW_stat( CLocaleThreadData* plocinfo, unsigned long dwInfoType, const wchar_t* lpSrcStr, int cchSrc, unsigned short* lpCharType, CCodePage& code_page, int lcid );
		static int __crtLCMapStringW_stat( CLocaleThreadData* plocinfo, unsigned long Locale, unsigned long dwMapFlags, const wchar_t* lpSrcStr, int cchSrc, CWStringRef lpDestStr, CCodePage& code_page );
		static int _chvalidator( int c, int mask );
		static int _chvalidator_l( CLocaleThreadData* plocinfo, int c, int mask );
	
		static bool __crtGetStringTypeA( CLocaleThreadData* plocinfo, unsigned long dwInfoType, const char* lpSrcStr, int cchSrc, unsigned short* lpCharType, CCodePage& code_page, int lcid, int bError );
		static bool __crtGetStringTypeW( CLocaleThreadData* plocinfo, unsigned long dwInfoType, const wchar_t* lpSrcStr, int cchSrc, unsigned short* lpCharType, CCodePage& code_page, int lcid );
		static int __crtLCMapStringW( CLocaleThreadData* plocinfo, unsigned long Locale, unsigned long dwMapFlags, const wchar_t* lpSrcStr, int cchSrc, CWStringRef lpDestStr, CCodePage& code_page );
		static int _itoa_s ( int val, char* buf, size_t sizeInChars, int radix );
		static int xtox_s( unsigned long val, char* buf, size_t sizeInChars, unsigned radix, int is_neg );
		static int wcsncnt ( const wchar_t* string, int cnt );

	};

}//nsWin32

#endif//WINQL_CS_TXT_LC_SETLOC_H_3
