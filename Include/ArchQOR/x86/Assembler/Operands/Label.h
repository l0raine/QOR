//Label.h

// Copyright (c) 2008-2010, Petr Kobalicek <kobalicek.petr@gmail.com>
// Copyright (c) Querysoft Limited 2012
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

// Label, jump target or data location, for x86 assembler

#ifndef ARCHQOR_X86PC_ASSEMBLERLABEL_H_2
#define ARCHQOR_X86PC_ASSEMBLERLABEL_H_2

#include "Operand.h"

//------------------------------------------------------------------------------
namespace nsArch
{
//------------------------------------------------------------------------------
namespace nsx86
{
	//------------------------------------------------------------------------------
	//Label represents locations typically used as jump targets, but may be also
	//used as position where are stored constants or static variables. If you
	//want to use Label you need first to associate it with Assembler or
	//HLAssembler instance. To create new label use Assembler::newLabel() or HLAssembler::newLabel().
	//------------------------------------------------------------------------------
	class __QOR_INTERFACE( __ARCHQOR ) CLabel : public COperand
	{
	public:

		CLabel() __QCMP_THROW;
		CLabel( const CLabel& other ) __QCMP_THROW;
		virtual ~CLabel() __QCMP_THROW;
		CLabel& operator = ( const CLabel& other );
		bool operator == ( const CLabel& other ) const __QCMP_THROW;
		bool operator != ( const CLabel& other ) const __QCMP_THROW;

		virtual COperand* Clone( CZone& zone ) const;
	};

}//nsx86
}//nsArch

#endif//ARCHQOR_X86PC_ASSEMBLERLABEL_H_2
