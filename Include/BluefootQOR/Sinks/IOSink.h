//IOSink.h

// Copyright Querysoft Limited 2017
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

#ifndef BLUEFOOT_SINKS_IO_H_3
#define BLUEFOOT_SINKS_IO_H_3

#include "CompilerQOR.h"

#ifdef	__QCMP_OPTIMIZEINCLUDE
#pragma	__QCMP_OPTIMIZEINCLUDE
#endif//__QCMP_OPTIMIZEINCLUDE

//Defines an IO Sink for a Bluefoot pipeline

#include "BluefootQOR/BFSink.h"

//------------------------------------------------------------------------------
namespace nsBluefoot
{
	//------------------------------------------------------------------------------
	//A generic data sink, possibly but not necessarily representing a device.
	//Derived classes handle output to specific devices
	class __QOR_INTERFACE(__BLUEFOOTQOR) CIOSink : public CSink
	{
	public:

		typedef nsCodeQOR::CTLRef< CIOSink > refSinkType;

		//--------------------------------------------------------------------------------
		CIOSink(CPlug* pConnector = 0) : CSink()
			, m_pIOSinkConnector(pConnector)
		{
		}

		//--------------------------------------------------------------------------------
		virtual ~CIOSink()
		{
			m_pIOSinkConnector = 0;
		}

		//--------------------------------------------------------------------------------
		refSinkType SinkRef(void)
		{
			refSinkType ref(this, false);
			return ref;
		}

		//--------------------------------------------------------------------------------
		CPlug* GetSinkConnector(void)
		{
			return m_pIOSinkConnector;
		}

		//--------------------------------------------------------------------------------
		void SetSinkConnector(CPlug* pIOConnector)
		{
			m_pIOSinkConnector = pIOConnector;
		}

		virtual bool Write(unsigned long& ulNumberOfUnitsWritten, unsigned long ulNumberOfUniteToWrite) = 0;
		virtual bool Flush(void) = 0;

	protected:

		CPlug* m_pIOSinkConnector;
	};

}//nsBluefoot

#endif//BLUEFOOT_SINKS_IO_H_3