//MSVC6.h

// Copyright Querysoft Limited 2015
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

//Header for MSVC 6 Compiler

#ifndef QCMP_MSVC6_H_1
#define QCMP_MSVC6_H_1

#include "../MSVC.h"

//--------------------------------------------------------------------------------
//turn off daft warnings globally

#if (_MSC_VER < 1300 ) // 1200 == VC++ 6.0, 1200-1202 == eVC++4
#	pragma warning( disable : 4786 ) // ident trunc to '255' chars in debug info
#endif
#pragma warning( disable : 4514 ) // should be off by default but sometimes shows up
#ifndef NDEBUG
#	pragma warning( disable : 4100 ) //silence this one while we're developing
#	pragma warning( disable : 4002 ) //Preprocessor library spews this all the time, no fix so suppress it
#	pragma warning( disable : 4003 ) //Preprocessor library spews this all the time, no fix so suppress it
#	pragma warning( disable : 4661 ) //MSVC constantly complains 'no suitable definition provided for explicit template instantiation request' but it doesn't seem to affect its ability to generate correct code
#endif//NDEBUG

#define __QCMP_OPTIMIZEINCLUDE

//--------------------------------------------------------------------------------
//compilation messages

#if ( __QCMP_REPORTCONIG == __QCS_YES_ )
#	define __QCMP_MESSAGE( _X )				//macro pragmas are not suported so we cannot have general messages from non MSVC specific code
#	define __QCMP_VC6_MESSAGE( _X )		message( _X )//We can however support messages in code that will only ever be seen by MSVC6 and derivative compilers
#else
#	define __QCMP_MESSAGE( _X )
#	define __QCMP_VC6_MESSAGE( _X )		comment( user, "" )
#endif

//--------------------------------------------------------------------------------
#ifdef UNICODE
#	define _QCMP_TXT( _X ) L##_X
#	pragma __QCMP_VC6_MESSAGE( "MSVC Targetting UNICODE platform." )
#else
#	define _QCMP_TXT( _X ) _X
#	pragma __QCMP_VC6_MESSAGE( "MSVC Targetting ASCII platform." )
#endif

//--------------------------------------------------------------------------------
#if		( __QCMP_REPORTDEFECITS == __QCS_YES_ )
#	if		( __QOR_PERFORMANCE == __QCS_MAX_PERFORMANCE_ )
#		define TODO(_Message) comment( user, "Incomplete code" )
#	else//!( __QOR_PERFORMANCE == __QCS_MAX_PERFORMANCE_ )
#		define TODO(_Message) message( __FILE__ "(" __QCMP_STRINGIZEA(__LINE__) "): TODO: " ##_Message)
#	endif//( __QOR_PERFORMANCE == __QCS_MAX_PERFORMANCE_ )
#else//!( __QCMP_REPORTDEFECITS == __QCS_YES_ )
#	define TODO(_Message)
#endif//( __QCMP_REPORTDEFECITS == __QCS_YES_ )

//--------------------------------------------------------------------------------
//Without macro pragmas we can't cleanly manage warnings throughout the codebase
#if		( __QOR_PERFORMANCE == __QCS_MAX_SAFETY_ )
#   define __QCMP_WARNING_PUSH 
#	define __QCMP_WARNING_DISABLE(_X, _Reason )
#else//!( __QOR_PERFORMANCE == __QCS_MAX_SAFETY_ )
#   define __QCMP_WARNING_PUSH 
#	define __QCMP_WARNING_DISABLE(_X, _Reason ) 
#endif//( __QOR_PERFORMANCE == __QCS_MAX_SAFETY_ )
#define __QCMP_WARNING_POP 
#define __QCMP_WARNING_ENABLE(_X) 

#define QOR_COMP_SUPPORTED_ARCHITECTURES (QOR_ARCH_ALPHA)(QOR_ARCH_IA64)(QOR_ARCH_MIPS)\
(QOR_ARCH_PPC)(QOR_ARCH_X86_32)

//--------------------------------------------------------------------------------
//report basic configuration
#ifdef _M_ALPHA
#	pragma __QCMP_VC6_MESSAGE( "MSVC Targetting Alpha platform." )
#elif defined _M_MPPC
#	pragma __QCMP_VC6_MESSAGE( "MSVC Targetting Power Macintosh platform." )
#elif defined _M_MRX000
#	pragma __QCMP_VC6_MESSAGE( "MSVC Targetting MIPS platform." )
#elif defined _M_MRX000
#	pragma __QCMP_VC6_MESSAGE( "MSVC Targetting Power PC platform." )
#elif ( defined _M_AMD64 || defined _M_X64 )
#	pragma __QCMP_VC6_MESSAGE( "MSVC Targetting x64 platform." )
//#	define _WIN64
#elif defined _M_IA64
#	pragma __QCMP_VC6_MESSAGE( "MSVC Targetting Itanium IA64 platform." )
#else
#	pragma __QCMP_VC6_MESSAGE( "MSVC Targetting x86 platform." )
#endif

//--------------------------------------------------------------------------------
//predefined macro support
#define __QCMP_SUPPORTS__FUNCSIG__	1
#define __QCMP_FUNCSIG__( _X ) __FUNCSIG__

//--------------------------------------------------------------------------------
//extensions
#define Unicode_Const_Str_Conversion_QCMPSUPPORTED		1	//MSVC 6 has L## builtin macro
#define Structured_Exceptions_QCMPSUPPORTED				1	//SEH support
#define SizeSuffixes_QCMPSUPPORTED						1
#define MIBSizedInts_QCMPSUPPORTED						1	//Has Microsoft/Intel/Borland style sized integers e.g. __int16
#ifdef _CPPUNWIND
#	define Exceptions_QCMPSUPPORTED						1	//C++ exception support		
#endif
#ifdef _CPPRTTI 
#	define RunTimeTypeInformation_QCMPSUPPORTED			1	//RTTI supported
#	pragma __QCMP_VC6_MESSAGE( "Compiler runtime type information enabled." )
#endif
#ifdef _MT
#	define MultiThreadingCompilerAssistance_QCMPSUPPORTED	1
#	pragma __QCMP_VC6_MESSAGE( "Compiler multiple threading support enabled." )
#endif

//--------------------------------------------------------------------------------
//type suffixes
#define	__QCMP_LONG_SUFFIX( _X )			_X##l
#define	__QCMP_UNSIGNED_SUFFIX( _X )		_X##u
#define	__QCMP_UNSIGNEDLONG_SUFFIX( _X )	_X##ul
#define	__QCMP_LONGLONG_SUFFIX( _X )		_X##ll
#define	__QCMP_FLOAT_SUFFIX( _X )			_X##f
#define __QCMP_i64_SUFFIX( _X )				_X##i64
#define __QCMP_ui64_SUFFIX( _X )			_X##ui64

//--------------------------------------------------------------------------------
//emulation of missing fundamental types
#if ( !__QCMP_SUPPORTS( __QCMP_FEATURE_NATIVEWCHARTSUPPORT ) )
	typedef unsigned short	wchar_t;
#endif

//--------------------------------------------------------------------------------
//assignment at declaration support
#define __QCMP_STATIC_CONSTANT( type, assignment ) enum { assignment }

//--------------------------------------------------------------------------------
//warnings

#define __QCMP_WARN_MACRO_REDEFINITION					4005
#define __QCMP_WARN_COND_EXPR_IS_CONST					4127
#define __QCMP_WARN_UNARY_MINUS_APPLIED_TO_UNSIGNED		4146
#define __QCMP_WARN_EXTENSION_USED_ZERO_SIZED_ARRAY		4200
#define __QCMP_WARN_NAMELESS_STRUCTUNION				4201
#define __QCMP_WARN_EXTENSION_EXTERN_TEMPLATE_INSTANCE	4231
#define __QCMP_WARN_CONV_FROM_LONG_DOUBLE_TO_DOUBLE		4244
#define __QCMP_WARN_CLASS_NEEDS_TO_HAVE_DLL_INTERFACE	4251
#define __QCMP_WARN_NON_EXPORTED_BASE_FOR_EXPORT		4275
#define __QCMP_WARN_EXCEPTION_SPEC_IGNORED				4290
#define __QCMP_WARN_TRUNCATION_FROM_DOUBLE_TO_FLOAT		4305
#define __QCMP_WARN_STRUCTURE_PADDED_DUE_TO_ALIGN		4324
#define __QCMP_WARN_THIS_USED_IN_BASE_INIT_LIST			4355
#define __QCMP_WARN_NO_DEFINITION_FOR_TEMPLATE_INST_REQ	4661
#define __QCMP_WARN_UNREF_LOCAL_FUNCTION				4505
#define __QCMP_WARN_UNINIT_LOCAL_VAR_USED				4700
#define __QCMP_WARN_ASSIGNMENT_WITHIN_COND_EXPR			4706



#if ! (defined(lint) || defined(RC_INVOKED))
#	if ( _MSC_VER >= 800 && !defined(_M_I86)) || defined(_PUSHPOP_SUPPORTED)
#		pragma warning(disable:4103)
#		if !(defined( MIDL_PASS )) || defined( __midl )
#			define __QCMP_PACK( _N ) pack(push,_N)
#			define __QCMP_END_PACK pack(pop)
#		else
#			define __QCMP_PACK( _N ) pack(_N)
#			define __QCMP_END_PACK pack()
#		endif
#	else
#		define __QCMP_END_PACK pack()
#	endif
#endif /* ! (defined(lint) || defined(RC_INVOKED)) */


//--------------------------------------------------------------------------------
//Linkage modes
#ifdef __cplusplus
#	define __QCMP_LINKAGE_C					extern "C"
#	define __QCMP_STARTLINKAGE_C			extern "C" {
#	define __QCMP_ENDLINKAGE_C				}
#	define __QCMP_LINKAGE_CPP				extern "C++"
#	define __QCMP_STARTLINKAGE_CPP			extern "C++" {
#	define __QCMP_ENDLINKAGE_CPP			}
#else
#	define __QCMP_LINKAGE_C					extern
#	define __QCMP_STARTLINKAGE_C
#	define __QCMP_ENDLINKAGE_C
#endif//__cplusplus

//--------------------------------------------------------------------------------
//Calling conventions
#define __QCMP_CALLCON						__cdecl
#define __QCMP_STDCALLCONVENTION			__stdcall
#define __QCMP_THISCALL						//explicit __thiscall not supported? not sure why you'd need it anyway?
#define __QCMP_FASTCALL						__fastcall


//--------------------------------------------------------------------------------
//Attributes
#define __QCMP_ALWAYSINLINE					__forceinline
#define __QCMP_DECLARE_PERTHREAD			__declspec(thread)
#define __QCMP_DECLARE_NAKED				__declspec(naked)
#define __QCMP_DECLARE_NOTHROW				__declspec(nothrow)
#define __QCMP_DECLARE_MERGE_INITIALIZERS	__declspec(selectany)
#define __QCMP_DECLARE_NORETURN				__declspec(noreturn)
#define __QCMP_DECLARE_TYPE_GUID(_UID)		__declspec(uuid(_UID))
#define __QCMP_DECLARE_PROPERTY(_GET, _PUT)	__declspec( property( get=_GET, put=_PUT ) )
#define __QCMP_DECLARE_ALIGNED( _ALIGNMENT ) __declspec( align( _ALIGNMENT ) )
#define __QCMP_RESTRICT						//not supported
#define __QCMP_NORETURN						//not supported
#define deprecated( _X )					//not supported
#define __QCMP_DECLARE_DEPRECATED			//not supported
#define __QCMP_ALIGNOF						__alignof
#define __QCMP_ALIGNAS(x)					__declspec(align(__alignof(x)))
#define __QCMP_DATA_SEGMENT(_X)				data_seg(_X) //for pragma data_seg() declarations
#define __QCMP_DEFAULT_DATA_SEGMENT			data_seg()
#define __attribute__(__ATTRIB__)			//not supported
#ifndef DECLSPEC_NORETURN
#	define DECLSPEC_NORETURN				__QCMP_DECLARE_NORETURN//Enable MinGW32 Win32 headers to declare noreturn
#endif//DECLSPEC_NORETURN
#define	__extension__						//not supported
#ifdef __QCMP_ITANIUM
#	define __QCMP_DECLARE_UNALIGNED			__unaligned
#else
#	define __QCMP_DECLARE_UNALIGNED
#endif

#define __QCMP_TEMPLATE_INST

//--------------------------------------------------------------------------------
//Module Interface declarations
#define __QCMP_EXPORT						__declspec(dllexport)	//declare an item as exported from the module
#define __QCMP_IMPORT						__declspec(dllimport) //declare an item as imported from another module
#define __QCMP_LOCAL						//declare an item as being local to a module

//--------------------------------------------------------------------------------
//exception specifications
#define __QCMP_THROW0()		
#define __QCMP_THROW1(x1)	
#define __QCMP_THROW throw()
#define __QCMP_NO_THROW throw()
#ifndef __THROW
#	define __THROW
#endif
#ifndef __NTH
#	define __NTH(fct) fct __THROW
#endif

//--------------------------------------------------------------------------------
//const qualifiers
#ifndef __const__
#	define __const__ const
#endif

#ifndef __const
#	define __const const
#endif
	
/*
//--------------------------------------------------------------------------------
//builtins and intrinsics

//Define the files to look in for built in compiler functions
//that is intrinsics which are always available regardless of architecture
#define __QCMP_BUILTINS_HEADER "CompilerQOR/MSVC/VC6/Builtins.h"
#define __QCMP_UNBUILTINS_HEADER "CompilerQOR/MSVC/VC6/UnBuiltins.h" //needed to undeclare functions as intrinsic
#define __QCMP_BUILTINS_INC "CompilerQOR/MSVC/VC6/Builtins.inl"

//define where to find the intrinsics for this compiler so they can be included once we know what architecture we're compiling for
#define __QCMP_INTRINSICS_HEADER "CompilerQOR/MSVC/VC6/Intrinsics.h"
#define __QCMP_INTRINSICS_INC "CompilerQOR/MSVC/VC6/Intrinsics.inl"
*/
//--------------------------------------------------------------------------------
namespace nsCompiler
{
	//--------------------------------------------------------------------------------
	namespace EH
	{
		struct UnwindMapEntry;
		struct TryBlockMapEntry;
	}//EH

	//--------------------------------------------------------------------------------
	class __QOR_INTERFACE( __QCMP ) CMSVCCompiler6
	{
	public:

		CMSVCCompiler6(){};
		virtual ~CMSVCCompiler6(){};

		//Name the supported basic types with single tokens

		typedef void					mxc_void;
		typedef const void				mxc_c_void;
		typedef volatile void			mxc_v_void;
		typedef bool					mxc_bool;
		typedef const bool				mxc_c_bool;
		typedef volatile bool			mxc_v_bool;
		typedef char					mxc_char;
		typedef const char				mxc_c_char;
		typedef volatile char			mxc_v_char;
		typedef short					mxc_short;
		typedef const short				mxc_c_short;
		typedef volatile short			mxc_v_short;
		typedef int						mxc_int;
		typedef const int				mxc_c_int;
		typedef volatile int			mxc_v_int;
		typedef long					mxc_long;
		typedef const long				mxc_c_long;
		typedef volatile long			mxc_v_long;
		typedef float					mxc_float;
		typedef const float				mxc_c_float;
		typedef volatile float			mxc_v_float;
		typedef	double					mxc_double;
		typedef	const double			mxc_c_double;
		typedef	volatile double			mxc_v_double;
		typedef signed char				mxc_signed_char;
		typedef const signed char		mxc_c_signed_char;
		typedef volatile signed char	mxc_v_signed_char;
		typedef unsigned char			mxc_unsigned_char;
		typedef const unsigned char		mxc_c_unsigned_char;
		typedef volatile unsigned char	mxc_v_unsigned_char;
		typedef short					mxc_signed_short;
		typedef const short				mxc_c_signed_short;
		typedef volatile short			mxc_v_signed_short;
		typedef unsigned short			mxc_unsigned_short;
		typedef const unsigned short	mxc_c_unsigned_short;
		typedef volatile unsigned short	mxc_v_unsigned_short;
		typedef int						mxc_signed_int;
		typedef const int				mxc_c_signed_int;
		typedef volatile int			mxc_v_signed_int;
		typedef unsigned int			mxc_unsigned_int;
		typedef const unsigned int		mxc_c_unsigned_int;
		typedef volatile unsigned int	mxc_v_unsigned_int;
		typedef long					mxc_signed_long;
		typedef const long				mxc_c_signed_long;
		typedef volatile long			mxc_v_signed_long;
		typedef unsigned long			mxc_unsigned_long;
		typedef const unsigned long		mxc_c_unsigned_long;
		typedef volatile unsigned long	mxc_v_unsigned_long;
		typedef long double				mxc_long_double;
		typedef const long double		mxc_c_long_double;
		typedef volatile long double	mxc_v_long_double;

		//Fake long long type where long long is not supported
		typedef __int64						mxc_long_long;
		typedef const __int64				mxc_c_long_long;
		typedef volatile __int64			mxc_v_long_long;
		typedef unsigned __int64			mxc_unsigned_long_long;
		typedef const unsigned __int64		mxc_c_unsigned_long_long;
		typedef volatile unsigned __int64	mxc_v_unsigned_long_long;

#if ( __QCMP_SUPPORTS( __QCMP_FEATURE_NATIVEWCHARTSUPPORT ) )
		typedef wchar_t						mxc_wchar_t;
		typedef const wchar_t				mxc_c_wchar_t;
		typedef volatile wchar_t			mxc_v_wchar_t;
#	else			
		typedef mxc_unsigned_short			mxc_wchar_t;
		typedef mxc_c_unsigned_short		mxc_c_wchar_t;
		typedef mxc_v_unsigned_short		mxc_v_wchar_t;
#	endif

		typedef unsigned __int8				mxc_unsigned__int8;
		typedef const unsigned __int8		mxc_c_unsigned__int8;
		typedef volatile unsigned __int8	mxc_v_unsigned__int8;
		typedef unsigned __int16			mxc_unsigned__int16;
		typedef const unsigned __int16		mxc_c_unsigned__int16;
		typedef volatile unsigned __int16	mxc_v_unsigned__int16;
		typedef unsigned __int32			mxc_unsigned__int32;
		typedef const unsigned __int32		mxc_c_unsigned__int32;
		typedef volatile unsigned __int32	mxc_v_unsigned__int32;
		typedef unsigned __int64			mxc_unsigned__int64;
		typedef const unsigned __int64		mxc_c_unsigned__int64;
		typedef volatile unsigned __int64	mxc_v_unsigned__int64;
		typedef signed __int8				mxc_signed__int8;
		typedef const signed __int8			mxc_c_signed__int8;
		typedef volatile signed __int8		mxc_v_signed__int8;
		typedef signed __int16				mxc_signed__int16;
		typedef const signed __int16		mxc_c_signed__int16;
		typedef volatile signed __int16		mxc_v_signed__int16;
		typedef signed __int32				mxc_signed__int32;
		typedef const signed __int32		mxc_c_signed__int32;
		typedef volatile signed __int32		mxc_v_signed__int32;
		typedef signed __int64				mxc_signed__int64;
		typedef const signed __int64		mxc_c_signed__int64;
		typedef volatile signed __int64		mxc_v_signed__int64;
		typedef __int8						mxc__int8;
		typedef const __int8				mxc_c__int8;
		typedef volatile __int8				mxc_v__int8;
		typedef __int16						mxc__int16;
		typedef const __int16				mxc_c__int16;
		typedef volatile __int16			mxc_v__int16;
		typedef __int32						mxc__int32;
		typedef const __int32				mxc_c__int32;
		typedef volatile __int32			mxc_v__int32;
		typedef __int64						mxc__int64;
		typedef const __int64				mxc_c__int64;
		typedef volatile __int64			mxc_v__int64;
		typedef mxc_int						mxc_int_ptr, *pmxc_int_ptr;
		typedef mxc_unsigned_int			mxc_uint_ptr, *pmxc_uint_ptr;
		typedef mxc_long					mxc_long_ptr, *pmxc_long_ptr;
		typedef mxc_unsigned_long			mxc_ulong_ptr, *pmxc_ulong_ptr;
		typedef mxc__int32					mxc__int3264;
		
		//--------------------------------------------------------------------------------
		struct FuncInfo
		{
			unsigned int magicNumber;
			int maxState;
			const EH::UnwindMapEntry* pUnwindMap;
			unsigned int nTryBlocks;
			const EH::TryBlockMapEntry* pTryBlockMap;
			unsigned int nIPMapEntries;
			void* pIPtoStateMap;
		};

		__QCMP_STATIC_CONSTANT( unsigned int, EH_MAGIC					= 0x19930520 );		//Magic number for exception supprt
		__QCMP_STATIC_CONSTANT( unsigned int, VTABLE_FUNCTION_BASE		= 0 );				//vtable decoding constants
		__QCMP_STATIC_CONSTANT( unsigned int, VTABLE_FUNCTION_STRIDE	= 1 );

		//--------------------------------------------------------------------------------
		//Compiler compatible non-virtual function address lookup
		template< typename TGenFuncPtrType, typename TActualFP >
		static TGenFuncPtrType GetNonVirtualMemberFunctionAddress( TActualFP fp )
		{
			union 
			{
				struct 
				{
					TGenFuncPtrType p;
				} mfp_structure;
				TActualFP fp;
			} conv;

			conv.fp = fp;
			return conv.mfp_structure.p;
		}

		//--------------------------------------------------------------------------------
		template< int s > static bool is_virtual_func( unsigned char* func ) 
		{
			if (*func == 0xE9)
			{
				return is_virtual_func< 0 >( func + 5 + *(unsigned int*)( func + 1 ) );
			}
			else
			{
				switch( *(unsigned int*)func )
				{ // mov ecx, this; jump [eax + v/Ib/Iw]
				case 0x20ff018b:
				case 0x60ff018b:
				case 0xA0ff018b: return true;
				default: return false;
				}
			}
		}

		//--------------------------------------------------------------------------------
		template< typename T > static bool is_virtual( T t )
		{
			union 
			{
				T t;
				unsigned long value;
			} conv;
			conv.t = t;
			return is_virtual_func< 0 >( (unsigned char*)conv.value );
		}

		//CSupportFuncs* m_pSupportFuncs;

		//--------------------------------------------------------------------------------
		void Init()
		{
			//m_pSupportFuncs = new CSupportFuncs();
		}
	};

}//nsCompiler

__QCMP_LINKAGE_C __QOR_INTERFACE( __QCMP ) void __QCMP_CALLCON _chkesp(void);

#endif//QCMP_MSVC6_H_1
