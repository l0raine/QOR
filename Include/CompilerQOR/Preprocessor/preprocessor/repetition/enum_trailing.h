//enum_trailing.h

# /* **************************************************************************
#  *                                                                          *
#  *     (C) Copyright Paul Mensonides 2002.
#  *     Distributed under the Boost Software License, Version 1.0. (See
#  *     accompanying file LICENSE_1_0.txt or copy at
#  *     http://www.boost.org/LICENSE_1_0.txt)
#  *                                                                          *
#  ************************************************************************** */

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

#ifndef QOR_PREPROCESSOR_REPETITION_ENUM_TRAILING_H_1
#define QOR_PREPROCESSOR_REPETITION_ENUM_TRAILING_H_1

#include "../cat.h"
#include "../config/config.h"
#include "../debug/error.h"
#include "../detail/auto_rec.h"
#include "repeat.h"
#include "../tuple/elem.h"
#include "../tuple/rem.h"

//QOR_PP_ENUM_TRAILING( count, macro, data )

#define QOR_PP_ENUM_TRAILING					QOR_PP_CAT( QOR_PP_ENUM_TRAILING_, QOR_PP_AUTO_REC( QOR_PP_REPEAT_P, 4 ) )

#if	~QOR_PP_CONFIG_FLAGS() & QOR_PP_CONFIG_EDG()
#	define QOR_PP_ENUM_TRAILING_1( c, m, d )	QOR_PP_REPEAT_1( c, QOR_PP_ENUM_TRAILING_M_1, ( m, d ) )
#	define QOR_PP_ENUM_TRAILING_2( c, m, d )	QOR_PP_REPEAT_2( c, QOR_PP_ENUM_TRAILING_M_2, ( m, d ) )
#	define QOR_PP_ENUM_TRAILING_3( c, m, d )	QOR_PP_REPEAT_3( c, QOR_PP_ENUM_TRAILING_M_3, ( m, d ) )
#else//EDG
#	define QOR_PP_ENUM_TRAILING_1( c, m, d )	QOR_PP_ENUM_TRAILING_1_I( c, m, d )
#	define QOR_PP_ENUM_TRAILING_2( c, m, d )	QOR_PP_ENUM_TRAILING_2_I( c, m, d )
#	define QOR_PP_ENUM_TRAILING_3( c, m, d )	QOR_PP_ENUM_TRAILING_3_I( c, m, d )
#	define QOR_PP_ENUM_TRAILING_1_I( c, m, d )	QOR_PP_REPEAT_1( c, QOR_PP_ENUM_TRAILING_M_1, ( m, d ) )
#	define QOR_PP_ENUM_TRAILING_2_I( c, m, d )	QOR_PP_REPEAT_2( c, QOR_PP_ENUM_TRAILING_M_2, ( m, d ) )
#	define QOR_PP_ENUM_TRAILING_3_I( c, m, d )	QOR_PP_REPEAT_3( c, QOR_PP_ENUM_TRAILING_M_3, ( m, d ) )
#endif

#define QOR_PP_ENUM_TRAILING_4( c, m, d )		QOR_PP_ERROR( 0x0003 )

#if QOR_PP_CONFIG_FLAGS() & QOR_PP_CONFIG_STRICT()
#   define QOR_PP_ENUM_TRAILING_M_1( z, n, md ) QOR_PP_ENUM_TRAILING_M_1_IM( z, n, QOR_PP_TUPLE_REM_2 md )
#   define QOR_PP_ENUM_TRAILING_M_2( z, n, md ) QOR_PP_ENUM_TRAILING_M_2_IM( z, n, QOR_PP_TUPLE_REM_2 md )
#   define QOR_PP_ENUM_TRAILING_M_3( z, n, md ) QOR_PP_ENUM_TRAILING_M_3_IM( z, n, QOR_PP_TUPLE_REM_2 md )
#   define QOR_PP_ENUM_TRAILING_M_1_IM( z, n, im ) QOR_PP_ENUM_TRAILING_M_1_I( z, n, im )
#   define QOR_PP_ENUM_TRAILING_M_2_IM( z, n, im ) QOR_PP_ENUM_TRAILING_M_2_I( z, n, im )
#   define QOR_PP_ENUM_TRAILING_M_3_IM( z, n, im ) QOR_PP_ENUM_TRAILING_M_3_I( z, n, im )
#else
#   define QOR_PP_ENUM_TRAILING_M_1( z, n, md ) QOR_PP_ENUM_TRAILING_M_1_I( z, n, QOR_PP_TUPLE_ELEM( 2, 0, md ), QOR_PP_TUPLE_ELEM( 2, 1, md ) )
#   define QOR_PP_ENUM_TRAILING_M_2( z, n, md ) QOR_PP_ENUM_TRAILING_M_2_I( z, n, QOR_PP_TUPLE_ELEM( 2, 0, md ), QOR_PP_TUPLE_ELEM( 2, 1, md ) )
#   define QOR_PP_ENUM_TRAILING_M_3( z, n, md ) QOR_PP_ENUM_TRAILING_M_3_I( z, n, QOR_PP_TUPLE_ELEM( 2, 0, md ), QOR_PP_TUPLE_ELEM( 2, 1, md ) )
#endif

#define QOR_PP_ENUM_TRAILING_M_1_I( z, n, m, d ) , m( z, n, d )
#define QOR_PP_ENUM_TRAILING_M_2_I( z, n, m, d ) , m( z, n, d )
#define QOR_PP_ENUM_TRAILING_M_3_I( z, n, m, d ) , m( z, n, d )

#endif//QOR_PREPROCESSOR_REPETITION_ENUM_TRAILING_H_1
