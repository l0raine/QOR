//ParamErrorDomain.h

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

//An Error Domain for parameter errors

#ifndef CODEQOR_ERROR_PARAMDOMAIN_H_1
#define CODEQOR_ERROR_PARAMDOMAIN_H_1

#include "CompilerQOR.h"

#ifdef	__QCMP_OPTIMIZEINCLUDE
#pragma	__QCMP_OPTIMIZEINCLUDE
#endif//__QCMP_OPTIMIZEINCLUDE

#include "CodeQOR/ErrorSystem/BaseErrorDomain.h"
#include "CodeQOR.h"

//--------------------------------------------------------------------------------
namespace nsCodeQOR
{
	class CParamErrorDomain;

#ifdef __CODEQOR
	extern CParamErrorDomain TheParamErrorDomain;
#endif

}//nsCodeQOR


//--------------------------------------------------------------------------------
namespace nsCodeQOR
{
	//--------------------------------------------------------------------------------
	//A specialized error domain for parameter validation errors
	class __QOR_INTERFACE( __CODEQOR ) CParamErrorDomain : public CBaseErrorDomain
	{		
	public:

		//--------------------------------------------------------------------------------
		enum E_Notes
		{
			MAX_PENOTES = CBaseErrorDomain::MAX_NOTES + 1,
		};

		//--------------------------------------------------------------------------------
		enum E_Warnings
		{					
			UNKNOWN_WARNING = CBaseErrorDomain::MAX_WARNS,
			UNINITIALIZED_RETURN,
			MAX_PEWARNS //Always last
		};

		//--------------------------------------------------------------------------------
		enum E_Errors
		{
			UNKNOWN_ERROR = CBaseErrorDomain::MAX_ERRORS,
			NULL_POINTER,
			UNREADABLE_POINTER,
			STRING_TOO_LONG,
			STRING_TOO_COMPLEX,
			UNWRITEABLE_POINTER,
			GENERAL_CHECK_FAILURE,
			MAX_PEERRORS //Always last
		};

		CParamErrorDomain();
		~CParamErrorDomain();

        virtual const CBaseErrorDomain::s_BaseError* NoteTemplate( unsigned int uiCode );
        virtual const CBaseErrorDomain::s_BaseError* WarningTemplate( unsigned int uiCode );
        virtual const CBaseErrorDomain::s_BaseError* ErrorTemplate( unsigned int uiCode );              

	protected:

		static const nsCodeQOR::CBaseErrorDomain::s_BaseError m_PENotes[ CParamErrorDomain::MAX_PENOTES - ( nsCodeQOR::CBaseErrorDomain::MAX_NOTES ) ];
		static const nsCodeQOR::CBaseErrorDomain::s_BaseError m_PEWarnings[ CParamErrorDomain::MAX_PEWARNS - ( nsCodeQOR::CBaseErrorDomain::MAX_WARNS ) ];
		static const nsCodeQOR::CBaseErrorDomain::s_BaseError m_PEErrors[ CParamErrorDomain::MAX_PEERRORS - ( nsCodeQOR::CBaseErrorDomain::MAX_ERRORS ) ];

	};

	__QOR_INTERFACE( __CODEQOR ) CParamErrorDomain& ParamErrorDomain( void );

}//nsCodeQOR

#endif//CODEQOR_ERROR_PARAMDOMAIN_H_1
