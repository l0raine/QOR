//ArchQOR.pp

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

//Preprocessor build script generator for ArchQOR.dll

#include "ModuleHeader.pph"

//Set ArchQOR specific definitions and overrides

#define QOR_MODULE_NAME ArchQOR

//Append the module specific PP defines to the list from the Operating System
#define QOR_CONFIG_DEFINES_ARCHQOR1 QOR_PP_LIST_APPEND( QOR_CONFIG_DEFINES_OS,("__ARCHQOR") )
#define QOR_CONFIG_DEFINES_ARCHQOR2 QOR_PP_LIST_APPEND( QOR_CONFIG_DEFINES_ARCHQOR1,("_LIBCPP_DLL") )
#define QOR_CONFIG_DEFINES_MODULE QOR_PP_LIST_APPEND( QOR_CONFIG_DEFINES_ARCHQOR2,("") )


#define QOR_CONFIG_INCLUDES (../../../include)\
(D:\Tools\Microsoft Visual Studio 14.0\VC\include)\
(D:\Tools\Microsoft Visual Studio 14.0\VC\atlmfc\include)\
(C:\Program Files (x86)\Windows Kits\10\Include\10.0.10240.0\ucrt)\
(C:\Program Files (x86)\Windows Kits\8.1\Include\um)\
(C:\Program Files (x86)\Windows Kits\8.1\Include\shared)\
(C:\Program Files (x86)\Windows Kits\8.1\Include\winrt)

#define QOR_PP_BUILD_CMP_IGNORE_STANDARD_INC_SELECT 1
#define QOR_PP_BUILD_CMP_CPP_EXCEPTIONS_SELECT 1
#define QOR_PP_BUILD_CMP_BUFFER_SECURITY_SELECT 1
#define QOR_PP_BUILD_CMP_RUNTIME_CHECKS_SELECT 4

//Include this to do any setup needed for a build such as creating folders
#include "BuildQOR/BeginBuild.pph"

//For each group of files that have the same folder and build options, define a group of sources

#define SOURCE_PATH ../../../Source/ArchQOR/
#define SOURCES (ArchQOR)\
				(Machine)

#include "BuildQOR/BuildGroup.pph"

#define SOURCE_PATH ../../../Source/ArchQOR/Common/
#define SOURCES (Logic)

#include "BuildQOR/BuildGroup.pph"

#define SOURCE_PATH ../../../Source/ArchQOR/Common/Assembler/
#define SOURCES (AsmBuffer)\
				(Assembler)\
				(CodeGenerator)\
				(Logger)\
				(MemoryManager)\
				(MemoryManagerPrivate)\
				(MemoryMarker)\
				(VirtualMemory)\
				(VirtualMemoryManager)\
				(Zone)

#include "BuildQOR/BuildGroup.pph"

#define SOURCE_PATH ../../../Source/ArchQOR/Common/Assembler/BatchCPU/
#define SOURCES (CPUBase)\
				(FPUBase)\
				(GPUBase)\
				(ISetExtension)

#include "BuildQOR/BuildGroup.pph"

#define SOURCE_PATH ../../../Source/ArchQOR/Common/HLAssembler/
#define SOURCES (EAlign)\
				(EComment)\
				(EData)\
				(EDummy)\
				(EFunctionEnd)\
				(Emittable)\
				(FunctionDefinition)\
				(HighLevelAssemblerBase)

#include "BuildQOR/BuildGroup.pph"

#if( QOR_ARCH == QOR_ARCH_X86_32 )

#	define SOURCE_PATH ../../../Source/ArchQOR/x86/
#	define SOURCES	(CPUInfo)\
					(VendorPackage)\
					(x86Logic)\
					(x86PCDefs)

#	include "BuildQOR/BuildGroup.pph"

#	define SOURCE_PATH ../../../Source/ArchQOR/x86/Assembler/
#	define SOURCES	(Defs)

#	include "BuildQOR/BuildGroup.pph"

#	define SOURCE_PATH ../../../Source/ArchQOR/x86/Assembler/BatchCPU/
#	define SOURCES	(i086CPU)\
					(i186CPU)\
					(i286CPU)\
					(i386CPU)\
					(i486CPU)\
					(i586CPU)\
					(i686CPU)\
					(i786CPU)\
					(InstEmitter)\
					(x86CPUCore)\
					(x86ISetExtension)
#	include "BuildQOR/BuildGroup.pph"

#	define SOURCE_PATH ../../../Source/ArchQOR/x86/Assembler/BatchCPU/Extensions/
#	define SOURCES	(3DNow)\
					(i387FPU)\
					(MMX)\
					(SSE)\
					(SSE2)\
					(SSE3)
#	include "BuildQOR/BuildGroup.pph"

#	define SOURCE_PATH ../../../Source/ArchQOR/x86/Assembler/Operands/
#	define SOURCES	(Imm)\
					(Label)\
					(Mem)\
					(Operand)
#	include "BuildQOR/BuildGroup.pph"

#	define SOURCE_PATH ../../../Source/ArchQOR/x86/Assembler/Operands/Registers/
#	define SOURCES	(BaseReg)\
					(GPReg)\
					(MMReg)\
					(SegmentReg)\
					(x87Reg)\
					(XMMReg)
#	include "BuildQOR/BuildGroup.pph"

#	define SOURCE_PATH ../../../Source/ArchQOR/x86/Assembler/Operands/Variables/
#	define SOURCES	(BaseVar)\
					(GPVar)\
					(MMVar)\
					(x87Var)\
					(XMMVar)
#	include "BuildQOR/BuildGroup.pph"

#	define SOURCE_PATH ../../../Source/ArchQOR/x86/HLAssembler/
#	define SOURCES	(FunctionPrototype)\
					(HLAssembler)\
					(x86HLAContext)\
					(x86HLAIntrinsics)\
					(x86HLAssembler)
#	include "BuildQOR/BuildGroup.pph"

#	define SOURCE_PATH ../../../Source/ArchQOR/x86/HLAssembler/Emittables/
#	define SOURCES	(ECall)\
					(EEpilog)\
					(EFunction)\
					(EInstruction)\
					(EJmp)\
					(EProlog)\
					(ERet)\
					(ETarget)\
					(EVariableHint)
#	include "BuildQOR/BuildGroup.pph"
#endif

//Generate the export and import libraries for the module where the linker will require them
#include "LibCmd2.pph"
