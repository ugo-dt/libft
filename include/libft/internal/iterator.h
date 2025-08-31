#pragma once

#include "libft.h"

#define _POINTER_ADD(__p, __size, __n) ((char*)(__p) + ((__n) * (__size)))
#define _POINTER_SUB(__p, __size, __n) ((char*)(__p) - ((__n) * (__size)))
#define _POINTER_INC(__p, __size) ((__p) = (_POINTER_ADD(__p, 1)))
#define _POINTER_DEC(__p, __size) ((__p) = (_POINTER_DEC(__p, 1)))

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

#define FT_ITER_VALUE(__it) (( \
	(__it)._type) == IteratorType_Reverse ? _POINTER_SUB((__it)._p, (__it)._sizeof_type, 1) : ((__it)._p))

#define FT_ITER_EQ(__it_a, __it_b) (((__it_a)._p) == ((__it_b)._p))

static inline ft_iterator	_make_iter(size_t sizeof_type, void* p, IteratorType type)
{
	return (ft_iterator){
		._p = p,
		._sizeof_type = sizeof_type,
		._type = type,
	};
}

// static inline int	_ft_iter_sign(IteratorType type)
// {
// 	return type == IteratorType_Reverse ? -1 : 1;
// }

// static inline ft_iterator	ft_iter_inc(ft_iterator* it)
// {
// 	return (ft_iterator){
// 		._p = (char*)it->_p + (it->_sizeof_type * _ft_iter_sign(it->_type)),
// 		._sizeof_type = it->_sizeof_type
// 	};
// }

// static inline ft_iterator	ft_iter_post_inc(ft_iterator* it)
// {
// 	ft_iterator i = *it;
// 	it->_p = (char*)it->_p + (i._sizeof_type * _ft_iter_sign(it->_type));
// 	return i;
// }

// static inline ft_iterator	ft_iter_dec(ft_iterator* it)
// {
// 	return (ft_iterator){
// 		._p = (char*)it->_p - (it->_sizeof_type * _ft_iter_sign(it->_type)),
// 		._sizeof_type = it->_sizeof_type
// 	};
// }

// static inline ft_iterator	ft_iter_post_dec(ft_iterator* it)
// {
// 	ft_iterator i = *it;
// 	it->_p = (char*)it->_p - (i._sizeof_type * _ft_iter_sign(it->_type));
// 	return i;
// }

// void*	ft_iter_value(const ft_iterator* it)
// {
// 	if (it->_type == IteratorType_Reverse)
// 		return (char*)it->_p - it->_sizeof_type;
// 	return it->_p;
// }
