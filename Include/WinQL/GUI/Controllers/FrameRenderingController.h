//FrameRenderingController.h

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

//GUI Controller for Frame Rendering

#ifndef WINQL_GUI_CONTROLLER_FRAMERENDERING_H_3
#define WINQL_GUI_CONTROLLER_FRAMERENDERING_H_3

#include "WinQL/GUI/Controllers/Parts/RenderingController.h"

//--------------------------------------------------------------------------------
namespace nsWin32
{
	//--------------------------------------------------------------------------------
	class __QOR_INTERFACE( __WINQL_GUI ) CFrameRenderingController : public CRenderingController
	{
	public:

		__QOR_DECLARE_OCLASS_ID( CFrameRenderingController );

		CFrameRenderingController( nsMammut::CModel* pModelItem = 0, nsQOR::CController::ref_type Parent = 0 );
		virtual ~CFrameRenderingController();
		virtual void OnSize( COSWindow& Window, Cmp_uint_ptr wParam, Cmp_long_ptr lParam );
		virtual long OnEraseBackground( COSWindow& Window, CDeviceContext& refDC );

	private:

		CFrameRenderingController( const CFrameRenderingController& );
		CFrameRenderingController& operator = ( const CFrameRenderingController& );

	};

}//nsWin32

#endif//WINQL_GUI_CONTROLLER_FRAMERENDERING_H_3
