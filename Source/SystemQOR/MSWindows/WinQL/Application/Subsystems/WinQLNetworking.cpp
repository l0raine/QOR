//WinQLNetworking.cpp

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

//WinQL Networking Subsystem

#include "WinQL/WinQL.h"

#ifdef	__QCMP_OPTIMIZEINCLUDE
#pragma	__QCMP_OPTIMIZEINCLUDE
#endif//__QCMP_OPTIMIZEINCLUDE

#include "WinQL/Application/Subsystems/WinQLNetworking.h"
#include "WinQL/Application/WinQLApplication.h"

//--------------------------------------------------------------------------------
namespace nsWin32
{
	__QOR_IMPLEMENT_EXTERNAL_FACTORY(CNetworking, 0x2b447030, 0x1943, 0x453b, 0x98, 0xe5, 0xdf, 0xfe, 0xf7, 0x63, 0x0, 0x4a );

	//--------------------------------------------------------------------------------
	CNetworking::CNetworking() : nsQOR::INetworking()
	{
	}

	//--------------------------------------------------------------------------------
	CNetworking::~CNetworking()
	{
	}

	//--------------------------------------------------------------------------------
	void CNetworking::Setup(nsQOR::IApplication& Application)
	{
		m_WinSockSession = new_shared_ref<CWinSockSession>(MakeWord(2, 2));	
	}

	//--------------------------------------------------------------------------------
	void CNetworking::Shutdown(nsQOR::IApplication& Application)
	{
		m_WinSockSession.Dispose();
	}

}//nsWin32