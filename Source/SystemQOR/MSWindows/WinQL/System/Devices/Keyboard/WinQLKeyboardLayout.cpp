//WinQLKeyboardLayout.cpp

// Copyright Querysoft Limited 2013, 2017
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

//Windows Keyboard

#include "WinQL/CodeServices/WinQLPolicy.h"
#include "WinQL/Application/Threading/WinQLCriticalSection.h"
#include "WinQL/Application/ErrorSystem/WinQLError.h"
#include "CompilerQOR.h"
#include "WinQL/System/Devices/Interfaces/WinQLDeviceInterface.h"
__QCMP_WARNING_PUSH
__QCMP_WARNING_DISABLE(__QCMP_WARN_THIS_USED_IN_BASE_INIT_LIST, "Safe usage: stored in member for later use")
#include "WinQL/System/Devices/Keyboard/WinQLKeyboardLayout.h"
__QCMP_WARNING_POP
#include "WinQL/Application/Threading/WinQLThread.h"
//#include "WinQL/Application/Resources/WinQLResourceManager.h"
#include "WinQAPI/User32.h"

//--------------------------------------------------------------------------------
namespace nsWin32
{
	using namespace nsWinQAPI;

	__QOR_IMPLEMENT_OCLASS_LUID(CKeyboardLayout);

	__QCMP_WARNING_PUSH
		__QCMP_WARNING_DISABLE(__QCMP_WARN_THIS_USED_IN_BASE_INIT_LIST, "Safe usage: stored in member for later use")

		//--------------------------------------------------------------------------------
		CKeyboardLayout::CKeyboardLayout(CKeyboardLayoutHandle::refType hKL) : m_Library(CUser32::Instance())
		, m_Handle(this, hKL->AsHandle().ptr())
	{
		_WINQ_FCONTEXT("CKeyboardLayout::CKeyboardLayout");
		m_pbResult = 0;
	}

	//--------------------------------------------------------------------------------
	CKeyboardLayout::CKeyboardLayout(const TCHAR* pwszKLID, unsigned int Flags, int* pbResult) : m_Library(CUser32::Instance())
		, m_Handle(this, 0)
	{
		_WINQ_FCONTEXT("CKeyboardLayout::CKeyboardLayout");
		__QOR_PROTECT
		{
			m_pbResult = 0;
		if (pbResult != 0)
		{
			m_pbResult = pbResult;
		}
		m_Handle = (m_Library.LoadKeyboardLayout(pwszKLID, Flags));
		}__QOR_ENDPROTECT
	}

	//--------------------------------------------------------------------------------
	CKeyboardLayout::~CKeyboardLayout()
	{
		_WINQ_FCONTEXT("CKeyboardLayout::~CKeyboardLayout");
		BOOL bResult = FALSE;
		__QOR_PROTECT
		{
			bResult = m_Library.UnloadKeyboardLayout(reinterpret_cast< ::HKL >(m_Handle.Use()));
		if (m_pbResult != 0)
		{
			*m_pbResult = bResult;
		}
		}__QOR_ENDPROTECT
	}

	//--------------------------------------------------------------------------------
	void CKeyboardLayout::Activate(unsigned int uiFlags)
	{
		_WINQ_FCONTEXT("CKeyboardLayout::Activate");
		__QOR_PROTECT
		{
			m_Library.ActivateKeyboardLayout(reinterpret_cast<::HKL>(m_Handle.Use()), uiFlags);
			//CKeyboardLayout::ref_type refDeactivate = CKeyboardLayout::FromHandle(CKeyboardLayoutHandle(0, (void*)()).Ref());

			//if (!refDeactivate.IsNull())
			//{
				//refDeactivate->OnDeactivate(ref(*this));
			//}

		}__QOR_ENDPROTECT
	}

	//--------------------------------------------------------------------------------
	void CKeyboardLayout::OnDeactivate(CKeyboardLayout::ref_type New)
	{
		_WINQ_FCONTEXT("CKeyboardLayout::OnDeactivate");
	}

	//--------------------------------------------------------------------------------
	CKeyboardLayoutHandle::refType CKeyboardLayout::Handle(void)
	{
		return m_Handle.Ref();
	}

}

