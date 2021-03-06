//BfProtocol.h

// Copyright Querysoft Limited 2013, 2016, 2017
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

#ifndef BLUEFOOT_PROTOCOL_H_3
#define BLUEFOOT_PROTOCOL_H_3

//Defines a protocol

#include "CodeQOR/DataTypes/GUID.h"
#include "CodeQOR/Macros/ClassIdentityMacros.h"
#include "CodeQOR/DataStructures/TLRef.h"
#include "BfPipeline.h"
#include "AppocritaQOR/Workflow.h"
#include "AppocritaQOR/State.h"
#include "AppocritaQOR/Subsystems/Thread.h"

//------------------------------------------------------------------------------
namespace nsBluefoot
{
	
	class __QOR_INTERFACE(__BLUEFOOTQOR) CProtocol;
	/*
	
	//------------------------------------------------------------------------------
	class __QOR_INTERFACE(__BLUEFOOTQOR) CProtocolWorkflow : public nsQOR::CWorkflow
	{
	public:

		//--------------------------------------------------------------------------------
		class State : public nsQOR::CCompoundState
		{
		public:

			//--------------------------------------------------------------------------------
			State(IWorkflow::ref_type pWorkflow) : nsQOR::CCompoundState(pWorkflow) 
			{
			}

			//--------------------------------------------------------------------------------
			void SetHigherLevelWorkflow(IWorkflow::ref_type Workflow)
			{
				m_pHigherLevelWorkflow = Workflow;
			}

			virtual unsigned long GetNextReadCount(void) = 0;
			virtual unsigned long GetNextWriteCount(void) = 0;
		protected:

			IWorkflow::ref_type m_pHigherLevelWorkflow;
		};


		CProtocolWorkflow() = delete;
		CProtocolWorkflow(nsQOR::IApplication::ref_type Application) : nsQOR::CWorkflow(Application) {}
		virtual ~CProtocolWorkflow() {}
		CProtocolWorkflow(const CProtocolWorkflow& src) : nsQOR::CWorkflow(src.GetApplication()) { *this = src; }
		CProtocolWorkflow& operator = (const CProtocolWorkflow& src) { return *this; }

		//--------------------------------------------------------------------------------
		void SetHigherLevelWorkflow(IWorkflow::ref_type Workflow)
		{
			m_pHigherLevelWorkflow = Workflow;
			m_pHigherLevelWorkflow.As< CProtocolWorkflow >()->SetProtocol(m_pProtocol);
		}

		//--------------------------------------------------------------------------------
		void SetProtocol( CProtocol* pProtocol)
		{
			m_pProtocol = pProtocol;
		}

		//--------------------------------------------------------------------------------
		CProtocol* GetProtocol(void)
		{
			return m_pProtocol;
		}

		virtual unsigned long GetNextReadCount(void) { return 0; }
		virtual unsigned long GetNextWriteCount(void) { return 0; }

	protected:

		IWorkflow::ref_type m_pHigherLevelWorkflow;
		CProtocol* m_pProtocol;

	};
*/
	//------------------------------------------------------------------------------
	class __QOR_INTERFACE( __BLUEFOOTQOR ) CProtocol : public nsQOR::CWorkflow
	{
	public:

		//--------------------------------------------------------------------------------
		class CProtocolState : public nsQOR::CCompoundState
		{
		public:

			__QOR_DECLARE_OCLASS_ID(CProtocol);

			//--------------------------------------------------------------------------------
			enum eProtocolEvents
			{
				ConnectionError = 1,
				DisconnectionError,
				Connected,
				Disconnected,
				ReadError,
				ReadSuccess,
				EndOfData,
				WriteError,
				WriteSuccess
			};

			CProtocolState(IWorkflow::ref_type pWorkflow);
			bool operator()(nsQOR::IEvent::ref_type _event, int iCookie);
			//void SetHigherLevelWorkflow(IWorkflow::ref_type Workflow);

		protected:

			virtual void GetNextReadCount(void);
			virtual void GetNextWriteCount(void);

			CProtocol* m_pProtocol;
		};

		//--------------------------------------------------------------------------------
		class StoppedState : public CProtocolState
		{
		public:
			StoppedState( IWorkflow::ref_type pWorkflow  ) : CProtocolState( pWorkflow ){}
		}m_StoppedState;

		//--------------------------------------------------------------------------------
		class ReadingState : public CProtocolState
		{
		public:

			//--------------------------------------------------------------------------------
			ReadingState( IWorkflow::ref_type pWorkflow ) : CProtocolState( pWorkflow ){}

			//--------------------------------------------------------------------------------
			void OnEnter(nsQOR::IEvent::ref_type pEvent)
			{
				m_pProtocol->Read();
			}

		}m_ReadingState;
		
		//--------------------------------------------------------------------------------
		class WritingState : public CProtocolState
		{
		public:

			//--------------------------------------------------------------------------------
			WritingState( IWorkflow::ref_type pWorkflow ) : CProtocolState( pWorkflow ){}

			//--------------------------------------------------------------------------------
			void OnEnter(nsQOR::IEvent::ref_type pEvent)
			{
				m_pProtocol->Write();
			}

		}m_WritingState;

		__QOR_DECLARE_OCLASS_ID(CProtocol);

		CProtocol() = delete;
		CProtocol( nsQOR::IApplication::ref_type Application );
		virtual ~CProtocol();
		CProtocol(const CProtocol& src);
		CProtocol& operator = (const CProtocol& src);

		virtual nsQOR::IState::ref_type InitialState( void ) const;

		void SetOutPipe( CPipeline* pOutPipe );
		CPipeline* GetOutPipe( void );
		void SetInPipe( CPipeline* pInPipe );
		CPipeline* GetInPipe( void );
		void SetConnection(CPlug* pConnection);

		virtual void GetNextReadCount( void );
		virtual void GetNextWriteCount( void );

		virtual bool Read( void );
		virtual bool Write( void );

		//For the use of a protocol as a sink/source via CProtocolSink, CProtocolSource below
		virtual bool OnRead( unsigned long& ulUnitsWritten, unsigned long ulUnitsToWrite = 1 ){ return false; }
		virtual bool OnWrite( unsigned long& ulUnitsRead, unsigned long ulUnitsToRead = 1 ){ return false; }

	protected:

		unsigned long m_ulDataSize;		
		CPipeline* m_pInPipe;
		CPipeline* m_pOutPipe;
		CPlug* m_pConnection;
	};

	//--------------------------------------------------------------------------------
	class __QOR_INTERFACE( __BLUEFOOTQOR ) CProtocolSink : public CSink
	{
	public:

		//--------------------------------------------------------------------------------
		CProtocolSink( CProtocol* pProtocol ) : CSink()
		,	m_pProtocol( pProtocol )
		{
		}

		//--------------------------------------------------------------------------------
		virtual ~CProtocolSink()
		{
		}

		//--------------------------------------------------------------------------------
		virtual bool Write( unsigned long& ulUnitsWritten, unsigned long ulUnitsToWrite = 1 )
		{
			return m_pProtocol->OnWrite( ulUnitsWritten, ulUnitsToWrite );
		}

		//--------------------------------------------------------------------------------
		virtual bool Flush( void )
		{
			return false;//m_pProtocol->FlushInPipe();
		}

	protected:

		CProtocol* m_pProtocol;
	};

	//--------------------------------------------------------------------------------
	class __QOR_INTERFACE( __BLUEFOOTQOR ) CProtocolSource : public CSource
	{
	public:

		//--------------------------------------------------------------------------------
		CProtocolSource( CProtocol* pProtocol ) : CSource()
		,	m_pProtocol( pProtocol )
		{
		}

		//--------------------------------------------------------------------------------
		virtual ~CProtocolSource()
		{
		}

		//--------------------------------------------------------------------------------
		virtual bool Read( unsigned long& ulUnitsRead, unsigned long ulUnitsToRead = 1 )
		{
			return m_pProtocol->OnRead( ulUnitsToRead, ulUnitsRead );
		}

		//--------------------------------------------------------------------------------
		virtual bool Flush( void )
		{
			return false;//m_pProtocol->FlushInPipe();
		}

	protected:

		CProtocol* m_pProtocol;
	};

}//nsBluefoot

#endif//BLUEFOOT_PROTOCOL_H_3
