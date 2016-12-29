//WinQLCommandLine.cpp

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

//Implements Command Line processing

#include <limits.h>
#include "CodeQOR/ErrorSystem/Error.h"
#include "AppocritaQOR/Controller.h"
#include "../Source/SystemQOR/MSWindows/WinQAPI/include/ErrorDomain.h"
#include "../Source/SystemQOR/MSWindows/WinQAPI/include/DynamicLibrary.h"
#include "WinQL/Application/ErrorSystem/WinQLError.h"
#include "WinQL/Application/Process/WinQLProcess.h"
#include "WinQL/Application/Process/WinQLJob.h"
#include "WinQL/Application/Threading/WinQLThread.h"
#include "WinQAPI/Kernel32.h"
#include "WinQAPI/User32.h"
#include "WinQAPI/PSAPI.h"

//------------------------------------------------------------------------------
namespace nsWin32
{
	using namespace nsWinQAPI;

	//--------------------------------------------------------------------------------
	int CProcess::ProcessCommandLine( int& argc, TCHAR**& argv )
	{
		int iArgumentCount= 0;
		int iCharacterCount = 0;
			
		ParseCommandLine( NULL, NULL, &iArgumentCount, &iCharacterCount);//Determine space requirements

		// allocate space for argv[] vector and strings */
		if( iArgumentCount >= ( UINT_MAX / sizeof( TCHAR* ) ) || iCharacterCount >= ( UINT_MAX / sizeof( TCHAR ) ) )
		{
			return -1;
		}

		if( ( iArgumentCount * sizeof( TCHAR* ) + iCharacterCount * sizeof( TCHAR ) ) < ( iCharacterCount * sizeof( TCHAR ) ) )
		{
			return -1;
		}

		TCHAR* pArgs = new TCHAR[ ( iArgumentCount * ( sizeof( TCHAR* ) / sizeof( TCHAR ) ) ) + iCharacterCount ];
        
		if( pArgs == 0 )
		{
			return -1;
		}

		argc = iArgumentCount - 1;
		argv = (TCHAR**)pArgs;

		ParseCommandLine( (TCHAR**)pArgs, pArgs + ( iArgumentCount * ( sizeof( TCHAR* ) / sizeof( TCHAR ) ) ), &iArgumentCount, &iCharacterCount );//Store the arguments

#ifdef WILDCARD
    // call _[w]cwild to expand wildcards in arg vector
#	ifdef WPRFLAG
    if (_wcwild())
#	else
    if (_cwild())
#	endif
        return -1;                  /* out of space */
#endif

		return 0;

	}

	//--------------------------------------------------------------------------------
	void CProcess::ParseCommandLine( TCHAR** argv,  TCHAR* args, int* piArgumentCount, int* piCharacterCount )
	{
		TCHAR* p;
		TCHAR c;
		bool bInQuote;				//Inside quotes 
		bool bCopyChar;                   /* 1 = copy char to *args */
		unsigned int numslash;              /* num of backslashes seen */

		*piCharacterCount = 0;
		*piArgumentCount = 1;                   /* the program name at least */

		TCHAR* cmdstart = GetCommandLine();

		// first scan the program name, copy it, and count the bytes
		p = cmdstart;
		if( argv )
		{
			*argv++ = args;
		}

#ifdef WILDCARD
		/* To handle later wild card expansion, we prefix each entry by
		it's first character before quote handling.  This is done
		so _[w]cwild() knows whether to expand an entry or not. */
		if( args )
		{
			*args++ = *p;
		}
		++*piCharacterCount;

#endif  /* WILDCARD */

		/* A quoted program name is handled here. The handling is much
        simpler than for other arguments. Basically, whatever lies
        between the leading double-quote and next one, or a terminal null
        character is simply accepted. Fancier handling is not required
        because the program name must be a legal NTFS/HPFS file name.
        Note that the double-quote characters are not copied, nor do they
        contribute to numchars. */
        
		bInQuote = false;
		do 
		{
			if( *p == DQUOTECHAR )
			{
				bInQuote = !bInQuote;
				c = (TCHAR) *p++;
				continue;
			}
			++*piCharacterCount;
			if (args)
			{
				*args++ = *p;
			}

			c = (TCHAR) *p++;
#ifdef _MBCS
			if( _ismbblead( c ) ) 
			{
				++*numchars;
				if( args )
				{
					*args++ = *p;   // copy 2nd byte too 
				}
				p++;  // skip over trail byte
			}
#endif  /* _MBCS */

		} while( ( c != NULCHAR && ( bInQuote || ( c != SPACECHAR && c != TABCHAR ) ) ) );

		if( c == NULCHAR ) 
		{
			p--;
		} 
		else 
		{
			if( args )
			{
				*(args-1) = NULCHAR;
			}
		}

		bInQuote = false;

		// loop on each argument
		for(;;) 
		{
			if( ! ParseArgument( argv, args, piArgumentCount, piCharacterCount, p, bInQuote, bCopyChar, numslash ) )
			{
				break;
			}
		}

		// We put one last argument in -- a null ptr
		if( argv )
		{
			*argv++ = NULL;
		}
		++*piArgumentCount;
	}

	//--------------------------------------------------------------------------------
	bool CProcess::ParseArgument( TCHAR** argv, TCHAR* args, int* piArgumentCount, int* piCharacterCount, TCHAR* p, bool& bInQuote, bool& bCopyChar, unsigned int& numslash )
	{
        if ( *p ) 
		{
            while ( *p == SPACECHAR || *p == TABCHAR )
			{
                ++p;
			}
        }

        if( *p == NULCHAR )
		{
            return false;				// end of args
		}

        // scan an argument
        if( argv )
		{
            *argv++ = args;     // store ptr to arg
		}

        ++*piArgumentCount;

#ifdef WILDCARD
		/* To handle later wild card expansion, we prefix each entry by it's first character before quote handling.  This is done so _[w]cwild() knows whether to expand an entry or not. */
		if( args )
		{
			*args++ = *p;
		}
		++*piCharacterCount;

#endif  /* WILDCARD */

		// loop through scanning one argument
		for (;;) 
		{
			if( !ParseOneArgument( args, piCharacterCount, bInQuote, bCopyChar, numslash, p ) )
			{
				break;
			}
        }

        // null-terminate the argument
        if( args )
		{
            *args++ = NULCHAR;          // terminate string
		}
        ++*piCharacterCount;
		return true;
	}

	//--------------------------------------------------------------------------------
	bool CProcess::ParseOneArgument( TCHAR* args, int* piCharacterCount, bool& bInQuote, bool& bCopyChar, unsigned int& numslash, TCHAR* p )
	{
        bCopyChar = true;
        /* Rules: 2N backslashes + " ==> N backslashes and begin/end quote 
		2N+1 backslashes + " ==> N backslashes + literal "
        N backslashes ==> N backslashes */
        numslash = 0;

        while( *p == SLASHCHAR ) 
		{
            // count number of backslashes for use below
            ++p;
            ++numslash;
        }

        if( *p == DQUOTECHAR ) 
		{
            // if 2N backslashes before, start/end quote, otherwise copy literally
            if( numslash % 2 == 0 ) 
			{
                if( bInQuote && p[ 1 ] == DQUOTECHAR ) 
				{
                    p++;    // Double quote inside quoted string
                } 
				else 
				{	// skip first quote char and copy second
                    bCopyChar = 0;       /* don't copy quote */
                    bInQuote = !bInQuote;
                }
            }
            numslash /= 2;          // divide numslash by two
        }

        // copy slashes
        while( numslash-- ) 
		{
            if( args )
			{
                *args++ = SLASHCHAR;
			}
            ++*piCharacterCount;
        }

        // if at end of arg, break loop
        if( *p == NULCHAR || ( !bInQuote && ( *p == SPACECHAR || *p == TABCHAR ) ) )
		{
            return false;//break;
		}

        // copy character into argument
#ifdef _MBCS
        if (bCopyChar) 
		{
            if( args ) 
			{
                if( _ismbblead( *p ) ) 
				{
                    *args++ = *p++;
                    ++*piCharacterCount;
                }
                *args++ = *p;
            } 
			else 
			{
                if( _ismbblead( *p ) ) 
				{
                    ++p;
                    ++*piCharacterCount;
                }
            }
            ++*piCharacterCount;
        }
        ++p;
#else
        if( bCopyChar ) 
		{
            if( args )
			{
                *args++ = *p;
			}
            ++*piCharacterCount;
        }
        ++p;
#endif
		return true;

	}

	//--------------------------------------------------------------------------------
	/*
	nsCodeQOR::CTLinkedList< nsWin32::nsCodeServices::CDll > CProcess::GetModuleList( void )
	{
		_WINQ_FCONTEXT( "CProcess::GetModuleList" );
		nsCodeQOR::CTLinkedList< nsWin32::nsCodeServices::CDll > ModuleList;
		__QOR_PROTECT
		{
			ModuleHandle nHandle;
			ModuleHandle* pHandles = 0;
			unsigned long ulByteCount = 0;				
			m_Win32Helper.EnumProcessModulesEx( reinterpret_cast< InstanceHandle >( m_hProcess ), &nHandle, 1, &ulByteCount, 03 );
			unsigned long ulModuleCount = ( ulByteCount / sizeof( HMODULE ) );

			if( ulModuleCount > 0 )
			{
				pHandles = new ModuleHandle[ ulModuleCount ];
				memset( pHandles, 0, ulModuleCount * sizeof( HMODULE ) );					
				m_Win32Helper.EnumProcessModulesEx( reinterpret_cast< InstanceHandle >( m_hProcess ), pHandles, ulByteCount, &ulByteCount, 0x3 );//LIST_MODULES_ALL

				while( ulModuleCount > 0 )
				{
					if( pHandles[ --ulModuleCount ] != 0 )
					{
						nsWin32::nsCodeServices::CDll* pModule = new nsWin32::nsCodeServices::CDll( reinterpret_cast< HMODULE >( pHandles[ ulModuleCount ] ), true );
						ModuleList.Append( pModule );
					}
				};
			}
		}__QOR_ENDPROTECT
		return ModuleList;
	}
	*/

}//nsWin32

