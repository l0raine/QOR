//stdio_types.h

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

//SanOS specific definitions associated with stdio

#ifndef SYSTEMQOR_SAN_TYPES_STDIO_H_1
#define SYSTEMQOR_SAN_TYPES_STDIO_H_1

#include "stddef_types.h"
#include "stdint_types.h"
//#include "ctype_types.h"

//--------------------------------------------------------------------------------
namespace nsSanOS
{
	static const int sc_BufferSize = 1024;
    static const int sc_IOFullyBuffered = 0;
    static const int sc_IOLineBuffered = 1;
    static const int sc_IOUnbuffered = 2;
    static const int sc_MaxLength_ctermid = 255;
    static const int sc_MaxLength_tmpnam = 512;
    static const int sc_Seek_Cur = 0;//Seek relative to current position
    static const int sc_Seek_End = 1;//Seek relative to end-of-file
    static const int sc_Seek_Set = 2;//Seek relative to start-of-file
    static const int sc_EndOfFile = -1;//EOF
    static const char* sc_TempDirPrefix="/tmp";
    static const int sc_MaxNumber_UniqueTempNames = 10000;

    typedef long off_t;

	struct _iobuf 
	{
		char* _ptr;
		int   _cnt;
		char* _base;
		int   _flag;
		int   _file;
		int   _charbuf;
		int   _bufsiz;
		char* _tmpfname;
	};
	typedef struct _iobuf FILE;

    // Directory where temporary files may be created.

    #define _P_tmpdir   "\\"
    #define _wP_tmpdir  L"\\"

    //#define FILENAME_MAX    260
    //#define FOPEN_MAX       20
    #define _SYS_OPEN       20


    // Define file position type
	typedef Cmp_long_long fpos_t;
	#define _FPOSOFF(fp) ((long)(fp))

    #define _IOREAD         0x0001
    #define _IOWRT          0x0002

    #define _IOMYBUF        0x0008
    #define _IOEOF          0x0010
    #define _IOERR          0x0020
    #define _IOSTRG         0x0040
    #define _IORW           0x0080

    // constants used by _set_output_format
    #define _TWO_DIGIT_EXPONENT 0x1

}//nsSanOS

#endif//SYSTEMQOR_SAN_TYPES_STDIO_H_1