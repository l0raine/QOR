//WinQLDCClipping.h

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

//inline header file for Device Context Clipping component class

#ifndef WINQL_GRAPHICS_DC_CLIPPING_H_3
#define WINQL_GRAPHICS_DC_CLIPPING_H_3

//--------------------------------------------------------------------------------
class __QOR_INTERFACE( __WINQL ) CClipping
{
public:

	__QOR_DECLARE_OCLASS_ID( CClipping );

	CClipping( CDeviceContext& DC );
	virtual ~CClipping();
	int ExcludeRect( int nLeftRect, int nTopRect, int nRightRect, int nBottomRect );
	int SelectRegion( CRegion& Rgn, int fnMode );
	int GetBox( nsWin32::RECT* lprc );
	int GetRegion( CRegion& Rgn );
	int UseSystemClippingRegion( CRegion& Rgn );
	int IntersectRect( int nLeftRect, int nTopRect, int nRightRect, int nBottomRect );
	int OffsetRgn( int nXOffset, int nYOffset );
	bool PtVisible( int X, int Y );
	bool RectVisible( const nsWin32::RECT* lprc );
	bool SelectPath( int iMode );
	int SelectRegion( CRegion& Rgn );

protected:

	CDeviceContext& m_DC;

private:

	//--------------------------------------------------------------------------------
	CClipping();//Not to be implemented
	CClipping( const CClipping& Src );//Not to be implemented
	CClipping& operator = ( const CClipping& Src );//Not to be implemented

};

#endif//WINQL_GRAPHICS_DC_CLIPPING_H_3
