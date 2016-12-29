// ReferenceTraits.h

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

//Per type reference strategy

#ifndef CODEQOR_TRAITS_REF_H_1
#define CODEQOR_TRAITS_REF_H_1

#ifdef	__QCMP_OPTIMIZEINCLUDE
#pragma	__QCMP_OPTIMIZEINCLUDE
#endif//__QCMP_OPTIMIZEINCLUDE

//#include "CodeQOR/DataStructures/TLRef.h"

#define __QOR_DECLARE_REF_TYPE( _T ) typedef nsCodeQOR::reference_type< _T >::type ref_type

#define __QOR_IMPL_REF( _T ) __QOR_DECLARE_REF_TYPE( _T);\
ref_type Ref( void ) const { return ref_type( this ); }

//--------------------------------------------------------------------------------
namespace nsCodeQOR
{	
	template< class T > class CTLRef;
	//Use template overrides to set up a reference type strategy for a particular type

	//--------------------------------------------------------------------------------
	//This template provides a default reference choice for all types
	//Overload it for any type for which you need to change the form of reference
	template< class T >
	struct reference_type
	{
	public:
		
		typedef CTLRef< T > type;
	};

}//nsCodeQOR

#endif//CODEQOR_TRAITS_REF_H_1
