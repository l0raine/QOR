//WinQLStandardIO.cpp

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

//WinQL Standard IO Subsystem

#include "WinQL/WinQL.h"

#ifdef	__QCMP_OPTIMIZEINCLUDE
#pragma	__QCMP_OPTIMIZEINCLUDE
#endif//__QCMP_OPTIMIZEINCLUDE

#include "WinQL/System/FileSystem/WinQLFile.h"
#include "WinQL/System/FileSystem/WinQLStream.h"
#include "WinQL/Application/Subsystems/WinQLStandardIO.h"
#include "WinQL/Application/Process/WinQLProcessHelper.h"

#define NOMINMAX
#include "WinQAPI/Kernel32.h"
#include <errno.h>
#include <algorithm>

//--------------------------------------------------------------------------------
namespace nsWin32
{
	__QOR_IMPLEMENT_EXTERNAL_FACTORY( CStandardIO, 0x261fc4e5, 0xad60, 0x4b8a, 0xb8, 0x4a, 0xd5, 0xa2, 0x3, 0x2e, 0xaa, 0x84 );

	//--------------------------------------------------------------------------------
	CStandardIO::CStandardIO() : m_uiNextStream( 0 ), m_uiInitialStreams( 20 ), m_uiMaxStreams( 512 ), m_bExitFlag( false ), m_umaskval( 0 ), m_fmode( 0 )
	{
		Initialize( CProcessHelper::StartupInfo() );
	}

	//--------------------------------------------------------------------------------
	CStandardIO::~CStandardIO()
	{
		// flush all streams
		_flushall();

		// if in callable exit, close all streams
		if( m_bExitFlag )
		{
			_fcloseall();
		}

		FreeStreams();
	}

	//--------------------------------------------------------------------------------
	void CStandardIO::Setup( nsQOR::IApplication& Application )
	{
	}

	//--------------------------------------------------------------------------------
	void CStandardIO::Shutdown( nsQOR::IApplication& Application )
	{
	}

	//------------------------------------------------------------------------------
	void CStandardIO::Initialize( const STARTUPINFO& StartupInfo )
	{
		if( ( StartupInfo.cbReserved2 != 0 ) && ( StartupInfo.lpReserved2 != NULL ) )
		{
			int iNumberOfIneritedHandles = *( (int*)( StartupInfo.lpReserved2 ) );

			byte* pFileInfo = (byte*)( StartupInfo.lpReserved2 ) + sizeof( int );
			intptr_t* pFileHandles = (intptr_t*)( pFileInfo + iNumberOfIneritedHandles );
			iNumberOfIneritedHandles = std::min( static_cast<unsigned int>( iNumberOfIneritedHandles ), m_uiMaxStreams );

			//AllocateStreams( std::max( static_cast< unsigned int >( iNumberOfIneritedHandles), m_uiInitialStreams ) );		//allocate the initial streams

			//Validate and copy the passed handle information
			for( int fh = 0; fh < iNumberOfIneritedHandles; fh++, pFileInfo++, pFileHandles++ )
			{

				//Copy the passed file info iff it appears to describe an open, valid file or device.
				//Note that GetFileType cannot be called for pipe handles since it may 'hang' if there is blocked read pending on the pipe in the parent.

				if( ( *pFileHandles != (intptr_t)Invalid_Handle_Value ) && ( *pFileHandles != _NO_CONSOLE_FILENO ) && ( *pFileInfo & FOPEN ) && ( ( *pFileInfo & FPIPE ) ||
					( nsWinQAPI::CKernel32::GetFileType( (void*)*pFileHandles ) != File_Type_Unknown ) ) )
				{
					int Descriptor = *pFileHandles;
					if( m_uiNextStream <= static_cast< unsigned int >( Descriptor ) )
					{
						m_uiNextStream = static_cast< unsigned int >( Descriptor + 1 );
					}

					CStream* pStream = new CStream();
					pStream->SetLowLevelFlags( *pFileInfo );
					CFileHandle handle( *pFileHandles );
					pStream->SetLowLevelFile( new CFile( handle ) );
					m_DescriptorStreamMap.insert( std::make_pair( Descriptor, pStream ) );
				}
			}
		}
		//If valid HANDLE-s for standard input, output and error were not inherited, try to obtain them directly from the OS. 
		//Also, set the appropriate bits in the osfile fields.
		intptr_t stdfh;
		unsigned long htype;

		for( int fh = 0; fh < STDIO_HANDLES_COUNT; fh++ )
		{
			auto stream_it = m_DescriptorStreamMap.find( fh );
			if( stream_it == m_DescriptorStreamMap.end() )
			{
				CStream* pStream = new CStream();
				pStream->SetLowLevelFlags( (byte)( FOPEN | FTEXT ) );
				if( ( ( stdfh = (intptr_t)GetStdHandle( stdhndl( fh ) ) ) != (intptr_t)INVALID_HANDLE_VALUE ) && ( stdfh != ( (intptr_t)NULL ) ) && ( ( htype = GetFileType( (HANDLE)stdfh ) ) != FILE_TYPE_UNKNOWN ) )
				{
					// obtained a valid HANDLE from GetStdHandle
					CFileHandle handle( stdfh );
					pStream->SetLowLevelFile( new CFile( handle ) );

					if( ( htype & 0xFF ) == FILE_TYPE_CHAR )
					{
						pStream->SetLowLevelFlags( (byte)( FOPEN | FTEXT | FDEV ) );
					}
					else if( ( htype & 0xFF ) == FILE_TYPE_PIPE )
					{
						pStream->SetLowLevelFlags( (byte)( FOPEN | FTEXT | FPIPE ) );
					}
				}
				else
				{
					m_ConsoleHelper.Alloc();
					pStream->SetLowLevelFile( new CFile( fh == 0 ? "CONIN$" : "CONOUT$", Generic_Read | Generic_Write, File_Share_Read | File_Share_Write, 0, Open_Existing, 0, 0 ) );

					/* For stdin, stdout & stderr, if there is no valid HANDLE, treat the CRT handle as being open in text mode on a
					device with _NO_CONSOLE_FILENO underlying it. We use this value different from _INVALID_HANDLE_VALUE to distinguish
					between a failure in opening a file & a program run without a console.*/
					pStream->SetLowLevelFlags( FOPEN | FTEXT | FDEV );
					pStream->SetLowLevelFileNumber( fh );//_NO_CONSOLE_FILENO;
				}
				m_DescriptorStreamMap.insert( std::make_pair( fh, pStream ) );
			}
			else
			{
				//handle was passed to us by parent process. make sure it is text mode.
				stream_it->second->SetLowLevelFlags( FTEXT );
			}
		}

	}


	//------------------------------------------------------------------------------
	void CStandardIO::AllocateStreams( unsigned int uiCount )
	{
		CCriticalSectionLock MapLock( m_MapSection );
		CCriticalSectionLock ListLock( m_FreeListSection );
		for( ; uiCount > 0; uiCount-- )
		{
			AllocateStream( false );
		}
	}

	//------------------------------------------------------------------------------
	void CStandardIO::AllocateStream( bool bLock )
	{
		if( bLock )
		{
			m_MapSection.Acquire();
			m_FreeListSection.Acquire();
		}

		if( m_uiNextStream < m_uiMaxStreams )
		{
			m_DescriptorStreamMap.insert( std::make_pair( m_uiNextStream, new CStream() ) );
			m_VecFreeLRUList.push_back( m_uiNextStream );
			m_uiNextStream++;
		}
		else
		{
			//TODO: Error:-Out of streams
		}

		if( bLock )
		{
			m_MapSection.Release();
			m_FreeListSection.Release();
		}
	}

	//------------------------------------------------------------------------------
	void CStandardIO::FreeHandle( int iFile )
	{
		m_VecFreeLRUList.push_back( static_cast< unsigned int >( iFile ) );
	}

	//------------------------------------------------------------------------------
	void CStandardIO::FreeStreams()
	{
		CCriticalSectionLock MapLock( m_MapSection );
		CCriticalSectionLock ListLock( m_FreeListSection );

		m_VecFreeLRUList.erase( m_VecFreeLRUList.begin(), m_VecFreeLRUList.end() );
		m_DescriptorStreamMap.erase( m_DescriptorStreamMap.begin(), m_DescriptorStreamMap.end() );
	}

	//------------------------------------------------------------------------------
	bool& CStandardIO::_exitflag( void )
	{
		return m_bExitFlag;
	}

	//------------------------------------------------------------------------------
	int CStandardIO::_flushall( void )
	{
		return( flsall( FlushAll ) );
	}

	//------------------------------------------------------------------------------
	void _lock_file( CStream* pFile )
	{
		if( pFile )
		{
			pFile->flockfile();
		}
	}

	//------------------------------------------------------------------------------
	void _lock_file2( int i, void* s )
	{
		CStream* pFile = reinterpret_cast< CStream* >( s );
		_lock_file( pFile );
	}

	//------------------------------------------------------------------------------
	void _unlock_file( CStream* pFile )
	{
		if( pFile )
		{
			pFile->funlockfile();
		}
	}

	//------------------------------------------------------------------------------
	void _unlock_file2( int i, void* s )
	{
		CStream* pFile = reinterpret_cast< CStream* >( s );
		_unlock_file( pFile );
	}


	//----------------------------------------------------------------------------------------
	int CStandardIO::_fcloseall()
	{
		int count = 0;

		CCriticalSectionLock MapLock( m_MapSection );

		std::map< const int, CStream* >::iterator it = m_DescriptorStreamMap.begin();

		it++;
		it++;
		it++;//Skip over standard streams

		while( it != m_DescriptorStreamMap.end() )
		{
			if( ( *it ).second->IsInUse() )
			{
				CStream& Stream( *( ( *it ).second ) );

				if( Stream.fclose() != EOF )
				{
					count++;

				}
			}
			it++;
		}
		return count;
	}

	//----------------------------------------------------------------------------------------
	int CStandardIO::flsall( int flushflag )
	{
		CCriticalSectionLock MapLock( m_MapSection );

		int count = 0;
		int err = 0;

		std::map< const int, CStream* >::iterator it = m_DescriptorStreamMap.begin();

		while( it != m_DescriptorStreamMap.end() )
		{
			if( ( *it ).second->IsInUse() )
			{
				CStream& Stream( *( ( *it ).second ) );

				Stream.flockfile();

				if( Stream.IsInUse() )
				{
					if( flushflag == FlushAll )
					{
						if( Stream._fflush_nolock() != EOF )
						{
							count++;
						}
					}
					else if( ( flushflag == FlushNULL ) && ( Stream.IsWrite() ) )
					{
						if( Stream._fflush_nolock() == EOF )
						{
							err = EOF;
						}
					}
				}
				Stream.funlockfile();
			}
			it++;
		}

		if( flushflag == FlushAll )
		{
			return count;
		}
		else
		{
			return err;
		}
	}

	/*
	* Number of ioinfo structs allocated at any given time. This number ranges
	* from a minimum of IOINFO_ARRAY_ELTS to a maximum of _NHANDLE_ (==
	* IOINFO_ARRAY_ELTS * IOINFO_ARRAYS) in steps of IOINFO_ARRAY_ELTS.
	*/
	//int _nhandle;

	/*
	* Array of pointers to arrays of ioinfo structs.
	*/
	//_CRTIMP ioinfo * __pioinfo[IOINFO_ARRAYS] = {0};

	/*
	* macro used to map 0, 1 and 2 to right value for call to GetStdHandle
	*/
	//#define stdhndl(fh)  ( (fh == 0) ? STD_INPUT_HANDLE : ((fh == 1) ?  STD_OUTPUT_HANDLE : STD_ERROR_HANDLE) )

	/***
	*_ioinit() -
	*
	*Purpose:
	*       Allocates and initializes initial array(s) of ioinfo structs. Then,
	*       obtains and processes information on inherited file handles from the
	*       parent process (e.g., cmd.exe).
	*
	*       Obtains the StartupInfo structure from the OS. The inherited file
	*       handle information is pointed to by the lpReserved2 field. The format
	*       of the information is as follows:
	*
	*           bytes 0 thru 3          - integer value, say N, which is the
	*                                     number of handles information is passed
	*                                     about
	*
	*           bytes 4 thru N+3        - the N values for osfile
	*
	*           bytes N+4 thru 5*N+3    - N double-words, the N OS HANDLE values
	*                                     being passed
	*
	*       Next, osfhnd and osfile for the first three ioinfo structs,
	*       corrsponding to handles 0, 1 and 2, are initialized as follows:
	*
	*           If the value in osfhnd is INVALID_HANDLE_VALUE, then try to
	*           obtain a HANDLE by calling GetStdHandle, and call GetFileType to
	*           help set osfile. Otherwise, assume _osfhndl and _osfile are
	*           valid, but force it to text mode (standard input/output/error
	*           are to always start out in text mode).
	*
	*       Notes:
	*           1. In general, not all of the passed info from the parent process
	*              will describe open handles! If, for example, only C handle 1
	*              (STDOUT) and C handle 6 are open in the parent, info for C
	*              handles 0 thru 6 is passed to the the child.
	*
	*           2. Care is taken not to 'overflow' the arrays of ioinfo structs.
	*
	*           3. See exec\dospawn.c for the encoding of the file handle info
	*              to be passed to a child process.
	*
	*Entry:
	*       No parameters: reads the STARTUPINFO structure.
	*
	*Exit:
	*       0 on success, -1 if error encountered
	*
	*Exceptions:
	*
	*******************************************************************************/

	//int  __cdecl _ioinit(void)
	//{
	//    int fh;
	//    ioinfo *pio;
	//#ifndef _CRT_APP
	//    STARTUPINFOW StartupInfo;
	//    int cfi_len;
	//    int i;
	//    char *posfile;
	//    UNALIGNED intptr_t *posfhnd;
	//#endif
	//#if !defined(_CRT_APP) || defined(_KERNELX)
	//    intptr_t stdfh;
	//    DWORD htype;
	//#endif  /* _CRT_APP */
	//
	//    _mlock(_OSFHND_LOCK);   /* lock the __pioinfo[] array */
	//
	//    __TRY
	//
	//        /*
	//         * Allocate and initialize the first array of ioinfo structs. This
	//         * array is pointed to by __pioinfo[0]
	//         */
	//        if ( (pio = _calloc_crt( IOINFO_ARRAY_ELTS, sizeof(ioinfo) ))
	//             == NULL )
	//        {
	//            return -1;
	//        }
	//
	//        __pioinfo[0] = pio;
	//        _nhandle = IOINFO_ARRAY_ELTS;
	//
	//        for ( ; pio < __pioinfo[0] + IOINFO_ARRAY_ELTS ; pio++ ) {
	//            pio->osfile = 0;
	//            pio->osfhnd = (intptr_t)INVALID_HANDLE_VALUE;
	//            pio->pipech = 10;                   /* linefeed/newline char */
	//            pio->lockinitflag = 0;              /* uninitialized lock */
	//            pio->textmode = 0;
	//            pio->unicode = 0;
	//            pio->pipech2[0] = 10;
	//            pio->pipech2[1] = 10;
	//            pio->dbcsBufferUsed = FALSE;
	//            pio->dbcsBuffer = '\0';
	//        }
	//
	//#ifndef _CRT_APP
	//        /*
	//         * Process inherited file handle information, if any
	//         */
	//
	//        GetStartupInfoW( &StartupInfo );
	//        if ( (StartupInfo.cbReserved2 != 0) &&
	//             (StartupInfo.lpReserved2 != NULL) )
	//        {
	//            /*
	//             * Get the number of handles inherited.
	//             */
	//            cfi_len = *(UNALIGNED int *)(StartupInfo.lpReserved2);
	//
	//            /*
	//             * Set pointers to the start of the passed file info and OS
	//             * HANDLE values.
	//             */
	//            posfile = (char *)(StartupInfo.lpReserved2) + sizeof( int );
	//            posfhnd = (UNALIGNED intptr_t *)(posfile + cfi_len);
	//
	//            /*
	//             * Ensure cfi_len does not exceed the number of supported
	//             * handles!
	//             */
	//            cfi_len = __min( cfi_len, _NHANDLE_ );
	//
	//            /*
	//             * Allocate sufficient arrays of ioinfo structs to hold inherited
	//             * file information.
	//             */
	//            for ( i = 1 ; _nhandle < cfi_len ; i++ ) {
	//
	//                /*
	//                 * Allocate another array of ioinfo structs
	//                 */
	//                if ( (pio = _calloc_crt( IOINFO_ARRAY_ELTS, sizeof(ioinfo) ))
	//                    == NULL )
	//                {
	//                    /*
	//                     * No room for another array of ioinfo structs, reduce
	//                     * the number of inherited handles we process.
	//                     */
	//                    cfi_len = _nhandle;
	//                    break;
	//                }
	//
	//                /*
	//                 * Update __pioinfo[] and _nhandle
	//                 */
	//                __pioinfo[i] = pio;
	//                _nhandle += IOINFO_ARRAY_ELTS;
	//
	//                for ( ; pio < __pioinfo[i] + IOINFO_ARRAY_ELTS ; pio++ ) {
	//                    pio->osfile = 0;
	//                    pio->osfhnd = (intptr_t)INVALID_HANDLE_VALUE;
	//                    pio->pipech = 10;
	//                    pio->lockinitflag = 0;
	//                    pio->textmode = 0;
	//                    pio->pipech2[0] = 10;
	//                    pio->pipech2[1] = 10;
	//                    pio->dbcsBufferUsed = FALSE;
	//                    pio->dbcsBuffer = '\0';
	//                }
	//            }
	//
	//            /*
	//             * Validate and copy the passed file information
	//             */
	//            for ( fh = 0 ; fh < cfi_len ; fh++, posfile++, posfhnd++ ) {
	//                /*
	//                 * Copy the passed file info iff it appears to describe
	//                 * an open, valid file or device.
	//                 *
	//                 * Note that GetFileType cannot be called for pipe handles
	//                 * since it may 'hang' if there is blocked read pending on
	//                 * the pipe in the parent.
	//                 */
	//                if ( (*posfhnd != (intptr_t)INVALID_HANDLE_VALUE) &&
	//                     (*posfhnd != _NO_CONSOLE_FILENO) &&
	//                     (*posfile & FOPEN) &&
	//                     ((*posfile & FPIPE) ||
	//                     (GetFileType( (HANDLE)*posfhnd ) != FILE_TYPE_UNKNOWN)) )
	//                {
	//                    pio = _pioinfo( fh );
	//                    pio->osfhnd = *posfhnd;
	//                    pio->osfile = *posfile;
	//                    /* Allocate the lock for this handle. */
	//                    __crtInitializeCriticalSectionEx( &pio->lock, _CRT_SPINCOUNT, 0 );
	//                    pio->lockinitflag++;
	//                }
	//            }
	//        }
	//#endif  /* _CRT_APP */
	//
	//        /*
	//         * If valid HANDLE-s for standard input, output and error were not
	//         * inherited, try to obtain them directly from the OS. Also, set the
	//         * appropriate bits in the osfile fields.
	//         */
	//        for ( fh = 0 ; fh < STDIO_HANDLES_COUNT ; fh++ ) {
	//
	//            pio = __pioinfo[0] + fh;
	//
	//#if defined(_CRT_APP) && !defined(_KERNELX)
	//                pio->osfile = FDEV | FOPEN | FTEXT;
	//                pio->osfhnd = _NO_CONSOLE_FILENO;
	//                if (__piob)
	//                    ((FILE*)__piob[fh])->_file = _NO_CONSOLE_FILENO;
	//#else  /* CRT_APP && !_KERNELX */
	//
	//            if ( (pio->osfhnd == (intptr_t)INVALID_HANDLE_VALUE) ||
	//                 (pio->osfhnd == _NO_CONSOLE_FILENO)) {
	//                /*
	//                 * mark the handle as open in text mode.
	//                 */
	//                pio->osfile = (char)(FOPEN | FTEXT);
	//
	//                if ( ((stdfh = (intptr_t)GetStdHandle( stdhndl(fh) )) != (intptr_t)INVALID_HANDLE_VALUE) &&
	//                     (stdfh!=((intptr_t)NULL)) &&
	//                     ((htype = GetFileType( (HANDLE)stdfh )) != FILE_TYPE_UNKNOWN) )
	//                {
	//                    /*
	//                     * obtained a valid HANDLE from GetStdHandle
	//                     */
	//                    pio->osfhnd = stdfh;
	//
	//                    /*
	//                     * finish setting osfile: determine if it is a character
	//                     * device or pipe.
	//                     */
	//                    if ( (htype & 0xFF) == FILE_TYPE_CHAR )
	//                        pio->osfile |= FDEV;
	//                    else if ( (htype & 0xFF) == FILE_TYPE_PIPE )
	//                        pio->osfile |= FPIPE;
	//
	//                    /* Allocate the lock for this handle. */
	//                    __crtInitializeCriticalSectionEx( &pio->lock,_CRT_SPINCOUNT, 0 );
	//                    pio->lockinitflag++;
	//                }
	//                else {
	//                    /*
	//                     * For stdin, stdout & stderr, if there is no valid HANDLE,
	//                     * treat the CRT handle as being open in text mode on a
	//                     * device with _NO_CONSOLE_FILENO underlying it. We use this
	//                     * value different from _INVALID_HANDLE_VALUE to distinguish
	//                     * between a failure in opening a file & a program run
	//                     * without a console.
	//                     */
	//                    pio->osfile |= FDEV;
	//                    pio->osfhnd = _NO_CONSOLE_FILENO;
	//
	//                    /* Also update the corresponding standard IO stream.
	//                     * Unless stdio was terminated already in __endstdio,
	//                     * __piob should be statically initialized in __initstdio.
	//                     */
	//                    if (__piob)
	//                        ((FILE*)__piob[fh])->_file = _NO_CONSOLE_FILENO;
	//                }
	//            }
	//            else  {
	//                /*
	//                 * handle was passed to us by parent process. make
	//                 * sure it is text mode.
	//                 */
	//                pio->osfile |= FTEXT;
	//            }
	//#endif  /* _CRT_APP */
	//        }
	//
	//    __FINALLY
	//        _munlock(_OSFHND_LOCK); /* unlock the __pioinfo[] table */
	//    __END_TRY_FINALLY
	//
	//    return 0;
	//}


	//	void __cdecl _ioterm ( void )
	//	{
	//       int i;
	//       ioinfo *pio;

	//       for ( i = 0 ; i < IOINFO_ARRAYS ; i++ ) {

	//           if ( __pioinfo[i] != NULL ) {
	//               /*
	//                * Delete any initialized critical sections.
	//                */
	//               for ( pio = __pioinfo[i] ;
	//                     pio < __pioinfo[i] + IOINFO_ARRAY_ELTS ;
	//                     pio++ )
	//               {
	//                   if ( pio->lockinitflag )
	//                       DeleteCriticalSection( &(pio->lock) );
	//               }
	//               /*
	//                * Free the memory which held the ioinfo array.
	//                */
	//               _free_crt( __pioinfo[i] );
	//               __pioinfo[i] = NULL;
	//           }
	//       }
	// }


	//TODO: //_CRTALLOC(".CRT$XPX") static _PVFV pterm = _rmtmp;

	//------------------------------------------------------------------------------
	int CStandardIO::_rmtmp()
	{
		int count = 0;

		CCriticalSectionLock MapLock( m_MapSection );
		CCriticalSectionLock ListLock( m_FreeListSection );

		std::map< const int, CStream* >::iterator it = m_DescriptorStreamMap.begin();

		while( it != m_DescriptorStreamMap.end() )
		{
			if( ( *it ).second->IsInUse() )
			{
				CStream& Stream( *( ( *it ).second ) );

				Stream.flockfile();

				if( Stream.IsInUse() )
				{
					if( Stream.GetTmpFileName() != NULL )
					{
						Stream._fclose_nolock();
						count++;
					}
				}

				Stream.funlockfile();
			}

			it++;
		}


		return count;
	}

	//------------------------------------------------------------------------------
	int CStandardIO::_setmaxstdio( unsigned int maxnum )
	{

		if( maxnum < m_uiInitialStreams || m_uiInitialStreams > 16384 )
		{
			errno = EINVAL;
			return -1;
		}

		CCriticalSectionLock MapLock( m_MapSection );
		CCriticalSectionLock ListLock( m_FreeListSection );

		m_uiMaxStreams = maxnum;

		return m_uiMaxStreams;
	}

	//------------------------------------------------------------------------------
	int CStandardIO::_getmaxstdio( void )
	{
		return m_uiMaxStreams;
	}


	//------------------------------------------------------------------------------
	CStream* CStandardIO::_getstream()
	{
		CStream* retval = NULL;
		unsigned int uiStream = 0;

		CCriticalSectionLock MapLock( m_MapSection );
		CCriticalSectionLock ListLock( m_FreeListSection );

		if( m_VecFreeLRUList.size() == 0 )
		{
			AllocateStream( false );
		}

		if( m_VecFreeLRUList.size() > 0 )
		{
			uiStream = m_VecFreeLRUList.front();
			m_VecFreeLRUList.pop_front();

			retval = m_DescriptorStreamMap.find( uiStream )->second;
		}

		if( retval != NULL )
		{
			retval->Reset();
			retval->flockfile();
			retval->SetLowLevelFileNumber( uiStream );
		}

		return retval;
	}

	//------------------------------------------------------------------------------
	CStream* CStandardIO::StreamFromID( int fd )
	{
		CStream* retval = NULL;

		CCriticalSectionLock MapLock( m_MapSection );
		CCriticalSectionLock ListLock( m_FreeListSection );

		retval = m_DescriptorStreamMap.find( static_cast< unsigned int >( fd ) )->second;

		std::deque< int >::iterator it = m_VecFreeLRUList.begin();

		while( it != m_VecFreeLRUList.end() )
		{
			if( ( *it ) == fd )
			{
				m_VecFreeLRUList.erase( it );
				break;
			}
			it++;
		}

		return retval;
	}

	//------------------------------------------------------------------------------
	errno_t CStandardIO::_umask_s( int mode, int* poldmode )
	{
		if( poldmode == NULL )
		{
			return EINVAL;
		}

		*poldmode = m_umaskval;

		if( !( ( mode & ~( CStream::_S_IREAD | CStream::_S_IWRITE ) ) == 0 ) )
		{
			return EINVAL;
		}

		// only user read/write permitted
		mode &= ( CStream::_S_IREAD | CStream::_S_IWRITE );
		m_umaskval = mode;
		return 0;
	}

	//------------------------------------------------------------------------------
	int CStandardIO::_umask( int mode )
	{
		int oldmode = 0;

		// silently ignore non-Windows modes
		mode &= ( CStream::_S_IREAD | CStream::_S_IWRITE );

		_umask_s( mode, &oldmode );
		return oldmode;
	}

	//------------------------------------------------------------------------------
	int CStandardIO::_umaskval()
	{
		return m_umaskval;
	}

	//------------------------------------------------------------------------------
	errno_t CStandardIO::_set_fmode( int mode )
	{
		if( !( ( mode == CStream::OText ) || ( mode == CStream::OBinary ) || ( mode == CStream::OWText ) ) )
		{
			return EINVAL;
		}

		m_InterlockedHelper.Exchange( &m_fmode, mode );

		return 0;
	}

	//------------------------------------------------------------------------------
	errno_t CStandardIO::_get_fmode( int* pMode )
	{
		if( pMode == 0 )
		{
			return EINVAL;
		}

		*pMode = m_fmode;

		return 0;
	}

}//nsWin32
