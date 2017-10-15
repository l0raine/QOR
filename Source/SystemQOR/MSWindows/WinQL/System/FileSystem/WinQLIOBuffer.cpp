//WinQLIOBuffer.cpp

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

#include <errno.h>
#include "WinQL/Application/ErrorSystem/WinQLError.h"
#include "WinQL/Application/ErrorSystem/WinQLErrDomain.h"
#include "WinQL/System/FileSystem/WinQLIOBuffer.h"

//--------------------------------------------------------------------------------
namespace nsWin32
{
	byte* CIOBuffer::m_spaStdIOBuffer[ 2 ] = { nullptr, nullptr };

	//--------------------------------------------------------------------------------
	CIOBuffer::CIOBuffer()
	{
		ResetBuffer();
	}

	//--------------------------------------------------------------------------------
	CIOBuffer::~CIOBuffer()
	{
	}

	//--------------------------------------------------------------------------------
	CIOBuffer::CIOBuffer( const CIOBuffer& src )
	{
		*this = src;
	}

	//--------------------------------------------------------------------------------
	CIOBuffer& CIOBuffer::operator = ( const CIOBuffer& src )
	{
		if( &src != this )
		{
			_ptr = src._ptr;
			_cnt = src._cnt;
			_base = src._base;
			_flag = src._flag;
			_file = src._file;
			_charbuf = src._charbuf;
			_bufsiz = src._bufsiz;
			_tmpfname = src._tmpfname;
		}
		return *this;
	}

	//--------------------------------------------------------------------------------
	void CIOBuffer::ResetBuffer()
	{
		_ptr = nullptr;
		_cnt = 0;
		_base = nullptr;
		_flag = 0;
		_file = -2;
		_charbuf = 0;
		_bufsiz = 0;
		_tmpfname = nullptr;
	}

	//--------------------------------------------------------------------------------
	void CIOBuffer::OpenBuffer( int FileNumber, int Flags )
	{
		ResetBuffer();
		SetFileNumber(FileNumber);
		_flag = Flags;
	}

	//--------------------------------------------------------------------------------
	int CIOBuffer::GetBufferSize( void )
	{
		return _bufsiz;
	}

	//--------------------------------------------------------------------------------
	void CIOBuffer::SetBufferSize( int iByteCount )
	{
		_bufsiz = iByteCount;
	}

	//--------------------------------------------------------------------------------
	bool CIOBuffer::IsUnBuffered( void )
	{
		return _base == 0 ? true : false;
	}

	//--------------------------------------------------------------------------------
	byte* CIOBuffer::GetFallbackBuffer( void )
	{
		return reinterpret_cast<byte*>( &_charbuf );
	}

	//--------------------------------------------------------------------------------
	char* CIOBuffer::GetTemporaryFileName( void )
	{
		return _tmpfname;
	}

	//--------------------------------------------------------------------------------
	void CIOBuffer::SetTemporaryFileName( char* pName )
	{
		_tmpfname = pName;
	}

	//--------------------------------------------------------------------------------
	int CIOBuffer::GetFileNumber( void )
	{
		return _file;
	}

	//--------------------------------------------------------------------------------
	void CIOBuffer::SetFileNumber( int iFileHandle )
	{
		_file = iFileHandle;
	}

	//--------------------------------------------------------------------------------
	int CIOBuffer::GetBufferFlags( void )
	{
		return _flag;
	}

	//--------------------------------------------------------------------------------
	void CIOBuffer::SetBufferFlags( int iFlags )
	{
		_flag = iFlags;
	}

	//--------------------------------------------------------------------------------
	byte* CIOBuffer::GetBufferBasePointer( void )
	{
		return reinterpret_cast<byte*>( _base );
	}

	//--------------------------------------------------------------------------------
	void CIOBuffer::SetBufferBasePoiner( byte* pBuffer )
	{
		_base = reinterpret_cast<char*>( pBuffer );
	}

	//--------------------------------------------------------------------------------
	int CIOBuffer::GetCountOfBytesLeftInBuffer( void )
	{
		return _cnt;
	}

	//--------------------------------------------------------------------------------
	void CIOBuffer::SetCountOfBytesLeftInBuffer( int iCount )
	{
		_cnt = iCount;
	}

	//--------------------------------------------------------------------------------
	char* CIOBuffer::GetPointerIntoBuffer( void )
	{
		return _ptr;
	}

	//--------------------------------------------------------------------------------
	void CIOBuffer::SetPointerIntoBuffer( char* ptr )
	{
		_ptr = ptr;
	}

	//--------------------------------------------------------------------------------
	void CIOBuffer::SetNoBuffering( void )
	{
		_flag &= ~( m_scusIOMyBuffer | m_scusIOYourBuffer | m_scusIOSetVBuffer | m_scusIOFEOF | m_scusIOFlushReturn | m_scusIOCtrlZ );
		_flag |= m_scusIONoBuffering;
		_bufsiz = 2;
		_ptr = _base = ( char * )&( _charbuf );
		_cnt = 0;
	}

	//--------------------------------------------------------------------------------
	void CIOBuffer::SetNoBufferingWrite( void )
	{
		SetNoBuffering();
		_flag |= ( CIOBuffer::m_scusIOWrite );
		_cnt = _bufsiz;
	}

	//--------------------------------------------------------------------------------
	void CIOBuffer::SetMyBuffering( unsigned int uiBufferSize )
	{
		_flag |= m_scusIOMyBuffer;
		_bufsiz = uiBufferSize;
		_ptr = _base;
		_cnt = 0;
	}

	//--------------------------------------------------------------------------------
	void CIOBuffer::SetMyBufferingWrite( unsigned int uiBufferSize )
	{
		SetMyBuffering( uiBufferSize );
		_flag |= ( CIOBuffer::m_scusIOWrite );
		_cnt = _bufsiz;
	}

	//--------------------------------------------------------------------------------
	void CIOBuffer::SetYourBuffering( char* pYourBuffer, const unsigned int uiSize )
	{
		if( pYourBuffer == nullptr )
		{
			pYourBuffer = (char*)malloc( uiSize );

			if( pYourBuffer == nullptr )
			{
				SetNoBuffering();
				return;
			}
			_flag |= ( CIOBuffer::m_scusIOMyBuffer );
		}
		else
		{
			_flag |= ( CIOBuffer::m_scusIOYourBuffer );
		}

		if( pYourBuffer != nullptr )
		{
			_ptr = _base = reinterpret_cast<char*>( pYourBuffer );
			_bufsiz = uiSize;
			_cnt = 0;
		}
	}

	//--------------------------------------------------------------------------------
	void CIOBuffer::SetYourBufferingWrite( char* pYourBuffer, const unsigned int uiSize )
	{
		SetYourBuffering( pYourBuffer, uiSize );
		_flag |= ( CIOBuffer::m_scusIOWrite );
		_cnt = _bufsiz;
	}

	//--------------------------------------------------------------------------------
	void CIOBuffer::DropYourBuffering()
	{
		if( IsYourBuffer() )
		{
			_flag &= ~( CIOBuffer::m_scusIOYourBuffer );
			_bufsiz = 0;
			_base = _ptr = nullptr;
		}
	}

	//--------------------------------------------------------------------------------
	void CIOBuffer::LockBuffer( void )
	{
		_flag |= m_scusIOLocked;
	}

	//--------------------------------------------------------------------------------
	void CIOBuffer::UnlockBuffer( void )
	{
		_flag &= ~m_scusIOLocked;
	}

	//--------------------------------------------------------------------------------
	bool CIOBuffer::IsVBuffer( void )
	{
		return ( _flag & m_scusIOSetVBuffer ) ? true : false;
	}

	//--------------------------------------------------------------------------------
	bool CIOBuffer::IsBufferLocked( void )
	{
		return ( _flag & m_scusIOLocked ) ? true : false;
	}

	//--------------------------------------------------------------------------------
	bool CIOBuffer::IsBufferString( void )
	{
		return ( _flag & m_scusIOString ) ? true : false;
	}

	//--------------------------------------------------------------------------------
	bool CIOBuffer::IsBufferError( void )
	{
		return ( _flag & m_scusIOError ) ? true : false;
	}

	//--------------------------------------------------------------------------------
	bool CIOBuffer::IsBufferReadWrite( void )
	{
		return ( _flag & m_scusIOReadWrite ) ? true : false;
	}

	//--------------------------------------------------------------------------------
	bool CIOBuffer::IsBufferRead( void )
	{
		return ( _flag & m_scusIORead ) ? true : false;
	}

	//--------------------------------------------------------------------------------
	void CIOBuffer::ClearBufferReadAndWrite()
	{
		if( IsBufferReadWrite() )
		{
			_flag &= ~( m_scusIORead | m_scusIOWrite );
		}
	}

	//--------------------------------------------------------------------------------
	bool CIOBuffer::IsBufferInUse( void )
	{
		return ( _flag & ( m_scusIORead | m_scusIOWrite | m_scusIOReadWrite ) ) ? true : false;
	}

	//--------------------------------------------------------------------------------
	bool CIOBuffer::IsBufferWrite( void )
	{
		return ( _flag & m_scusIOWrite ) ? true : false;
	}

	//--------------------------------------------------------------------------------
	bool CIOBuffer::IsMyBuffer(  )
	{
		return ( _flag & m_scusIOMyBuffer ) ? true : false;
	}

	//--------------------------------------------------------------------------------
	bool CIOBuffer::IsNoBuffer(  )
	{
		return ( _flag & m_scusIONoBuffering ) ? true : false;
	}

	//--------------------------------------------------------------------------------
	bool CIOBuffer::IsYourBuffer(  )
	{
		return ( _flag & m_scusIOYourBuffer ) ? true : false;
	}

	//--------------------------------------------------------------------------------
	bool CIOBuffer::IsBigBuffer(  )
	{
		return ( _flag & ( m_scusIOMyBuffer | m_scusIOYourBuffer ) ) ? true : false;
	}

	//--------------------------------------------------------------------------------
	bool CIOBuffer::IsAnyBuffer(  )
	{
		return ( _flag & ( m_scusIOMyBuffer | m_scusIONoBuffering | m_scusIOYourBuffer ) ) ? true : false;
	}

	//------------------------------------------------------------------------------
	bool CIOBuffer::IsInUse(  )
	{
		return ( _flag & ( m_scusIORead | m_scusIOWrite | m_scusIOReadWrite ) ) ? true : false;
	}

	//--------------------------------------------------------------------------------
	bool CIOBuffer::IsBufferFlushReturn( void )
	{
		return ( _flag & m_scusIOFlushReturn ) ? true : false;
	}

	//--------------------------------------------------------------------------------
	void CIOBuffer::SetBufferFlushReturn( bool bFlushReturn )
	{
		if( bFlushReturn )
		{
			_flag |= m_scusIOFlushReturn;
		}
		else
		{
			_flag &= ~m_scusIOFlushReturn;
		}
	}

	//--------------------------------------------------------------------------------
	int CIOBuffer::SetVBuffering( char* buffer, int type, size_t size )
	{
		int retval = 0;

		// Clear a bunch of bits in stream->_flag. all bits related to buffering 
		_flag &= ~( m_scusIOMyBuffer | m_scusIOYourBuffer | m_scusIONoBuffering | m_scusIOSetVBuffer | m_scusIOFEOF | m_scusIOFlushReturn | m_scusIOCtrlZ );

		//CASE 1: No Buffering.
		if( type & m_scusIONoBuffering )
		{
			SetNoBuffering();
		}
		else
		{
			// NOTE: Cases 2 and 3 (below) cover type == _IOFBF or type == _IOLBF Line buffering is treated as the same as full buffering, so the _IOLBF bit in stream->_flag is never set. 
			//Finally, since _IOFBF is defined to be 0, full buffering is simply assumed whenever _IONBF is not set.

			//CASE 2: Default Buffering -- Allocate a buffer for the user.

			SetYourBuffering( buffer, size );

			_flag |= m_scusIOSetVBuffer;

		}
		return retval;
	}

	//------------------------------------------------------------------------------
	void CIOBuffer::GetBuffer()
	{
		assert( this != NULL );

		// Try to get a big buffer
		_base = reinterpret_cast<char*>( malloc( m_scuiInternalBufferSize ) );
		if( _base != 0 )
		{
			SetMyBuffering();
		}
		else
		{
			SetNoBuffering();// Did NOT get a buffer - use single char buffering.
		}

		return;
	}

	//------------------------------------------------------------------------------
	void CIOBuffer::FreeBuffer()
	{
		assert( this != NULL );

		if( IsBufferInUse() && IsMyBuffer() )
		{
			free( _base );
			_flag &= ~( m_scusIOMyBuffer | m_scusIOSetVBuffer );
			_base = _ptr = NULL;
			_cnt = _bufsiz = 0;
		}
	}

	//------------------------------------------------------------------------------
	void CIOBuffer::ClearBufferErrorFlags()
	{
		_flag &= ~( m_scusIOError | m_scusIOEOF );	// Clear stdio level flags
	}

	//------------------------------------------------------------------------------
	bool CIOBuffer::BufferNeedsFlushing( int& nchar )
	{
		return( ( _flag & ( m_scusIORead | m_scusIOWrite ) ) == m_scusIOWrite && IsBigBuffer() && ( nchar = (int)( _ptr - _base ) ) > 0 ) ? true : false;
	}

	//------------------------------------------------------------------------------
	void CIOBuffer::SetError( void )
	{
		_flag |= m_scusIOError;
	}

	//------------------------------------------------------------------------------
	void CIOBuffer::EndWrite()
	{
		_flag &= ~m_scusIOWrite;
	}

	//------------------------------------------------------------------------------
	void CIOBuffer::EndRead()
	{
		_flag &= ~m_scusIORead;
	}

	//------------------------------------------------------------------------------
	void CIOBuffer::BeginWrite()
	{
		_flag |= m_scusIOWrite;
	}

	//------------------------------------------------------------------------------
	void CIOBuffer::BeginRead()
	{
		_flag |= m_scusIORead;
	}

	//------------------------------------------------------------------------------
	void CIOBuffer::BufferFlushed( void )
	{
		_ptr = _base;
		_cnt = 0;
	}

	//------------------------------------------------------------------------------
	bool CIOBuffer::IsCommit( void )
	{
		return _flag | m_scusIOCommit ? true : false;
	}

	//------------------------------------------------------------------------------
	void CIOBuffer::StartTempBuffering()
	{
		_flag |= ( m_scusIOWrite | m_scusIOFlushReturn );
	}

	//------------------------------------------------------------------------------
	bool CIOBuffer::IsTempBuffering()
	{
		return _flag & m_scusIOFlushReturn ? true : false;
	}

	//------------------------------------------------------------------------------
	void CIOBuffer::EndTempBuffering( void )
	{
		//Tear down temp buffering.
		if( _flag & m_scusIOFlushReturn )
		{
			_flag &= ~( m_scusIOYourBuffer | m_scusIOFlushReturn );
			_bufsiz = 0;
			_base = _ptr = NULL;
		}
	}

	//------------------------------------------------------------------------------
	bool CIOBuffer::IsTmpFileName( void )
	{
		return _tmpfname == nullptr ? false : true;
	}

	//------------------------------------------------------------------------------
	void CIOBuffer::SetTmpFileName( char* pName )
	{
		_tmpfname = pName;
	}

	//------------------------------------------------------------------------------
	char* CIOBuffer::GetTmpFileName( void )
	{
		return _tmpfname;
	}

	//------------------------------------------------------------------------------
	void CIOBuffer::NormalizeCount( void )
	{
		if( _cnt < 0 )
		{
			_cnt = 0;
		}
	}

	//------------------------------------------------------------------------------
	int CIOBuffer::Count()
	{
		return _cnt;
	}

	//------------------------------------------------------------------------------
	int CIOBuffer::BufferOffset()
	{
		return ( _ptr - _base );
	}

	//------------------------------------------------------------------------------
	bool CIOBuffer::IsBufferEOF()
	{
		return _flag & m_scusIOEOF ? true : false;
	}

	//------------------------------------------------------------------------------
	void CIOBuffer::ClearBufferEOF()
	{
		_flag &= ~m_scusIOEOF;
	}

	//------------------------------------------------------------------------------
	void CIOBuffer::SetBufferEOF( void )
	{
		_flag |= m_scusIOEOF;
	}

	//------------------------------------------------------------------------------
	void CIOBuffer::BufferPrepare()
	{
		// If file opened for read/write, clear flags since we don't know what the user is going to do next. If the file was opened for read access only, decrease _bufsiz so that the next _filbuf won't cost quite so much
		if( IsBufferReadWrite() )
		{
			_flag &= ~( m_scusIOWrite | m_scusIORead );
		}
		else if( ( IsBufferRead() ) && ( IsMyBuffer() ) && !( IsVBuffer() ) )
		{
			_bufsiz = m_scuiBufferSize;
		}
	}

	//------------------------------------------------------------------------------
	int CIOBuffer::BufferUngetChar( int ch )
	{
		// If stream is unbuffered, get one.
		if( _base == NULL )
		{
			GetBuffer();
		}

		// now we know _base != NULL; since file must be buffered

		if( _ptr == _base )
		{
			if( _cnt )
			{ // my back is against the wall; I've already done ungetc, and there's no room for this one 
				return EOF;
			}

			_ptr++;
		}

		if( IsBufferString() )
		{
			// If stream opened by sscanf do not modify buffer
			if( *--_ptr != (char)ch )
			{
				++_ptr;
				return EOF;
			}
		}
		else
		{
			*--_ptr = (char)ch;
		}

		_cnt++;
		_flag &= ~_IOEOF;
		_flag |= _IOREAD;       // may already be set

		return( 0xff & ch );
	}

	//------------------------------------------------------------------------------
	int CIOBuffer::DecrementBufferCount()
	{
		return --_cnt;
	}

	//------------------------------------------------------------------------------
	char CIOBuffer::GetNextChar()
	{
		return *_ptr++;
	}

	//------------------------------------------------------------------------------
	char CIOBuffer::PutNextChar( char c )
	{
		return *_ptr++ = c;
	}

	//------------------------------------------------------------------------------
	byte* CIOBuffer::WriteIntoBuffer( const byte* data, unsigned int nBytes)
	{
		byte* pResult = (byte*)memcpy( _ptr, data, nBytes );
		_cnt -= nBytes;
		_ptr += nBytes;
		return pResult;
	}

	//------------------------------------------------------------------------------
	errno_t CIOBuffer::ReadFromBuffer(char* data, size_t dataSize, unsigned int nbytes )
	{
		errno_t Result = memcpy_s( data, dataSize, _ptr, nbytes );

		_cnt -= nbytes;
		_ptr += nbytes;
		return Result;
	}

}//nsWin32
