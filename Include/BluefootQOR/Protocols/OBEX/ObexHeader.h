//ObexHeader.h

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

#ifndef BLUEFOOT_OBEXHEADER_H_3
#define BLUEFOOT_OBEXHEADER_H_3

//Defines an Obex Header

#include "CodeQOR/Text/TString.h"
#include "CodeQOR/Text/Char16.h"
#include <stdint.h>

//------------------------------------------------------------------------------
namespace nsOBEX
{
	//------------------------------------------------------------------------------
	// Standard headers
	enum obex_hdr_mask
	{
		HDR_TYPE_SHIFT = 6,
		HDR_TYPE_MASK = 0xc0,
		HDR_ID_MASK = 0x3f,
	};

	//------------------------------------------------------------------------------
	// Type part of an obex header value
	enum obex_hdr_type
	{
		HDR_TYPE_INVALID = -1,								/** used as invalid return value */
		HDR_TYPE_UNICODE = (0 << HDR_TYPE_SHIFT),		/** zero terminated unicode string (network byte order) */
		HDR_TYPE_BYTES = (1 << HDR_TYPE_SHIFT),		/** byte array */
		HDR_TYPE_UINT8 = (2 << HDR_TYPE_SHIFT),		/** 8bit unsigned integer */
		HDR_TYPE_UINT32 = (3 << HDR_TYPE_SHIFT),		/** 32bit unsigned integer */
	};

	//------------------------------------------------------------------------------
	// Identifier part of an obex header value 
	enum obex_hdr_id
	{
		HDR_ID_INVALID = -1,			// used as invalid return value			
		HDR_ID_COUNT = 0,				// Number of objects (used by connect)			
		HDR_ID_NAME = 1,				// Name of the object
		HDR_ID_TYPE = 2,				// Type of the object
		HDR_ID_LENGTH = 3,				// Total length of object			
		HDR_ID_TIME = 4,				// Last modification time of (ISO8601)
		HDR_ID_DESCRIPTION = 5,		// Description of object			
		HDR_ID_TARGET = 6,				// Identifies the target for the object			
		HDR_ID_HTTP = 7,				// An HTTP 1.x header			
		HDR_ID_BODY = 8,				// Data part of the object			
		HDR_ID_BODY_END = 9,			// Last data part of the object			
		HDR_ID_WHO = 10,				// Identifies the sender of the object			
		HDR_ID_CONNECTION = 11,		// Connection identifier			
		HDR_ID_APPARAM = 12,			// Application parameters			
		HDR_ID_AUTHCHAL = 13,			// Authentication challenge			
		HDR_ID_AUTHRESP = 14,			// Authentication response			
		HDR_ID_CREATOR = 15,			// indicates the creator of an object
		HDR_ID_WANUUID = 16,			// uniquely identifies the network client (OBEX server)
		HDR_ID_OBJECTCLASS = 17,		// OBEX Object class of object
		HDR_ID_SESSIONPARAM = 18,		// Parameters used in session commands/responses
		HDR_ID_SESSIONSEQ = 19,		// Sequence number used in each OBEX packet for reliability			
		HDR_ID_ACTION_ID = 20,			// Specifies the action for the ACTION command			
		HDR_ID_DESTNAME = 21,			// Destination object name	
		HDR_ID_PERMISSIONS = 22,		// bit mask for setting permissions	
		HDR_ID_SRM = 23,				// response mode selection			
		HDR_ID_SRM_FLAGS = 24,			// flags for single response mode
	};

	//------------------------------------------------------------------------------
	typedef struct
	{
		obex_hdr_id id;
		obex_hdr_type type;
		unsigned int size;
		union
		{
			uint32_t bq4;		// use this when header type is #OBEX_HDR_TYPE_UINT32			
			uint8_t bq1;		// use this when header type is #OBEX_HDR_TYPE_UINT8
			const uint8_t *bs;	// use this when header type is #OBEX_HDR_TYPE_BYTES or #OBEX_HDR_TYPE_UNICODE
		}data;
	}obex_headerdata_t;

	//------------------------------------------------------------------------------
	class __QOR_INTERFACE( __BLUEFOOTQOR ) CHeader
	{
	public:

		__QOR_DECLARE_OCLASS_ID(CHeader);

		CHeader();
		CHeader(obex_headerdata_t& header_data);

	protected:

		obex_hdr_id m_ID;
		obex_hdr_type m_Type;
	};

	//------------------------------------------------------------------------------
	class __QOR_INTERFACE(__BLUEFOOTQOR) CConnectHeader
	{
	public:

		__QOR_DECLARE_OCLASS_ID(CHeader);

		CConnectHeader(uint8_t Version, uint8_t Flags, uint16_t MTU);

	protected:
		
		uint8_t  m_Version;
		uint8_t  m_Flags;
		uint16_t m_MTU;

	};

	//------------------------------------------------------------------------------
	class __QOR_INTERFACE(__BLUEFOOTQOR) CDescriptionHeader : public CHeader
	{
	public:

		CDescriptionHeader(obex_headerdata_t& header_data, nsCodeQOR::CUCS2String& Description);

	protected:

		nsCodeQOR::CUCS2String m_strDescription;
	};

	//------------------------------------------------------------------------------
	class __QOR_INTERFACE(__BLUEFOOTQOR) CCountHeader : public CHeader
	{
	public:

		CCountHeader(obex_headerdata_t& header_data, uint32_t Count);

	protected:

		uint32_t m_Count;
	};

	//------------------------------------------------------------------------------
	class __QOR_INTERFACE(__BLUEFOOTQOR) CLengthHeader : public CHeader
	{
	public:

		CLengthHeader(obex_headerdata_t& header_data, uint32_t Length);

	protected:

		uint32_t m_Length;
	};

	//------------------------------------------------------------------------------
	class __QOR_INTERFACE(__BLUEFOOTQOR) CConnectionIDHeader : public CHeader
	{
	public:

		CConnectionIDHeader(obex_headerdata_t& header_data, uint32_t ConnectionID);

	protected:

		uint32_t m_ConnectionID;
	};

	//------------------------------------------------------------------------------
	class __QOR_INTERFACE(__BLUEFOOTQOR) CMIMETypeHeader : public CHeader
	{
	public:

		CMIMETypeHeader(obex_headerdata_t& header_data, byte* pData);

	protected:

		nsCodeQOR::CASCIIString m_strMIMEType;
	};
	

}//nsOBEX

#endif//BLUEFOOT_OBEXHEADER_H_3
