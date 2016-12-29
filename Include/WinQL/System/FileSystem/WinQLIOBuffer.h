//WinQLIOBuffer.h

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

#ifndef WINQL_FILESYSTEM_IOBUFFER_H_3
#define WINQL_FILESYSTEM_IOBUFFER_H_3

#include <stdio.h>
#include <assert.h>
#include "WinQL/WinQL.h"
#include "WinQL/Application/Threading/WinQLCriticalSection.h"
#include "WinQL/Application/Threading/WinQLSynchronization.h"
#include "WinQL/System/FileSystem/WinQLFile.h"
#include "WinQL/Application/ErrorSystem/WinQLErrorHandling.h"
#include "WinQL/System/FileSystem/WinQLFileManagement.h"

//------------------------------------------------------------------------------
namespace nsWin32
{
	//------------------------------------------------------------------------------
	class __QOR_INTERFACE( __WINQL ) CIOBuffer : private FILE
	{
	public:

		__QCMP_STATIC_CONSTANT( unsigned short, m_scusIOFullBuffering	= 0x0000 );//_IOFBF
		__QCMP_STATIC_CONSTANT( unsigned short, m_scusIOLineBuffering	= 0x0040 );//_IOLBF
		__QCMP_STATIC_CONSTANT( unsigned short, m_scusIORead			= 0x0001 );//_IOREAD
		__QCMP_STATIC_CONSTANT( unsigned short, m_scusIOWrite			= 0x0002 );//_IOWRT
		__QCMP_STATIC_CONSTANT( unsigned short, m_scusIONoBuffering		= 0x0004 );//_IONBF
		__QCMP_STATIC_CONSTANT( unsigned short, m_scusIOMyBuffer		= 0x0008 );//_IOMYBUF
		__QCMP_STATIC_CONSTANT( unsigned short, m_scusIOEOF				= 0x0010 );//_IOEOF
		__QCMP_STATIC_CONSTANT( unsigned short, m_scusIOError			= 0x0020 );//_IOERR
		__QCMP_STATIC_CONSTANT( unsigned short, m_scusIOString			= 0x0040 );//_IOSTRG
		__QCMP_STATIC_CONSTANT( unsigned short, m_scusIOReadWrite		= 0x0080 );//_IORW
		__QCMP_STATIC_CONSTANT( unsigned short, m_scusIOYourBuffer		= 0x0100 );//_IOYOURBUF
		__QCMP_STATIC_CONSTANT( unsigned short, m_scusIOSetVBuffer		= 0x0400 );//_IOSETVBUF
		__QCMP_STATIC_CONSTANT( unsigned short, m_scusIOFEOF			= 0x0800 );//_IOFEOF
		__QCMP_STATIC_CONSTANT( unsigned short, m_scusIOFlushReturn		= 0x1000 );//_IOFLRTN
		__QCMP_STATIC_CONSTANT( unsigned short, m_scusIOCtrlZ			= 0x2000 );//_IOCTRLZ
		__QCMP_STATIC_CONSTANT( unsigned short, m_scusIOCommit			= 0x4000 );//_IOCOMMIT
		__QCMP_STATIC_CONSTANT( unsigned short, m_scusIOLocked			= 0x8000 );//_IOLOCKED 

		__QCMP_STATIC_CONSTANT( unsigned int, m_scuiSmallBufferSize		= 512 );
		__QCMP_STATIC_CONSTANT( unsigned int, m_scuiBufferSize			= 1024 );
		__QCMP_STATIC_CONSTANT( unsigned int, m_scuiInternalBufferSize	= 4096 );

		CIOBuffer();
		~CIOBuffer();
		CIOBuffer( const CIOBuffer& src );
		CIOBuffer& operator = ( const CIOBuffer& src );

		char* GetTmpFileName( void );

		//------------------------------------------------------------------------------
		void SetLowLevelFileNumber( int iFile )
		{
			_file = iFile;
		}

		bool IsInUse( void );

	protected:

		static byte* m_spaStdIOBuffer[ 2 ];// = { NULL, NULL };

		void ResetBuffer();
		void OpenBuffer( int FileNumber, int Flags );

		int GetBufferSize( void );//_bufsiz
		void SetBufferSize( int iByteCount );//_bufsiz

		byte* GetFallbackBuffer( void );//_charbuf

		char* GetTemporaryFileName( void );//_tmpfname
		void SetTemporaryFileName( char* pName );//_tmpfname

		int GetFileNumber( void );//_file
		void SetFileNumber( int iFileHandle );//_file

		int GetBufferFlags( void );//_flag
		void SetBufferFlags( int iFlags );//_flag

		byte* GetBufferBasePointer( void );//_base
		void SetBufferBasePoiner( byte* );//_base

		int GetCountOfBytesLeftInBuffer( void );//_cnt
		void SetCountOfBytesLeftInBuffer( int );//_cnt

		char* GetPointerIntoBuffer( void );//_ptr
		void SetPointerIntoBuffer( char* );//_ptr

		void SetNoBuffering( void );
		void SetNoBufferingWrite( void );
		void SetMyBuffering( unsigned int uiBufferSize = m_scuiInternalBufferSize );
		void SetMyBufferingWrite( unsigned int uiBufferSize = m_scuiInternalBufferSize );
		void SetYourBuffering( char* pYourBuffer, const unsigned int uiSize );
		void SetYourBufferingWrite( char* pYourBuffer, const unsigned int uiSize );
		void DropYourBuffering();

		void LockBuffer( void );
		void UnlockBuffer( void );
		bool IsVBuffer( void );
		bool IsBufferLocked( void );
		bool IsBufferString( void );
		bool IsBufferError( void );
		bool IsBufferReadWrite( void );
		bool IsBufferRead( void );
		void ClearBufferReadAndWrite( void );
		bool IsBufferInUse( void );
		bool IsBufferWrite( void );
		bool IsMyBuffer( void );
		bool IsNoBuffer( void );
		bool IsYourBuffer( void );
		bool IsBigBuffer( void );
		bool IsAnyBuffer( void );		
		bool IsBufferFlushReturn( void );
		void SetBufferFlushReturn( bool bFlushReturn );
		int SetVBuffering( char* buffer, int type, size_t size );
		void GetBuffer( void );
		void FreeBuffer( void );
		void ClearBufferErrorFlags( void );
		bool BufferNeedsFlushing( int& nchar );
		void SetError( void );
		void EndWrite( void );
		void EndRead( void );
		void BeginWrite( void );
		void BeginRead( void );
		void BufferFlushed( void );
		bool IsCommit( void );
		void StartTempBuffering( void );
		bool IsTempBuffering( void );
		void EndTempBuffering( void );

		bool IsTmpFileName( void );
		void SetTmpFileName( char* pName );		
		void NormalizeCount( void );
		int Count( void );
		int BufferOffset( void );

		bool IsBufferEOF( void );
		void SetBufferEOF( void );
		void ClearBufferEOF( void );
		void BufferPrepare( void );
		int BufferUngetChar( int ch );

		int DecrementBufferCount( void );
		char GetNextChar( void );
		char PutNextChar( char c );
		byte* WriteIntoBuffer( const byte*, unsigned int );
		errno_t ReadFromBuffer( char* data, size_t dataSize, unsigned int nbytes );

	private:
		/*
		char* _ptr;
		int   _cnt;
		char* _base;
		int   _flag;
		int   _file;
		int   _charbuf;
		int   _bufsiz;
		char* _tmpfname;*/
	};

}//nsWin32

#endif//WINQL_FILESYSTEM_IOBUFFER_H_3
