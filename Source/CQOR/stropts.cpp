//stropts.cpp

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

#include "CQOR/CQORPolicy.h"
#include <stropts.h>
#include <errno.h>
#include <stdarg.h>
#include "SystemQOR.h"
#include QOR_SYS_PLATFORMHEADER(stropts.h)
#include "CodeQOR/Tracing/FunctionContextBase.h"
#include "CodeQOR/ErrorSystem/Error.h"
#include "CQOR.h"

//--------------------------------------------------------------------------------
namespace
{
	nsPlatform::Cstropts _stropts;
}//anonymous

__QCMP_STARTLINKAGE_C

//--------------------------------------------------------------------------------
__QOR_INTERFACE( __CQOR ) int fattach( int fd, const char* szPath )
{
    __QCS_FCONTEXT( "fattach" );
    int iResult = -1;
    __QCS_PROTECT
    {
        iResult = _stropts.fattach( fd, szPath );
    }__QCS_ENDPROTECT
    return iResult;
}

//--------------------------------------------------------------------------------
__QOR_INTERFACE( __CQOR ) int fdetach( const char* szPath )
{
    __QCS_FCONTEXT( "fdetach" );
    int iResult = -1;
    __QCS_PROTECT
    {
        iResult = _stropts.fdetach( szPath );
    }__QCS_ENDPROTECT
    return iResult;
}

//--------------------------------------------------------------------------------
__QOR_INTERFACE( __CQOR ) int getmsg( int fd, ::strbuf* __QCMP_RESTRICT ctlptr, ::strbuf* __QCMP_RESTRICT dataptr, int* __QCMP_RESTRICT flagsp )
{
    __QCS_FCONTEXT( "getmsg" );
    int iResult = -1;
    __QCS_PROTECT
    {
        iResult = _stropts.getmsg( fd, ctlptr, dataptr, flagsp );
    }__QCS_ENDPROTECT
    return iResult;
}

//--------------------------------------------------------------------------------
__QOR_INTERFACE( __CQOR ) int getpmsg( int fd, ::strbuf* __QCMP_RESTRICT ctlptr, ::strbuf* __QCMP_RESTRICT dataptr, int* __QCMP_RESTRICT bandp, int* __QCMP_RESTRICT flagsp )
{
    __QCS_FCONTEXT( "getpmsg" );
    int iResult = -1;
    __QCS_PROTECT
    {
        iResult = _stropts.getpmsg( fd, ctlptr, dataptr, bandp, flagsp );
    }__QCS_ENDPROTECT
    return iResult;
}

//--------------------------------------------------------------------------------
__QOR_INTERFACE( __CQOR ) int ioctl( int fd, int iRequest, ... )
{
    __QCS_FCONTEXT( "ioctl" );
    int iResult = -1;
    __QCS_PROTECT
	{
        va_list args;
        va_start( args, iRequest );
        iResult = _stropts.ioctl( fd, iRequest, args );
		va_end( args );
    }__QCS_ENDPROTECT
    return iResult;
}

//--------------------------------------------------------------------------------
__QOR_INTERFACE( __CQOR ) int isastream( int fd )
{
    __QCS_FCONTEXT( "isastream" );
    int iResult = -1;
    __QCS_PROTECT
    {
        iResult = _stropts.isastream( fd );
    }__QCS_ENDPROTECT
    return iResult;
}

//--------------------------------------------------------------------------------
__QOR_INTERFACE( __CQOR ) int putmsg( int fd, const ::strbuf* ctlptr, const ::strbuf* dataptr, int flags )
{
    __QCS_FCONTEXT( "putmsg" );
    int iResult = -1;
    __QCS_PROTECT
    {
        iResult = _stropts.putmsg( fd, ctlptr, dataptr, flags );
    }__QCS_ENDPROTECT
    return iResult;
}

//--------------------------------------------------------------------------------
__QOR_INTERFACE( __CQOR ) int putpmsg( int fd, const ::strbuf* ctlptr, const ::strbuf* dataptr, int band, int flags )
{
    __QCS_FCONTEXT( "putpmsg" );
    int iResult = -1;
    __QCS_PROTECT
    {
        iResult = _stropts.putpmsg( fd, ctlptr, dataptr, band, flags );
    }__QCS_ENDPROTECT
    return iResult;
}

__QCMP_ENDLINKAGE_C

