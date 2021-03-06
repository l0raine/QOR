
//  (C) Copyright Edward Diener 2011-2015
//  Use, modification and distribution are subject to the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt).

#if !defined(QOR_VMD_DETAIL_SEQUENCE_TO_ARRAY_H)
#define QOR_VMD_DETAIL_SEQUENCE_TO_ARRAY_H

#include "CompilerQOR/Preprocessor/preprocessor/control/iif.h"
#include "CompilerQOR/Preprocessor/preprocessor/vmd/detail/modifiers.h"
#include "CompilerQOR/Preprocessor/preprocessor/vmd/detail/mods.h"
#include "CompilerQOR/Preprocessor/preprocessor/vmd/detail/not_empty.h"
#include "CompilerQOR/Preprocessor/preprocessor/vmd/detail/sequence_elem.h"

#define QOR_VMD_DETAIL_SEQUENCE_TO_ARRAY(...) \
    QOR_PP_IIF \
        ( \
        QOR_VMD_DETAIL_NOT_EMPTY(QOR_VMD_DETAIL_SEQUENCE_ELEM_GET_VSEQ(__VA_ARGS__)), \
        QOR_VMD_DETAIL_SEQUENCE_ELEM_PROCESS_TUPLE \
            ( \
            QOR_VMD_DETAIL_SEQUENCE_ELEM_GET_VSEQ(__VA_ARGS__), \
            , \
            QOR_VMD_TYPE_ARRAY, \
            QOR_VMD_DETAIL_NEW_MODS(QOR_VMD_ALLOW_RETURN,__VA_ARGS__) \
            ), \
        (0,()) \
        ) \
/**/

#define QOR_VMD_DETAIL_SEQUENCE_TO_ARRAY_D(d,...) \
    QOR_PP_IIF \
        ( \
        QOR_VMD_DETAIL_NOT_EMPTY(QOR_VMD_DETAIL_SEQUENCE_ELEM_GET_VSEQ(__VA_ARGS__)), \
        QOR_VMD_DETAIL_SEQUENCE_ELEM_PROCESS_TUPLE_D \
            ( \
            d, \
            QOR_VMD_DETAIL_SEQUENCE_ELEM_GET_VSEQ(__VA_ARGS__), \
            , \
            QOR_VMD_TYPE_ARRAY, \
            QOR_VMD_DETAIL_NEW_MODS_D(d,QOR_VMD_ALLOW_RETURN,__VA_ARGS__) \
            ), \
        (0,()) \
        ) \
/**/

#endif /* QOR_VMD_DETAIL_SEQUENCE_TO_ARRAY_H */
