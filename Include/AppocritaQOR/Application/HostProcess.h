//HostProcess.h

// Copyright Querysoft Limited 2017
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

//Host Process

#include "CompilerQOR.h"

#ifdef	__QCMP_OPTIMIZEINCLUDE
#pragma	__QCMP_OPTIMIZEINCLUDE
#endif//__QCMP_OPTIMIZEINCLUDE

#ifndef APPOCRITAQOR_HOSTPROCESS_H_3
#define APPOCRITAQOR_HOSTPROCESS_H_3

#include "CodeQOR/Macros/ClassIdentityMacros.h"
#include "CodeQOR/Traits/ReferenceTraits.h"
#include "CodeQOR/DataTypes/GUID.h"
#include "CodeQOR/DataStructures/TRef.h"

//------------------------------------------------------------------------------
namespace nsQOR
{
	//------------------------------------------------------------------------------
	class __QOR_INTERFACE(__APPOCRITA) IHostProcess
	{
	public:

		__QOR_DECLARE_OCLASS_ID(IHostProcess);

		__QOR_IMPL_REF(IHostProcess);

		IHostProcess() {}
		virtual ~IHostProcess() {};

	};

	//------------------------------------------------------------------------------
	class __QOR_INTERFACE(__APPOCRITA) CHostProcess : public IHostProcess
	{
	public:

		CHostProcess();
		virtual ~CHostProcess();

	private:

	};

}//nsQOR

#endif//APPOCRITAQOR_HOSTPROCESS_H_3

