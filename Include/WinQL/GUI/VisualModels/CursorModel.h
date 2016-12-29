//CursorModel.h

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

//Model for Windows Cursor

#ifdef	__QCMP_OPTIMIZEINCLUDE
#pragma	__QCMP_OPTIMIZEINCLUDE
#endif//__QCMP_OPTIMIZEINCLUDE

#ifndef WINQL_GUI_VISMODELS_CURSOR_H_3
#define WINQL_GUI_VISMODELS_CURSOR_H_3

//#include "stdafx.h"
#include "MammutQOR/Model.h"
#include "MammutQOR/Model/MProperty.h"
#include "MammutQOR/Model/MPropertySet.h"
#include "CodeQOR/ClassReg/ClassRegEntry.h"
#include "WinQL/Application/Process/Module/WinQLModule.h"
#include "WinQL/GUI/Cursor.h"

//--------------------------------------------------------------------------------
namespace nsWin32
{
	//--------------------------------------------------------------------------------
	class __QOR_INTERFACE( __WINQL_GUI ) CCursorModel : public nsMammut::CPropertySet
	{
	public:

		__QOR_DECLARE_OCLASS_ID( CCursorModel );

		//--------------------------------------------------------------------------------
		typedef enum
		{
			eScratchCursor = 1,
			eFileCursor,
			eByNameCursor
		} eCursorModelType;

		CCursorModel( CModel* pContainer = 0 );
		virtual ~CCursorModel();
		CCursorModel( const CCursorModel& );
		CCursorModel( nsMammut::CPropertySet& src );
		CCursorModel& operator = ( const CCursorModel& );
		CCursorModel& operator = ( const nsMammut::CPropertySet& src );

		nsMammut::CProperty< eCursorModelType > m_Type;
		nsMammut::CProperty< CWinModule* > m_pModule;
		nsMammut::CProperty< const TCHAR* > m_szName;
		nsMammut::CProperty< int > m_iXHotSpot;
		nsMammut::CProperty< int > m_iYHotSpot;
		nsMammut::CProperty< int > m_iHeight;
		nsMammut::CProperty< int > m_iWidth;
		nsMammut::CProperty< const void* > m_pANDPlane;
		nsMammut::CProperty< const void* > m_pORPlane;
		
	};

}//nsWin32

#endif//WINQL_GUI_VISMODELS_CURSOR_H_3