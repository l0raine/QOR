//WinQLFile.h

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

#ifndef WINQL_FILESYSTEM_FILE_H_3
#define WINQL_FILESYSTEM_FILE_H_3

#ifdef	__QCMP_OPTIMIZEINCLUDE
#pragma	__QCMP_OPTIMIZEINCLUDE
#endif//__QCMP_OPTIMIZEINCLUDE

#include "WinQL/System/Devices/WinQLDeviceFile.h"
#include "WinQL/System/FileSystem/WinQLFileHandle.h"
#include "WinQL/System/FileSystem/WinQLFileManagement.h"

//--------------------------------------------------------------------------------
namespace nsWin32
{
	
	//--------------------------------------------------------------------------------
	typedef enum _FILE_ID_TYPE 
	{
		  FileIdType,
		  ObjectIdType,
		  MaximumFileIdType
	} FILE_ID_TYPE, *PFILE_ID_TYPE;

	//--------------------------------------------------------------------------------
	typedef struct FILE_ID_DESCRIPTOR 
	{
		unsigned long dwSize;  // Size of the struct
		FILE_ID_TYPE Type; // Describes the type of identifier passed in.

__QCMP_WARNING_PUSH
__QCMP_WARNING_DISABLE( __QCMP_WARN_NAMELESS_STRUCTUNION, "Deliberate use of Microsoft extension" )

		union __QCMP_NAMELESS_STRUCT
		{
			nsWin32::LARGE_INTEGER FileId;
			struct
			{
				unsigned long int Data1;
				unsigned short int Data2;
				unsigned short int Data3;
				unsigned char Data4[8];
			}ObjectId;
		} DUMMYUNIONNAME;

__QCMP_WARNING_POP

	} FILE_ID_DESCRIPTOR, *LPFILE_ID_DESCRIPTOR;

	//--------------------------------------------------------------------------------
	typedef struct _BY_HANDLE_FILE_INFORMATION 
	{
		unsigned long dwFileAttributes;
		FILETIME ftCreationTime;
		FILETIME ftLastAccessTime;
		FILETIME ftLastWriteTime;
		unsigned long dwVolumeSerialNumber;
		unsigned long nFileSizeHigh;
		unsigned long nFileSizeLow;
		unsigned long nNumberOfLinks;
		unsigned long nFileIndexHigh;
		unsigned long nFileIndexLow;
	} BY_HANDLE_FILE_INFORMATION, *PBY_HANDLE_FILE_INFORMATION, *LPBY_HANDLE_FILE_INFORMATION;
	
	//--------------------------------------------------------------------------------
	typedef enum _FILE_INFO_BY_HANDLE_CLASS 
	{
		FileBasicInfo,
		FileStandardInfo,
		FileNameInfo,
		FileRenameInfo,
		FileDispositionInfo,
		FileAllocationInfo,
		FileEndOfFileInfo,
		FileStreamInfo,
		FileCompressionInfo,
		FileAttributeTagInfo,
		FileIdBothDirectoryInfo,
		FileIdBothDirectoryRestartInfo,
		FileIoPriorityHintInfo,
		FileRemoteProtocolInfo, 
		MaximumFileInfoByHandleClass
	} FILE_INFO_BY_HANDLE_CLASS, *PFILE_INFO_BY_HANDLE_CLASS;

	//--------------------------------------------------------------------------------
	typedef union _FILE_SEGMENT_ELEMENT 
	{
		void* Buffer;
		Cmp_unsigned_long_long Alignment;
	}FILE_SEGMENT_ELEMENT, *PFILE_SEGMENT_ELEMENT;

	//--------------------------------------------------------------------------------	
	class __QOR_INTERFACE( __WINQL ) CFile : public nsWin32::CDeviceFile
	{
	public:

		CFile();
		CFile( CFileHandle& hExisting );
		CFile( const char* lpFileName, unsigned long dwDesiredAccess, unsigned long dwShareMode, nsWin32::LPSECURITY_ATTRIBUTES lpSecurityAttributes, unsigned long dwCreationDisposition, unsigned long dwFlagsAndAttributes, void* hTemplateFile );
		CFile( const wchar_t* lpFileName, unsigned long dwDesiredAccess, unsigned long dwShareMode, nsWin32::LPSECURITY_ATTRIBUTES lpSecurityAttributes, unsigned long dwCreationDisposition, unsigned long dwFlagsAndAttributes, void* hTemplateFile );
		CFile( const TCHAR* lpFileName, unsigned long dwDesiredAccess, unsigned long dwShareMode, nsWin32::LPSECURITY_ATTRIBUTES lpSecurityAttributes, unsigned long dwCreationDisposition, unsigned long dwFlagsAndAttributes, void* hTemplateFile, void* hTransaction, unsigned short* pusMiniVersion, void* pExtendedParameter );
		CFile( const char* lpFileName, nsWin32::LPOFSTRUCT lpReOpenBuff, unsigned int uStyle );
		CFile( CFileHandle& hFile, nsWin32::LPFILE_ID_DESCRIPTOR lpFileID, unsigned long dwDesiredAccess, unsigned long dwShareMode, nsWin32::LPSECURITY_ATTRIBUTES lpSecurityAttributes, unsigned long dwFlags );
		virtual ~CFile();

		bool CancelIo( void );
		bool CancelIoEx( nsWin32::LPOVERLAPPED lpOverlapped );
		bool FlushBuffers();
		bool GetBandwidthReservation( unsigned long* lpPeriodMilliseconds, unsigned long* lpBytesPerPeriod, int* pDiscardable, unsigned long* lpTransferSize, unsigned long* lpNumOutstandingRequests );
		bool GetInformation( nsWin32::LPBY_HANDLE_FILE_INFORMATION lpFileInformation );
		bool GetInformationEx( nsWin32::FILE_INFO_BY_HANDLE_CLASS FileInformationClass, void* lpFileInformation, unsigned long dwBufferSize );
		unsigned long GetSize( unsigned long* lpFileSizeHigh );
		bool GetSizeEx( nsWin32::LARGE_INTEGER* lpFileSize );
		unsigned long GetType();
		unsigned long GetFinalPathName( TCHAR* lpszFilePath, unsigned long cchFilePath, unsigned long dwFlags );
		bool Lock( unsigned long dwFileOffsetLow, unsigned long dwFileOffsetHigh, unsigned long nNumberOfBytesToLockLow, unsigned long nNumberOfBytesToLockHigh );
		bool LockEx( unsigned long dwFlags, unsigned long dwReserved, unsigned long nNumberOfBytesToLockLow, unsigned long nNumberOfBytesToLockHigh, nsWin32::LPOVERLAPPED lpOverlapped );
		bool Read( void* lpBuffer, unsigned long nNumberOfBytesToRead, unsigned long* lpNumberOfBytesRead, nsWin32::LPOVERLAPPED lpOverlapped );
		bool ReadEx( void* lpBuffer, unsigned long nNumberOfBytesToRead, nsWin32::LPOVERLAPPED lpOverlapped, nsWin32::LPOVERLAPPED_COMPLETION_ROUTINE lpCompletionRoutine );
		bool ReadScatter( nsWin32::FILE_SEGMENT_ELEMENT aSegmentArray[], unsigned long nNumberOfBytesToRead, unsigned long* lpReserved, nsWin32::LPOVERLAPPED lpOverlapped );
		CFile& ReOpen( unsigned long dwDesiredAccess, unsigned long dwShareMode, unsigned long dwFlags );
		bool SetEOF();
		bool SetBandwidthReservation( unsigned long nPeriodMilliseconds, unsigned long nBytesPerPeriod, bool bDiscardable, unsigned long* lpTransferSize, unsigned long* lpNumOutstandingRequests );
		bool SetCompletionNotificationModes( unsigned char Flags );
		bool SetInformation( nsWin32::FILE_INFO_BY_HANDLE_CLASS FileInformationClass, void* lpFileInformation, unsigned long dwBufferSize );
		bool SetIoOverlappedRange( unsigned char* OverlappedRangeStart, unsigned long Length );
		unsigned long SetPointer( long lDistanceToMove, long* lpDistanceToMoveHigh, unsigned long dwMoveMethod );
		bool SetPointerEx( nsWin32::LARGE_INTEGER liDistanceToMove, nsWin32::LARGE_INTEGER* lpNewFilePointer, unsigned long dwMoveMethod );
		bool SetShortName( const TCHAR* lpShortName );
		bool SetValidData( Cmp_long_long ValidDataLength );
		bool Unlock( unsigned long dwFileOffsetLow, unsigned long dwFileOffsetHigh, unsigned long nNumberOfBytesToUnlockLow, unsigned long nNumberOfBytesToUnlockHigh );
		bool UnlockEx( unsigned long dwReserved, unsigned long nNumberOfBytesToUnlockLow, unsigned long nNumberOfBytesToUnlockHigh, nsWin32::LPOVERLAPPED lpOverlapped );
		bool Write( const void* lpBuffer, unsigned long nNumberOfBytesToWrite, unsigned long* lpNumberOfBytesWritten, nsWin32::LPOVERLAPPED lpOverlapped );
		bool WriteEx( const void* lpBuffer, unsigned long  nNumberOfBytesToWrite, nsWin32::LPOVERLAPPED lpOverlapped, nsWin32::LPOVERLAPPED_COMPLETION_ROUTINE lpCompletionRoutine );
		bool WriteGather( nsWin32::FILE_SEGMENT_ELEMENT aSegmentArray[], unsigned long nNumberOfBytesToWrite, unsigned long* lpReserved, nsWin32::LPOVERLAPPED lpOverlapped );
		bool IsOpen( void );

	private:

		CFile( const CFile& );
		CFile& operator = ( const CFile& );
	};

}//nsWin32

#endif//WINQL_FILESYSTEM_FILE_H_3