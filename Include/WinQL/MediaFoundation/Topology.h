//Topology.h

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

#ifndef WINQL_MEDIAFOUND_TOPOLOGY_H_3
#define WINQL_MEDIAFOUND_TOPOLOGY_H_3

#ifdef	__QCMP_OPTIMIZEINCLUDE
#pragma	__QCMP_OPTIMIZEINCLUDE
#endif//__QCMP_OPTIMIZEINCLUDE

#include "WinQL/MediaFoundation/MediaFoundation.h"
#include "WinQL/MediaFoundation/MediaType.h"

//--------------------------------------------------------------------------------
namespace nsWin32
{
	//--------------------------------------------------------------------------------
	namespace nsMediaFoundation
	{
		//--------------------------------------------------------------------------------
		//A topology describes a collection of media sources, sinks, and transforms that are connected in a certain order
		//A topology describes the path of multimedia data through these nodes represented by TopologyNode(s)
		class __QOR_INTERFACE(__WINQL_MEDIA) CTopology : public CTMediaFoundationObject< IMFTopology >
		{
		public:

			__QOR_DECLARE_OCLASS_ID( CTopology );

			CTopology();	//Create an empty topology
			CTopology( IMFMediaSource* pSrc, const wchar_t* pwszOutputFilePath, IMFTranscodeProfile* pProfile );//Create a transcode topology
			virtual ~CTopology();

		private:

			CTopology( CTopology& );
			CTopology& operator = ( const CTopology& );
		};

		//--------------------------------------------------------------------------------
		class __QOR_INTERFACE(__WINQL_MEDIA) CTopologyNode : public CTMediaFoundationObject< IMFTopologyNode >
		{
		public:

			__QOR_DECLARE_OCLASS_ID( CTopologyNode );

			CTopologyNode( MF_TOPOLOGY_TYPE NodeType );
			virtual ~CTopologyNode();
			CMediaType GetCurrentType( unsigned long dwStreamIndex, int fOutput );

		private:

			CTopologyNode();
			CTopologyNode( const CTopologyNode& );
			CTopologyNode& operator = ( const CTopologyNode& );
		};

	}//nsMediaFoundation

}//nsWin32

#endif//WINQL_MEDIAFOUND_TOPOLOGY_H_3

