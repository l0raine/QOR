//3DNow.cpp

// Copyright (c) 2008-2010, Petr Kobalicek <kobalicek.petr@gmail.com>
// Copyright (c) Querysoft Limited 2016
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

//Implement 3DNow extensions

#include "ArchQOR.h"

#if		( QOR_ARCH == QOR_ARCH_X86_32 || QOR_ARCH == QOR_ARCH_X86_64 )

#include "ArchQOR/x86/Assembler/BatchCPU/Extensions/3DNow.h"

//------------------------------------------------------------------------------
namespace nsArch
{
	namespace nsx86
	{
		//------------------------------------------------------------------------------
		C3DNOW::C3DNOW( Cx86CPUCore& refCPU ) : Cx86ISetExtension( refCPU )
		{
		}

		//------------------------------------------------------------------------------
		C3DNOW::~C3DNOW()
		{
		}

		//------------------------------------------------------------------------------
		//Faster EMMS (3dNow!).
		// Note Use only for early AMD processors where is only 3dNow! or SSE. If
		// CPU contains SSE2, it's better to use emms() ( femms() is mapped
		// to emms() ).
		void C3DNOW::femms()
		{
			m_PU._emitInstruction( INST_FEMMS );
		}

		//------------------------------------------------------------------------------
		//Packed SP-FP to Integer Convert (3dNow!).
		void C3DNOW::pf2id( const CMMReg& dst, const CMMReg& src )
		{
			m_PU._emitInstruction( INST_PF2ID, &dst, &src );
		}

		//------------------------------------------------------------------------------
		//Packed SP-FP to Integer Convert (3dNow!).
		void C3DNOW::pf2id( const CMMReg& dst, const CMem& src )
		{
			m_PU._emitInstruction( INST_PF2ID, &dst, &src );
		}

		//------------------------------------------------------------------------------
		// Packed SP-FP to Integer Word Convert (3dNow!).
		void C3DNOW::pf2iw( const CMMReg& dst, const CMMReg& src )
		{
			m_PU._emitInstruction( INST_PF2IW, &dst, &src );
		}

		//------------------------------------------------------------------------------
		// Packed SP-FP to Integer Word Convert (3dNow!).
		void C3DNOW::pf2iw( const CMMReg& dst, const CMem& src )
		{
			m_PU._emitInstruction( INST_PF2IW, &dst, &src );
		}

		//------------------------------------------------------------------------------
		//Packed SP-FP Accumulate (3dNow!).
		void C3DNOW::pfacc( const CMMReg& dst, const CMMReg& src )
		{
			m_PU._emitInstruction( INST_PFACC, &dst, &src );
		}

		//------------------------------------------------------------------------------
		//Packed SP-FP Accumulate (3dNow!).
		void C3DNOW::pfacc( const CMMReg& dst, const CMem& src )
		{
			m_PU._emitInstruction( INST_PFACC, &dst, &src );
		}

		//------------------------------------------------------------------------------
		//Packed SP-FP Addition (3dNow!).
		void C3DNOW::pfadd( const CMMReg& dst, const CMMReg& src )
		{
			m_PU._emitInstruction( INST_PFADD, &dst, &src );
		}

		//------------------------------------------------------------------------------
		//Packed SP-FP Addition (3dNow!).
		void C3DNOW::pfadd( const CMMReg& dst, const CMem& src )
		{
			m_PU._emitInstruction( INST_PFADD, &dst, &src );
		}

		//------------------------------------------------------------------------------
		//Packed SP-FP Compare - dst == src (3dNow!).
		void C3DNOW::pfcmpeq( const CMMReg& dst, const CMMReg& src )
		{
			m_PU._emitInstruction( INST_PFCMPEQ, &dst, &src );
		}

		//------------------------------------------------------------------------------
		//Packed SP-FP Compare - dst == src (3dNow!).
		void C3DNOW::pfcmpeq( const CMMReg& dst, const CMem& src )
		{
			m_PU._emitInstruction( INST_PFCMPEQ, &dst, &src );
		}

		//------------------------------------------------------------------------------
		//Packed SP-FP Compare - dst >= src (3dNow!).
		void C3DNOW::pfcmpge( const CMMReg& dst, const CMMReg& src )
		{
			m_PU._emitInstruction( INST_PFCMPGE, &dst, &src );
		}

		//------------------------------------------------------------------------------
		//Packed SP-FP Compare - dst >= src (3dNow!).
		void C3DNOW::pfcmpge( const CMMReg& dst, const CMem& src )
		{
			m_PU._emitInstruction( INST_PFCMPGE, &dst, &src );
		}

		//------------------------------------------------------------------------------
		//Packed SP-FP Compare - dst > src (3dNow!).
		void C3DNOW::pfcmpgt( const CMMReg& dst, const CMMReg& src )
		{
			m_PU._emitInstruction( INST_PFCMPGT, &dst, &src );
		}

		//------------------------------------------------------------------------------
		//Packed SP-FP Compare - dst > src (3dNow!).
		void C3DNOW::pfcmpgt( const CMMReg& dst, const CMem& src )
		{
			m_PU._emitInstruction( INST_PFCMPGT, &dst, &src );
		}

		//------------------------------------------------------------------------------
		//Packed SP-FP Maximum (3dNow!).
		void C3DNOW::pfmax( const CMMReg& dst, const CMMReg& src )
		{
			m_PU._emitInstruction( INST_PFMAX, &dst, &src );
		}

		//------------------------------------------------------------------------------
		//Packed SP-FP Maximum (3dNow!).
		void C3DNOW::pfmax( const CMMReg& dst, const CMem& src )
		{
			m_PU._emitInstruction( INST_PFMAX, &dst, &src );
		}

		//------------------------------------------------------------------------------
		//Packed SP-FP Minimum (3dNow!).
		void C3DNOW::pfmin( const CMMReg& dst, const CMMReg& src )
		{
			m_PU._emitInstruction( INST_PFMIN, &dst, &src );
		}

		//------------------------------------------------------------------------------
		//Packed SP-FP Minimum (3dNow!).
		void C3DNOW::pfmin( const CMMReg& dst, const CMem& src )
		{
			m_PU._emitInstruction( INST_PFMIN, &dst, &src );
		}

		//------------------------------------------------------------------------------
		//Packed SP-FP Multiply (3dNow!).
		void C3DNOW::pfmul( const CMMReg& dst, const CMMReg& src )
		{
			m_PU._emitInstruction( INST_PFMUL, &dst, &src );
		}

		//------------------------------------------------------------------------------
		//Packed SP-FP Multiply (3dNow!).
		void C3DNOW::pfmul( const CMMReg& dst, const CMem& src )
		{
			m_PU._emitInstruction( INST_PFMUL, &dst, &src );
		}

		//------------------------------------------------------------------------------
		//Packed SP-FP Negative Accumulate (3dNow!).
		void C3DNOW::pfnacc( const CMMReg& dst, const CMMReg& src )
		{
			m_PU._emitInstruction( INST_PFNACC, &dst, &src );
		}

		//------------------------------------------------------------------------------
		//Packed SP-FP Negative Accumulate (3dNow!).
		void C3DNOW::pfnacc( const CMMReg& dst, const CMem& src )
		{
			m_PU._emitInstruction( INST_PFNACC, &dst, &src );
		}

		//------------------------------------------------------------------------------
		//Packed SP-FP Mixed Accumulate (3dNow!).
		void C3DNOW::pfpnaxx( const CMMReg& dst, const CMMReg& src )
		{
			m_PU._emitInstruction( INST_PFPNACC, &dst, &src );
		}

		//------------------------------------------------------------------------------
		//Packed SP-FP Mixed Accumulate (3dNow!).
		void C3DNOW::pfpnacc( const CMMReg& dst, const CMem& src )
		{
			m_PU._emitInstruction( INST_PFPNACC, &dst, &src );
		}

		//------------------------------------------------------------------------------
		//Packed SP-FP Reciprocal Approximation (3dNow!).
		void C3DNOW::pfrcp( const CMMReg& dst, const CMMReg& src )
		{
			m_PU._emitInstruction( INST_PFRCP, &dst, &src );
		}

		//------------------------------------------------------------------------------
		//Packed SP-FP Reciprocal Approximation (3dNow!).
		void C3DNOW::pfrcp( const CMMReg& dst, const CMem& src )
		{
			m_PU._emitInstruction( INST_PFRCP, &dst, &src );
		}

		//------------------------------------------------------------------------------
		//Packed SP-FP Reciprocal, First Iteration Step (3dNow!).
		void C3DNOW::pfrcpit1( const CMMReg& dst, const CMMReg& src )
		{
			m_PU._emitInstruction( INST_PFRCPIT1, &dst, &src );
		}

		//------------------------------------------------------------------------------
		//Packed SP-FP Reciprocal, First Iteration Step (3dNow!).
		void C3DNOW::pfrcpit1( const CMMReg& dst, const CMem& src )
		{
			m_PU._emitInstruction( INST_PFRCPIT1, &dst, &src );
		}

		//------------------------------------------------------------------------------
		//Packed SP-FP Reciprocal, Second Iteration Step (3dNow!).
		void C3DNOW::pfrcpit2( const CMMReg& dst, const CMMReg& src )
		{
			m_PU._emitInstruction( INST_PFRCPIT2, &dst, &src );
		}

		//------------------------------------------------------------------------------
		//Packed SP-FP Reciprocal, Second Iteration Step (3dNow!).
		void C3DNOW::pfrcpit2( const CMMReg& dst, const CMem& src )
		{
			m_PU._emitInstruction( INST_PFRCPIT2, &dst, &src );
		}

		//------------------------------------------------------------------------------
		//Packed SP-FP Reciprocal Square Root, First Iteration Step (3dNow!).
		void C3DNOW::pfrsqit1( const CMMReg& dst, const CMMReg& src )
		{
			m_PU._emitInstruction( INST_PFRSQIT1, &dst, &src );
		}

		//------------------------------------------------------------------------------
		//Packed SP-FP Reciprocal Square Root, First Iteration Step (3dNow!).
		void C3DNOW::pfrsqit1( const CMMReg& dst, const CMem& src )
		{
			m_PU._emitInstruction( INST_PFRSQIT1, &dst, &src );
		}

		//------------------------------------------------------------------------------
		//Packed SP-FP Reciprocal Square Root Approximation (3dNow!).
		void C3DNOW::pfrsqrt( const CMMReg& dst, const CMMReg& src )
		{
			m_PU._emitInstruction( INST_PFRSQRT, &dst, &src );
		}

		//------------------------------------------------------------------------------
		//Packed SP-FP Reciprocal Square Root Approximation (3dNow!).
		void C3DNOW::pfrsqrt( const CMMReg& dst, const CMem& src )
		{
			m_PU._emitInstruction( INST_PFRSQRT, &dst, &src );
		}

		//------------------------------------------------------------------------------
		//Packed SP-FP Subtract (3dNow!).
		void C3DNOW::pfsub( const CMMReg& dst, const CMMReg& src )
		{
			m_PU._emitInstruction( INST_PFSUB, &dst, &src );
		}

		//------------------------------------------------------------------------------
		//Packed SP-FP Subtract (3dNow!).
		void C3DNOW::pfsub( const CMMReg& dst, const CMem& src )
		{
			m_PU._emitInstruction( INST_PFSUB, &dst, &src );
		}

		//------------------------------------------------------------------------------
		//Packed SP-FP Reverse Subtract (3dNow!).
		void C3DNOW::pfsubr( const CMMReg& dst, const CMMReg& src )
		{
			m_PU._emitInstruction( INST_PFSUBR, &dst, &src );
		}

		//------------------------------------------------------------------------------
		//Packed SP-FP Reverse Subtract (3dNow!).
		void C3DNOW::pfsubr( const CMMReg& dst, const CMem& src )
		{
			m_PU._emitInstruction( INST_PFSUBR, &dst, &src );
		}

		//------------------------------------------------------------------------------
		//Packed DWords to SP-FP (3dNow!).
		void C3DNOW::pi2fd( const CMMReg& dst, const CMMReg& src )
		{
			m_PU._emitInstruction( INST_PI2FD, &dst, &src );
		}

		//------------------------------------------------------------------------------
		//Packed DWords to SP-FP (3dNow!).
		void C3DNOW::pi2fd( const CMMReg& dst, const CMem& src )
		{
			m_PU._emitInstruction( INST_PI2FD, &dst, &src );
		}

		//------------------------------------------------------------------------------
		//Packed Words to SP-FP (3dNow!).
		void C3DNOW::pi2fw( const CMMReg& dst, const CMMReg& src )
		{
			m_PU._emitInstruction( INST_PI2FW, &dst, &src );
		}

		//------------------------------------------------------------------------------
		//Packed Words to SP-FP (3dNow!).
		void C3DNOW::pi2fw( const CMMReg& dst, const CMem& src )
		{
			m_PU._emitInstruction( INST_PI2FW, &dst, &src );
		}

		//------------------------------------------------------------------------------
		//Packed swap DWord (3dNow!)
		void C3DNOW::pswapd( const CMMReg& dst, const CMMReg& src )
		{
			m_PU._emitInstruction( INST_PSWAPD, &dst, &src );
		}

		//------------------------------------------------------------------------------
		//Packed swap DWord (3dNow!)
		void C3DNOW::pswapd( const CMMReg& dst, const CMem& src )
		{
			m_PU._emitInstruction( INST_PSWAPD, &dst, &src );
		}

		// [AMD only]		

		//Prefetch (3dNow - Amd).
		//
		// Loads the entire 64-byte aligned memory sequence containing the
		// specified memory address into the L1 data cache. The position of
		// the specified memory address within the 64-byte cache line is
		// irrelevant. If a cache hit occurs, or if a memory fault is detected,
		// no bus cycle is initiated and the instruction is treated as a NOP.
		void C3DNOW::amd_prefetch( const CMem& mem )
		{
			m_PU._emitInstruction( INST_AMD_PREFETCH, &mem );
		}

		//------------------------------------------------------------------------------
		//Prefetch and set cache to modified (3dNow - Amd).
		//
		// The PREFETCHW instruction loads the prefetched line and sets the
		// cache-line state to Modified, in anticipation of subsequent data
		// writes to the line. The PREFETCH instruction, by contrast, typically
		// sets the cache-line state to Exclusive (depending on the hardware
		// implementation).
		void C3DNOW::amd_prefetchw( const CMem& mem )
		{
			m_PU._emitInstruction( INST_AMD_PREFETCHW, &mem );
		}

	}//nsx86
}//nsArch

#endif//( QOR_ARCH == QOR_ARCH_X86_32 || QOR_ARCH == QOR_ARCH_X86_64 )
