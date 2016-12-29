//select.cpp

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

//Generic select implementation
//An exported standard C interface which forwards calls to the matching C++ implementaion for the platform

#include "CQOR/CQORPolicy.h"
#include <sys/select.h>
#include <errno.h>
#include "SystemQOR.h"

#include QOR_SYS_PLATFORMSYSHEADER(select.h)
#include "CodeQOR/Tracing/FunctionContextBase.h"
#include "CodeQOR/ErrorSystem/Error.h"
#include "CQOR.h"

//--------------------------------------------------------------------------------
namespace
{
	nsPlatform::Cselect _select;
}//anonymous

__QCMP_STARTLINKAGE_C

//--------------------------------------------------------------------------------
__QOR_INTERFACE( __CQOR ) void FD_CLR( int fd, ::fd_set* fdset )
{
    __QCS_FCONTEXT( "FD_CLR" );
    __QCS_PROTECT
    {
        _select.FD_CLR( fd, fdset );
    }__QCS_ENDPROTECT
}

//--------------------------------------------------------------------------------
__QOR_INTERFACE( __CQOR ) int FD_ISSET( int fd, ::fd_set* fdset )
{
    __QCS_FCONTEXT( "FD_ISET" );
	int iResult = 0;
    __QCS_PROTECT
    {
        iResult =_select.FD_ISSET( fd, fdset );
    }__QCS_ENDPROTECT
	return iResult;
}

//--------------------------------------------------------------------------------
__QOR_INTERFACE( __CQOR ) void FD_SET( int fd, ::fd_set* fdset )
{
    __QCS_FCONTEXT( "FD_SET" );
    __QCS_PROTECT
    {
        _select.FD_SET( fd, fdset );
    }__QCS_ENDPROTECT
}

//--------------------------------------------------------------------------------
__QOR_INTERFACE( __CQOR ) void FD_ZERO( ::fd_set* fdset )
{
    __QCS_FCONTEXT( "FD_ZERO" );
    __QCS_PROTECT
    {
        _select.FD_ZERO( fdset );
    }__QCS_ENDPROTECT
}

//--------------------------------------------------------------------------------
__QOR_INTERFACE( __CQOR ) int pselect( int nfds, ::fd_set* __QCMP_RESTRICT readfds, ::fd_set* __QCMP_RESTRICT writefds, ::fd_set* __QCMP_RESTRICT errorfds, const ::timespec* __QCMP_RESTRICT timeout, const ::sigset_t* __QCMP_RESTRICT sigmask )
{
    __QCS_FCONTEXT( "pselect" );
    int iResult = 0;
    __QCS_PROTECT
    {
        iResult = _select.pselect( nfds, readfds, writefds, errorfds, timeout, sigmask );
    }__QCS_ENDPROTECT
    return iResult;
}

//--------------------------------------------------------------------------------
__QOR_INTERFACE( __CQOR ) int select( int nfds, ::fd_set* __QCMP_RESTRICT readfds, ::fd_set* __QCMP_RESTRICT writefds, ::fd_set* __QCMP_RESTRICT errorfds, ::timeval* __QCMP_RESTRICT timeout )
{
	__QCS_FCONTEXT( "select" );
	int iResult = 0;
	__QCS_PROTECT
	{
		iResult = _select.select( nfds, readfds, writefds, errorfds, timeout );
	}__QCS_ENDPROTECT
	return iResult;
}

__QCMP_ENDLINKAGE_C