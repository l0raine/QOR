//WinQLPipeSource.h

// Copyright Querysoft Limited 2013, 2017
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

#ifndef WINQL_IO_PIPESOURCE_H_3
#define WINQL_IO_PIPESOURCE_H_3

#ifdef	__QCMP_OPTIMIZEINCLUDE
#pragma	__QCMP_OPTIMIZEINCLUDE
#endif//__QCMP_OPTIMIZEINCLUDE

#include "WinQL/Application/IO/WinQLOverlappedHandler.h"
#include "WinQL/Application/Comms/IPC/Pipe/WinQLPipe.h"
#include "WinQL/Application/IO/WinQLIOSource.h"

//--------------------------------------------------------------------------------
namespace nsWin32
{
	class __QOR_INTERFACE( __WINQL ) CPipeConnector;

	//--------------------------------------------------------------------------------
	//A Bluefoot source which reads from a Win32 Pipe connection
	class __QOR_INTERFACE( __WINQL ) CPipeSource : public CIOSource
	{
	public:

		__QOR_DECLARE_OCLASS_ID( CPipeSource );

		CPipeSource( CPipeConnector* pPipeConnector );
		virtual ~CPipeSource();

		virtual bool Read(unsigned long& ulNumberOfUnitsRead, unsigned long ulNumberOfUnitsToRead = 1);
		virtual bool IsAtEnd( void );

		virtual bool ReadAsync(unsigned long& ulNumberOfUnitsRead, unsigned long ulNumberOfUnitsToRead, byte* pBuffer);
		virtual bool ReadSync(unsigned long& ulNumberOfUnitsRead, unsigned long ulNumberOfUnitsToRead, byte* pBuffer);

	};

}//nsWin32

#endif//WINQL_IO_PIPESOURCE_H_3
