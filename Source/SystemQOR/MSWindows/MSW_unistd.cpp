//MSW_unistd.cpp

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

#include "SystemQOR.h"

#if		(QOR_SYS_OS == QOR_SYS_MSW)

#include "SystemQOR/MSWindows/MSW_unistd.h"
#include <stdlib.h>
#include "PosumQOR/PosumStream.h"

//--------------------------------------------------------------------------------
namespace nsWin32
{
	//--------------------------------------------------------------------------------
	Cunistd::Cunistd()
	{
		__QCS_MEMBER_FCONTEXT( "Cunistd::Cunistd" );
	}

	//--------------------------------------------------------------------------------
	Cunistd::~Cunistd()
	{
		__QCS_MEMBER_FCONTEXT( "Cunistd::~Cunistd" );
	}

	//--------------------------------------------------------------------------------
    int Cunistd::access( const char*, int )
    {
        return 0;
    }

    //--------------------------------------------------------------------------------
    unsigned Cunistd::alarm( unsigned )
    {
        return 0;
    }

    //--------------------------------------------------------------------------------
    int Cunistd::chdir( const char* )
    {
        return 0;
    }

    //--------------------------------------------------------------------------------
    int Cunistd::chown( const char*, uid_t, gid_t )
    {
        return 0;
    }

    //--------------------------------------------------------------------------------
    int Cunistd::close( int )
    {
        return 0;
    }

    //--------------------------------------------------------------------------------
    size_t Cunistd::confstr( int, char*, size_t )
    {
        return 0;
    }

    //--------------------------------------------------------------------------------
    char* Cunistd::crypt( const char*, const char* )
    {
        return 0;
    }

    //--------------------------------------------------------------------------------
    char* Cunistd::ctermid( char* )
    {
        return 0;
    }

    //--------------------------------------------------------------------------------
    int Cunistd::dup( int )
    {
        return 0;
    }

    //--------------------------------------------------------------------------------
    int Cunistd::dup2( int, int )
    {
        return 0;
    }

    //--------------------------------------------------------------------------------
    void Cunistd::encrypt( char[64], int )
    {
    }

    //--------------------------------------------------------------------------------
    int Cunistd::execl( const char*, const char*, ... )
    {
        return 0;
    }

    //--------------------------------------------------------------------------------
    int Cunistd::execle( const char*, const char*, ... )
    {
        return 0;
    }

    //--------------------------------------------------------------------------------
    int Cunistd::execlp( const char*, const char*, ... )
    {
        return 0;
    }

    //--------------------------------------------------------------------------------
    int Cunistd::execv( const char*, char* const[] )
    {
        return 0;
    }

    //--------------------------------------------------------------------------------
    int Cunistd::execve( const char*, char* const[], char* const[] )
    {
        return 0;
    }

    //--------------------------------------------------------------------------------
    int Cunistd::execvp( const char*, char* const[] )
    {
        return 0;
    }

    //--------------------------------------------------------------------------------
    void Cunistd::_exit( int )
    {
    }

    //--------------------------------------------------------------------------------
    int Cunistd::fchown( int, uid_t, gid_t )
    {
        return 0;
    }

    //--------------------------------------------------------------------------------
    int Cunistd::fchdir( int )
    {
        return 0;
    }

    //--------------------------------------------------------------------------------
    int Cunistd::fdatasync( int )
    {
        return 0;
    }

    //--------------------------------------------------------------------------------
    pid_t Cunistd::fork( void )
    {
        return 0;
    }

    //--------------------------------------------------------------------------------
    long Cunistd::fpathconf( int, int )
    {
        return 0;
    }

    //--------------------------------------------------------------------------------
    int Cunistd::fsync( int )
    {
        return 0;
    }

    //--------------------------------------------------------------------------------
    int Cunistd::ftruncate( int, off_t )
    {
        return 0;
    }

    //--------------------------------------------------------------------------------
    char* Cunistd::getcwd( char*, size_t )
    {
        return 0;
    }

    //--------------------------------------------------------------------------------
    gid_t Cunistd::getegid( void )
    {
        return 0;
    }

    //--------------------------------------------------------------------------------
	//Get the effective user ID
    uid_t Cunistd::geteuid( void )
    {
        _WINQ_FCONTEXT( "Cunistd::geteuid" );
		pid_t Result = m_Process.GetEffectiveUserID();
        return Result;
    }

    //--------------------------------------------------------------------------------
    gid_t Cunistd::getgid( void )
    {
        return 0;
    }

    //--------------------------------------------------------------------------------
    int Cunistd::getgroups( int, gid_t[] )
    {
        return 0;
    }

    //--------------------------------------------------------------------------------
    long Cunistd::gethostid( void )
    {
        return 0;
    }

    //--------------------------------------------------------------------------------
    int Cunistd::gethostname( char*, size_t )
    {
        return 0;
    }

    //--------------------------------------------------------------------------------
    char* Cunistd::getlogin( void )
    {
        return 0;
    }

    //--------------------------------------------------------------------------------
    int Cunistd::getlogin_r( char*, size_t )
    {
        return 0;
    }

    //--------------------------------------------------------------------------------
    int Cunistd::getopt( int, char* const[], const char* )
    {
        return 0;
    }

    //--------------------------------------------------------------------------------
	//Get the Process Group ID for a process
    pid_t Cunistd::getpgid( pid_t process )
    {
		_WINQ_FCONTEXT( "Cunistd::getpgid" );
		pid_t Result = m_Process.GetGroupID( process );
        return Result;
    }

    //--------------------------------------------------------------------------------
    pid_t Cunistd::getpgrp( void )
    {
        return 0;
    }

    //--------------------------------------------------------------------------------
	//Get the Process ID
    pid_t Cunistd::getpid( void )
    {
		_WINQ_FCONTEXT( "Cunistd::getpid" );
		pid_t Result = m_Process.GetID();
        return Result;
    }

    //--------------------------------------------------------------------------------
    pid_t Cunistd::getppid( void )
    {
        return 0;
    }

    //--------------------------------------------------------------------------------
	//Get process Id of Session leader
    pid_t Cunistd::getsid( pid_t ProcessID )
    {
		_WINQ_FCONTEXT( "Cunistd::getsid" );
		pid_t Result = m_Process.GetSessionLeaderID( ProcessID );
        return Result;
    }

    //--------------------------------------------------------------------------------
    uid_t Cunistd::getuid( void )
    {
        return 0;
    }

    //--------------------------------------------------------------------------------
    char* Cunistd::getwd( char* )// (LEGACY )
    {
        return 0;
    }

    //--------------------------------------------------------------------------------
    int Cunistd::isatty( int )
    {
        return 0;
    }

    //--------------------------------------------------------------------------------
    int Cunistd::lchown( const char*, uid_t, gid_t )
    {
        return 0;
    }

    //--------------------------------------------------------------------------------
    int Cunistd::link( const char* , const char* )
    {
        return 0;
    }

    //--------------------------------------------------------------------------------
    int Cunistd::lockf( int, int, off_t )
    {
        return 0;
    }

    //--------------------------------------------------------------------------------
    off_t Cunistd::lseek( int, off_t, int )
    {
        return 0;
    }

    //--------------------------------------------------------------------------------
    int Cunistd::nice( int )
    {
        return 0;
    }

    //--------------------------------------------------------------------------------
    long Cunistd::pathconf( const char*, int )
    {
        return 0;
    }

    //--------------------------------------------------------------------------------
    int Cunistd::pause( void )
    {
        return 0;
    }

    //--------------------------------------------------------------------------------
    int Cunistd::pipe( int[ 2 ] )
    {
        return 0;
    }

    //--------------------------------------------------------------------------------
    ssize_t Cunistd::pread( int, void*, size_t, off_t )
    {
        return 0;
    }

    //--------------------------------------------------------------------------------
    ssize_t Cunistd::pwrite( int, const void*, size_t, off_t )
    {
        return 0;
    }

    //--------------------------------------------------------------------------------
    ssize_t Cunistd::read( int nFD, void* pDestBuffer, size_t BufferByteCount )
    {
		nsPosum::CStream Stream( nFD );

		ssize_t Result = Stream.fread( pDestBuffer, 1, BufferByteCount );
        return Result;
    }

    //--------------------------------------------------------------------------------
    ssize_t Cunistd::readlink( const char* __QCMP_RESTRICT, char* __QCMP_RESTRICT, size_t )
    {
        return 0;
    }

    //--------------------------------------------------------------------------------
    int Cunistd::rmdir( const char* )
    {
        return 0;
    }

    //--------------------------------------------------------------------------------
    int Cunistd::setegid( gid_t )
    {
        return 0;
    }

    //--------------------------------------------------------------------------------
    int Cunistd::seteuid( uid_t )
    {
        return 0;
    }

    //--------------------------------------------------------------------------------
    int Cunistd::setgid( gid_t )
    {
        return 0;
    }

    //--------------------------------------------------------------------------------
    int Cunistd::setpgid( pid_t, pid_t )
    {
        return 0;
    }

    //--------------------------------------------------------------------------------
    pid_t Cunistd::setpgrp( void )
    {
        return 0;
    }

    //--------------------------------------------------------------------------------
    int Cunistd::setregid( gid_t, gid_t )
    {
        return 0;
    }

    //--------------------------------------------------------------------------------
    int Cunistd::setreuid( uid_t, uid_t )
    {
        return 0;
    }

    //--------------------------------------------------------------------------------
    pid_t Cunistd::setsid( void )
    {
        return 0;
    }

    //--------------------------------------------------------------------------------
    int Cunistd::setuid( uid_t )
    {
        return 0;
    }

    //--------------------------------------------------------------------------------
    unsigned Cunistd::sleep( unsigned )
    {
        return 0;
    }

    //--------------------------------------------------------------------------------
    void Cunistd::swab( const void* __QCMP_RESTRICT, void* __QCMP_RESTRICT, ssize_t )
    {
        return;
    }

    //--------------------------------------------------------------------------------
    int Cunistd::symlink( const char*, const char* )
    {
        return 0;
    }

    //--------------------------------------------------------------------------------
    void Cunistd::sync( void )
    {
    }

    //--------------------------------------------------------------------------------
    long Cunistd::sysconf( int )
    {
        return 0;
    }

    //--------------------------------------------------------------------------------
    pid_t Cunistd::tcgetpgrp( int )
    {
        return 0;
    }

    //--------------------------------------------------------------------------------
    int Cunistd::tcsetpgrp( int, pid_t )
    {
        return 0;
    }

    //--------------------------------------------------------------------------------
    int Cunistd::truncate( const char*, off_t )
    {
        return 0;
    }

    //--------------------------------------------------------------------------------
    char* Cunistd::ttyname( int )
    {
        return 0;
    }

    //--------------------------------------------------------------------------------
    int Cunistd::ttyname_r( int, char*, size_t )
    {
        return 0;
    }

    //--------------------------------------------------------------------------------
    useconds_t Cunistd::ualarm( useconds_t, useconds_t )
    {
        return 0;
    }

    //--------------------------------------------------------------------------------
    int Cunistd::unlink( const char* )
    {
        return 0;
    }

    //--------------------------------------------------------------------------------
    int Cunistd::usleep( useconds_t )
    {
        return 0;
    }

    //--------------------------------------------------------------------------------
    pid_t Cunistd::vfork( void )
    {
        return 0;
    }

    //--------------------------------------------------------------------------------
    ssize_t Cunistd::write( int, const void*, size_t )
    {
        return 0;
    }

	//--------------------------------------------------------------------------------
	void* Cunistd::sbrk( intptr_t delta )
	{
		return m_MemoryManager.SetBreak( delta );
	}

}//nsWin32

#endif//(QOR_SYS_OS == QOR_SYS_MSW)