//BfSocket.h

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

//An Abstract Socket

#ifndef BLUEFOOT_SOCKET_H_3
#define BLUEFOOT_SOCKET_H_3

#include "CompilerQOR.h"
#include "CodeQOR/Traits/ReferenceTraits.h"
#include "CodeQOR/DataStructures/TRef.h"
#include "CodeQOR/Tracing/FunctionContextBase.h"
#include "BluefootQOR/BfPlug.h"
#include "BluefootQOR/Socket/BfSocketInterface.h"

//------------------------------------------------------------------------------
namespace nsBluefoot
{	
	//------------------------------------------------------------------------------
	class __QOR_INTERFACE(__BLUEFOOTQOR) CSocket : public ISocket
	{
	public:

		CSocket();
		CSocket(ISocket::ref_type Impl);
		virtual ~CSocket();
		CSocket(const CSocket& src);
		CSocket& operator = (const CSocket& src);

		virtual void Create(eAddressFamily AF, eType Type, eProtocol Protocol);
		virtual int Bind(const Address& Name);
		virtual int Listen(int iBacklog);
		virtual ISocket::ref_type Accept( Address& Address );
		virtual int Connect(const Address& Address );
		virtual int GetPeerName(Address& Address);
		virtual int GetSockName(Address& Address);
		virtual int GetSockOpt(int iLevel, int iOptName, char* pOptVal, int* pOptLen);
		virtual int SetSockOpt(int iLevel, int iOptName, const char* pOptVal, int iOptLen);
		virtual int AsyncReceive(char* pBuffer, int iLen, void* pSyncObject);
		virtual int Receive(char* buf, int len, int flags);
		virtual int ReceiveFrom(char* Buffer, int iLen, int iFlags, Address& From );
		virtual int AsyncSend(char* Buffer, int iLen, void* pSyncObject);
		virtual int Send(const char* Buffer, int iLen);
		virtual int SendTo(const char* Buffer, int iLen, int iFlags, const Address& To );
		virtual int Shutdown(int iHow);
		virtual Cmp_uint_ptr ID(void);
		virtual  int GetLastError(void);

	protected:

		ISocket::ref_type m_Impl;

		eProtocol m_Protocol;
		eType m_Type;

		Address m_Address;
	};

}//nsBluefoot

#endif//BLUEFOOT_SOCKET_H_3
