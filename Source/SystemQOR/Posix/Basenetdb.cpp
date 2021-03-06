//Basenetdb.cpp

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

#include "SystemQOR/Posix/Basenetdb.h"
#include <errno.h>
#include "CodeQOR/Tracing/FunctionContextBase.h"

//--------------------------------------------------------------------------------
namespace nsBaseCRT
{
	__QOR_IMPLEMENT_OCLASS_LUID( Cnetdb );
	
	//--------------------------------------------------------------------------------
	Cnetdb::Cnetdb()
	{
		__QCS_MEMBER_FCONTEXT( "Cnetdb::Cnetdb" );
	}

	//--------------------------------------------------------------------------------
	Cnetdb::~Cnetdb()
	{
		__QCS_MEMBER_FCONTEXT( "Cnetdb::~Cnetdb" );
	}

	//--------------------------------------------------------------------------------
	void Cnetdb::endhostent( void )
	{
		__QCS_MEMBER_FCONTEXT( "Cnetdb::Cnetdb" );
	}

	//--------------------------------------------------------------------------------
	void Cnetdb::endnetent( void )
	{
		__QCS_MEMBER_FCONTEXT( "Cnetdb::Cnetdb" );
		errno = ENOSYS;
	}

	//--------------------------------------------------------------------------------
	void Cnetdb::endprotoent( void )
	{
		__QCS_MEMBER_FCONTEXT( "Cnetdb::Cnetdb" );
		errno = ENOSYS;
	}

	//--------------------------------------------------------------------------------
	void Cnetdb::endservent( void )
	{
		__QCS_MEMBER_FCONTEXT( "Cnetdb::Cnetdb" );
		errno = ENOSYS;
	}

	//--------------------------------------------------------------------------------
	void Cnetdb::freeaddrinfo( addrinfo* )
	{
		__QCS_MEMBER_FCONTEXT( "Cnetdb::Cnetdb" );
		errno = ENOSYS;
	}

	//--------------------------------------------------------------------------------
	const char* Cnetdb::gai_strerror( int )
	{
		__QCS_MEMBER_FCONTEXT( "Cnetdb::Cnetdb" );
		errno = ENOSYS;
		return 0;
	}

	//--------------------------------------------------------------------------------
	int Cnetdb::getaddrinfo( const char*, const char*, const addrinfo*, addrinfo** )
	{
		__QCS_MEMBER_FCONTEXT( "Cnetdb::Cnetdb" );
		errno = ENOSYS;
		return 0;
	}

	//--------------------------------------------------------------------------------
	hostent* Cnetdb::gethostbyaddr( const void*, socklen_t, int )
	{
		__QCS_MEMBER_FCONTEXT( "Cnetdb::Cnetdb" );
		errno = ENOSYS;
		return 0;
	}

	//--------------------------------------------------------------------------------
	hostent* Cnetdb::gethostbyname( const char* )
	{
		__QCS_MEMBER_FCONTEXT( "Cnetdb::Cnetdb" );
		errno = ENOSYS;
		return 0;
	}

	//--------------------------------------------------------------------------------
	hostent* Cnetdb::gethostent( void )
	{
		__QCS_MEMBER_FCONTEXT( "Cnetdb::Cnetdb" );
		errno = ENOSYS;
		return 0;
	}

	//--------------------------------------------------------------------------------
	int Cnetdb::getnameinfo( const sockaddr*, socklen_t, char*, socklen_t, char*, socklen_t, int )
	{
		__QCS_MEMBER_FCONTEXT( "Cnetdb::Cnetdb" );
		errno = ENOSYS;
		return 0;
	}

	//--------------------------------------------------------------------------------
	netent* Cnetdb::getnetbyaddr( uint32_t, int )
	{
		__QCS_MEMBER_FCONTEXT( "Cnetdb::Cnetdb" );
		errno = ENOSYS;
		return 0;
	}

	//--------------------------------------------------------------------------------
	netent* Cnetdb::getnetbyname( const char* )
	{
		__QCS_MEMBER_FCONTEXT( "Cnetdb::Cnetdb" );
		errno = ENOSYS;
		return 0;
	}

	//--------------------------------------------------------------------------------
	netent* Cnetdb::getnetent( void )
	{
		__QCS_MEMBER_FCONTEXT( "Cnetdb::Cnetdb" );
		errno = ENOSYS;
		return 0;
	}

	//--------------------------------------------------------------------------------
	protoent* Cnetdb::getprotobyname( const char* )
	{
		__QCS_MEMBER_FCONTEXT( "Cnetdb::Cnetdb" );
		errno = ENOSYS;
		return 0;
	}

	//--------------------------------------------------------------------------------
	protoent* Cnetdb::getprotobynumber( int )
	{
		__QCS_MEMBER_FCONTEXT( "Cnetdb::Cnetdb" );
		errno = ENOSYS;
		return 0;
	}

	//--------------------------------------------------------------------------------
	protoent* Cnetdb::getprotoent( void )
	{
		__QCS_MEMBER_FCONTEXT( "Cnetdb::Cnetdb" );
		errno = ENOSYS;
		return 0;
	}

	//--------------------------------------------------------------------------------
	servent* Cnetdb::getservbyname( const char*, const char* )
	{
		__QCS_MEMBER_FCONTEXT( "Cnetdb::Cnetdb" );
		errno = ENOSYS;
		return 0;
	}

	//--------------------------------------------------------------------------------
	servent* Cnetdb::getservbyport( int, const char* )
	{
		__QCS_MEMBER_FCONTEXT( "Cnetdb::Cnetdb" );
		errno = ENOSYS;
		return 0;
	}

	//--------------------------------------------------------------------------------
	servent* Cnetdb::getservent( void )
	{
		__QCS_MEMBER_FCONTEXT( "Cnetdb::Cnetdb" );
		errno = ENOSYS;
		return 0;
	}

	//--------------------------------------------------------------------------------
	void Cnetdb::sethostent( int )
	{
		__QCS_MEMBER_FCONTEXT( "Cnetdb::Cnetdb" );
		errno = ENOSYS;
	}

	//--------------------------------------------------------------------------------
	void Cnetdb::setnetent( int )
	{
		__QCS_MEMBER_FCONTEXT( "Cnetdb::Cnetdb" );
		errno = ENOSYS;
	}

	//--------------------------------------------------------------------------------
	void Cnetdb::setprotoent( int )
	{
		__QCS_MEMBER_FCONTEXT( "Cnetdb::Cnetdb" );
		errno = ENOSYS;
	}

	//--------------------------------------------------------------------------------
	void Cnetdb::setservent( int )
	{
		__QCS_MEMBER_FCONTEXT( "Cnetdb::Cnetdb" );
		errno = ENOSYS;
	}

}//namespace nsBaseCRT
