//wait.h

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

#ifndef	QOR_SYS_WAIT_H_3
#define QOR_SYS_WAIT_H_3

#include <signal.h>
#include "SystemQOR.h"
#include QOR_SYS_PLATFORMSYSTYPES(wait)

//the following symbolic constants for use with waitpid():

//#define WCONTINUED			8			//[XSI]  Report status of continued child process.  
//#define WNOHANG				1			//Do not hang if no status is available; return immediately. 
//#define WUNTRACED			2			//Report status of stopped child process. 

//the following macros for analysis of process status values:
/*
#define WEXITSTATUS( status )			( WaitExitStatus( status ) )		//Return exit status. 
#define WIFCONTINUED					( WaitIfContinued() )				//[XSI]  True if child has been continued.  
#define WIFEXITED( status )				( WaitIfExited( status ) )			//True if child exited normally. 
#define WIFSIGNALED( status )			( WaitIfSignaled( status ) )		//True if child exited due to uncaught signal. 
#define WIFSTOPPED( status )			( WaitIfStopped( status ) )			//True if child is currently stopped. 
#define WSTOPSIG( status )				( WaitStopSignal( status ) )		//Return signal number that caused process to stop. 
#define WTERMSIG( status )				( WaitTermSignal( status ) )		//Return signal number that caused process to terminate. 
*/

/*
#define WEXITSTATUS(s) (((s) & 0xff00) >> 8)
#define WIFCONTINUED(s) ((s) == 0xffff)
#define WIFEXITED(s) (!WTERMSIG(s))
#define WIFSIGNALED(s) (((s)&0xffff)-1U < 0xffu)
#define WIFSTOPPED(s) ((short)((((s)&0xffff)*0x10001)>>8) > 0x7f00)
#define WSTOPSIG(s) WEXITSTATUS(s)
#define WTERMSIG(s) ((s) & 0x7f)
#define WCOREDUMP(s) ((s) & 0x80)
*/

//the following symbolic constants as possible values for the options argument to waitid():

#define WEXITED				4				//Wait for processes that have exited. 
#define WNOWAIT				0x1000000		//Keep the process whose status is returned in infop in a waitable state. 
#define WSTOPPED			2				//Status is returned for any child that has stopped upon receipt of a signal. 

typedef nsPlatform::idtype_t idtype_t;
typedef nsPlatform::siginfo_t siginfo_t;
typedef nsPlatform::pid_t pid_t;
typedef nsPlatform::id_t id_t;

__QCMP_STARTLINKAGE_C

    __QOR_INTERFACE( __CQOR ) ::pid_t	wait( int* );
    __QOR_INTERFACE( __CQOR ) int		waitid( ::idtype_t, ::id_t, ::siginfo_t*, int );
    __QOR_INTERFACE( __CQOR ) ::pid_t	waitpid( ::pid_t, int*, int );

__QCMP_ENDLINKAGE_C

#endif//QOR_SYS_WAIT_H_3