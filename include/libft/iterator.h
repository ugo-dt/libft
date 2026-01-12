#pragma once

#include "libft/libft.h"

#define _POINTER_ADD(__p, __size, __n) ((char*)(__p) + ((__n) * (__size)))
#define _POINTER_SUB(__p, __size, __n) ((char*)(__p) - ((__n) * (__size)))
#define _POINTER_INC(__p, __size) ((__p) = (_POINTER_ADD(__p, 1)))
#define _POINTER_DEC(__p, __size) ((__p) = (_POINTER_DEC(__p, 1)))

#define POINTER_ADD(__v, __p, __n) _POINTER_ADD((__p), ((__v)->alloc.sizeof_type), (__n))
#define POINTER_SUB(__v, __p, __n) _POINTER_SUB((__p), ((__v)->alloc.sizeof_type), (__n))
#define POINTER_INC(__v, __p) ((__p) = (POINTER_ADD(__v, __p, 1)))
#define POINTER_DEC(__v, __p) ((__p) = (POINTER_SUB(__v, __p, 1)))

// type size is inferred. never use with void*
// #define _POINTER_POST_ADD(__p, __n) ({ __typeof__(__p) _old = (__p); (__p) = (__p) + __n; _old; })
// #define POINTER_POST_INC(__p) _POINTER_POST_ADD(__p, 1)
// #define POINTER_POST_DEC(__p) _POINTER_POST_ADD(__p, -1)

#define _ITER_ADD_SUB_TYPE(__p, __size, __n, __type) _POINTER_ADD((__p), (__size), ((__n) * (__type)))

#define _FT_ITER_ADD_P(__it, __n) _ITER_ADD_SUB_TYPE((__it)._p, (__it)._sizeof_type, (__n), (__it)._type)
#define _FT_ITER_SUB_P(__it, __n) _ITER_ADD_SUB_TYPE((__it)._p, (__it)._sizeof_type, (__n), ((__it)._type * -1))

#define _ITER_INC_DEC_TYPE(__p, __size, __type) _ITER_ADD_SUB_TYPE((__p), (__size), 1, (__type))
#define _FT_ITER_INC_P(__it) _ITER_INC_DEC_TYPE((__it)._p, (__it)._sizeof_type, (__it)._type)
#define _FT_ITER_DEC_P(__it) _ITER_INC_DEC_TYPE((__it)._p, (__it)._sizeof_type, ((__it)._type * -1))

// Modify the iterator in place
#define FT_ITER_ADD(__it, __n) ((__it) = (ft_iterator){ \
	._p = _FT_ITER_ADD_P(__it, __n), ._sizeof_type = (__it)._sizeof_type, ._type = (__it)._type} )
#define FT_ITER_SUB(__it, __n) ((__it) = (ft_iterator){ \
	._p = _FT_ITER_SUB_P(__it, __n), ._sizeof_type = (__it)._sizeof_type, ._type = (__it)._type} )
#define FT_ITER_INC(__it) ((__it) = (ft_iterator){ \
	._p = _FT_ITER_INC_P((__it)), ._sizeof_type = (__it)._sizeof_type, ._type = (__it)._type} )
#define FT_ITER_DEC(__it) ((__it) = (ft_iterator){ \
	._p = _FT_ITER_DEC_P((__it)), ._sizeof_type = (__it)._sizeof_type, ._type = (__it)._type} )

// Makes a new iterator
#define FT_ITER_ADD_NEW(__it, __n) ((ft_iterator){ \
	._p = _FT_ITER_ADD_P(__it, __n), ._sizeof_type = (__it)._sizeof_type, ._type = (__it)._type} )
#define FT_ITER_SUB_NEW(__it, __n) ((ft_iterator){ \
	._p = _FT_ITER_SUB_P(__it, __n), ._sizeof_type = (__it)._sizeof_type, ._type = (__it)._type} )
#define FT_ITER_INC_NEW(__it) ((ft_iterator){ \
	._p = _FT_ITER_INC_P((__it)), ._sizeof_type = (__it)._sizeof_type, ._type = (__it)._type} )
#define FT_ITER_DEC_NEW(__it) ((ft_iterator){ \
	._p = _FT_ITER_DEC_P((__it)), ._sizeof_type = (__it)._sizeof_type, ._type = (__it)._type} )

#define FT_ITER_REF(__it) (( \
	(__it)._type) == IteratorType_Reverse ? _POINTER_SUB((__it)._p, (__it)._sizeof_type, 1) : ((__it)._p))
#define FT_ITER_VALUE(__it, __type) (*(__type *)(FT_ITER_REF(__it))) // dereference
 
#define FT_ITER_EQ(__it_a, __it_b) (((__it_a)._p) == ((__it_b)._p)) // equal
#define FT_ITER_LT(__it_a, __it_b) (((__it_a)._p) < ((__it_b)._p)) // less than
#define FT_ITER_NEQ(__it_a, __it_b) (!(FT_ITER_EQ((__it_a), (__it_b)))) // not equal
#define FT_ITER_GT(__it_a, __it_b) (FT_ITER_LT((__it_b), (__it_a)) && FT_ITER_NEQ((__it_a), (__it_b))) // greater than
#define FT_ITER_LE(__it_a, __it_b) (!FT_ITER_GT((__it_a), (__it_b))) // less than or equal
#define FT_ITER_GE(__it_a, __it_b) (!FT_ITER_LT((__it_a), (__it_b))) // greater than or equal

#define ftv_each(__vector, __it) \
	for (ft_iterator __it = _ftv_begin((&__vector)); \
		 FT_ITER_NEQ(__it, _ftv_end((&__vector))); \
		 FT_ITER_INC(__it))

#define ftv_each_reverse(__vector, __rit) \
	for (ft_iterator __rit = _ftv_rbegin((&__vector)); \
		 FT_ITER_NEQ(__rit, _ftv_rend((&__vector))); \
		 FT_ITER_INC(__rit))
