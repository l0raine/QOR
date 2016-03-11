//Builtins.inl

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

//These intrinsic functions which are always available with MSVC 9
//and will become members of the CCompiler class

#include "../VS2003/Builtins.inl"

#ifndef	QOR_MONOLITHIC

//--------------------------------------------------------------------------------
#pragma intrinsic(_byteswap_ushort)
//--------------------------------------------------------------------------------
unsigned short CCompiler::_byteswap_ushort( unsigned short value )
{
	return ::_byteswap_ushort(value);
}

//--------------------------------------------------------------------------------
#pragma intrinsic(_byteswap_ulong)
//--------------------------------------------------------------------------------
unsigned long CCompiler::_byteswap_ulong( unsigned long value )
{
	return ::_byteswap_ulong(value);
}

//--------------------------------------------------------------------------------
#pragma intrinsic(_byteswap_uint64)
//--------------------------------------------------------------------------------
CCompiler::mxc_unsigned__int64 CCompiler::_byteswap_uint64( CCompiler::mxc_unsigned__int64 value )
{
	return::_byteswap_uint64(value);
}

//--------------------------------------------------------------------------------
#pragma intrinsic(__debugbreak)
//--------------------------------------------------------------------------------
void CCompiler::__debugbreak( void )
{
	::__debugbreak();
}

//--------------------------------------------------------------------------------
#pragma intrinsic(_lrotl)
//--------------------------------------------------------------------------------
unsigned long CCompiler::_lrotl( unsigned long ul, int i )
{
	return ::_lrotl( ul, i );
}

//--------------------------------------------------------------------------------
#pragma intrinsic(strset)
//--------------------------------------------------------------------------------
CCompiler::mxc_char* CCompiler::strset( CCompiler::mxc_char* psz, CCompiler::mxc_int i )
{
	return ::strset( psz, i );
}

//--------------------------------------------------------------------------------
#pragma intrinsic(_rotl64)
//--------------------------------------------------------------------------------
CCompiler::mxc_unsigned__int64	CCompiler::_rotl64( CCompiler::mxc_unsigned__int64 ui64, CCompiler::mxc_int i )
{
	return ::_rotl64( ui64, i );
}

//--------------------------------------------------------------------------------
#pragma intrinsic(_rotr64)
//--------------------------------------------------------------------------------
CCompiler::mxc_unsigned__int64	CCompiler::_rotr64( CCompiler::mxc_unsigned__int64 ui64, CCompiler::mxc_int i )
{
	return ::_rotr64( ui64, i );
}

//--------------------------------------------------------------------------------
#pragma intrinsic(_abs64)
//--------------------------------------------------------------------------------
CCompiler::mxc__int64 CCompiler::_abs64( CCompiler::mxc__int64 i64 )
{
	return ::_abs64( i64 );
}

#endif//QOR_MONOLITHIC