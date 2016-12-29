//SSE4.h

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

#ifndef ARCHQOR_ISET_X86_SSE4_H_2
#define ARCHQOR_ISET_X86_SSE4_H_2

#include "SSE3.h"

//------------------------------------------------------------------------------
namespace nsArch
{
	//------------------------------------------------------------------------------
	namespace nsx86
	{
		//------------------------------------------------------------------------------
		class __QOR_INTERFACE( __ARCHQOR ) CSSE4_A : public CSSSE3
		{
		public:

			//------------------------------------------------------------------------------
			CSSE4_A( ) : CSSSE3( )
			{
			}

			//------------------------------------------------------------------------------
			virtual ~CSSE4_A()
			{
			}

			__QCS_DECLARE_NONCOPYABLE( CSSE4_A );
		};

		//------------------------------------------------------------------------------
		class __QOR_INTERFACE(__ARCHQOR) CSSE4_1 : public CSSE4_A
		{
		public:

			//------------------------------------------------------------------------------
			CSSE4_1(  ) : CSSE4_A(  )
			{
			}

			//------------------------------------------------------------------------------
			virtual ~CSSE4_1()
			{
			}

			//------------------------------------------------------------------------------
			//Blend Packed DP-FP Values (SSE4.1).
			inline void blendpd( const CXMMReg& dst, const CXMMReg& src, const CImm& imm8 )
			{
				_emitInstruction( INST_BLENDPD, &dst, &src, &imm8 );
			}

			//------------------------------------------------------------------------------
			//Blend Packed DP-FP Values (SSE4.1).
			inline void blendpd( const CXMMReg& dst, const CMem& src, const CImm& imm8 )
			{
				_emitInstruction( INST_BLENDPD, &dst, &src, &imm8 );
			}

			//------------------------------------------------------------------------------
			//Blend Packed SP-FP Values (SSE4.1).
			inline void blendps( const CXMMReg& dst, const CXMMReg& src, const CImm& imm8 )
			{
				_emitInstruction( INST_BLENDPS, &dst, &src, &imm8 );
			}

			//------------------------------------------------------------------------------
			//Blend Packed SP-FP Values (SSE4.1).
			inline void blendps( const CXMMReg& dst, const CMem& src, const CImm& imm8 )
			{
				_emitInstruction( INST_BLENDPS, &dst, &src, &imm8 );
			}

			//------------------------------------------------------------------------------
			//Variable Blend Packed DP-FP Values (SSE4.1).
			inline void blendvpd( const CXMMReg& dst, const CXMMReg& src )
			{
				_emitInstruction( INST_BLENDVPD, &dst, &src );
			}

			//------------------------------------------------------------------------------
			//Variable Blend Packed DP-FP Values (SSE4.1).
			inline void blendvpd( const CXMMReg& dst, const CMem& src )
			{
				_emitInstruction( INST_BLENDVPD, &dst, &src );
			}

			//------------------------------------------------------------------------------
			//Variable Blend Packed SP-FP Values (SSE4.1).
			inline void blendvps( const CXMMReg& dst, const CXMMReg& src )
			{
				_emitInstruction( INST_BLENDVPS, &dst, &src );
			}

			//------------------------------------------------------------------------------
			//Variable Blend Packed SP-FP Values (SSE4.1).
			inline void blendvps( const CXMMReg& dst, const CMem& src )
			{
				_emitInstruction( INST_BLENDVPS, &dst, &src );
			}

			//------------------------------------------------------------------------------
			//Dot Product of Packed DP-FP Values (SSE4.1).
			inline void dppd( const CXMMReg& dst, const CXMMReg& src, const CImm& imm8 )
			{
				_emitInstruction( INST_DPPD, &dst, &src, &imm8 );
			}

			//------------------------------------------------------------------------------
			//Dot Product of Packed DP-FP Values (SSE4.1).
			inline void dppd( const CXMMReg& dst, const CMem& src, const CImm& imm8 )
			{
				_emitInstruction( INST_DPPD, &dst, &src, &imm8 );
			}

			//------------------------------------------------------------------------------
			//Dot Product of Packed SP-FP Values (SSE4.1).
			inline void dpps( const CXMMReg& dst, const CXMMReg& src, const CImm& imm8 )
			{
				_emitInstruction( INST_DPPS, &dst, &src, &imm8 );
			}

			//------------------------------------------------------------------------------
			//Dot Product of Packed SP-FP Values (SSE4.1).
			inline void dpps( const CXMMReg& dst, const CMem& src, const CImm& imm8 )
			{
				_emitInstruction( INST_DPPS, &dst, &src, &imm8 );
			}

			//------------------------------------------------------------------------------
			//Extract Packed SP-FP Value (SSE4.1).
			inline void extractps( const CXMMReg& dst, const CXMMReg& src, const CImm& imm8 )
			{
				_emitInstruction( INST_EXTRACTPS, &dst, &src, &imm8 );
			}

			//------------------------------------------------------------------------------
			//Extract Packed SP-FP Value (SSE4.1).
			inline void extractps( const CXMMReg& dst, const CMem& src, const CImm& imm8 )
			{
				_emitInstruction( INST_EXTRACTPS, &dst, &src, &imm8 );
			}

			//------------------------------------------------------------------------------
			//Load Double Quadword Non-Temporal Aligned Hint (SSE4.1).
			inline void movntdqa( const CXMMReg& dst, const CMem& src )
			{
				_emitInstruction( INST_MOVNTDQA, &dst, &src );
			}

			//------------------------------------------------------------------------------
			//Compute Multiple Packed Sums of Absolute Difference (SSE4.1).
			inline void mpsadbw( const CXMMReg& dst, const CXMMReg& src, const CImm& imm8 )
			{
				_emitInstruction( INST_MPSADBW, &dst, &src, &imm8 );
			}

			//------------------------------------------------------------------------------
			//Compute Multiple Packed Sums of Absolute Difference (SSE4.1).
			inline void mpsadbw( const CXMMReg& dst, const CMem& src, const CImm& imm8 )
			{
				_emitInstruction( INST_MPSADBW, &dst, &src, &imm8 );
			}

			//------------------------------------------------------------------------------
			//Pack with Unsigned Saturation (SSE4.1).
			inline void packusdw( const CXMMReg& dst, const CXMMReg& src )
			{
				_emitInstruction( INST_PACKUSDW, &dst, &src );
			}

			//------------------------------------------------------------------------------
			//Pack with Unsigned Saturation (SSE4.1).
			inline void packusdw( const CXMMReg& dst, const CMem& src )
			{
				_emitInstruction( INST_PACKUSDW, &dst, &src );
			}

			//------------------------------------------------------------------------------
			//Variable Blend Packed Bytes (SSE4.1).
			inline void pblendvb( const CXMMReg& dst, const CXMMReg& src )
			{
				_emitInstruction( INST_PBLENDVB, &dst, &src );
			}

			//------------------------------------------------------------------------------
			//Variable Blend Packed Bytes (SSE4.1).
			inline void pblendvb( const CXMMReg& dst, const CMem& src )
			{
				_emitInstruction( INST_PBLENDVB, &dst, &src );
			}

			//------------------------------------------------------------------------------
			//Blend Packed Words (SSE4.1).
			inline void pblendw( const CXMMReg& dst, const CXMMReg& src, const CImm& imm8 )
			{
				_emitInstruction( INST_PBLENDW, &dst, &src, &imm8 );
			}

			//------------------------------------------------------------------------------
			//Blend Packed Words (SSE4.1).
			inline void pblendw( const CXMMReg& dst, const CMem& src, const CImm& imm8 )
			{
				_emitInstruction( INST_PBLENDW, &dst, &src, &imm8 );
			}

			//------------------------------------------------------------------------------
			//Compare Packed Qword Data for Equal (SSE4.1).
			inline void pcmpeqq( const CXMMReg& dst, const CXMMReg& src )
			{
				_emitInstruction( INST_PCMPEQQ, &dst, &src );
			}

			//------------------------------------------------------------------------------
			//Compare Packed Qword Data for Equal (SSE4.1).
			inline void pcmpeqq( const CXMMReg& dst, const CMem& src )
			{
				_emitInstruction( INST_PCMPEQQ, &dst, &src );
			}

			//------------------------------------------------------------------------------
			//Extract Byte (SSE4.1).
			inline void pextrb( const CGPReg& dst, const CXMMReg& src, const CImm& imm8 )
			{
				_emitInstruction( INST_PEXTRB, &dst, &src, &imm8 );
			}

			//------------------------------------------------------------------------------
			//Extract Byte (SSE4.1).
			inline void pextrb( const CMem& dst, const CXMMReg& src, const CImm& imm8 )
			{
				_emitInstruction( INST_PEXTRB, &dst, &src, &imm8 );
			}

			//------------------------------------------------------------------------------
			//Extract Dword (SSE4.1).
			inline void pextrd( const CGPReg& dst, const CXMMReg& src, const CImm& imm8 )
			{
				_emitInstruction( INST_PEXTRD, &dst, &src, &imm8 );
			}

			//------------------------------------------------------------------------------
			//Extract Dword (SSE4.1).
			inline void pextrd( const CMem& dst, const CXMMReg& src, const CImm& imm8 )
			{
				_emitInstruction( INST_PEXTRD, &dst, &src, &imm8 );
			}

			//------------------------------------------------------------------------------
			//Extract Dword (SSE4.1).
			inline void pextrq( const CGPReg& dst, const CXMMReg& src, const CImm& imm8 )
			{
				_emitInstruction( INST_PEXTRQ, &dst, &src, &imm8 );
			}

			//------------------------------------------------------------------------------
			//Extract Dword (SSE4.1).
			inline void pextrq( const CMem& dst, const CXMMReg& src, const CImm& imm8 )
			{
				_emitInstruction( INST_PEXTRQ, &dst, &src, &imm8 );
			}

			//------------------------------------------------------------------------------
			//Extract Word (SSE4.1).
			inline void pextrw( const CGPReg& dst, const CXMMReg& src, const CImm& imm8 )
			{
				_emitInstruction( INST_PEXTRW, &dst, &src, &imm8 );
			}

			//------------------------------------------------------------------------------
			//Extract Word (SSE4.1).
			inline void pextrw( const CMem& dst, const CXMMReg& src, const CImm& imm8 )
			{
				_emitInstruction( INST_PEXTRW, &dst, &src, &imm8 );
			}

			//------------------------------------------------------------------------------
			//Packed Horizontal Word Minimum (SSE4.1).
			inline void phminposuw( const CXMMReg& dst, const CXMMReg& src )
			{
				_emitInstruction( INST_PHMINPOSUW, &dst, &src );
			}

			//------------------------------------------------------------------------------
			//Packed Horizontal Word Minimum (SSE4.1).
			inline void phminposuw( const CXMMReg& dst, const CMem& src )
			{
				_emitInstruction( INST_PHMINPOSUW, &dst, &src );
			}

			//------------------------------------------------------------------------------
			//Insert Byte (SSE4.1).
			inline void pinsrb( const CXMMReg& dst, const CGPReg& src, const CImm& imm8 )
			{
				_emitInstruction( INST_PINSRB, &dst, &src, &imm8 );
			}

			//------------------------------------------------------------------------------
			//Insert Byte (SSE4.1).
			inline void pinsrb( const CXMMReg& dst, const CMem& src, const CImm& imm8 )
			{
				_emitInstruction( INST_PINSRB, &dst, &src, &imm8 );
			}

			//------------------------------------------------------------------------------
			//Insert Dword (SSE4.1).
			inline void pinsrd( const CXMMReg& dst, const CGPReg& src, const CImm& imm8 )
			{
				_emitInstruction( INST_PINSRD, &dst, &src, &imm8 );
			}

			//------------------------------------------------------------------------------
			//Insert Dword (SSE4.1).
			inline void pinsrd( const CXMMReg& dst, const CMem& src, const CImm& imm8 )
			{
				_emitInstruction( INST_PINSRD, &dst, &src, &imm8 );
			}

			//------------------------------------------------------------------------------
			//Insert Dword (SSE4.1).
			inline void pinsrq( const CXMMReg& dst, const CGPReg& src, const CImm& imm8 )
			{
				_emitInstruction( INST_PINSRQ, &dst, &src, &imm8 );
			}

			//------------------------------------------------------------------------------
			//Insert Dword (SSE4.1).
			inline void pinsrq( const CXMMReg& dst, const CMem& src, const CImm& imm8 )
			{
				_emitInstruction( INST_PINSRQ, &dst, &src, &imm8 );
			}
			//------------------------------------------------------------------------------
			//Maximum of Packed Word Integers (SSE4.1).
			inline void pmaxuw( const CXMMReg& dst, const CXMMReg& src )
			{
				_emitInstruction( INST_PMAXUW, &dst, &src );
			}

			//------------------------------------------------------------------------------
			//Maximum of Packed Word Integers (SSE4.1).
			inline void pmaxuw( const CXMMReg& dst, const CMem& src )
			{
				_emitInstruction( INST_PMAXUW, &dst, &src );
			}

			//------------------------------------------------------------------------------
			//Maximum of Packed Signed Byte Integers (SSE4.1).
			inline void pmaxsb( const CXMMReg& dst, const CXMMReg& src )
			{
				_emitInstruction( INST_PMAXSB, &dst, &src );
			}

			//------------------------------------------------------------------------------
			//Maximum of Packed Signed Byte Integers (SSE4.1).
			inline void pmaxsb( const CXMMReg& dst, const CMem& src )
			{
				_emitInstruction( INST_PMAXSB, &dst, &src );
			}

			//------------------------------------------------------------------------------
			//Maximum of Packed Signed Dword Integers (SSE4.1).
			inline void pmaxsd( const CXMMReg& dst, const CXMMReg& src )
			{
				_emitInstruction( INST_PMAXSD, &dst, &src );
			}

			//------------------------------------------------------------------------------
			//Maximum of Packed Signed Dword Integers (SSE4.1).
			inline void pmaxsd( const CXMMReg& dst, const CMem& src )
			{
				_emitInstruction( INST_PMAXSD, &dst, &src );
			}

			//------------------------------------------------------------------------------
			//Maximum of Packed Unsigned Dword Integers (SSE4.1).
			inline void pmaxud( const CXMMReg& dst, const CXMMReg& src )
			{
				_emitInstruction( INST_PMAXUD, &dst, &src );
			}

			//------------------------------------------------------------------------------
			//Maximum of Packed Unsigned Dword Integers (SSE4.1).
			inline void pmaxud( const CXMMReg& dst, const CMem& src )
			{
				_emitInstruction( INST_PMAXUD, &dst, &src );
			}

			//------------------------------------------------------------------------------
			//Minimum of Packed Signed Byte Integers (SSE4.1).
			inline void pminsb( const CXMMReg& dst, const CXMMReg& src )
			{
				_emitInstruction( INST_PMINSB, &dst, &src );
			}

			//------------------------------------------------------------------------------
			//Minimum of Packed Signed Byte Integers (SSE4.1).
			inline void pminsb( const CXMMReg& dst, const CMem& src )
			{
				_emitInstruction( INST_PMINSB, &dst, &src );
			}

			//------------------------------------------------------------------------------
			//Minimum of Packed Word Integers (SSE4.1).
			inline void pminuw( const CXMMReg& dst, const CXMMReg& src )
			{
				_emitInstruction( INST_PMINUW, &dst, &src );
			}

			//------------------------------------------------------------------------------
			//Minimum of Packed Word Integers (SSE4.1).
			inline void pminuw( const CXMMReg& dst, const CMem& src )
			{
				_emitInstruction( INST_PMINUW, &dst, &src );
			}

			//------------------------------------------------------------------------------
			//Minimum of Packed Dword Integers (SSE4.1).
			inline void pminud( const CXMMReg& dst, const CXMMReg& src )
			{
				_emitInstruction( INST_PMINUD, &dst, &src );
			}

			//------------------------------------------------------------------------------
			//Minimum of Packed Dword Integers (SSE4.1).
			inline void pminud( const CXMMReg& dst, const CMem& src )
			{
				_emitInstruction( INST_PMINUD, &dst, &src );
			}

			//------------------------------------------------------------------------------
			//Minimum of Packed Dword Integers (SSE4.1).
			inline void pminsd( const CXMMReg& dst, const CXMMReg& src )
			{
				_emitInstruction( INST_PMINSD, &dst, &src );
			}

			//------------------------------------------------------------------------------
			//Minimum of Packed Dword Integers (SSE4.1).
			inline void pminsd( const CXMMReg& dst, const CMem& src )
			{
				_emitInstruction( INST_PMINSD, &dst, &src );
			}

			//------------------------------------------------------------------------------
			//Packed Move with Sign Extend (SSE4.1).
			inline void pmovsxbw( const CXMMReg& dst, const CXMMReg& src )
			{
				_emitInstruction( INST_PMOVSXBW, &dst, &src );
			}

			//------------------------------------------------------------------------------
			//Packed Move with Sign Extend (SSE4.1).
			inline void pmovsxbw( const CXMMReg& dst, const CMem& src )
			{
				_emitInstruction( INST_PMOVSXBW, &dst, &src );
			}

			//------------------------------------------------------------------------------
			//Packed Move with Sign Extend (SSE4.1).
			inline void pmovsxbd( const CXMMReg& dst, const CXMMReg& src )
			{
				_emitInstruction( INST_PMOVSXBD, &dst, &src );
			}

			//------------------------------------------------------------------------------
			//Packed Move with Sign Extend (SSE4.1).
			inline void pmovsxbd( const CXMMReg& dst, const CMem& src )
			{
				_emitInstruction( INST_PMOVSXBD, &dst, &src );
			}

			//------------------------------------------------------------------------------
			//Packed Move with Sign Extend (SSE4.1).
			inline void pmovsxbq( const CXMMReg& dst, const CXMMReg& src )
			{
				_emitInstruction( INST_PMOVSXBQ, &dst, &src );
			}

			//------------------------------------------------------------------------------
			//Packed Move with Sign Extend (SSE4.1).
			inline void pmovsxbq( const CXMMReg& dst, const CMem& src )
			{
				_emitInstruction( INST_PMOVSXBQ, &dst, &src );
			}

			//------------------------------------------------------------------------------
			//Packed Move with Sign Extend (SSE4.1).
			inline void pmovsxwd( const CXMMReg& dst, const CXMMReg& src )
			{
				_emitInstruction( INST_PMOVSXWD, &dst, &src );
			}

			//------------------------------------------------------------------------------
			//Packed Move with Sign Extend (SSE4.1).
			inline void pmovsxwd( const CXMMReg& dst, const CMem& src )
			{
				_emitInstruction( INST_PMOVSXWD, &dst, &src );
			}

			//------------------------------------------------------------------------------
			//(SSE4.1).
			inline void pmovsxwq( const CXMMReg& dst, const CXMMReg& src )
			{
				_emitInstruction( INST_PMOVSXWQ, &dst, &src );
			}

			//------------------------------------------------------------------------------
			//(SSE4.1).
			inline void pmovsxwq( const CXMMReg& dst, const CMem& src )
			{
				_emitInstruction( INST_PMOVSXWQ, &dst, &src );
			}

			//------------------------------------------------------------------------------
			//(SSE4.1).
			inline void pmovsxdq( const CXMMReg& dst, const CXMMReg& src )
			{
				_emitInstruction( INST_PMOVSXDQ, &dst, &src );
			}

			//------------------------------------------------------------------------------
			//(SSE4.1).
			inline void pmovsxdq( const CXMMReg& dst, const CMem& src )
			{
				_emitInstruction( INST_PMOVSXDQ, &dst, &src );
			}

			//------------------------------------------------------------------------------
			//Packed Move with Zero Extend (SSE4.1).
			inline void pmovzxbw( const CXMMReg& dst, const CXMMReg& src )
			{
				_emitInstruction( INST_PMOVZXBW, &dst, &src );
			}

			//------------------------------------------------------------------------------
			//Packed Move with Zero Extend (SSE4.1).
			inline void pmovzxbw( const CXMMReg& dst, const CMem& src )
			{
				_emitInstruction( INST_PMOVZXBW, &dst, &src );
			}

			//------------------------------------------------------------------------------
			//Packed Move with Zero Extend (SSE4.1).
			inline void pmovzxbd( const CXMMReg& dst, const CXMMReg& src )
			{
				_emitInstruction( INST_PMOVZXBD, &dst, &src );
			}

			//------------------------------------------------------------------------------
			//Packed Move with Zero Extend (SSE4.1).
			inline void pmovzxbd( const CXMMReg& dst, const CMem& src )
			{
				_emitInstruction( INST_PMOVZXBD, &dst, &src );
			}

			//------------------------------------------------------------------------------
			//Packed Move with Zero Extend (SSE4.1).
			inline void pmovzxbq( const CXMMReg& dst, const CXMMReg& src )
			{
				_emitInstruction( INST_PMOVZXBQ, &dst, &src );
			}

			//------------------------------------------------------------------------------
			//Packed Move with Zero Extend (SSE4.1).
			inline void pmovzxbq( const CXMMReg& dst, const CMem& src )
			{
				_emitInstruction( INST_PMOVZXBQ, &dst, &src );
			}

			//------------------------------------------------------------------------------
			//Packed Move with Zero Extend (SSE4.1).
			inline void pmovzxwd( const CXMMReg& dst, const CXMMReg& src )
			{
				_emitInstruction( INST_PMOVZXWD, &dst, &src );
			}

			//------------------------------------------------------------------------------
			//Packed Move with Zero Extend (SSE4.1).
			inline void pmovzxwd( const CXMMReg& dst, const CMem& src )
			{
				_emitInstruction( INST_PMOVZXWD, &dst, &src );
			}

			//------------------------------------------------------------------------------
			//(SSE4.1).
			inline void pmovzxwq( const CXMMReg& dst, const CXMMReg& src )
			{
				_emitInstruction( INST_PMOVZXWQ, &dst, &src );
			}

			//------------------------------------------------------------------------------
			//(SSE4.1).
			inline void pmovzxwq( const CXMMReg& dst, const CMem& src )
			{
				_emitInstruction( INST_PMOVZXWQ, &dst, &src );
			}

			//------------------------------------------------------------------------------
			//(SSE4.1).
			inline void pmovzxdq( const CXMMReg& dst, const CXMMReg& src )
			{
				_emitInstruction( INST_PMOVZXDQ, &dst, &src );
			}

			//------------------------------------------------------------------------------
			//(SSE4.1).
			inline void pmovzxdq( const CXMMReg& dst, const CMem& src )
			{
				_emitInstruction( INST_PMOVZXDQ, &dst, &src );
			}

			//------------------------------------------------------------------------------
			//Multiply Packed Signed Dword Integers (SSE4.1).
			inline void pmuldq( const CXMMReg& dst, const CXMMReg& src )
			{
				_emitInstruction( INST_PMULDQ, &dst, &src );
			}

			//------------------------------------------------------------------------------
			//Multiply Packed Signed Dword Integers (SSE4.1).
			inline void pmuldq( const CXMMReg& dst, const CMem& src )
			{
				_emitInstruction( INST_PMULDQ, &dst, &src );
			}

			//------------------------------------------------------------------------------
			//Multiply Packed Signed Integers and Store Low Result (SSE4.1).
			inline void pmulld( const CXMMReg& dst, const CXMMReg& src )
			{
				_emitInstruction( INST_PMULLD, &dst, &src );
			}

			//------------------------------------------------------------------------------
			//Multiply Packed Signed Integers and Store Low Result (SSE4.1).
			inline void pmulld( const CXMMReg& dst, const CMem& src )
			{
				_emitInstruction( INST_PMULLD, &dst, &src );
			}

			//------------------------------------------------------------------------------
			//Logical Compare (SSE4.1).
			inline void ptest( const CXMMReg& op1, const CXMMReg& op2 )
			{
				_emitInstruction( INST_PTEST, &op1, &op2 );
			}

			//------------------------------------------------------------------------------
			//Logical Compare (SSE4.1).
			inline void ptest( const CXMMReg& op1, const CMem& op2 )
			{
				_emitInstruction( INST_PTEST, &op1, &op2 );
			}

			//------------------------------------------------------------------------------
			// Round Packed SP-FP Values (SSE4.1).
			inline void roundps( const CXMMReg& dst, const CXMMReg& src, const CImm& imm8 )
			{
				_emitInstruction( INST_ROUNDPS, &dst, &src, &imm8 );
			}

			//------------------------------------------------------------------------------
			// Round Packed SP-FP Values (SSE4.1).
			inline void roundps( const CXMMReg& dst, const CMem& src, const CImm& imm8 )
			{
				_emitInstruction( INST_ROUNDPS, &dst, &src, &imm8 );
			}

			//------------------------------------------------------------------------------
			//Round Scalar SP-FP Values (SSE4.1).
			inline void roundss( const CXMMReg& dst, const CXMMReg& src, const CImm& imm8 )
			{
				_emitInstruction( INST_ROUNDSS, &dst, &src, &imm8 );
			}

			//------------------------------------------------------------------------------
			//Round Scalar SP-FP Values (SSE4.1).
			inline void roundss( const CXMMReg& dst, const CMem& src, const CImm& imm8 )
			{
				_emitInstruction( INST_ROUNDSS, &dst, &src, &imm8 );
			}

			//------------------------------------------------------------------------------
			//Round Packed DP-FP Values (SSE4.1).
			inline void roundpd( const CXMMReg& dst, const CXMMReg& src, const CImm& imm8 )
			{
				_emitInstruction( INST_ROUNDPD, &dst, &src, &imm8 );
			}

			//------------------------------------------------------------------------------
			//Round Packed DP-FP Values (SSE4.1).
			inline void roundpd( const CXMMReg& dst, const CMem& src, const CImm& imm8 )
			{
				_emitInstruction( INST_ROUNDPD, &dst, &src, &imm8 );
			}

			//------------------------------------------------------------------------------
			//Round Scalar DP-FP Values (SSE4.1).
			inline void roundsd( const CXMMReg& dst, const CXMMReg& src, const CImm& imm8 )
			{
				_emitInstruction( INST_ROUNDSD, &dst, &src, &imm8 );
			}

			//------------------------------------------------------------------------------
			//Round Scalar DP-FP Values (SSE4.1).
			inline void roundsd( const CXMMReg& dst, const CMem& src, const CImm& imm8 )
			{
				_emitInstruction( INST_ROUNDSD, &dst, &src, &imm8 );
			}

			__QCS_DECLARE_NONCOPYABLE( CSSE4_1 );
		};

		//------------------------------------------------------------------------------
		class __QOR_INTERFACE(__ARCHQOR) CSSE4_2 : public CSSE4_1
		{
		public:

			//------------------------------------------------------------------------------
			CSSE4_2(  ) : CSSE4_1( )
			{
			}

			//------------------------------------------------------------------------------
			virtual ~CSSE4_2()
			{
			}

			//------------------------------------------------------------------------------
			//Accumulate CRC32 Value (polynomial 0x11EDC6F41) (SSE4.2).
			inline void crc32( const CGPReg& dst, const CGPReg& src )
			{
				//assert(dst.isRegType(REG_TYPE_GPD) || dst.isRegType(REG_TYPE_GPQ));
				_emitInstruction( INST_CRC32, &dst, &src );
			}

			//------------------------------------------------------------------------------
			//Accumulate CRC32 Value (polynomial 0x11EDC6F41) (SSE4.2).
			inline void crc32( const CGPReg& dst, const CMem& src )
			{
				//assert(dst.isRegType(REG_TYPE_GPD) || dst.isRegType(REG_TYPE_GPQ));
				_emitInstruction( INST_CRC32, &dst, &src );
			}

			//------------------------------------------------------------------------------
			//Packed Compare Explicit Length Strings, Return Index (SSE4.2).
			inline void pcmpestri( const CXMMReg& dst, const CXMMReg& src, const CImm& imm8 )
			{
				_emitInstruction( INST_PCMPESTRI, &dst, &src, &imm8 );
			}

			//------------------------------------------------------------------------------
			//Packed Compare Explicit Length Strings, Return Index (SSE4.2).
			inline void pcmpestri( const CXMMReg& dst, const CMem& src, const CImm& imm8 )
			{
				_emitInstruction( INST_PCMPESTRI, &dst, &src, &imm8 );
			}

			//------------------------------------------------------------------------------
			//Packed Compare Explicit Length Strings, Return Mask (SSE4.2).
			inline void pcmpestrm( const CXMMReg& dst, const CXMMReg& src, const CImm& imm8 )
			{
				_emitInstruction( INST_PCMPESTRM, &dst, &src, &imm8 );
			}

			//------------------------------------------------------------------------------
			//Packed Compare Explicit Length Strings, Return Mask (SSE4.2).
			inline void pcmpestrm( const CXMMReg& dst, const CMem& src, const CImm& imm8 )
			{
				_emitInstruction( INST_PCMPESTRM, &dst, &src, &imm8 );
			}

			//------------------------------------------------------------------------------
			//Packed Compare Implicit Length Strings, Return Index (SSE4.2).
			inline void pcmpistri( const CXMMReg& dst, const CXMMReg& src, const CImm& imm8 )
			{
				_emitInstruction( INST_PCMPISTRI, &dst, &src, &imm8 );
			}

			//------------------------------------------------------------------------------
			//Packed Compare Implicit Length Strings, Return Index (SSE4.2).
			inline void pcmpistri( const CXMMReg& dst, const CMem& src, const CImm& imm8 )
			{
				_emitInstruction( INST_PCMPISTRI, &dst, &src, &imm8 );
			}

			//------------------------------------------------------------------------------
			//Packed Compare Implicit Length Strings, Return Mask (SSE4.2).
			inline void pcmpistrm( const CXMMReg& dst, const CXMMReg& src, const CImm& imm8 )
			{
				_emitInstruction( INST_PCMPISTRM, &dst, &src, &imm8 );
			}

			//------------------------------------------------------------------------------
			//Packed Compare Implicit Length Strings, Return Mask (SSE4.2).
			inline void pcmpistrm( const CXMMReg& dst, const CMem& src, const CImm& imm8 )
			{
				_emitInstruction( INST_PCMPISTRM, &dst, &src, &imm8 );
			}

			//------------------------------------------------------------------------------
			//Compare Packed Data for Greater Than (SSE4.2).
			inline void pcmpgtq( const CXMMReg& dst, const CXMMReg& src )
			{
				_emitInstruction( INST_PCMPGTQ, &dst, &src );
			}

			//------------------------------------------------------------------------------
			//Compare Packed Data for Greater Than (SSE4.2).
			inline void pcmpgtq( const CXMMReg& dst, const CMem& src )
			{
				_emitInstruction( INST_PCMPGTQ, &dst, &src );
			}

			//------------------------------------------------------------------------------
			//Return the Count of Number of Bits Set to 1 (SSE4.2).
			inline void popcnt( const CGPReg& dst, const CGPReg& src )
			{
				//assert(!dst.isGPB());
				//assert(src.getRegType() == dst.getRegType());
				_emitInstruction( INST_POPCNT, &dst, &src );
			}

			//------------------------------------------------------------------------------
			//Return the Count of Number of Bits Set to 1 (SSE4.2).
			inline void popcnt( const CGPReg& dst, const CMem& src )
			{
				//assert(!dst.isGPB());
				_emitInstruction( INST_POPCNT, &dst, &src );
			}

			__QCS_DECLARE_NONCOPYABLE( CSSE4_2 );
		};
	}
}

#endif//ARCHQOR_ISET_X86_SSE4_H_2