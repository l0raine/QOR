//SystemQOR.h

// Copyright Querysoft Limited 2013, 2015, 2016
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

//Declarations for the SystemQOR library

#ifndef QOR_SYSTEM_H_3
#define QOR_SYSTEM_H_3

#include "SystemQOR/Config/SupportedOSList.h"	//Include the list of supported Operating Systems
#include "ArchQOR.h"							//Reference ArchQOR for Architecture base + compiler + config
#include "SystemQOR/Config/SystemSelection.h"	//Select the Operating System support to include

#ifdef QOR_SYS_SYSTEMHEADER
#	include QOR_SYS_SYSTEMHEADER					//include everything needed to support and use the selected OS
#endif

#ifdef QOR_MONOLITHIC
extern "C"
{
    extern void* __dso_handle;
}
#endif

#endif//QOR_SYSTEM_H_1
