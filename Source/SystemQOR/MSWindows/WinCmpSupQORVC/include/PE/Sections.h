//Sections.h

// Copyright Querysoft Limited 2013
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

//Set up the PE image sections for IA64 builds

#ifndef WINCMPSUPVC_SECTIONS_H_1
#define WINCMPSUPVC_SECTIONS_H_1

#ifdef _M_IA64

	#pragma section(".CRT$XCA",long,read)
	#pragma section(".CRT$XCAA",long,read)
	#pragma section(".CRT$XCC",long,read)
	#pragma section(".CRT$XCZ",long,read)
	#pragma section(".CRT$XIA",long,read)
	#pragma section(".CRT$XIC",long,read)
	#pragma section(".CRT$XIY",long,read)
	#pragma section(".CRT$XIZ",long,read)
	#pragma section(".CRT$XLA",long,read)
	#pragma section(".CRT$XLZ",long,read)
	#pragma section(".CRT$XPA",long,read)
	#pragma section(".CRT$XPX",long,read)
	#pragma section(".CRT$XPZ",long,read)
	#pragma section(".CRT$XTA",long,read)
	#pragma section(".CRT$XTB",long,read)
	#pragma section(".CRT$XTX",long,read)
	#pragma section(".CRT$XTZ",long,read)
	#pragma section(".rdata$T",long,read)
	#pragma section(".rtc$IAA",long,read)
	#pragma section(".rtc$IZZ",long,read)
	#pragma section(".rtc$TAA",long,read)
	#pragma section(".rtc$TZZ",long,read)

	#define _CRTALLOC(x) __declspec(allocate(x))

#else 

	#define _CRTALLOC(x)

#endif 

#endif//WINCMPSUPVC_SECTIONS_H_1
