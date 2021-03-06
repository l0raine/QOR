//SystemQOR.pp

// Copyright Querysoft Limited 2016
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

//Preprocessor build script generator for SystemQOR.dll

#include "ModuleHeader.pph"

//Set SystemQOR specific definitions and overrides

#define QOR_MODULE_NAME SystemQOR

//Append the module specific PP defines to the list from the Operating System
#define QOR_CONFIG_DEFINES_SYSTEMQOR1 QOR_PP_LIST_APPEND( QOR_CONFIG_DEFINES_OS,("__QSYS") )
#define QOR_CONFIG_DEFINES_SYSTEMQOR2 QOR_PP_LIST_APPEND( QOR_CONFIG_DEFINES_SYSTEMQOR1,("_LIBCPP_DLL") )
#define QOR_CONFIG_DEFINES_MODULE QOR_CONFIG_DEFINES_SYSTEMQOR2


#define QOR_CONFIG_INCLUDES (../../../include)\
(D:\Tools\Microsoft Visual Studio 14.0\VC\include)\
(D:\Tools\Microsoft Visual Studio 14.0\VC\atlmfc\include)\
(C:\Program Files (x86)\Windows Kits\10\Include\10.0.10240.0\ucrt)\
(C:\Program Files (x86)\Windows Kits\8.1\Include\um)\
(C:\Program Files (x86)\Windows Kits\8.1\Include\shared)\
(C:\Program Files (x86)\Windows Kits\8.1\Include\winrt)

#define QOR_PP_BUILD_CMP_IGNORE_STANDARD_INC_SELECT 1
#define QOR_PP_BUILD_CMP_CPP_EXCEPTIONS_SELECT 1
#define QOR_PP_BUILD_CMP_BUFFER_SECURITY_SELECT 1
#define QOR_PP_BUILD_CMP_RUNTIME_CHECKS_SELECT 4

//Include this to do any setup needed for a build such as creating folders
#include "BuildQOR/BeginBuild.pph"

//For each group of files that have the same folder and build options, define a group of sources

#define SOURCE_PATH ../../../Source/SystemQOR/Common/
#define SOURCES (ExePageAllocator)\
				(SharedBootStrap)\
				(System)\
				(SystemQOR)
#include "BuildQOR/BuildGroup.pph"

#define SOURCE_PATH ../../../Source/SystemQOR/Posix/
#define SOURCES (Baseaio)\
				(Baseassert)\
				(Basecomplex)\
				(Basecpio)\
				(BaseCRT)\
				(Basectype)\
				(Basedirent)\
				(Basedlfcn)\
				(Baseerrno)\
				(Basefcntl)\
				(Basefenv)\
				(Basefmtmsg)\
				(Basefnmatch)\
				(Baseftw)\
				(Baseglob)\
				(Basegrp)\
				(Baseiconv)\
				(Baseinttypes)\
				(Baseiso646)\
				(Baselanginfo)\
				(Baselibgen)\
				(Baselimits)\
				(Baselocale)\
				(Basemath)\
				(Basemonetary)\
				(Basemqueue)\
				(Basendbm)\
				(Basenetdb)\
				(Basenl_types)\
				(Basepoll)\
				(Basepthread)\
				(Basepwd)\
				(Baseregex)\
				(Basesched)\
				(Basesearch)\
				(Basesemaphore)\
				(Basesetjmp)\
				(Basesignal)\
				(Basespawn)\
				(Basestdarg)\
				(Basestdbool)\
				(Basestddef)\
				(Basestdint)\
				(Basestdio)\
				(Basestdlib)\
				(Basestring)\
				(Basestrings)\
				(Basestropts)\
				(Basesyslog)\
				(Basetar)\
				(Basetermios)\
				(Basetgmath)\
				(Basetime)\
				(Basetrace)\
				(Baseucontext)\
				(Baseulimit)\
				(Baseunistd)\
				(Baseutime)\
				(Baseutmpx)\
				(Basewchar)\
				(Basewctype)\
				(Basewordexp)
#include "BuildQOR/BuildGroup.pph"

#define SOURCE_PATH ../../../Source/SystemQOR/Posix/arpa/
#define SOURCES (Baseinet)
#include "BuildQOR/BuildGroup.pph"

#define SOURCE_PATH ../../../Source/SystemQOR/Posix/math/
#define SOURCES (acos)\
				(acosh)\
				(asin)\
				(asinh)\
				(atan)\
				(atan2)\
				(atanh)\
				(cabs)\
				(cbrt)\
				(ceil)\
				(copysign)\
				(cos)\
				(cosh)\
				(drem)\
				(erf)\
				(exp)\
				(exp2)\
				(expm1)\
				(fabs)\
				(fdim)\
				(finite)\
				(floor)\
				(fma)\
				(fmax)\
				(fmin)\
				(fmod)\
				(fpclassify)\
				(frexp)\
				(gamma)\
				(hypot)\
				(ilogb)\
				(infinity)\
				(isinf)\
				(isinfd)\
				(isnan)\
				(isnand)\
				(j0)\
				(j1)\
				(jn)\
				(ldexp)\
				(lgamma)\
				(lib_ver)\
				(log)\
				(log10)\
				(log1p)\
				(logb)\
				(lrint)\
				(lround)\
				(matherr)\
				(modf)\
				(nan)\
				(nearbyint)\
				(nextafter)\
				(pow)\
				(remainder)\
				(remquo)\
				(rem_pio2)\
				(rint)\
				(round)\
				(scalb)\
				(scalbln)\
				(scalbn)\
				(signbit)\
				(signif)\
				(sin)\
				(sincos)\
				(sinh)\
				(sqrt)\
				(standard)\
				(tan)\
				(tanh)\
				(tgamma)\
				(trunc)
#include "BuildQOR/BuildGroup.pph"

#define SOURCE_PATH ../../../Source/SystemQOR/Posix/net/
#define SOURCES (Baseif)
#include "BuildQOR/BuildGroup.pph"

#define SOURCE_PATH ../../../Source/SystemQOR/Posix/netinet/
#define SOURCES (Basein)\
				(Basetcp)
#include "BuildQOR/BuildGroup.pph"

#define SOURCE_PATH ../../../Source/SystemQOR/Posix/sys/
#define SOURCES (Baseipc)\
				(Basemman)\
				(Basemsg)\
				(Baseresource)\
				(Baseselect)\
				(Basesem)\
				(Baseshm)\
				(Basesocket)\
				(Basestat)\
				(Basestatvfs)\
				(Basesystime)\
				(Basetimeb)\
				(Basetimes)\
				(Basetypes)\
				(Baseuio)\
				(Baseun)\
				(Baseutsname)\
				(Basewait)
#include "BuildQOR/BuildGroup.pph"


#if( QOR_SYS_OS == QOR_SYS_MSW )

#	define SOURCE_PATH ../../../Source/SystemQOR/MSwindows/
#	define SOURCES	(MSW_aio)\
					(MSW_complex)\
					(MSW_CRT0)\
					(MSW_ctype)\
					(MSW_dirent)\
					(MSW_dlfcn)\
					(MSW_errno)\
					(MSW_fcntl)\
					(MSW_fenv)\
					(MSW_fmtmsg)\
					(MSW_fnmatch)\
					(MSW_ftw)\
					(MSW_glob)\
					(MSW_grp)\
					(MSW_iconv)\
					(MSW_inttypes)\
					(MSW_langinfo)\
					(MSW_libgen)\
					(MSW_limits)\
					(MSW_locale)\
					(MSW_math)\
					(MSW_monetary)\
					(MSW_mqueue)\
					(MSW_ndbm)\
					(MSW_netdb)\
					(MSW_nl_types)\
					(MSW_poll)\
					(MSW_pthread)\
					(MSW_pwd)\
					(MSW_PX_sched)\
					(MSW_regex)\
					(MSW_search)\
					(MSW_semaphore)\
					(MSW_setjmp)\
					(MSW_signal)\
					(MSW_spawn)\
					(MSW_stdio)\
					(MSW_stdlib)\
					(MSW_string)\
					(MSW_strings)\
					(MSW_stropts)\
					(MSW_syslog)\
					(MSW_termios)\
					(MSW_time)\
					(MSW_trace)\
					(MSW_ucontext)\
					(MSW_ulimit)\
					(MSW_unistd)\
					(MSW_utime)\
					(MSW_utmpx)\
					(MSW_wchar)\
					(MSW_wctype)\
					(MSW_wordexp)
#	include "BuildQOR/BuildGroup.pph"

#	define SOURCE_PATH ../../../Source/SystemQOR/MSwindows/arpa/
#	define SOURCES	(MSW_inet)
#	include "BuildQOR/BuildGroup.pph"

#	define SOURCE_PATH ../../../Source/SystemQOR/MSwindows/sys/
#	define SOURCES	(MSW_wait)\
					(MSW_utsname)\
					(MSW_uio)\
					(MSW_times)\
					(MSW_timeb)\
					(MSW_systime)\
					(MSW_sys_sem)\
					(MSW_statvfs)\
					(MSW_stat)\
					(MSW_socket)\
					(MSW_shm)\
					(MSW_select)\
					(MSW_resource)\
					(MSW_msg)\
					(MSW_mman)
#	include "BuildQOR/BuildGroup.pph"

#	define SOURCE_PATH ../../../Source/SystemQOR/MSwindows/winpthreads/
#	define SOURCES	(MSW_barrier)\
					(MSW_clock)\
					(MSW_cond)\
					(MSW_dll_math)\
					(MSW_misc)\
					(MSW_mutex)\
					(MSW_nanosleep)\
					(MSW_rwlock)\
					(MSW_sched)\
					(MSW_sem)\
					(MSW_spinlock)\
					(MSW_thread)
#	include "BuildQOR/BuildGroup.pph"

#endif

//Generate the export and import libraries for the module where the linker will require them
#include "LibCmd2.pph"

