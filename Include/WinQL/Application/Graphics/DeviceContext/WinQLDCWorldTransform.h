//WinQLDCWorldTransform.h

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

//inline header file for Device Context World Transform component class

#ifndef _QSYS_MSWINDOWS_WIN32_OSGRAPHICS_DC_WORLDTRANSFORM_H_
#define _QSYS_MSWINDOWS_WIN32_OSGRAPHICS_DC_WORLDTRANSFORM_H_

//--------------------------------------------------------------------------------
class __QOR_INTERFACE( __WINQL ) CWorldTransform : public CXForm
{
public:

	CWorldTransform( CDeviceContext& DC );
	CWorldTransform( CDeviceContext& DC, const nsWin32::XFORM* lpxform1, const nsWin32::XFORM* lpxform2, int& bResult );
	virtual ~CWorldTransform();
	bool Get( nsWin32::XFORM* lpXform );
	bool Modify( const nsWin32::XFORM* lpXform, unsigned long iMode );
	bool Set( const nsWin32::XFORM* lpXform );

protected:

	CDeviceContext& m_DC;

private:

	CWorldTransform( const CWorldTransform& Src ); //Not to be implemented
	CWorldTransform& operator = ( const CWorldTransform& Src ); //Not to be implemented

};

#endif//_QSYS_MSWINDOWS_WIN32_OSGRAPHICS_DC_WORLDTRANSFORM_H_