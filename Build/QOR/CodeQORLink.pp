//CodeQORLink.pp

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

//Preprocessor build script generator for CodeQOR.dll

#include "ModuleHeader.pph"

//Set CodeQOR specific definitions and overrides

#define QOR_MODULE_NAME CodeQOR

//Include this to do any setup needed for a build such as creating folders
#include "BuildQOR/BeginLink.pph"

//Define the paths to look on for link time static dependencies
#define QOR_LIB_PATHS \
	(..\..\..\Build\%build_project%\%build_architecture%\%build_os%\%build_os_ver%\%build_form%\%build_config%\%buildtype%)\
	(D:\Tools\Microsoft Visual Studio 14.0\VC\lib)\
	(D:\Tools\Microsoft Visual Studio 14.0\VC\atlmfc\lib)\
	(C:\Program Files (x86)\Windows Kits\10\lib\10.0.10240.0\ucrt\x86)\
	(C:\Program Files (x86)\Windows Kits\8.1\lib\winv6.3\um\x86)\
	(C:\Program Files (x86)\Windows Kits\NETFXSDK\4.6.1\Lib\um\x86)

//#define QOR_PP_BUILD_LINK_SUBSYSTEM_SELECT 8
#define QOR_PP_BUILD_LINK_NODEFAULTLIB_SELECT 1

//Define the list of link time dependencies 
#define QOR_LIBS \
	(QORModule)\
	(WinCmpSupQORVC)\
	(WinSharedBootstrap)\
	(ArchQOR)\
	(CompilerQOR)\
	(SystemQOR)\
	(CQOR)\
	(AppocritaQOR)\
	(stdQOR)\
	(WinQAPI)\
	(WinQL)\
	(kernel32)


//Include this to link the outputs of the translation units compiled above into a dynamic library

#include "LinkCmd2.pph"

