//limits.h

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

#ifndef QOR_LIMITS_H_3
#define QOR_LIMITS_H_3

#include "SystemQOR.h"

//universal definitions which can be used by platform as well
#define CHAR_BIT			8								//Number of bits in a type char.
#define __CHAR_BIT__		8
#define SCHAR_MAX			(+127)							//Maximum value for an object of type signed char.
#define SCHAR_MIN			(-128)							//Minimum value for an object of type signed char.
#define UCHAR_MAX			255								//Maximum value for an object of type unsigned char.

#include QOR_SYS_PLATFORMHEADER(limits.h)

#define LDBL_MAX_EXP			( nsPlatform::LongDoubleMaxExp )
#define FLT_MAX_EXP				( nsPlatform::FloatMaxExp )
#define DBL_MAX_EXP				( nsPlatform::DoubleMaxExp );			// max binary exponent
#define AIO_LISTIO_MAX			( nsPlatform::AIOListIOMax )			//Maximum number of I/O operations in a single list I/O call supported by the implementation. Minimum Acceptable Value: {_POSIX_AIO_LISTIO_MAX} 
#define AIO_MAX					( nsPlatform::AIOMax )					//Maximum number of outstanding asynchronous I/O operations supported by the implementation. Minimum Acceptable Value: {_POSIX_AIO_MAX} 
#define AIO_PRIO_DELTA_MAX		( nsPlatform::AIOPrioDeltaMax )			//The maximum amount by which a process can decrease its asynchronous I/O priority level from its own scheduling priority. Minimum Acceptable Value: 0 
#define ARG_MAX					( nsPlatform::ArgMax )					//Maximum length of argument to the exec functions including environment data. Minimum Acceptable Value: {_POSIX_ARG_MAX} 
#define ATEXIT_MAX				( nsPlatform::AtExitMax )				//Maximum number of functions that may be registered with atexit(). Minimum Acceptable Value: 32 
#define CHILD_MAX				( nsPlatform::ChildMax )				//Maximum number of simultaneous processes per real user ID. Minimum Acceptable Value: {_POSIX_CHILD_MAX} 
#define DELAYTIMER_MAX			( nsPlatform::DelayTimerMax )			//Maximum number of timer expiration overruns. Minimum Acceptable Value: {_POSIX_DELAYTIMER_MAX} 
#define HOST_NAME_MAX			( nsPlatform::HostNameMax )				//Maximum length of a host name (not including the terminating null) as returned from the gethostname() function. Minimum Acceptable Value: {_POSIX_HOST_NAME_MAX} 
#define IOV_MAX					( nsPlatform::IOVMax )					//Maximum number of iovec structures that one process has available for use with readv() or writev(). Minimum Acceptable Value: {_XOPEN_IOV_MAX}  
#define LOGIN_NAME_MAX			( nsPlatform::LoginNameMax )			//Maximum length of a login name. Minimum Acceptable Value: {_POSIX_LOGIN_NAME_MAX} 
#define MQ_OPEN_MAX				( nsPlatform::MessageQueueOpenMax )		//The maximum number of open message queue descriptors a process may hold. Minimum Acceptable Value: {_POSIX_MQ_OPEN_MAX}  
#define MQ_PRIO_MAX				( nsPlatform::MessageQueueProrityMax )	//The maximum number of message priorities supported by the implementation. Minimum Acceptable Value: {_POSIX_MQ_PRIO_MAX}  
#define OPEN_MAX				( nsPlatform::OpenMax )					//A value one greater than the maximum value that the system may assign to a newly-created file descriptor. Minimum Acceptable Value: {_POSIX_OPEN_MAX} 
#define PAGESIZE				( nsPlatform::PageSize )				//Size in bytes of a page. Minimum Acceptable Value: 1 
#define PAGE_SIZE				( nsPlatform::PageSize )				//Equivalent to {PAGESIZE}. If either {PAGESIZE} or {PAGE_SIZE} is defined, the other is defined with the same value.  
#define PTHREAD_DESTRUCTOR_ITERATIONS	( nsPlatform::PThreadDestructorIterations )	//Maximum number of attempts made to destroy a thread's thread-specific data values on thread exit. Minimum Acceptable Value: {_POSIX_THREAD_DESTRUCTOR_ITERATIONS} 
#define PTHREAD_KEYS_MAX		( nsPlatform::PThreadKeysMax )			//Maximum number of data keys that can be created by a process. Minimum Acceptable Value: {_POSIX_THREAD_KEYS_MAX} 
#define PTHREAD_STACK_MIN		( nsPlatform::PThreadStackMin )			//Minimum size in bytes of thread stack storage. Minimum Acceptable Value: 0 
#define PTHREAD_THREADS_MAX		( nsPlatform::PThreadThreadsMax )		//Maximum number of threads that can be created per process.Minimum Acceptable Value: {_POSIX_THREAD_THREADS_MAX} 
#define RE_DUP_MAX				( nsPlatform::ReDupMax )				//Maximum number of repeated occurrences of a BRE or ERE interval expression; see BREs Matching Multiple Characters and EREs Matching Multiple Characters . Minimum Acceptable Value: {_POSIX2_RE_DUP_MAX} 
#define RTSIG_MAX				( nsPlatform::RTSigMax )				//Maximum number of realtime signals reserved for application use in this implementation. Minimum Acceptable Value: {_POSIX_RTSIG_MAX} 
#define SEM_NSEMS_MAX			( nsPlatform::SemaphoresMax )			//Maximum number of semaphores that a process may have. Minimum Acceptable Value: {_POSIX_SEM_NSEMS_MAX} 
#define SEM_VALUE_MAX			( nsPlatform::SemaphoreMaxValue )		//The maximum value a semaphore may have. Minimum Acceptable Value: {_POSIX_SEM_VALUE_MAX} 
#define SIGQUEUE_MAX			( nsPlatform::SigQueueMax )				//Maximum number of queued signals that a process may send and have pending at the receiver(s) at any time. Minimum Acceptable Value: {_POSIX_SIGQUEUE_MAX} 
#define SS_REPL_MAX				( nsPlatform::SSReplMax )				//The maximum number of replenishment operations that may be simultaneously pending for a particular sporadic server scheduler. Minimum Acceptable Value: {_POSIX_SS_REPL_MAX}  
#define STREAM_MAX				( nsPlatform::StreamMax )				//Maximum number of streams that one process can have open at one time. If defined, it has the same value as {FOPEN_MAX} (see <stdio.h>). Minimum Acceptable Value: {_POSIX_STREAM_MAX} 
#define SYMLOOP_MAX				( nsPlatform::SymLoopMax )				//Maximum number of symbolic links that can be reliably traversed in the resolution of a pathname in the absence of a loop. Minimum Acceptable Value: {_POSIX_SYMLOOP_MAX} 
#define TIMER_MAX				( nsPlatform::TimerMax )				//Maximum number of timers per process supported by the implementation. Minimum Acceptable Value: {_POSIX_TIMER_MAX} 
#define TRACE_EVENT_NAME_MAX	( nsPlatform::TraceEventNameMax )		//Maximum length of the trace event name (not including the terminating null). Minimum Acceptable Value: {_POSIX_TRACE_EVENT_NAME_MAX}  
#define TRACE_NAME_MAX			( nsPlatform::TraceNameMax )			//Maximum length of the trace generation version string or of the trace stream name (not including the terminating null). Minimum Acceptable Value: {_POSIX_TRACE_NAME_MAX}  
#define TRACE_SYS_MAX			( nsPlatform::TraceSysMax )				//Maximum number of trace streams that may simultaneously exist in the system. Minimum Acceptable Value: {_POSIX_TRACE_SYS_MAX}  
#define TRACE_USER_EVENT_MAX	( nsPlatform::TraceUserEventMax )		//Maximum number of user trace event type identifiers that may simultaneously exist in a traced process, including the predefined user trace event POSIX_TRACE_UNNAMED_USER_EVENT. Minimum Acceptable Value: {_POSIX_TRACE_USER_EVENT_MAX}  
#define TTY_NAME_MAX			( nsPlatform::TTYNameMax )				//Maximum length of terminal device name. Minimum Acceptable Value: {_POSIX_TTY_NAME_MAX} 
#define TZNAME_MAX				( nsPlatform::TimeZoneNameMax )			//Maximum number of bytes supported for the name of a timezone (not of the TZ variable). Minimum Acceptable Value: {_POSIX_TZNAME_MAX} 
//Note: The length given by {TZNAME_MAX} does not include the quoting characters mentioned in Other Environment Variables . 

//Pathname Variable Values
//The values in the following list may be constants within an implementation or may vary from one pathname to another. For example, file systems or directories may have different characteristics.
//A definition of one of the symbolic constants in the following list shall be omitted from the <limits.h> header on specific implementations where the corresponding value is equal to or greater than the stated minimum, but where the value can vary depending on the file to which it is applied. The actual value supported for a specific pathname shall be provided by the pathconf() function.

//{FILESIZEBITS}									//Minimum number of bits needed to represent, as a signed integer value, the maximum size of a regular file allowed in the specified directory. Minimum Acceptable Value: 32 
//{LINK_MAX}										//Maximum number of links to a single file. Minimum Acceptable Value: {_POSIX_LINK_MAX} 
//{MAX_CANON}										//Maximum number of bytes in a terminal canonical input line. Minimum Acceptable Value: {_POSIX_MAX_CANON} 
//{MAX_INPUT}										//Minimum number of bytes for which space is available in a terminal input queue; therefore, the maximum number of bytes a conforming application may require to be typed as input before reading them. Minimum Acceptable Value: {_POSIX_MAX_INPUT} 
//{NAME_MAX}										//Maximum number of bytes in a filename (not including the terminating null). Minimum Acceptable Value: {_POSIX_NAME_MAX} [XSI]  Minimum Acceptable Value: {_XOPEN_NAME_MAX}  
#define PATH_MAX				( nsPlatform::PathMax )					//Maximum number of bytes the implementation will store as a pathname in a user-supplied buffer of unspecified size, including the terminating null character. Minimum number the implementation will accept as the maximum number of bytes in a pathname. Minimum Acceptable Value: {_POSIX_PATH_MAX} [XSI]  Minimum Acceptable Value: {_XOPEN_PATH_MAX}  
//{PIPE_BUF}										//Maximum number of bytes that is guaranteed to be atomic when writing to a pipe. Minimum Acceptable Value: {_POSIX_PIPE_BUF} 
//{POSIX_ALLOC_SIZE_MIN}							//Minimum number of bytes of storage actually allocated for any portion of a file. Minimum Acceptable Value: Not specified.  
//{POSIX_REC_INCR_XFER_SIZE}						//Recommended increment for file transfer sizes between the {POSIX_REC_MIN_XFER_SIZE} and {POSIX_REC_MAX_XFER_SIZE} values. Minimum Acceptable Value: Not specified.  
//{POSIX_REC_MAX_XFER_SIZE}							//Maximum recommended file transfer size. Minimum Acceptable Value: Not specified.  
//{POSIX_REC_MIN_XFER_SIZE}							//Minimum recommended file transfer size. Minimum Acceptable Value: Not specified.  
//{POSIX_REC_XFER_ALIGN}							//Recommended file transfer buffer alignment. Minimum Acceptable Value: Not specified.  
//{SYMLINK_MAX}										//Maximum number of bytes in a symbolic link. Minimum Acceptable Value: {_POSIX_SYMLINK_MAX} 

//Runtime Increasable Values
//The magnitude limitations in the following list shall be fixed by specific implementations. An application should assume that the value of the symbolic constant defined by <limits.h> in a specific implementation is the minimum that pertains whenever the application is run under that implementation. A specific instance of a specific implementation may increase the value relative to that supplied by <limits.h> for that implementation. The actual value supported by a specific instance shall be provided by the sysconf() function.

//{BC_BASE_MAX}									//Maximum obase values allowed by the bc utility.Minimum Acceptable Value: {_POSIX2_BC_BASE_MAX} 
//{BC_DIM_MAX}									//Maximum number of elements permitted in an array by the bc utility.Minimum Acceptable Value: {_POSIX2_BC_DIM_MAX} 
//{BC_SCALE_MAX}									//Maximum scale value allowed by the bc utility.Minimum Acceptable Value: {_POSIX2_BC_SCALE_MAX} 
//{BC_STRING_MAX}									//Maximum length of a string constant accepted by the bc utility.Minimum Acceptable Value: {_POSIX2_BC_STRING_MAX} 
//{CHARCLASS_NAME_MAX}							//Maximum number of bytes in a character class name. Minimum Acceptable Value: {_POSIX2_CHARCLASS_NAME_MAX} 
//{COLL_WEIGHTS_MAX}								//Maximum number of weights that can be assigned to an entry of the LC_COLLATE order keyword in the locale definition file; see Locale. Minimum Acceptable Value: {_POSIX2_COLL_WEIGHTS_MAX} 
//{EXPR_NEST_MAX}									//Maximum number of expressions that can be nested within parentheses by the expr utility. Minimum Acceptable Value: {_POSIX2_EXPR_NEST_MAX} 
//{LINE_MAX}										//Unless otherwise noted, the maximum length, in bytes, of a utility's input line (either standard input or another file), when the utility is described as processing text files. The length includes room for the trailing <newline>. Minimum Acceptable Value: {_POSIX2_LINE_MAX} 
//{NGROUPS_MAX}									//Maximum number of simultaneous supplementary group IDs per process. Minimum Acceptable Value: {_POSIX_NGROUPS_MAX} 
//{RE_DUP_MAX}									//Maximum number of repeated occurrences of a regular expression permitted when using the interval notation \{m,n\}; see Regular Expressions. Minimum Acceptable Value: {_POSIX2_RE_DUP_MAX} 

//Maximum Values
//The <limits.h> header shall define the following symbolic constants with the values shown. These are the most restrictive values for certain features on an implementation. A conforming implementation shall provide values no larger than these values. A conforming application must not require a smaller value for correct operation.

#define _POSIX_CLOCKRES_MIN			20000000				//The resolution of the CLOCK_REALTIME clock, in nanoseconds.
//[MON]  If the Monotonic Clock option is supported, the resolution of the CLOCK_MONOTONIC clock, in nanoseconds, is represented by {_POSIX_CLOCKRES_MIN}. 

//Minimum Values
//The <limits.h> header shall define the following symbolic constants with the values shown. These are the most restrictive values for certain features on an implementation conforming to this volume of POSIX.1-2008. Related symbolic constants are defined elsewhere in this volume of POSIX.1-2008 which reflect the actual implementation and which need not be as restrictive. A conforming implementation shall provide values at least this large. A strictly conforming application must not require a larger value for correct operation.

#define _POSIX_AIO_LISTIO_MAX		2						//The number of I/O operations that can be specified in a list I/O call.
#define _POSIX_AIO_MAX				1						//The number of outstanding asynchronous I/O operations.
#define _POSIX_ARG_MAX				4096					//Maximum length of argument to the exec functions including environment data.
#define _POSIX_CHILD_MAX			25						//Maximum number of simultaneous processes per real user ID.
#define _POSIX_DELAYTIMER_MAX		32						//The number of timer expiration overruns.
#define _POSIX_HOST_NAME_MAX		255						//Maximum length of a host name (not including the terminating null) as returned from the gethostname() function.
#define _POSIX_LINK_MAX				8						//Maximum number of links to a single file.
#define _POSIX_LOGIN_NAME_MAX		9						//The size of the storage required for a login name, in bytes (including the terminating null).
#define _POSIX_MAX_CANON			255						//Maximum number of bytes in a terminal canonical input queue.
#define _POSIX_MAX_INPUT			255						//Maximum number of bytes allowed in a terminal input queue.
#define _POSIX_MQ_OPEN_MAX			8						//The number of message queues that can be open for a single process.
#define _POSIX_MQ_PRIO_MAX			32						//The maximum number of message priorities supported by the implementation.
#define _POSIX_NAME_MAX				14						//Maximum number of bytes in a filename (not including the terminating null).
#define _POSIX_NGROUPS_MAX			8						//Maximum number of simultaneous supplementary group IDs per process.
#define _POSIX_OPEN_MAX				20						//Maximum number of files that one process can have open at any one time.
#define _POSIX_PATH_MAX				256						//Minimum number the implementation will accept as the maximum number of bytes in a pathname.
#define _POSIX_PIPE_BUF				512						//Maximum number of bytes that is guaranteed to be atomic when writing to a pipe.
#define _POSIX_RE_DUP_MAX			255						//The number of repeated occurrences of a BRE permitted by the regexec() and regcomp() functions when using the interval notation {\(m,n\}; see BREs Matching Multiple Characters .
#define _POSIX_RTSIG_MAX			8						//The number of realtime signal numbers reserved for application use.
#define _POSIX_SEM_NSEMS_MAX		256						//The number of semaphores that a process may have.
#define _POSIX_SEM_VALUE_MAX		32767					//The maximum value a semaphore may have.
#define _POSIX_SIGQUEUE_MAX			32						//The number of queued signals that a process may send and have pending at the receiver(s) at any time.
#define _POSIX_SSIZE_MAX			32767					//The value that can be stored in an object of type ssize_t.
#define _POSIX_SS_REPL_MAX			4						//The number of replenishment operations that may be simultaneously pending for a particular sporadic server scheduler.
#define _POSIX_STREAM_MAX			8						//The number of streams that one process can have open at one time.
#define _POSIX_SYMLINK_MAX			255						//The number of bytes in a symbolic link.
#define _POSIX_SYMLOOP_MAX			8						//The number of symbolic links that can be traversed in the resolution of a pathname in the absence of a loop.
#define _POSIX_THREAD_DESTRUCTOR_ITERATIONS		4			//The number of attempts made to destroy a thread's thread-specific data values on thread exit.
#define _POSIX_THREAD_KEYS_MAX		128						//The number of data keys per process.
#define _POSIX_THREAD_THREADS_MAX	64						//The number of threads per process.
#define _POSIX_TIMER_MAX			32						//The per-process number of timers.
#define _POSIX_TRACE_EVENT_NAME_MAX	30						//The length in bytes of a trace event name (not including the terminating null).
#define _POSIX_TRACE_NAME_MAX		8						//The length in bytes of a trace generation version string or a trace stream name (not including the terminating null).
#define _POSIX_TRACE_SYS_MAX		8						//The number of trace streams that may simultaneously exist in the system.
#define _POSIX_TRACE_USER_EVENT_MAX	32						//The number of user trace event type identifiers that may simultaneously exist in a traced process, including the predefined user trace event POSIX_TRACE_UNNAMED_USER_EVENT.
#define _POSIX_TTY_NAME_MAX			9						//The size of the storage required for a terminal device name, in bytes (including the terminating null).
#define _POSIX_TZNAME_MAX			6						//Maximum number of bytes supported for the name of a timezone (not of the TZ variable).
															//Note: The length given by {_POSIX_TZNAME_MAX} does not include the quoting characters mentioned in Other Environment Variables . 
#define _POSIX2_BC_BASE_MAX			99						//Maximum obase values allowed by the bc utility.
#define _POSIX2_BC_DIM_MAX			2048					//Maximum number of elements permitted in an array by the bc utility.
#define _POSIX2_BC_SCALE_MAX		99						//Maximum scale value allowed by the bc utility.
#define _POSIX2_BC_STRING_MAX		1000					//Maximum length of a string constant accepted by the bc utility.
#define _POSIX2_CHARCLASS_NAME_MAX	14						//Maximum number of bytes in a character class name.
#define _POSIX2_COLL_WEIGHTS_MAX	2						//Maximum number of weights that can be assigned to an entry of the LC_COLLATE order keyword in the locale definition file; see Locale .
#define _POSIX2_EXPR_NEST_MAX		32						//Maximum number of expressions that can be nested within parentheses by the expr utility.
#define _POSIX2_LINE_MAX			2048					//Unless otherwise noted, the maximum length, in bytes, of a utility's input line (either standard input or another file), when the utility is described as processing text files. The length includes room for the trailing <newline>.
#define _POSIX2_RE_DUP_MAX			255						//Maximum number of repeated occurrences of a regular expression permitted when using the interval notation \{m,n\}; see Regular Expressions .
#define _XOPEN_IOV_MAX				16						//Maximum number of iovec structures that one process has available for use with readv() or writev().
#define _XOPEN_NAME_MAX				255						//Maximum number of bytes in a filename (not including the terminating null).
#define _XOPEN_PATH_MAX				1024					//Minimum number the implementation will accept as the maximum number of bytes in a pathname.

//Numerical Limits
//The <limits.h> header shall define the following macros and, except for {CHAR_BIT}, {LONG_BIT}, {MB_LEN_MAX}, and {WORD_BIT}, they shall be replaced by expressions that have the same type as would an expression that is an object of the corresponding type converted according to the integer promotions.
//If the value of an object of type char is treated as a signed integer when used in an expression, the value of {CHAR_MIN} is the same as that of {SCHAR_MIN} and the value of {CHAR_MAX} is the same as that of {SCHAR_MAX}. Otherwise, the value of {CHAR_MIN} is 0 and the value of {CHAR_MAX} is the same as that of {UCHAR_MAX}.

#define CHAR_MAX			( nsPlatform::CharMax )			//Maximum value for an object of type char.Value: {UCHAR_MAX} or {SCHAR_MAX} 
#define CHAR_MIN			( nsPlatform::CharMin )			//Minimum value for an object of type char.Value: {SCHAR_MIN} or 0 
#define INT_MAX				( nsPlatform::IntMax )			//Maximum value for an object of type int. Minimum Acceptable Value: 2 147 483 647  
#define INT_MIN				( nsPlatform::IntMin )			//Minimum value for an object of type int. Maximum Acceptable Value: -2 147 483 647  
#define LLONG_MAX			( nsPlatform::LongLongMax )		//Maximum value for an object of type long long. Minimum Acceptable Value: +9223372036854775807 
#define LLONG_MIN			( nsPlatform::LongLongMin )		//Minimum value for an object of type long long. Maximum Acceptable Value: -9223372036854775807 
#define LONG_BIT			( sizeof( long ) * CHAR_BIT )	//Number of bits in an object of type long. Minimum Acceptable Value: 32 
#define LONG_MAX			( nsPlatform::LongMax )			//Maximum value for an object of type long. Minimum Acceptable Value: +2 147 483 647 
#define LONG_MIN			( nsPlatform::LongMin )			//Minimum value for an object of type long. Maximum Acceptable Value: -2 147 483 647 
#define MB_LEN_MAX			( nsPlatform::MBLenMax )		//Maximum number of bytes in a character, for any supported locale. Minimum Acceptable Value: 1 
#define SHRT_MAX			( nsPlatform::ShortMax )		//Maximum value for an object of type short. Minimum Acceptable Value: +32 767 
#define SHRT_MIN			( nsPlatform::ShortMin )		//Minimum value for an object of type short. Maximum Acceptable Value: -32 767 
#define SSIZE_MAX			( nsPlatform::SSizeMax )		//Maximum value for an object of type ssize_t. Minimum Acceptable Value: {_POSIX_SSIZE_MAX} 
#define UINT_MAX			( nsPlatform::UIntMax )			//Maximum value for an object of type unsigned. Minimum Acceptable Value: 4 294 967 295  
#define ULLONG_MAX			( nsPlatform::ULongLongMax )	//Maximum value for an object of type unsigned long long. Minimum Acceptable Value: 18446744073709551615 
#define ULONG_MAX			( nsPlatform::ULongMax )		//Maximum value for an object of type unsigned long. Minimum Acceptable Value: 4 294 967 295 
#define USHRT_MAX			( nsPlatform::UShortMax )		//Maximum value for an object of type unsigned short. Minimum Acceptable Value: 65 535 
#define WORD_BIT			( sizeof( int ) * CHAR_BIT )	//Number of bits in an object of type int. Minimum Acceptable Value: 32 

//Other Invariant Values

#define NL_ARGMAX			( nsPlatform::NLArgMax )			//Maximum value of n in conversion specifications using the "%n$" sequence in calls to the printf() and scanf() families of functions.
																//Minimum Acceptable Value: 9 
#define NL_LANGMAX			( nsPlatform::NLLangMax )			//Maximum number of bytes in a LANG name.
																//Minimum Acceptable Value: 14  
#define NL_MSGMAX			( nsPlatform::NLMsgMax )			//Maximum message number.
																//Minimum Acceptable Value: 32 767 
#define NL_SETMAX			( nsPlatform::NLSetMax )			//Maximum set number.
																//Minimum Acceptable Value: 255 
#define NL_TEXTMAX			( nsPlatform::NLTextMax )			//Maximum number of bytes in a message string.
																//Minimum Acceptable Value: {_POSIX2_LINE_MAX} 
#define NZERO				( nsPlatform::NZero )				//Default process priority.
																//Minimum Acceptable Value: 20  

#endif //QOR_LIMITS_H_3
