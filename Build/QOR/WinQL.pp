//WinQL.pp

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

//Preprocessor build script generator for WinQL.dll

#include "ModuleHeader.pph"

//Set WinQAPI specific definitions and overrides

#define QOR_MODULE_NAME WinQL

//Append the module specific PP defines to the list from the Operating System
#define QOR_CONFIG_DEFINES_WINQL1 QOR_PP_LIST_APPEND( QOR_CONFIG_DEFINES_OS,("__WINQL") )
#define QOR_CONFIG_DEFINES_WINQL2 QOR_PP_LIST_APPEND( QOR_CONFIG_DEFINES_WINQL1,("_LIBCPP_DLL") )
#define QOR_CONFIG_DEFINES_MODULE QOR_CONFIG_DEFINES_WINQL2


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

#	define SOURCE_PATH ../../../Source/SystemQOR/MSWindows/WinQL/
#	define SOURCES	(WinQL)

#	include "BuildQOR/BuildGroup.pph"

#	define SOURCE_PATH ../../../Source/SystemQOR/MSWindows/WinQL/Application/
#	define SOURCES	(WinQLActCtx)\
					(WinQLApplication)
#	include "BuildQOR/BuildGroup.pph"

#	define SOURCE_PATH ../../../Source/SystemQOR/MSWindows/WinQL/Application/Roles/
#	define SOURCES	(WinQLCmdLineToolRole)\
					(WinQLSystemServiceRole)\
					(WinQLTestingRole)
#	include "BuildQOR/BuildGroup.pph"

#	define SOURCE_PATH ../../../Source/SystemQOR/MSWindows/WinQL/Application/Subsystems/
#	define SOURCES	(WinQLStandardIO)\
					(WinQLTerminal)\
					(WinQLServer)\
					(WinQLThreading)\
					(WinQLBluetooth)\
					(WinQLNetworking)
#	include "BuildQOR/BuildGroup.pph"

#	define SOURCE_PATH ../../../Source/SystemQOR/MSWindows/WinQL/Application/Backup/
#	define SOURCES	(WinQLBackup)
#	include "BuildQOR/BuildGroup.pph"

#	define SOURCE_PATH ../../../Source/SystemQOR/MSWindows/WinQL/Application/Comms/Bluetooth/
#	define SOURCES	(WinQLBluetoothAuthenticateSession)\
					(WinQLBluetoothFindDeviceSession)\
					(WinQLBluetoothFindRadioSession)\
					(WinQLBluetoothRemoteDevice)
#	include "BuildQOR/BuildGroup.pph"

#	define SOURCE_PATH ../../../Source/SystemQOR/MSWindows/WinQL/Application/Comms/IPC/Atoms/
#	define SOURCES	(WinQLAtoms)
#	include "BuildQOR/BuildGroup.pph"

#	define SOURCE_PATH ../../../Source/SystemQOR/MSWindows/WinQL/Application/Comms/IPC/DDE/
#	define SOURCES	(WinQLDDE)\
					(WinQLDDEAppinstance)\
					(WinQLDDEServer)
#	include "BuildQOR/BuildGroup.pph"

#	define SOURCE_PATH ../../../Source/SystemQOR/MSWindows/WinQL/Application/Comms/IPC/MailSlot/
#	define SOURCES	(WinQLMailSlot)
#	include "BuildQOR/BuildGroup.pph"

#	define SOURCE_PATH ../../../Source/SystemQOR/MSWindows/WinQL/Application/Comms/IPC/Pipe/
#	define SOURCES	(WinQLPipe)
#	include "BuildQOR/BuildGroup.pph"

#	define SOURCE_PATH ../../../Source/SystemQOR/MSWindows/WinQL/Application/Comms/Network/
#	define SOURCES	(WinQLAddressInfo)\
					(WinQLAddressRegistration)\
					(WinQLNameInfo)\
					(WinQLNameSpaceProvider)\
					(WinQLNetworkHost)\
					(WinQLProtocolFilter)\
					(WinQLProviderChangeNotification)\
					(WinQLServiceClassRegistration)\
					(WinQLServiceInstanceRegistration)\
					(WinQLServiceLookup)\
					(WinQLSocket)\
					(WinQLSocketEvent)\
					(WinQLSocketHelper)\
					(WinQLTransportProvider)\
					(WinQLWinSockSession)
#	include "BuildQOR/BuildGroup.pph"

#	define SOURCE_PATH ../../../Source/SystemQOR/MSWindows/WinQL/Application/Comms/Serial/
#	define SOURCES	(WinQLComm)
#	include "BuildQOR/BuildGroup.pph"

#	define SOURCE_PATH ../../../Source/SystemQOR/MSWindows/WinQL/Application/Console/
#	define SOURCES	(WinQLConsole)\
					(WinQLConsoleAliases)\
					(WinQLConsoleHelper)\
					(WinQLConsoleScreenBuffer)
#	include "BuildQOR/BuildGroup.pph"

#	define SOURCE_PATH ../../../Source/SystemQOR/MSWindows/WinQL/Application/ErrorSystem/
#	define SOURCES	(WinQLDebugging)\
					(WinQLDOSError)\
					(WinQLErrDomain)\
					(WinQLError)\
					(WinQLErrorHandling)\
					(WinQLExceptionFrame)\
					(WinQLFlagChecks)\
					(WinQLParamErrorDomain)\
					(WinQLParameterCheck)\
					(WinQLPointerChecks)\
					(WinQLSEH)\
					(WinQLStringChecks)
#	include "BuildQOR/BuildGroup.pph"

#	define SOURCE_PATH ../../../Source/SystemQOR/MSWindows/WinQL/Application/Event/
#	define SOURCES	(WinQLWinEventClient)\
					(WinQLWinEventServer)
#	include "BuildQOR/BuildGroup.pph"

#	define SOURCE_PATH ../../../Source/SystemQOR/MSWindows/WinQL/Application/Graphics/
#	define SOURCES	(WinQLBitmap)\
					(WinQLBrush)\
					(WinQLDeviceContext)\
					(WinQLDisplay)\
					(WinQLEnhMetaFile)\
					(WinQLFont)\
					(WinQLGDIObj)\
					(WinQLMetaFile)\
					(WinQLPalette)\
					(WinQLPen)\
					(WinQLRectangle)\
					(WinQLRegion)
#	include "BuildQOR/BuildGroup.pph"

#	define SOURCE_PATH ../../../Source/SystemQOR/MSWindows/WinQL/Application/Graphics/DeviceContext/
#	define SOURCES	(WinQLDCInternal)
#	include "BuildQOR/BuildGroup.pph"

#	define SOURCE_PATH ../../../Source/SystemQOR/MSWindows/WinQL/Application/I18n/
#	define SOURCES	(WinQLI18n)
#	include "BuildQOR/BuildGroup.pph"

#	define SOURCE_PATH ../../../Source/SystemQOR/MSWindows/WinQL/Application/IO/
#	define SOURCES	(WinQLIOServer)\
					(WinQLOverlappedHandler)
#	include "BuildQOR/BuildGroup.pph"

#	define SOURCE_PATH ../../../Source/SystemQOR/MSWindows/WinQL/Application/IO/File/
#	define SOURCES	(WinQLFileConnector)\
					(WinQLFileSink)\
					(WinQLFileSource)
#	include "BuildQOR/BuildGroup.pph"

#	define SOURCE_PATH ../../../Source/SystemQOR/MSWindows/WinQL/Application/IO/MailSlot/
#	define SOURCES	(WinQLMailSlotConnector)\
					(WinQLMailSlotSink)\
					(WinQLMailSlotSource)
#	include "BuildQOR/BuildGroup.pph"

#	define SOURCE_PATH ../../../Source/SystemQOR/MSWindows/WinQL/Application/IO/Pipe/
#	define SOURCES	(WinQLPipeClientAdaptor)\
					(WinQLPipeConnector)\
					(WinQLPipeServer)\
					(WinQLPipeServerAdaptor)\
					(WinQLPipeSink)\
					(WinQLPipeSource)
#	include "BuildQOR/BuildGroup.pph"

#	define SOURCE_PATH ../../../Source/SystemQOR/MSWindows/WinQL/Application/Memory/
#	define SOURCES	(WinQLAllocator)\
					(WinQLExePageAllocator)\
					(WinQLGlobal)\
					(WinQLHeap)\
					(WinQLLocal)\
					(WinQLMemFile)\
					(WinQLMemory)\
					(WinQLVirtualMemory)
#	include "BuildQOR/BuildGroup.pph"

#	define SOURCE_PATH ../../../Source/SystemQOR/MSWindows/WinQL/Application/Process/
#	define SOURCES	(WinQLAtExit)\
					(WinQLCommandLine)\
					(WinQLEnvironment)\
					(WinQLJob)\
					(WinQLProcess)\
					(WinQLProcessHelper)\
					(WinQLProcThreadAttribList)\
					(WinQLRemoteProcess)\
					(WinQLTerminate)
#	include "BuildQOR/BuildGroup.pph"

#	define SOURCE_PATH ../../../Source/SystemQOR/MSWindows/WinQL/Application/RecoveryAndRestart/
#	define SOURCES	(WinQLAppRecovery)\
					(WinQLAppRestart)
#	include "BuildQOR/BuildGroup.pph"

#	define SOURCE_PATH ../../../Source/SystemQOR/MSWindows/WinQL/Application/Resources/
#	define SOURCES	(WinQLResourceManager)\
					(WinQLResources)\
					(WinQLResourceUpdateHandle)
#	include "BuildQOR/BuildGroup.pph"

#	define SOURCE_PATH ../../../Source/SystemQOR/MSWindows/WinQL/Application/Threading/
#	define SOURCES	(WinQLBoundaryDescriptor)\
					(WinQLConditionVariable)\
					(WinQLCriticalSection)\
					(WinQLEvent)\
					(WinQLFiber)\
					(WinQLFLS)\
					(WinQLInitOnce)\
					(WinQLMutex)\
					(WinQLPrivateNamespace)\
					(WinQLSemaphore)\
					(WinQLSList)\
					(WinQLSRWLock)\
					(WinQLSynchronization)\
					(WinQLThread)\
					(WinQLThreadAffinity)\
					(WinQLThreadImpl)\
					(WinQLThreadPool)\
					(WinQLThreadState)\
					(WinQLTLS)\
					(WinQLWait)\
					(WinQLWaitableObject)
#	include "BuildQOR/BuildGroup.pph"

#	define SOURCE_PATH ../../../Source/SystemQOR/MSWindows/WinQL/Application/Timer/
#	define SOURCES	(WinQLTimer)\
					(WinQLTimerQueue)\
					(WinQLWaitableTimer)
#	include "BuildQOR/BuildGroup.pph"

#	define SOURCE_PATH ../../../Source/SystemQOR/MSWindows/WinQL/Application/User/
#	define SOURCES	(WinQLUserObject)
#	include "BuildQOR/BuildGroup.pph"

#	define SOURCE_PATH ../../../Source/SystemQOR/MSWindows/WinQL/Bootstrap/
#	define SOURCES	(WinQLModuleBootstrap)\
					(WinQLProcessBootstrap)\
					(WinQLSharedBootstrap)
#	include "BuildQOR/BuildGroup.pph"

//#	define SOURCE_PATH ../../../Source/SystemQOR/MSWindows/WinQL/CodeServices/ErrorSystem/
//#	define SOURCES	(WinQLErrDomain)\
//					(WinQLError)\
//					(WinQLErrorHandling)\
//					(WinQLExceptionFrame)\
//					(WinQLFunctionContext)
//#	include "BuildQOR/BuildGroup.pph"

#	define SOURCE_PATH ../../../Source/SystemQOR/MSWindows/WinQL/CodeServices/Handles/
#	define SOURCES	(WinQLHandle)\
					(WinQLRAIISessionHandle)\
					(WinQLSyncHandle)
#	include "BuildQOR/BuildGroup.pph"

#	define SOURCE_PATH ../../../Source/SystemQOR/MSWindows/WinQL/CodeServices/Hook/
#	define SOURCES	(WinQLHook)
#	include "BuildQOR/BuildGroup.pph"

#	define SOURCE_PATH ../../../Source/SystemQOR/MSWindows/WinQL/CodeServices/Locale/
#	define SOURCES	(WinQLCharData)\
					(WinQLGeoLocation)\
					(WinQLLocale)\
					(WinQLLocaleConv)\
					(WinQLLocaleNames)\
					(WinQLLocaleThreadData)\
					(WinQLLocaleUpdate)\
					(WinQLMBCInfo)\
					(WinQLSetLoc)\
					(WinQLThreadLocaleInfo)
#	include "BuildQOR/BuildGroup.pph"

//#	define SOURCE_PATH ../../../Source/SystemQOR/MSWindows/WinQL/CodeServices/Memory/
//#	define SOURCES	(WinQLHeap)
//#	include "BuildQOR/BuildGroup.pph"

#	define SOURCE_PATH ../../../Source/SystemQOR/MSWindows/WinQL/CodeServices/Module/
#	define SOURCES	(WinQLDll)\
					(WinQLWinModule)
#	include "BuildQOR/BuildGroup.pph"

#	define SOURCE_PATH ../../../Source/SystemQOR/MSWindows/WinQL/CodeServices/Text/
#	define SOURCES	(WinQLChar)\
					(WinQLCodePage)\
					(WinQLFormatter)\
					(WinQLString)\
					(WinQLStringServices)
					//(WinString)
#	include "BuildQOR/BuildGroup.pph"

#	define SOURCE_PATH ../../../Source/SystemQOR/MSWindows/WinQL/CodeServices/Text/BluefootFilters/
#	define SOURCES	(WinQLANSICodePointFilter)\
					(WinQLCodePointANSIFilter)
#	include "BuildQOR/BuildGroup.pph"

//#	define SOURCE_PATH ../../../Source/SystemQOR/MSWindows/WinQL/CodeServices/Threading/
//#	define SOURCES	(WinQLCriticalSection)\
//					(WinQLMutex)\
//					(WinQLThread)\
//					(WinQLThreadAffinity)\
//					(WinQLThreadImpl)\
//					(WinQLThreadState)
//#	include "BuildQOR/BuildGroup.pph"

#	define SOURCE_PATH ../../../Source/SystemQOR/MSWindows/WinQL/CodeServices/Tracing/
#	define SOURCES	(WinQLDebugTrace)
#	include "BuildQOR/BuildGroup.pph"

//#	define SOURCE_PATH ../../../Source/SystemQOR/MSWindows/WinQL/COM/
//#	define SOURCES	()\
//#	include "BuildQOR/BuildGroup.pph"

//#	define SOURCE_PATH ../../../Source/SystemQOR/MSWindows/WinQL/DeviceIO/
//#	define SOURCES	(WinQLDeviceFile)\
//					(WinQLDeviceHandle)
//#	include "BuildQOR/BuildGroup.pph"

//#	define SOURCE_PATH ../../../Source/SystemQOR/MSWindows/WinQL/FileSystem/
//#	define SOURCES	(WinQLFile)\
//					(WinQLFileHandle)\
//					(WinQLFileManagement)
//#	include "BuildQOR/BuildGroup.pph"

//#	define SOURCE_PATH ../../../Source/SystemQOR/MSWindows/WinQL/GUI/
//#	define SOURCES	()\
//#	include "BuildQOR/BuildGroup.pph"

//#	define SOURCE_PATH ../../../Source/SystemQOR/MSWindows/WinQL/MediaFoundation/
//#	define SOURCES	()\
//#	include "BuildQOR/BuildGroup.pph"

//#	define SOURCE_PATH ../../../Source/SystemQOR/MSWindows/WinQL/OLEDB/
//#	define SOURCES	(WinQL-OLEDB)
//#	include "BuildQOR/BuildGroup.pph"
//
//#	define SOURCE_PATH ../../../Source/SystemQOR/MSWindows/WinQL/OLEDB/Consumer/
//#	define SOURCES	(DBPropSet)\
//					(OLEDBEnumerator)
//#	include "BuildQOR/BuildGroup.pph"
//
//#	define SOURCE_PATH ../../../Source/SystemQOR/MSWindows/WinQL/OLEDB/Consumer/Clients/
//#	define SOURCES	(DBInitializer)\
//					(DBProperties)
//#	include "BuildQOR/BuildGroup.pph"

//#	define SOURCE_PATH ../../../Source/SystemQOR/MSWindows/WinQL/QursesGUI/
//#	define SOURCES	(WinQLQursesGUI)
//#	include "BuildQOR/BuildGroup.pph"

#	define SOURCE_PATH ../../../Source/SystemQOR/MSWindows/WinQL/System/
#	define SOURCES	(WinQLSystem)\
					(WinQLSystemHelper)
#	include "BuildQOR/BuildGroup.pph"

#	define SOURCE_PATH ../../../Source/SystemQOR/MSWindows/WinQL/System/Atoms/
#	define SOURCES	(WinQLGlobalAtoms)
#	include "BuildQOR/BuildGroup.pph"

#	define SOURCE_PATH ../../../Source/SystemQOR/MSWindows/WinQL/System/Clipboard/
#	define SOURCES	(WinQLClipboard)
#	include "BuildQOR/BuildGroup.pph"

#	define SOURCE_PATH ../../../Source/SystemQOR/MSWindows/WinQL/System/Clock/
#	define SOURCES	(WinQLTime)
#	include "BuildQOR/BuildGroup.pph"

#	define SOURCE_PATH ../../../Source/SystemQOR/MSWindows/WinQL/System/Devices/
#	define SOURCES	(WinQLConfigManSession)\
					(WinQLDeviceFile)\
					(WinQLDeviceHandle)\
					(WinQLDeviceManager)\
					(WinQLDeviceNode)\
					(WinQLNotification)\
					(WinQLNotificationFilter)\
					(WinQLIODevice)
#	include "BuildQOR/BuildGroup.pph"

#	define SOURCE_PATH ../../../Source/SystemQOR/MSWindows/WinQL/System/Devices/WindowsPortableDevices/
#	define SOURCES	(WinQLWindowsPortableDevice)\
					(WinQLWPDPrivate)
#	include "BuildQOR/BuildGroup.pph"

#	define SOURCE_PATH ../../../Source/SystemQOR/MSWindows/WinQL/System/Devices/USB/
#	define SOURCES	(WinQLUSBDevice)\
					(WinQLUSBHostController)\
					(WinQLUSBHub)\
					(WinQLUSBHubPort)
#	include "BuildQOR/BuildGroup.pph"

#	define SOURCE_PATH ../../../Source/SystemQOR/MSWindows/WinQL/System/Devices/ThermalZone/
#	define SOURCES	(WinQLThermalZone)
#	include "BuildQOR/BuildGroup.pph"

#	define SOURCE_PATH ../../../Source/SystemQOR/MSWindows/WinQL/System/Devices/SystemButton/
#	define SOURCES	(WinQLSystemButton)
#	include "BuildQOR/BuildGroup.pph"

#	define SOURCE_PATH ../../../Source/SystemQOR/MSWindows/WinQL/System/Devices/Storage/
#	define SOURCES	(WinQLCDChanger)\
					(WinQLCDROM)\
					(WinQLDisk)\
					(WinQLFloppy)\
					(WinQLMediumChanger)\
					(WinQLPartition)\
					(WinQLStoragePort)\
					(WinQLTape)\
					(WinQLVolumeDevice)\
					(WinQLWriteOnceDisk)
#	include "BuildQOR/BuildGroup.pph"

#	define SOURCE_PATH ../../../Source/SystemQOR/MSWindows/WinQL/System/Devices/Slideshow/
#	define SOURCES	(WinQLSlideshow)
#	include "BuildQOR/BuildGroup.pph"

#	define SOURCE_PATH ../../../Source/SystemQOR/MSWindows/WinQL/System/Devices/SetupClasses/
#	define SOURCES	(WinQLDeviceInfoSet)\
					(WinQLDeviceSetupClass)\
					(WinQLDeviceSetupClassEnumerator)
#	include "BuildQOR/BuildGroup.pph"

#	define SOURCE_PATH ../../../Source/SystemQOR/MSWindows/WinQL/System/Devices/RawInput/
#	define SOURCES	(WinQLRawInput)
#	include "BuildQOR/BuildGroup.pph"

#	define SOURCE_PATH ../../../Source/SystemQOR/MSWindows/WinQL/System/Devices/Processor/
#	define SOURCES	(WinQLProcessor)
#	include "BuildQOR/BuildGroup.pph"

#	define SOURCE_PATH ../../../Source/SystemQOR/MSWindows/WinQL/System/Devices/Ports/
#	define SOURCES	(WinQLCOMPortDevice)\
					(WinQLParallelClass)\
					(WinQLParallelPortDevice)\
					(WinQLSerialBusEnumerator)
#	include "BuildQOR/BuildGroup.pph"

#	define SOURCE_PATH ../../../Source/SystemQOR/MSWindows/WinQL/System/Devices/Network/
#	define SOURCES	(WinQLNetworkDevice)
#	include "BuildQOR/BuildGroup.pph"

#	define SOURCE_PATH ../../../Source/SystemQOR/MSWindows/WinQL/System/Devices/Mouse/
#	define SOURCES	(WinQLMouse)
#	include "BuildQOR/BuildGroup.pph"

#	define SOURCE_PATH ../../../Source/SystemQOR/MSWindows/WinQL/System/Devices/Modem/
#	define SOURCES	(WinQLModem)
#	include "BuildQOR/BuildGroup.pph"

#	define SOURCE_PATH ../../../Source/SystemQOR/MSWindows/WinQL/System/Devices/MessageIndicator/
#	define SOURCES	(WinQLMessageIndicator)
#	include "BuildQOR/BuildGroup.pph"

#	define SOURCE_PATH ../../../Source/SystemQOR/MSWindows/WinQL/System/Devices/Memory/
#	define SOURCES	(WinQLMemoryDevice)
#	include "BuildQOR/BuildGroup.pph"

#	define SOURCE_PATH ../../../Source/SystemQOR/MSWindows/WinQL/System/Devices/Keyboard/
#	define SOURCES	(WinQLDefaultKeyboard)\
					(WinQLHotKey)\
					(WinQLKeyboardDevice)\
					(WinQLKeyboardInput)\
					(WinQLKeyboardLayout)
#	include "BuildQOR/BuildGroup.pph"

#	define SOURCE_PATH ../../../Source/SystemQOR/MSWindows/WinQL/System/Devices/Interfaces/
#	define SOURCES	(WinQLDeviceInterface)\
					(WinQLDeviceInterfaceClass)\
					(WinQLDeviceInterfaceClassCollection)
#	include "BuildQOR/BuildGroup.pph"

#	define SOURCE_PATH ../../../Source/SystemQOR/MSWindows/WinQL/System/Devices/Instances/
#	define SOURCES	(WinQLDeviceCollection)\
					(WinQLDeviceInstance)\
					(WinQLDeviceInstanceCollection)\
					(WinQLDeviceInstanceEnumerator)
#	include "BuildQOR/BuildGroup.pph"

#	define SOURCE_PATH ../../../Source/SystemQOR/MSWindows/WinQL/System/Devices/Input/
#	define SOURCES	(WinQLHID)
#	include "BuildQOR/BuildGroup.pph"

#	define SOURCE_PATH ../../../Source/SystemQOR/MSWindows/WinQL/System/Devices/FireWire/
#	define SOURCES	(WinQL1394)\
					(WinQL61883)
#	include "BuildQOR/BuildGroup.pph"

#	define SOURCE_PATH ../../../Source/SystemQOR/MSWindows/WinQL/System/Devices/Enumerator/
#	define SOURCES	(WinQLDeviceEnumerator)\
					(WinQLRootDeviceEnumerator)
#	include "BuildQOR/BuildGroup.pph"

#	define SOURCE_PATH ../../../Source/SystemQOR/MSWindows/WinQL/System/Devices/Drivers/
#	define SOURCES	(WinQLDeviceDriver)\
					(WinQLDeviceDriverCollection)
#	include "BuildQOR/BuildGroup.pph"

#	define SOURCE_PATH ../../../Source/SystemQOR/MSWindows/WinQL/System/Devices/DisplayAndImage/
#	define SOURCES	(WinQLBrightness)\
					(WinQLDisplayAdapter)\
					(WinQLDisplayDeviceArrival)\
					(WinQLI2C)\
					(WinQLImage)\
					(WinQLMonitor)\
					(WinQLOPM)\
					(WinQLVideoOutputArrival)
#	include "BuildQOR/BuildGroup.pph"

#	define SOURCE_PATH ../../../Source/SystemQOR/MSWindows/WinQL/System/Devices/BluetoothRadio/
#	define SOURCES	(WinQLBluetoothRadio)
#	include "BuildQOR/BuildGroup.pph"

#	define SOURCE_PATH ../../../Source/SystemQOR/MSWindows/WinQL/System/Devices/Battery/
#	define SOURCES	(WinQLBattery)
#	include "BuildQOR/BuildGroup.pph"

#	define SOURCE_PATH ../../../Source/SystemQOR/MSWindows/WinQL/System/Devices/ApplicationLaunchButton/
#	define SOURCES	(WinQLApplicationLaunchButton)
#	include "BuildQOR/BuildGroup.pph"

#	define SOURCE_PATH ../../../Source/SystemQOR/MSWindows/WinQL/System/Devices/ACPI_Lid/
#	define SOURCES	(WinQLLid)
#	include "BuildQOR/BuildGroup.pph"

#	define SOURCE_PATH ../../../Source/SystemQOR/MSWindows/WinQL/System/EventLogging/
#	define SOURCES	(WinQLClassicControllerSession)\
					(WinQLClassicProviderSession)\
					(WinQLEventLog)
#	include "BuildQOR/BuildGroup.pph"

#	define SOURCE_PATH ../../../Source/SystemQOR/MSWindows/WinQL/System/FileSystem/
#	define SOURCES	(WinQLCRTFile)\
					(WinQLDiskManagement)\
					(WinQLFile)\
					(WinQLFileHandle)\
					(WinQLFileManagement)\
					(WinQLFileSystem)\
					(WinQLFindFile)\
					(WinQLFolderManagement)\
					(WinQLIOBuffer)\
					(WinQLIOCompletionPort)\
					(WinQLIOStream)\
					(WinQLStream)\
					(WinQLStreamFormatter)\
					(WinQLVolume)\
					(WinQLVolumeManagement)
#	include "BuildQOR/BuildGroup.pph"

#	define SOURCE_PATH ../../../Source/SystemQOR/MSWindows/WinQL/System/Info/
#	define SOURCES	(WinQLInfo)\
					(WinQLSystemInfoHelper)
#	include "BuildQOR/BuildGroup.pph"

#	define SOURCE_PATH ../../../Source/SystemQOR/MSWindows/WinQL/System/Locale/
#	define SOURCES	(WinQLSystemLocale)
#	include "BuildQOR/BuildGroup.pph"

#	define SOURCE_PATH ../../../Source/SystemQOR/MSWindows/WinQL/System/Performance/
#	define SOURCES	(WinQLPerformanceHelper)
#	include "BuildQOR/BuildGroup.pph"

#	define SOURCE_PATH ../../../Source/SystemQOR/MSWindows/WinQL/System/Power/
#	define SOURCES	(WinQLPowerManagement)
#	include "BuildQOR/BuildGroup.pph"

#	define SOURCE_PATH ../../../Source/SystemQOR/MSWindows/WinQL/System/ProcessManager/
#	define SOURCES	(WinQLProcessManager)\
					(WinQLServiceController)\
					(WinQLServiceControlManager)\
					(WinQLServiceControlSession)
#	include "BuildQOR/BuildGroup.pph"

#	define SOURCE_PATH ../../../Source/SystemQOR/MSWindows/WinQL/System/Registry/
#	define SOURCES	(WinQLRegistry)\
					(WinQLRegistryHelper)
#	include "BuildQOR/BuildGroup.pph"

#	define SOURCE_PATH ../../../Source/SystemQOR/MSWindows/WinQL/System/Security/
#	define SOURCES	(WinQLAccessControlList)\
					(WinQLAccessToken)\
					(WinQLAuthorization)\
					(WinQLExplicitAccess)\
					(WinQLImpersonation)\
					(WinQLLocalSecAuthority)\
					(WinQLLSAPolicy)\
					(WinQLLUID)\
					(WinQLSecurityDescriptor)\
					(WinQLTrustee)
#	include "BuildQOR/BuildGroup.pph"

#	define SOURCE_PATH ../../../Source/SystemQOR/MSWindows/WinQL/System/Session/
#	define SOURCES	(WinQLSession)
#	include "BuildQOR/BuildGroup.pph"

#	define SOURCE_PATH ../../../Source/SystemQOR/MSWindows/WinQL/System/TerminalServices/
#	define SOURCES	(WinQLTerminalServices)
#	include "BuildQOR/BuildGroup.pph"

#	define SOURCE_PATH ../../../Source/SystemQOR/MSWindows/WinQL/System/User/
#	define SOURCES	(WinQLUser)
#	include "BuildQOR/BuildGroup.pph"



//	Generate the export and import libraries for the module where the linker will require them
#	include "LibCmd2.pph"
#endif
