//ArchitectureSelection.h

// Copyright Querysoft Limited 2013, 2015
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

//Select the basic target architecture

#ifndef ARCHQOR_ARCHITECTURESELECTION_H_1
#define ARCHQOR_ARCHITECTURESELECTION_H_1

#include "Architectures.h"

#ifdef QOR_ARCHITECTURE
#	define QOR_ARCH QOR_PP_CAT(QOR_ARCH_,QOR_ARCHITECTURE)
#else
#	include "ArchQOR/Common/ArchitectureDetection.h"
#endif

#if (QOR_ARCH == QOR_ARCH_X86_32)
#	define QOR_ARCH_ROOT_FOLDER	x86
#elif (QOR_ARCH	== QOR_ARCH_X86_64)
#	define QOR_ARCH_ROOT_FOLDER	x86
#elif (QOR_ARCH == QOR_ARCH_Z)
#	define QOR_ARCH_ROOT_FOLDER	Zarch
#elif (QOR_ARCH == QOR_ARCH_SYS390)
#	define QOR_ARCH_ROOT_FOLDER	SYS390
#elif (QOR_ARCH == QOR_ARCH_SYS370)
#	define QOR_ARCH_ROOT_FOLDER	SYS370
#elif (QOR_ARCH == QOR_ARCH_SUPERH)
#	define QOR_ARCH_ROOT_FOLDER	SuperH
#elif (QOR_ARCH == QOR_ARCH_SPARC)
#	define QOR_ARCH_ROOT_FOLDER	Sparc
#elif (QOR_ARCH == QOR_ARCH_RS6K)
#	define QOR_ARCH_ROOT_FOLDER	RS6000
#elif (QOR_ARCH == QOR_ARCH_PYRAMID)
#	define QOR_ARCH_ROOT_FOLDER	Pyramid
#elif (QOR_ARCH == QOR_ARCH_PPC)
#	define QOR_ARCH_ROOT_FOLDER	PPC
#elif (QOR_ARCH == QOR_ARCH_PARISC)
#	define QOR_ARCH_ROOT_FOLDER	PARISC
#elif (QOR_ARCH	== QOR_ARCH_MIPS)
#	define QOR_ARCH_ROOT_FOLDER	MIPS
#elif (QOR_ARCH	== QOR_ARCH_M68K)
#	define QOR_ARCH_ROOT_FOLDER	M68K
#elif (QOR_ARCH	== QOR_ARCH_IA64)
#	define QOR_ARCH_ROOT_FOLDER	IA64
#elif (QOR_ARCH == QOR_ARCH_CONVEX)
#	define QOR_ARCH_ROOT_FOLDER	Convex
#elif (QOR_ARCH	== QOR_ARCH_BLACKFIN)
#	define QOR_ARCH_ROOT_FOLDER	Blackfin
#elif (QOR_ARCH == QOR_ARCH_ARM)
#	define QOR_ARCH_ROOT_FOLDER	Arm
#elif (QOR_ARCH == QOR_ARCH_ALPHA)
#	define QOR_ARCH_ROOT_FOLDER	Alpha
#else
#	error Target architecture could not be determine from host compiler predefinitions or is not supported. define QOR_ARCHITECTURE or modify __FILE__:
#endif

#	define QOR_ARCH_VERSION_INCLUDE QOR_PP_STRINGIZE( QOR_PP_CAT(ArchQOR/,QOR_PP_CAT(QOR_ARCH_ROOT_FOLDER,QOR_PP_CAT(/,QOR_PP_CAT(QOR_ARCH_ROOT_FOLDER,Version.h)))) )
#	define QOR_ARCH_CLASS_INCLUDE QOR_PP_STRINGIZE( QOR_PP_CAT(ArchQOR/,QOR_PP_CAT(QOR_ARCH_ROOT_FOLDER,QOR_PP_CAT(/,QOR_PP_CAT(QOR_ARCH_ROOT_FOLDER,.h)))) )

#include QOR_ARCH_VERSION_INCLUDE

/*
__QCMP_MESSAGE( "Target Architecture " QOR_ARCH_NAME )

#include "ArchQOR/Common/WordSizeSelection.h"
#include QOR_ARCH_CLASS_INCLUDE
*/
#endif//ARCHQOR_ARCHITECTURESELECTION_H_1
