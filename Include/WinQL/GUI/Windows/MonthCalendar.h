//MonthCalendar.h

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

//MonthCalendar Common Control Window

#ifndef WINQL_GUI_WND_CCTRL_MONTHCALENDAR_H_3
#define WINQL_GUI_WND_CCTRL_MONTHCALENDAR_H_3

#include "WinQL/GUI/Views/WindowView.h"
#include "WinQL/GUI/Windows/WinCtrlWindow.h"
#include "MammutQOR/Model.h"
#include "WinQL/Application/Graphics/WinQLRectangle.h"
#include "WinQL/System/Clock/WinQLTime.h"
#include "WinQL/GUI/WindowFactory.h"
#include "WinQL/GUI/CommonCtrl.h"

//--------------------------------------------------------------------------------
namespace nsWin32
{
	//--------------------------------------------------------------------------------
	class __QOR_INTERFACE( __WINQL_GUI ) CMonthCalendarClass : public CWindowClass
	{
	public:

		__QOR_DECLARE_OCLASS_ID( CMonthCalendarClass );

		CMonthCalendarClass();
		virtual ~CMonthCalendarClass();
		virtual bool Preregistered();
		const TCHAR* Name();

	private:

		CCommonCtrl m_ComCtrl32;

		CMonthCalendarClass( const CMonthCalendarClass& );
		CMonthCalendarClass& operator = ( const CMonthCalendarClass& );
	};

	//--------------------------------------------------------------------------------
	class __QOR_INTERFACE( __WINQL_GUI ) CMonthCalendar : public CWinCtrlWindow
	{
	public:

		//--------------------------------------------------------------------------------
		typedef struct tagMCGRIDINFO 
		{
			unsigned int       cbSize;
			unsigned long      dwPart;
			unsigned long      dwFlags;
			int        iCalendar;
			int        iRow;
			int        iCol;
			int       bSelected;
			nsWin32::SystemTime stStart;
			nsWin32::SystemTime stEnd;
			RECT       rc;
			wchar_t*      pszName;
			size_t     cchName;
		} MCGRIDINFO, *PMCGRIDINFO;

		//--------------------------------------------------------------------------------
		struct NMDAYSTATE : public NotificationMessageHeader
		{
			//NMHDR           nmhdr;  // this must be first, so we don't break WM_NOTIFY
			nsWin32::SystemTime      stStart;
			int             cDayState;
			unsigned long* prgDayState; // points to cDayState MONTHDAYSTATEs
		};

		//--------------------------------------------------------------------------------
		struct MCHITTESTINFO
		{
			unsigned int cbSize;
			POINT pt;

			unsigned int uHit;   // out param
			nsWin32::SystemTime st;
#if		(NTDDI_VERSION >= NTDDI_VISTA)
			RECT rc;
			int iOffset;
			int iRow;
			int iCol;
#endif//(NTDDI_VERSION >= NTDDI_VISTA)
		};

		//--------------------------------------------------------------------------------
		typedef struct tagNMSELCHANGE : public NotificationMessageHeader
		{
			//NMHDR           nmhdr;  // this must be first, so we don't break WM_NOTIFY
			nsWin32::SystemTime      stSelStart;
			nsWin32::SystemTime      stSelEnd;
		} NMSELCHANGE, *LPNMSELCHANGE;

		//--------------------------------------------------------------------------------
		typedef struct tagNMVIEWCHANGE : public NotificationMessageHeader
		{
			//NMHDR           nmhdr;  // this must be first, so we don't break WM_NOTIFY
			unsigned long           dwOldView;
			unsigned long           dwNewView;
		} NMVIEWCHANGE, *LPNMVIEWCHANGE;

		__QCMP_STATIC_CONSTANT( int, MCN_FIRST            = (0U-746U) ); 
		__QCMP_STATIC_CONSTANT( int, MCN_LAST             = (0U-752U) ); 

		//Notifications
		__QCMP_STATIC_CONSTANT( int, MCN_SELECT          = (MCN_FIRST) ); // -746
		__QCMP_STATIC_CONSTANT( int, MCN_GETDAYSTATE     = (MCN_FIRST - 1) ); // -747			
		__QCMP_STATIC_CONSTANT( int, MCN_SELCHANGE       = (MCN_FIRST - 3) ); // -749
		__QCMP_STATIC_CONSTANT( int, MCN_VIEWCHANGE      = (MCN_FIRST - 4) ); // -750

		//Messages
		__QCMP_STATIC_CONSTANT( int, MCM_FIRST           = 0x1000		   );
		__QCMP_STATIC_CONSTANT( int, MCM_GETCURSEL       = (MCM_FIRST + 1)  );
		__QCMP_STATIC_CONSTANT( int, MCM_SETCURSEL       = (MCM_FIRST + 2)  );
		__QCMP_STATIC_CONSTANT( int, MCM_GETMAXSELCOUNT  = (MCM_FIRST + 3)  );
		__QCMP_STATIC_CONSTANT( int, MCM_SETMAXSELCOUNT  = (MCM_FIRST + 4)  );
		__QCMP_STATIC_CONSTANT( int, MCM_GETSELRANGE     = (MCM_FIRST + 5)  );
		__QCMP_STATIC_CONSTANT( int, MCM_SETSELRANGE     = (MCM_FIRST + 6)  );
		__QCMP_STATIC_CONSTANT( int, MCM_GETMONTHRANGE   = (MCM_FIRST + 7)  );
		__QCMP_STATIC_CONSTANT( int, MCM_SETDAYSTATE     = (MCM_FIRST + 8)  );
		__QCMP_STATIC_CONSTANT( int, MCM_GETMINREQRECT   = (MCM_FIRST + 9)  );
		__QCMP_STATIC_CONSTANT( int, MCM_SETCOLOR        = (MCM_FIRST + 10) );
		__QCMP_STATIC_CONSTANT( int, MCM_GETCOLOR        = (MCM_FIRST + 11) );
		__QCMP_STATIC_CONSTANT( int, MCM_SETTODAY		= (MCM_FIRST + 12) );
		__QCMP_STATIC_CONSTANT( int, MCM_GETTODAY		= (MCM_FIRST + 13) );
		__QCMP_STATIC_CONSTANT( int, MCM_HITTEST         = (MCM_FIRST + 14) );
		__QCMP_STATIC_CONSTANT( int, MCM_SETFIRSTDAYOFWEEK	= (MCM_FIRST + 15) );
		__QCMP_STATIC_CONSTANT( int, MCM_GETFIRSTDAYOFWEEK	= (MCM_FIRST + 16) );
		__QCMP_STATIC_CONSTANT( int, MCM_GETRANGE			= (MCM_FIRST + 17) );
		__QCMP_STATIC_CONSTANT( int, MCM_SETRANGE			= (MCM_FIRST + 18) );
		__QCMP_STATIC_CONSTANT( int, MCM_GETMONTHDELTA		= (MCM_FIRST + 19) );
		__QCMP_STATIC_CONSTANT( int, MCM_SETMONTHDELTA		= (MCM_FIRST + 20) );
		__QCMP_STATIC_CONSTANT( int, MCM_GETMAXTODAYWIDTH	= (MCM_FIRST + 21) );
		__QCMP_STATIC_CONSTANT( int, MCM_GETCURRENTVIEW		= (MCM_FIRST + 22) );
		__QCMP_STATIC_CONSTANT( int, MCM_GETCALENDARCOUNT	= (MCM_FIRST + 23) );
		__QCMP_STATIC_CONSTANT( int, MCM_GETCALENDARGRIDINFO = (MCM_FIRST + 24) );
		__QCMP_STATIC_CONSTANT( int, MCM_GETCALID			= (MCM_FIRST + 27) );
		__QCMP_STATIC_CONSTANT( int, MCM_SETCALID			= (MCM_FIRST + 28) );
		__QCMP_STATIC_CONSTANT( int, MCM_SIZERECTTOMIN		= (MCM_FIRST + 29) );
		__QCMP_STATIC_CONSTANT( int, MCM_SETCALENDARBORDER	= (MCM_FIRST + 30) );
		__QCMP_STATIC_CONSTANT( int, MCM_GETCALENDARBORDER	= (MCM_FIRST + 31) );
		__QCMP_STATIC_CONSTANT( int, MCM_SETCURRENTVIEW		= (MCM_FIRST + 32) );

		__QCMP_STATIC_CONSTANT( int, MCM_SETUNICODEFORMAT    = CCM_SETUNICODEFORMAT );
		__QCMP_STATIC_CONSTANT( int, MCM_GETUNICODEFORMAT    = CCM_GETUNICODEFORMAT );

		__QOR_DECLARE_OCLASS_ID( CMonthCalendar );

		CMonthCalendar();
		virtual ~CMonthCalendar();

		long OnNotify( NotificationMessageHeader* pHdr );

		virtual void OnGetDayState( NMDAYSTATE* pHdr );
		virtual void OnSelChange( NMSELCHANGE* pHdr );
		virtual void OnSelect( NMSELCHANGE* pHdr );
		virtual void OnViewChange( NMVIEWCHANGE* pHdr );
		virtual void OnReleasedCapture( NotificationMessageHeader* pHdr );
		virtual long OnUnknownNotification( NotificationMessageHeader* pHdr );

		long GetBorderPixels();
		long GetCalendarCount();
		bool GetGridInfo( MCGRIDINFO& GridInfo );
		long GetCalendarID();
		unsigned long GetColour( int iColour );
		long GetCurrentView();
		bool GetCurSel( nsWin32::SystemTime& SelTime );
		long GetFirstDayOfWeek();
		long GetMaxSelCount();
		long GetMaxTodayWidth();
		bool GetMinRequiredRect( CRectangle& rcMinMonth );
		long GetMonthDelta();
		long GetMonthRange( unsigned long dwFlags, nsWin32::SystemTime* paRange );
		long GetRange( nsWin32::SystemTime* paRange );
		bool GetSelRange( nsWin32::SystemTime* paRange );
		bool GetToday( nsWin32::SystemTime& Today );
		bool GetUnicodeFormat();
		long HitTest( MCHITTESTINFO& HitTestInfo );
		void SetBorderPixels( Cmp_long_ptr PixelWidth, bool bReset );
		void SetCalendarID( Cmp_uint_ptr CalID );
		unsigned long SetColour( int iColour, unsigned long clr );
		bool SetCurrentView( Cmp_long_ptr View );
		bool SetCurSel( SystemTime SelDate );
		bool SetDayState( int iMonths, unsigned long* paState );
		long SetFirstDayOfWeek( int iDay );
		bool SetMaxSelCount( int iMax );
		long SetMonthDelta( int iDelta );
		bool SetRange( short sWhichLimits, SystemTime* paRange );
		bool SetSelRange( SystemTime* paRange );
		void SetToday ( nsWin32::SystemTime Today );
		bool SetUnicodeFormat( bool bUnicode );
		void SizeRectToMin( CRectangle& rcMinSize );

	};

	//--------------------------------------------------------------------------------
	class __QOR_INTERFACE( __WINQL_GUI ) CMonthCalendarFactory : public CWindowFactory
	{
	public:

		__QCMP_STATIC_CONSTANT( int, MCS_DAYSTATE        = 0x0001 );
		__QCMP_STATIC_CONSTANT( int, MCS_MULTISELECT     = 0x0002 );
		__QCMP_STATIC_CONSTANT( int, MCS_WEEKNUMBERS     = 0x0004 );
#if		(_WIN32_IE >= 0x0400)
		__QCMP_STATIC_CONSTANT( int, MCS_NOTODAYCIRCLE   = 0x0008 );
		__QCMP_STATIC_CONSTANT( int, MCS_NOTODAY         = 0x0010 );
#else//(_WIN32_IE >= 0x0400)
		__QCMP_STATIC_CONSTANT( int, MCS_NOTODAY         = 0x0008 );
#endif
#if		(NTDDI_VERSION >= NTDDI_VISTA)
		__QCMP_STATIC_CONSTANT( int, MCS_NOTRAILINGDATES  = 0x0040 );
		__QCMP_STATIC_CONSTANT( int, MCS_SHORTDAYSOFWEEK  = 0x0080 );
		__QCMP_STATIC_CONSTANT( int, MCS_NOSELCHANGEONNAV = 0x0100 );
#endif//(NTDDI_VERSION >= NTDDI_VISTA)

		__QOR_DECLARE_OCLASS_ID( CMonthCalendarFactory );

		CMonthCalendarFactory();
		virtual ~CMonthCalendarFactory();

		virtual CMonthCalendar* Create();
			
		bool GetDayState();
		void SetDayState( bool bFlag );
		bool GetMultiSelect();
		void SetMultiSelect( bool bFlag );
		bool GetWeekNumbers();
		void SetWeekNumbers( bool bFlag );
		bool GetNoTodayCircle();
		void SetNoTodayCircle( bool bFlag );
		bool GetNoToday();
		void SetNoToday( bool bFlag );
		bool GetNoTrailingDates();
		void SetNoTrailingDates( bool bFlag );
		bool GetShortDaysOfWeek();
		void SetShortDaysOfWeek( bool bFlag );
		bool GetNoSelChangeOnNav();
		void SetNoSelChangeOnNav( bool bFlag );
 
	};

}//nsWin32

#endif//WINQL_GUI_WND_CCTRL_MONTHCALENDAR_H_3
