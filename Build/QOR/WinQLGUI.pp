//WinQLGUI.pp

// Copyright Querysoft Limited 2016
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

//Preprocessor build script generator for WinQLGUI.dll

#include "ModuleHeader.pph"

//Set WinQLGUI specific definitions and overrides

#define QOR_MODULE_NAME WinQLGUI

//Append the module specific PP defines to the list from the Operating System
#define QOR_CONFIG_DEFINES_WINQLGUI1 QOR_PP_LIST_APPEND( QOR_CONFIG_DEFINES_OS,("__WINQL_GUI") )
#define QOR_CONFIG_DEFINES_WINQLGUI2 QOR_PP_LIST_APPEND( QOR_CONFIG_DEFINES_WINQLGUI1,("_LIBCPP_DLL") )
#define QOR_CONFIG_DEFINES_MODULE QOR_PP_LIST_APPEND( QOR_CONFIG_DEFINES_WINQLGUI2,("") )


#define QOR_CONFIG_INCLUDES (../../../include)\
(../../../Source/SystemQOR/MSWindows/WinCmpSupQORVC/include/Exceptions/SEH)\
(C:\Program Files (x86)\Windows Kits\8.1\Include\um)\
(C:\Program Files (x86)\Windows Kits\8.1\Include\shared)\
(C:\Program Files (x86)\Windows Kits\8.1\Include\winrt)

#define QOR_PP_BUILD_CMP_IGNORE_STANDARD_INC_SELECT 1
#define QOR_PP_BUILD_CMP_CPP_EXCEPTIONS_SELECT 1
#define QOR_PP_BUILD_CMP_BUFFER_SECURITY_SELECT 1
#define QOR_PP_BUILD_CMP_RUNTIME_CHECKS_SELECT 4
//#define QOR_PP_BUILD_CMP_WARNING_LEVEL_SELECT 4

//Include this to do any setup needed for a build such as creating folders
#include "BuildQOR/BeginBuild.pph"

//For each group of files that have the same folder and build options, define a group of sources

#if( QOR_SYS_OS == QOR_SYS_MSW )

#	define SOURCE_PATH ../../../Source/SystemQOR/MSWindows/WinQL/GUI/
#	define SOURCES	(WinQLWindowStation)\
					(WinQLWindowFactory)\
					(WinQLWindowClass)\
					(WinQLWindow)\
					(WinQLPaintSession)\
					(WinQLMultilingual)\
					(WinQLMessageHandler)\
					(WinQLMessageBox)\
					(WinQLMenu)\
					(WinQLImageList)\
					(WinQLIcon)\
					(WinQL-GUI)\
					(WinQLGUI)\
					(WinQLDragDropReg)\
					(WinQLDialog)\
					(WinQLDesktop)\
					(WinQLDeferWindowPos)\
					(WinQLCursor)\
					(WinQLCommonCtrl)\
					(WinQLCaret)\
					(WinQLAcceleratorTable)
#	include "BuildQOR/BuildGroup.pph"

#	define SOURCE_PATH ../../../Source/SystemQOR/MSWindows/WinQL/GUI/Rendering/
#	define SOURCES	(WinQLDirectComposition)
#	include "BuildQOR/BuildGroup.pph"

#	define SOURCE_PATH ../../../Source/SystemQOR/MSWindows/WinQL/GUI/Windows/
#	define SOURCES	(WinQLAnimate)\
					(WinQLButton)\
					(WinQLComboBox)\
					(WinQLComboBoxEx)\
					(WinQLDateTimePicker)\
					(WinQLDialogFactory)\
					(WinQLDragListBox)\
					(WinQLEdit)\
					(WinQLFrameClient)\
					(WinQLFrameWindow)\
					(WinQLHeader)\
					(WinQLHotKey)\
					(WinQLIPAddress)\
					(WinQLListBox)\
					(WinQLListCtrl)\
					(WinQLMDIChildFrame)\
					(WinQLMDIClientWindow)\
					(WinQLMDIFrameWindow)\
					(WinQLMonthCalendar)\
					(WinQLPager)\
					(WinQLProgressBar)\
					(WinQLRebar)\
					(WinQLScrollBar)\
					(WinQLStatic)\
					(WinQLStatusBar)\
					(WinQLSubclassWindow)\
					(WinQLSysLink)\
					(WinQLTab)\
					(WinQLToolbar)\
					(WinQLToolTip)\
					(WinQLTrackbar)\
					(WinQLTreeView)\
					(WinQLUpDown)
#	include "BuildQOR/BuildGroup.pph"

#	define SOURCE_PATH ../../../Source/SystemQOR/MSWindows/WinQL/GUI/VisualModels/
#	define SOURCES	(WinQLBitmapModel)\
					(WinQLBrushModel)\
					(WinQLButtonVisMod)\
					(WinQLCursorModel)\
					(WinQLFrameWindowClassModel)\
					(WinQLFrameWindowModel)\
					(WinQLFrameWindowStyleModel)\
					(WinQLIconModel)\
					(WinQLMenuModel)\
					(WinQLWindowClassModel)\
					(WinQLWindowLayoutModel)\
					(WinQLWindowModel)\
					(WinQLWindowStyleModel)
#	include "BuildQOR/BuildGroup.pph"

#	define SOURCE_PATH ../../../Source/SystemQOR/MSWindows/WinQL/GUI/Views/
#	define SOURCES	(WinQLBrushFactory)\
					(WinQLCursorFactory)\
					(WinQLDialogView)\
					(WinQLFrameWindowClassFactory)\
					(WinQLFrameWindowView)\
					(WinQLIconFactory)\
					(WinQLInteractiveWindowView)\
					(WinQLMDIChildFrameView)\
					(WinQLMDIFrameView)\
					(WinQLMenuFactory)\
					(WinQLOwnerView)\
					(WinQLParentView)\
					(WinQLRenderedWindowView)\
					(WinQLRowView)\
					(WinQLWinCtrlViews)\
					(WinQLWindowClassFactory)\
					(WinQLWindowView)\
					(WinQLWorkspaceView)
#	include "BuildQOR/BuildGroup.pph"

#	define SOURCE_PATH ../../../Source/SystemQOR/MSWindows/WinQL/GUI/Theme/
#	define SOURCES	(WinQLBufferedAnimation)\
					(WinQLBufferPaintSession)\
					(WinQLPanningFeedback)\
					(WinQLThemeData)
#	include "BuildQOR/BuildGroup.pph"

#	define SOURCE_PATH ../../../Source/SystemQOR/MSWindows/WinQL/GUI/Controllers/
#	define SOURCES	(WinQLAppWindowController)\
					(WinQLBaseWindowController)\
					(WinQLButtonController)\
					(WinQLChildFrameController)\
					(WinQLContainerController)\
					(WinQLDragListParentController)\
					(WinQLFrameMenuController)\
					(WinQLFrameNCController)\
					(WinQLFrameRenderingController)\
					(WinQLFrameScrollController)\
					(WinQLFrameWindowController)\
					(WinQLInteractiveWindowController)\
					(WinQLLayoutController)\
					(WinQLMDIFrameClientController)\
					(WinQLMDIFrameRenderingController)\
					(WinQLMDIFrameWindowController)\
					(WinQLNCButtonController)\
					(WinQLRenderedWindowController)\
					(WinQLRowContainer)
#	include "BuildQOR/BuildGroup.pph"

#	define SOURCE_PATH ../../../Source/SystemQOR/MSWindows/WinQL/GUI/Controllers/Parts/
#	define SOURCES	(WinQLBaseTextController)\
					(WinQLBaseWindowPartController)\
					(WinQLClipboardOwnerController)\
					(WinQLCommonCtrlParentController)\
					(WinQLCursorController)\
					(WinQLDeviceChangeController)\
					(WinQLDragAndDropController)\
					(WinQLFocusController)\
					(WinQLHelpController)\
					(WinQLIconizedController)\
					(WinQLIMEController)\
					(WinQLKeyboardInputController)\
					(WinQLMenuController)\
					(WinQLNCController)\
					(WinQLNCPointerController)\
					(WinQLNCRenderController)\
					(WinQLOwnerController)\
					(WinQLParentController)\
					(WinQLPointerController)\
					(WinQLRenderingController)\
					(WinQLScrollController)\
					(WinQLStyleController)\
					(WinQLTextController)\
					(WinQLTimerController)\
					(WinQLUserController)\
					(WinQLWinCtrlParentController)
#	include "BuildQOR/BuildGroup.pph"

//	Generate the export and import libraries for the module where the linker will require them
#	include "LibCmd2.pph"
#endif