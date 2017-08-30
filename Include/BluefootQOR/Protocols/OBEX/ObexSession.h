//ObexSession.h

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

#ifndef BLUEFOOT_OBEXSESSION_H_3
#define BLUEFOOT_OBEXSESSION_H_3

//Defines an Obex Session

#include "BluefootQOR/Protocols/OBEX/ObexObject.h"

//------------------------------------------------------------------------------
namespace nsOBEX
{
	//------------------------------------------------------------------------------
	// Possible modes
	enum mode
	{
		MODE_CLIENT = 0, /**< client mode */
		MODE_SERVER = 1, /**< server mode */
	};

	//------------------------------------------------------------------------------
	class __QOR_INTERFACE(__BLUEFOOTQOR) CSession
	{
	public:
		CSession();
		~CSession();

		CObject& Object(void);

		//------------------------------------------------------------------------------
		void SetSingleResponseMode(bool bSingleResponseMode = true)
		{

		}

		//------------------------------------------------------------------------------
		void InitializeClientSession(void)
		{

		}

		//------------------------------------------------------------------------------
		void InitializeServerSession(void)
		{

		}

		//------------------------------------------------------------------------------
		void Connect(void)
		{
			//Make an outgoing conneciton from Client by sending CONNECT object
			m_Object.AddHeader(new CConnectHeader(m_scucVersion, 0, mtu_rx));
		}

	protected:

		uint16_t mtu_tx;			// Maximum OBEX TX packet size
		uint16_t mtu_rx;			// Maximum OBEX RX packet size
		uint16_t mtu_tx_max;		// Maximum TX we can accept

		obex_rsp_mode m_ResponseMode;		// OBEX_RSP_MODE_

		unsigned int init_flags;
		unsigned int srm_flags;		// Flags for single response mode

		static const unsigned char m_scucVersion = 0x10;
		CObject m_Object;
	};

}//nsOBEX

#endif//BLUEFOOT_OBEXSESSION_H_3
