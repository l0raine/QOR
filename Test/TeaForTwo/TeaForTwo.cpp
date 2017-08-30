//TeaForTwo.cpp

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

//Minimal test application for Strata-1 qualification

#include "SystemQOR.h"
#include "SystemQOR/MSWindows/MSW_tchar.h"

//------------------------------------------------------------------------------
int _tmain( int /*argc*/, TCHAR** /*argv*/)
{
    return 42;
}

/*
To reach the main function above and return 42 to the calling process via the OS 
the QOR framework must bootstrap successfully and shutdown reasonably cleanly.
This is the purpose of the test to ensure that the essential elements of the QOR
can be compiled for, loaded and initialised on the target system.


For example the loading and initialisation process on a Windows target is a two 
pass algortihm as follows...

The OS creates our process memory space and possibly loads the main TeaForTwo.exe
binary file but doesn't yet call any entry point on it.
Implicitly linked Dlls are loaded (Kernel32.dll first even if we don't ask for it)
and each one is initialised by calling the entry point 

__QCMP_NOINLINE int __stdcall _DllMainCRTStartup( void* hDllHandle, unsigned long ulReason, void* pReserved )

which is in the WinSharedBootstrap.lib static library.

This is why WinSharedBootstrap.lib must be linked into all QOR shared libraries.

_DllMainCRTStartup sets up the Stack Security Cookie and Structured Exception Handling
and the creates a CWinQORSharedBootStrap object on the Default Process Heap.

Constructing a CWinQORSharedBootStrap sets up the atexit chain for functions to be called
before the Dll is unloaded. The Module base class of the SharedBootStrap also represents
the loaded module from now on until it is unloaded.

When all implicitly linked libraries have been initialized like this the OS loader calls
the entry point on the TeaForTwo executable.

__QCMP_LINKAGE_C int __cdecl _tMainCRTStartup( void )

This is provided by the WinUsrExeBootCon.lib static library, which is why WinUsrExeBootCon must
be linked into all QOR Windows Console executables.
This is the end of the first pass which is under the control of Windows.

The _tMainCRTStartup function creates a CBootStrap object on the stack and calls its Execute 
function.

As it's being created the CBootStrap object gets from the OS a list of the modules that
have already been loaded into the process. It walks through the list looking for QOR
modules which are identified by having an entry point like this.

__QCMP_EXPORT nsCodeQOR::mxGUID* QORidentity( void )

This function which is implemented in the main file of each QOR module provides a unique
identifier ( a 128-bit number ) for each QOR module.

The list of QOR modules is reordered according to a table of dependencies between them
and then each QOR module is called through the entry point

__QCMP_EXPORT int QORinit( void )

which is provided by the WinSharedBootstrap static library. This looks up the Module
object created in the first pass initialisation, the CWinQORSharedBootStrap and calls 
the InitStatic() function on it.

All static objects for the module are now created.

When this has been done for all the loaded QOR modules the static objects in the main
executable are initialised.

The CBootStrap object is now fully constructed and the second pass is almost complete.

CBootStrap::Execute is called which sets up Structured Exception Handling and calls
the application main function above.

This two pass initialisation allows statics in the application to depend on QOR framework
statics by gaurenteeing the coarse order of initialisation of static objects between libraries.
This also enables the overall application to be self aware to the extent of being able to enumare
the modules and libraries of which it is composed at runtime.

*/

