//WinQLRegistry.h

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

#ifndef WINQL_SYSTEM_REGISTRY_H_3
#define WINQL_SYSTEM_REGISTRY_H_3

#ifdef	__QCMP_OPTIMIZEINCLUDE
#pragma	__QCMP_OPTIMIZEINCLUDE
#endif//__QCMP_OPTIMIZEINCLUDE

#include "CodeQOR/Macros/codingmacros.h"
#include "WinQL/CodeServices/WinQLPolicy.h"
#include "WinQL/Application/Threading/WinQLCriticalSection.h"
#include "WinQL/Definitions/Handles.h"
#include "WinQL/Definitions/Security.h"
#include "WinQL/Definitions/IO.h"
#include "WinQL/CodeServices/WinQLSharedRef.h"
#include "WinQL/System/Registry/WinQLRegistryHelper.h"

//--------------------------------------------------------------------------------
namespace nsWinQAPI
{
	class __QOR_INTERFACE( __WINQAPI ) CAdvAPI32;
}

//--------------------------------------------------------------------------------
namespace nsWin32
{
	//--------------------------------------------------------------------------------
	struct ValEnt
	{
		TCHAR*   ve_valuename;
		unsigned long ve_valuelen;
		Cmp_ulong_ptr ve_valueptr;
		unsigned long ve_type;
	};
	
	// Reserved Key Handles.
	__QCMP_STATIC_CONSTANT( KeyHandle, HKey_Classes_Root				 = (( KeyHandle ) (Cmp_ulong_ptr)((long)0x80000000) ) );
	__QCMP_STATIC_CONSTANT( KeyHandle, HKey_Current_User                 = (( KeyHandle ) (Cmp_ulong_ptr)((long)0x80000001) ) );
	__QCMP_STATIC_CONSTANT( KeyHandle, HKey_Local_Machine                = (( KeyHandle ) (Cmp_ulong_ptr)((long)0x80000002) ) );
	__QCMP_STATIC_CONSTANT( KeyHandle, HKey_Users                        = (( KeyHandle ) (Cmp_ulong_ptr)((long)0x80000003) ) );
	__QCMP_STATIC_CONSTANT( KeyHandle, HKey_Performance_Data             = (( KeyHandle ) (Cmp_ulong_ptr)((long)0x80000004) ) );
	__QCMP_STATIC_CONSTANT( KeyHandle, HKey_Performance_Text             = (( KeyHandle ) (Cmp_ulong_ptr)((long)0x80000050) ) );
	__QCMP_STATIC_CONSTANT( KeyHandle, HKey_Performance_NLSText          = (( KeyHandle ) (Cmp_ulong_ptr)((long)0x80000060) ) );
#if		(WINVER >= 0x0400)
	__QCMP_STATIC_CONSTANT( KeyHandle, HKey_Current_Config               = (( KeyHandle ) (Cmp_ulong_ptr)((long)0x80000005) ) );
	__QCMP_STATIC_CONSTANT( KeyHandle, HKey_Dyn_Data                     = (( KeyHandle ) (Cmp_ulong_ptr)((long)0x80000006) ) );
	__QCMP_STATIC_CONSTANT( KeyHandle, HKey_Current_User_Local_Settings  = (( KeyHandle ) (Cmp_ulong_ptr)((long)0x80000007) ) );
#endif//(WINVER >= 0x0400)

	//--------------------------------------------------------------------------------
	class __QOR_INTERFACE( __WINQL ) CRegKey
	{
	public:

		typedef nsCodeQOR::CTLRef< CRegKey > refType;

		// Registry Specific Access Rights.

		__QCMP_STATIC_CONSTANT( unsigned int, Query_Value				= 0x0001	);
		__QCMP_STATIC_CONSTANT( unsigned int, Set_Value					= 0x0002	);
		__QCMP_STATIC_CONSTANT( unsigned int, Create_Sub_Key			= 0x0004	);
		__QCMP_STATIC_CONSTANT( unsigned int, Enumerate_Sub_Keys		= 0x0008	);
		__QCMP_STATIC_CONSTANT( unsigned int, Notify					= 0x0010	);
		__QCMP_STATIC_CONSTANT( unsigned int, Create_Link				= 0x0020	);
		__QCMP_STATIC_CONSTANT( unsigned int, WOW64_32Key				= 0x0200	);
		__QCMP_STATIC_CONSTANT( unsigned int, WOW64_64Key				= 0x0100	);
		__QCMP_STATIC_CONSTANT( unsigned int, WOW64_Res					= 0x0300	);
		__QCMP_STATIC_CONSTANT( unsigned int, Read						= ( ( Standard_Rights_Read | Query_Value | Enumerate_Sub_Keys | Notify ) & (~Synchronize) ) );
		__QCMP_STATIC_CONSTANT( unsigned int, Write						= ( ( Standard_Rights_Write | Set_Value | Create_Sub_Key ) & (~Synchronize) ) );
		__QCMP_STATIC_CONSTANT( unsigned int, Execute					= ( ( Read ) & (~Synchronize) ) );
		__QCMP_STATIC_CONSTANT( unsigned int, All_Access				= ( ( Standard_Rights_All | Query_Value | Set_Value | Create_Sub_Key | Enumerate_Sub_Keys | Notify | Create_Link ) & (~Synchronize) ) );

		__QOR_DECLARE_OCLASS_ID( CRegKey );

		CRegKey( KeyHandle hKey );
		CRegKey( unsigned long samDesired );
		CRegKey( const TCHAR* lpMachineName, KeyHandle hKey );

		//TODO: Replace most of these with functor () operator overloads which return CKeyRefs to subkeys
		CRegKey( const CRegKey& Parent, const TCHAR* lpSubKey, bool bCreate = true );
		CRegKey( const CRegKey& Parent, const TCHAR* lpSubKey, unsigned long ulOptions, unsigned long samDesired );
		CRegKey( const CRegKey& Parent, const TCHAR* lpSubKey, unsigned long Reserved, TCHAR* lpClass, unsigned long dwOptions, unsigned long samDesired, LPSECURITY_ATTRIBUTES lpSecurityAttributes, unsigned long* lpdwDisposition );
		CRegKey( const CRegKey& Parent, const TCHAR* lpSubKey, unsigned long ulOptions, unsigned long samDesired, void* hTransaction, void* pExtendedParameter );
		CRegKey( const CRegKey& Parent, const TCHAR* lpSubKey, unsigned long Reserved, TCHAR* lpClass, unsigned long dwOptions, unsigned long samDesired, const LPSECURITY_ATTRIBUTES lpSecurityAttributes,unsigned long* lpdwDisposition, void* hTransaction, void* pExtendedParemeter );
		CRegKey( const TCHAR* lpFile, unsigned long samDesired, unsigned long dwOptions );
        CRegKey( void* hToken, unsigned long dwOptions, unsigned long samDesired );

		//--------------------------------------------------------------------------------
		refType Ref( void )
		{
			return refType( this );
		}

		virtual ~CRegKey();
        long OverridePredef( KeyHandle hNewHKey );
		long Close();
		long CopyTree( const TCHAR* lpSubKey, KeyHandle hKeyDest );
		long Delete( const TCHAR* lpSubKey, unsigned long samDesired = 0, void* hTransaction = 0 );
		long DeleteKeyValue( const TCHAR* lpSubKey, const TCHAR* lpValueName );
		long DeleteTree( const TCHAR* lpSubKey );
		long DeleteValue( const TCHAR* lpValueName );
		long DisableReflection();
		long EnableReflection();
		long EnumKey( unsigned long dwIndex, TCHAR* lpName, unsigned long cchName );
		long EnumKeyEx( unsigned long dwIndex, TCHAR* lpName, unsigned long* lpcName, TCHAR* lpClass, unsigned long* lpcClass, PFILETIME lpftLastWriteTime );
		long EnumValue( unsigned long dwIndex, TCHAR* lpValueName, unsigned long* lpcchValueName, unsigned long* lpType, unsigned char* lpData, unsigned long* lpcbData );
		long Flush( void );
		long GetValue( const TCHAR* lpSubKey, const TCHAR* lpValue, unsigned long dwFlags, unsigned long* pdwType, void* pvData, unsigned long* pcbData );
		long LoadKey( const TCHAR* lpSubKey, const TCHAR* lpFile );
		long LoadMUIString( const TCHAR* pszValue, TCHAR* pszOutBuf, unsigned long cbOutBuf, unsigned long* pcbData, unsigned long Flags, const TCHAR* pszDirectory );
		long NotifyChange( bool bWatchSubtree, unsigned long dwNotifyFilter, void* hEvent, bool fAsynchronous );
        long QueryInfo( TCHAR* lpClass, unsigned long* lpcClass, unsigned long* lpReserved, unsigned long* lpcSubKeys, 
            unsigned long* lpcMaxSubKeyLen, unsigned long* lpcMaxClassLen, unsigned long* lpcValues, unsigned long* lpcMaxValueNameLen, 
            unsigned long* lpcMaxValueLen, unsigned long* lpcbSecurityDescriptor, PFILETIME lpftLastWriteTime );
        long QueryMultipleValues( ValEnt* val_list, unsigned long num_vals, TCHAR* lpValueBuf, unsigned long* ldwTotsize );
        long QueryReflection( int* bIsReflectionDisabled );
		long QueryValue( const TCHAR* lpSubKey, TCHAR* lpValue, long* lpcbValue );
		long QueryValueEx( const TCHAR* lpValueName, unsigned long* lpType, unsigned char* lpData, unsigned long* lpcbData );
		long Replace( const TCHAR* lpSubKey, const TCHAR* lpNewFile, const TCHAR* lpOldFile );
		long Restore( const TCHAR* lpFile, unsigned long dwFlags );
		long Save( const TCHAR* lpFile, LPSECURITY_ATTRIBUTES lpSecurityAttributes, unsigned long Flags = 0 );
		long SetKeyValue( const TCHAR* lpSubKey, const TCHAR* lpValueName, unsigned long dwType, const void* lpData, unsigned long cbData );
		long SetValue( const TCHAR* lpSubKey, unsigned long dwType, const TCHAR* lpData, unsigned long cbData );
		long SetValueEx( const TCHAR* lpValueName, unsigned long dwType, const unsigned char* lpData, unsigned long cbData );
		long UnLoadKey( const TCHAR* lpSubKey );

	private:

		KeyHandle m_hKey;

		CRegKey();//no default constructor
		nsWinQAPI::CAdvAPI32& m_AdvAPI32Library;

		__QCS_DECLARE_NONCOPYABLE( CRegKey );
	};

	//--------------------------------------------------------------------------------
    class __QOR_INTERFACE( __WINQL ) CRegistry
	{
	public:

        class CProfile;
        class CPrivateProfile;

        typedef CRegKey::refType CKeyRef;        

		//--------------------------------------------------------------------------------
		class __QOR_INTERFACE( __WINQL ) CProfile
		{
		public:

			typedef nsCodeQOR::CTLRef< CProfile > refType;

			CProfile( const TCHAR* lpStrAppName );
			~CProfile();

			//--------------------------------------------------------------------------------
			refType Ref( void )
			{
				return refType( this );
			}

			unsigned int GetInt( const TCHAR* lpKeyName, int nDefault );
			unsigned long GetSection( TCHAR* lpReturnedString, unsigned long nSize );
			int WriteSection( const TCHAR* lpString );
			unsigned long GetString( const TCHAR* lpKeyName, const TCHAR* lpDefault, TCHAR* lpReturnedString, unsigned long nSize );
			int WriteString( const TCHAR* lpKeyName, const TCHAR* lpString );

		protected:

			CRegistryHelper m_Win32ProfileHelper;
            const TCHAR* m_strAppName;
		};

		typedef CProfile::refType CProfileRef;

		//--------------------------------------------------------------------------------
		class __QOR_INTERFACE( __WINQL ) CPrivateProfile : public CProfile
		{
		public:

			typedef nsCodeQOR::CTLRef< CPrivateProfile > refType;

			CPrivateProfile( const TCHAR* szFile, const TCHAR* lpAppName );
			~CPrivateProfile();

			//--------------------------------------------------------------------------------
			refType Ref( void )
			{
				return refType( this );
			}

			unsigned int GetInt( const TCHAR* lpAppName, const TCHAR* lpKeyName, int nDefault );
			unsigned long GetSection( const TCHAR* lpAppName, TCHAR* lpReturnedString, unsigned long nSize );
			int WriteSection( const TCHAR* lpAppName, const TCHAR* lpString );
			unsigned long GetSectionNames( TCHAR* lpszReturnBuffer, unsigned long nSize );
			unsigned long GetString( const TCHAR* lpAppName, const TCHAR* lpKeyName, const TCHAR* lpDefault, TCHAR* lpReturnedString, unsigned long nSize );
			int WriteString( const TCHAR* lpAppName, const TCHAR* lpKeyName, const TCHAR* lpString );
			int GetStruct( const TCHAR* lpszSection, const TCHAR* lpszKey, void* lpStruct, unsigned int uSizeStruct );
			int WriteStruct( const TCHAR* lpszSection, const TCHAR* lpszKey, void* lpStruct, unsigned int uSizeStruct );

		protected:

			const TCHAR* m_szFileName;
		};
		
		typedef CPrivateProfile::refType CPrivateProfileRef;

        CRegistry();
		~CRegistry();

		CPrivateProfileRef GetPrivateProfile( const TCHAR* szFile, const TCHAR* szApp );
        CProfileRef GetProfile( const TCHAR* strApp );
        CKeyRef LocalMachine( void );
        CKeyRef Classes( void );
        CKeyRef CurrentConfig( void );
        CKeyRef CurrentUser( void );
#if		( _WIN32_WINNT > 0x0600 )
        CKeyRef CurrentUserLocalSettings( void );
#endif//( _WIN32_WINNT > 0x0600 )
        CKeyRef PerformanceData( void );
        CKeyRef PerformanceNLSText( void );
        CKeyRef PerformanceText( void );
        CKeyRef Users( void );
	};

}//nsWin32


#endif//WINQL_SYSTEM_REGISTRY_H_3
