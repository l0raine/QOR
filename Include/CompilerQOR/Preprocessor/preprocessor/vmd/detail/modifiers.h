
//  (C) Copyright Edward Diener 2011-2015
//  Use, modification and distribution are subject to the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt).

#if !defined(QOR_VMD_DETAIL_MODIFIERS_H)
#define QOR_VMD_DETAIL_MODIFIERS_H

#include "CompilerQOR/Preprocessor/preprocessor/vmd/detail/match_single_identifier.h"

#define QOR_VMD_REGISTER_QOR_VMD_RETURN_NO_TYPE (QOR_VMD_RETURN_NO_TYPE)
#define QOR_VMD_REGISTER_QOR_VMD_RETURN_TYPE (QOR_VMD_RETURN_TYPE)
#define QOR_VMD_REGISTER_QOR_VMD_RETURN_TYPE_TUPLE (QOR_VMD_RETURN_TYPE_TUPLE)
#define QOR_VMD_REGISTER_QOR_VMD_RETURN_TYPE_ARRAY (QOR_VMD_RETURN_TYPE_ARRAY)
#define QOR_VMD_REGISTER_QOR_VMD_RETURN_TYPE_LIST  (QOR_VMD_RETURN_TYPE_LIST)

#define QOR_VMD_REGISTER_QOR_VMD_RETURN_AFTER (QOR_VMD_RETURN_AFTER)
#define QOR_VMD_REGISTER_QOR_VMD_RETURN_NO_AFTER (QOR_VMD_RETURN_NO_AFTER)
#define QOR_VMD_REGISTER_QOR_VMD_RETURN_ONLY_AFTER (QOR_VMD_RETURN_ONLY_AFTER)

#define QOR_VMD_REGISTER_QOR_VMD_RETURN_INDEX (QOR_VMD_RETURN_INDEX)
#define QOR_VMD_REGISTER_QOR_VMD_RETURN_NO_INDEX (QOR_VMD_RETURN_NO_INDEX)

#define QOR_VMD_DETECT_QOR_VMD_RETURN_NO_TYPE_QOR_VMD_RETURN_NO_TYPE
#define QOR_VMD_DETECT_QOR_VMD_RETURN_TYPE_QOR_VMD_RETURN_TYPE
#define QOR_VMD_DETECT_QOR_VMD_RETURN_TYPE_TUPLE_QOR_VMD_RETURN_TYPE_TUPLE
#define QOR_VMD_DETECT_QOR_VMD_RETURN_TYPE_ARRAY_QOR_VMD_RETURN_TYPE_ARRAY
#define QOR_VMD_DETECT_QOR_VMD_RETURN_TYPE_LIST_QOR_VMD_RETURN_TYPE_LIST

#define QOR_VMD_DETECT_QOR_VMD_RETURN_AFTER_QOR_VMD_RETURN_AFTER
#define QOR_VMD_DETECT_QOR_VMD_RETURN_NO_AFTER_QOR_VMD_RETURN_NO_AFTER
#define QOR_VMD_DETECT_QOR_VMD_RETURN_ONLY_AFTER_QOR_VMD_RETURN_ONLY_AFTER

#define QOR_VMD_DETECT_QOR_VMD_RETURN_INDEX_QOR_VMD_RETURN_INDEX
#define QOR_VMD_DETECT_QOR_VMD_RETURN_NO_INDEX_QOR_VMD_RETURN_NO_INDEX

#define QOR_VMD_REGISTER_QOR_VMD_ALLOW_ALL  (QOR_VMD_ALLOW_ALL)
#define QOR_VMD_REGISTER_QOR_VMD_ALLOW_RETURN  (QOR_VMD_ALLOW_RETURN)
#define QOR_VMD_REGISTER_QOR_VMD_ALLOW_AFTER  (QOR_VMD_ALLOW_AFTER)
#define QOR_VMD_REGISTER_QOR_VMD_ALLOW_INDEX  (QOR_VMD_ALLOW_INDEX)

#define QOR_VMD_DETECT_QOR_VMD_ALLOW_ALL_QOR_VMD_ALLOW_ALL
#define QOR_VMD_DETECT_QOR_VMD_ALLOW_RETURN_QOR_VMD_ALLOW_RETURN
#define QOR_VMD_DETECT_QOR_VMD_ALLOW_AFTER_QOR_VMD_ALLOW_AFTER
#define QOR_VMD_DETECT_QOR_VMD_ALLOW_INDEX_QOR_VMD_ALLOW_INDEX

#define QOR_VMD_DETAIL_IS_RETURN_TYPE_TUPLE(id) \
    QOR_VMD_DETAIL_MATCH_SINGLE_IDENTIFIER(id,QOR_VMD_RETURN_TYPE_TUPLE) \
/**/

#define QOR_VMD_DETAIL_IS_RETURN_TYPE_ARRAY(id) \
    QOR_VMD_DETAIL_MATCH_SINGLE_IDENTIFIER(id,QOR_VMD_RETURN_TYPE_ARRAY) \
/**/

#define QOR_VMD_DETAIL_IS_RETURN_TYPE_LIST(id) \
    QOR_VMD_DETAIL_MATCH_SINGLE_IDENTIFIER(id,QOR_VMD_RETURN_TYPE_LIST) \
/**/

#define QOR_VMD_DETAIL_IS_RETURN_TYPE(id) \
    QOR_VMD_DETAIL_MATCH_SINGLE_IDENTIFIER(id,QOR_VMD_RETURN_TYPE) \
/**/

#define QOR_VMD_DETAIL_IS_RETURN_NO_TYPE(id) \
    QOR_VMD_DETAIL_MATCH_SINGLE_IDENTIFIER(id,QOR_VMD_RETURN_NO_TYPE) \
/**/

#define QOR_VMD_DETAIL_IS_RETURN_AFTER(id) \
    QOR_VMD_DETAIL_MATCH_SINGLE_IDENTIFIER(id,QOR_VMD_RETURN_AFTER) \
/**/

#define QOR_VMD_DETAIL_IS_RETURN_ONLY_AFTER(id) \
    QOR_VMD_DETAIL_MATCH_SINGLE_IDENTIFIER(id,QOR_VMD_RETURN_ONLY_AFTER) \
/**/

#define QOR_VMD_DETAIL_IS_RETURN_NO_AFTER(id) \
    QOR_VMD_DETAIL_MATCH_SINGLE_IDENTIFIER(id,QOR_VMD_RETURN_NO_AFTER) \
/**/

#define QOR_VMD_DETAIL_IS_RETURN_INDEX(id) \
    QOR_VMD_DETAIL_MATCH_SINGLE_IDENTIFIER(id,QOR_VMD_RETURN_INDEX) \
/**/

#define QOR_VMD_DETAIL_IS_RETURN_NO_INDEX(id) \
    QOR_VMD_DETAIL_MATCH_SINGLE_IDENTIFIER(id,QOR_VMD_RETURN_NO_INDEX) \
/**/

#define QOR_VMD_DETAIL_IS_ALLOW_ALL(id) \
    QOR_VMD_DETAIL_MATCH_SINGLE_IDENTIFIER(id,QOR_VMD_ALLOW_ALL) \
/**/

#define QOR_VMD_DETAIL_IS_ALLOW_RETURN(id) \
    QOR_VMD_DETAIL_MATCH_SINGLE_IDENTIFIER(id,QOR_VMD_ALLOW_RETURN) \
/**/

#define QOR_VMD_DETAIL_IS_ALLOW_AFTER(id) \
    QOR_VMD_DETAIL_MATCH_SINGLE_IDENTIFIER(id,QOR_VMD_ALLOW_AFTER) \
/**/

#define QOR_VMD_DETAIL_IS_ALLOW_INDEX(id) \
    QOR_VMD_DETAIL_MATCH_SINGLE_IDENTIFIER(id,QOR_VMD_ALLOW_INDEX) \
/**/

#endif /* QOR_VMD_DETAIL_MODIFIERS_H */
