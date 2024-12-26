#include "libft.h"

typedef void*				value_type;
typedef const void * const	const_value_type;
typedef void*				pointer;
typedef const void * const	const_pointer;

typedef struct ft_vector
{
	size_t			type_size;
	ft_allocator	alloc;
	void *		_begin;
	void *		_end;
	void *		_end_cap;
}ft_vector;

ft_vector	*_ft_vector_create(size_t type_size, ft_allocator alloc)
{
	ft_vector	*v = LIBFT_MALLOC(sizeof(struct ft_vector));

	LIBFT_ASSERT(v);
	v->type_size = type_size;
	v->alloc = alloc;
	v->_begin = v->_end = v->_end_cap = NULL;
	return v;
}

void	_ft_vector_swap(pointer *a, pointer *b)
{
	pointer tmp;

	tmp = *a;
	*a = *b;
	*b = tmp;
}

void	*_ft_fill_n(const ft_allocator *_a, pointer first, size_t n, const_value_type x, size_t type_size)
{
	for (; n > 0; _ft_pointer_inc(first, type_size), (void)--n)
		_a->construct(first, x, type_size);
	return first;
}

size_t	_ft_vector_realcap(const ft_vector *_v)
{
	return (size_t)_ft_pointer_subp(_v->_end_cap, _v->_begin);
}

size_t	_ft_vector_realsize(const ft_vector *_v)
{
	return (size_t)_ft_pointer_subp(_v->_end, _v->_begin);
}

size_t	_ft_vector_recommend(const ft_vector *_v, size_t new_size)
{
	LIBFT_ASSERT(new_size < SIZE_MAX);
    const size_t cap = ft_vector_capacity(_v);
    if (cap >= SIZE_MAX / 2)
        return SIZE_MAX;
    return max(2 * cap, new_size);
}

void	_ft_vector_destruct_at_end(ft_vector *_v, pointer new_last)
{
	pointer soon_to_be_end = _v->_end;

	while (new_last != soon_to_be_end)
	{
		_ft_pointer_dec(soon_to_be_end, _v->type_size);
		_v->alloc.destroy(soon_to_be_end);
	}
	_v->_end = new_last;
}

void	_ft_vector_clear(ft_vector *_v)
{
	if (_v->_begin != NULL)
		_ft_vector_destruct_at_end(_v, _v->_begin);
}

void	_ft_vector_destroy(ft_vector *_v)
{
	if (_v->_begin != NULL)
	{
		_ft_vector_clear(_v);
		_v->alloc.deallocate(_v->_begin, _ft_vector_realcap(_v));
	}
}

void	_ft_vector_vallocate(ft_vector *_v, size_t n)
{
	LIBFT_ASSERT(n <= SIZE_MAX);
	_v->_begin = _v->_end = _v->alloc.allocate(n, _v->type_size);
	_v->_end_cap = _ft_pointer_add(_v->_begin, n, _v->type_size);
}

void	_ft_vector_vdeallocate(ft_vector *_v)
{
	if (_v->_begin != 0)
	{
		_ft_vector_clear(_v);
		_v->alloc.deallocate(_v->_begin, _ft_vector_realcap(_v));
		_v->_begin = _v->_end = _v->_end_cap = 0;
	}
}

void	_ft_vector_construct_at_end(ft_vector *_v, size_t n, const_pointer _x)
{
	if (_ft_vector_realsize(_v) + n * _v->type_size > _ft_vector_realcap(_v))
		return ;
	while (n-- > 0)
	{
		_v->alloc.construct(_v->_end, _x, _v->type_size);
		_ft_pointer_inc(_v->_end, _v->type_size);
	}
}

void	_ft_vector_construct_at_end_range(ft_vector *_v, pointer first, pointer last, size_t n)
{
	if (_ft_vector_realsize(_v) + n * _v->type_size > _ft_vector_realcap(_v) || n == 0)
		return ;
	for (; first != last; _ft_pointer_inc(first, _v->type_size))
	{
		_v->alloc.construct(_v->_end, first, _v->type_size);
		_ft_pointer_inc(_v->_end, _v->type_size);
	}
}

ft_vector	*ft_vector_copy(ft_vector *_v, const ft_vector *_src)
{
	if (_v != _src)
	{
		// _copy_assign_alloc(_v, _src);
		ft_vector_reserve(_v, _ft_vector_realcap(_src));
		ft_vector_assign_range(_v, _src->_begin, _src->_end);
	}
	return _v;
}

LIBFT_BOOL	ft_vector_empty(const ft_vector *_v)
{
	return _v->_begin == _v->_end;
}

size_t	ft_vector_size(const ft_vector *_v)
{
	LIBFT_ASSERT(_v->type_size > 0);
	return (_ft_vector_realsize(_v) / _v->type_size);
}

size_t	LIBFT_VECTOR_TYPE_size(const ft_vector *_v)
{
	return _v->type_size;
}

size_t	ft_vector_capacity(const ft_vector *_v)
{
	LIBFT_ASSERT(_v->type_size > 0);
	return (_ft_vector_realcap(_v) / _v->type_size);
}

value_type	ft_vector_data(ft_vector *_v)
{
	return _v->_begin;
}

value_type	ft_vector_at(ft_vector *_v, size_t n)
{
	return _ft_pointer_add(_v->_begin, n, _v->type_size);
}

void	ft_vector_clear(ft_vector *_v)
{
	_ft_vector_clear(_v);
}

void	ft_vector_destroy(ft_vector *_v)
{
	_ft_vector_destroy(_v);
	LIBFT_FREE(_v);
}

void	ft_vector_pop_back(ft_vector *_v)
{
	_ft_vector_destruct_at_end(_v, _ft_pointer_sub(_v->_end, 1, _v->type_size));
}

void	ft_vector_reserve(ft_vector *_v, size_t n)
{
	if (n * _v->type_size > _ft_vector_realcap(_v))
	{
		size_t cs = ft_vector_size(_v);
		ft_vector	new_v = { .type_size = _v->type_size, .alloc = _v->alloc };

		_ft_vector_vallocate(&new_v, n);
		_ft_vector_construct_at_end_range(&new_v, _v->_begin, _ft_pointer_add(_v->_begin, cs, _v->type_size), cs);
		ft_vector_swap(_v, &new_v);
		_ft_vector_destroy(&new_v);
	}
}

void	_ft_vector_append(ft_vector *_v, size_t n, const_value_type x)
{
	if ((size_t)_ft_pointer_subp(_v->_end_cap, _v->_end) >= n)
		_ft_vector_construct_at_end(_v, n, x);
	else
	{
		size_t cs = ft_vector_size(_v);
		ft_vector new_v = { .type_size = _v->type_size, .alloc = _v->alloc };

		_ft_vector_vallocate(&new_v, _ft_vector_recommend(_v, cs + n));
		_ft_vector_construct_at_end_range(&new_v, _v->_begin, _ft_pointer_add(_v->_begin, cs, _v->type_size), cs);
		_ft_vector_construct_at_end(&new_v, n, x);
		ft_vector_swap(_v, &new_v);
		_ft_vector_destroy(&new_v);
	}
}

void	ft_vector_resize(ft_vector *_v, size_t n, const_value_type value)
{
	size_t cs = ft_vector_size(_v);
	if (cs < n)
		_ft_vector_append(_v, n - cs, value);
	else if (cs > n)
		_ft_vector_destruct_at_end(_v, ft_vector_at(_v, n));
}

void	ft_vector_assign(ft_vector *_v, size_t n, const_value_type x)
{
	if (n *_v->type_size <= _ft_vector_realcap(_v))
	{
		size_t s = ft_vector_size(_v);
		_ft_fill_n(&_v->alloc, _v->_begin, min(n, s), x, _v->type_size);
		if (n > s)
			_ft_vector_construct_at_end(_v, n - s, x);
		else
			_ft_vector_destruct_at_end(_v, _ft_pointer_add(_v->_begin, n, _v->type_size));
	}
	else
	{
		_ft_vector_vdeallocate(_v);
		_ft_vector_vallocate(_v, n);
		_ft_vector_construct_at_end(_v, n, x);
	}
}

void	ft_vector_assign_range(ft_vector *_v, pointer first, pointer last)
{
	_ft_vector_clear(_v);
	for (; first != last; _ft_pointer_inc(first, _v->type_size))
		ft_vector_push_back(_v, first);
}

void	ft_vector_push_back(ft_vector *_v, const_value_type x)
{
	if (_v->_end != _v->_end_cap)
		_ft_vector_construct_at_end(_v, 1, x);
	else
	{
		ft_vector	new_v = { .type_size = _v->type_size, .alloc = _v->alloc };

		ft_vector_reserve(&new_v, _ft_vector_recommend(_v, ft_vector_size(_v) + 1));

		ft_vector_assign_range(&new_v, _v->_begin, _v->_end);
		_v->alloc.construct(new_v._end, x, new_v.type_size);
		_ft_pointer_inc(new_v._end, new_v.type_size);
		ft_vector_swap(_v, &new_v);
		_ft_vector_destroy(&new_v);
	}
}

void	_insert_in_array(ft_vector *_v, pointer p, size_t n, size_t position, const_value_type x)
{
	size_t	size;
	pointer data;
	pointer _dst, _src, _pos, _end;

	size = _ft_vector_realsize(_v);
	data = NULL;
	if (p >= _v->_begin && p <= _v->_end)
	{
		data = _v->alloc.allocate(size, 1);
		ft_memcpy(data, _v->_begin, size);
		_src = data;
	}
	else
	{
		_src = _v->_begin;
	}

	_dst = p;
	_pos = _ft_pointer_add(_src, position, _v->type_size);
	_end = _ft_pointer_add(_src, size, 1);
	for (; _src != _pos; _ft_pointer_inc(_src, _v->type_size))
	{
		if (_src)
			_v->alloc.construct(_dst, _src, _v->type_size);
		_ft_pointer_inc(_dst, _v->type_size);
	}
	while (n--)
	{
		_v->alloc.construct(_dst, x, _v->type_size);
		_ft_pointer_inc(_dst, _v->type_size);
	}
	for (; _src != _end; _ft_pointer_inc(_src, _v->type_size))
	{
		if (_src)
			_v->alloc.construct(_dst, _src, _v->type_size);
		_ft_pointer_inc(_dst, _v->type_size);
	}
	if (data)
		_v->alloc.deallocate(data, size);
}

void	_insert_in_array_range(ft_vector *_v, pointer p, size_t position, pointer first, pointer last)
{
	size_t	size;
	pointer data;
	pointer _dst, _src, _pos, _end;

	size = _ft_vector_realsize(_v);
	data = NULL;
	if (p >= _v->_begin && p <= _v->_end)
	{
		data = _v->alloc.allocate(size, 1);
		ft_memcpy(data, _v->_begin, size);
		_src = data;
	}
	else
	{
		_src = _v->_begin;
	}

	_dst = p;
	_pos = _ft_pointer_add(_src, position, _v->type_size);
	_end = _ft_pointer_add(_src, size, 1);
	for (; _src != _pos; _ft_pointer_inc(_src, _v->type_size))
	{
		if (_src)
			_v->alloc.construct(_dst, _src, _v->type_size);
		_ft_pointer_inc(_dst, _v->type_size);
	}
	for (; first != last; _ft_pointer_inc(first, _v->type_size))
	{
		_v->alloc.construct(_dst, first, _v->type_size);
		_ft_pointer_inc(_dst, _v->type_size);
	}
	for (; _src != _end; _ft_pointer_inc(_src, _v->type_size))
	{
		if (_src)
			_v->alloc.construct(_dst, _src, _v->type_size);
		_ft_pointer_inc(_dst, _v->type_size);
	}
	if (data)
		_v->alloc.deallocate(data, size);
}

pointer	ft_vector_insert(ft_vector *_v, size_t position, const_value_type x)
{
	LIBFT_ASSERT(position <= ft_vector_size(_v));

	ptrdiff_t d = (ptrdiff_t)_ft_pointer_subp(ft_vector_at(_v, position), _v->_begin);
	pointer p = _ft_pointer_add(_v->_begin, d, _v->type_size);

	if (_v->_end < _v->_end_cap)
	{
		if (p == _v->_end)
			ft_vector_push_back(_v, x);
		else
			_insert_in_array(_v, _v->_begin, 1, position, x);
	}
	else
	{
		ft_vector   new_v = { .type_size = _v->type_size, .alloc = _v->alloc };

		ft_vector_reserve(&new_v, ft_vector_size(_v) + 1);
		ft_vector_copy(&new_v, _v);
		_insert_in_array(_v, new_v._begin, 1, position, x);
		ft_vector_swap(_v, &new_v);
		_ft_vector_destroy(&new_v);
	}
	_ft_pointer_inc(_v->_end, _v->type_size);
	return _ft_pointer_add(_v->_begin, d, _v->type_size);
}

void	ft_vector_insert_count(ft_vector *_v, size_t position, size_t n, const_value_type x)
{
	if (n <= (size_t)_ft_pointer_subp(_v->_end_cap, _v->_end))
	{
		_insert_in_array(_v, _v->_begin, n, position, x);
	}
	else
	{
		ft_vector   new_v = { .type_size = _v->type_size, .alloc = _v->alloc };

		ft_vector_reserve(&new_v, ft_vector_size(_v) + n);
		ft_vector_copy(&new_v, _v);
		_insert_in_array(_v, new_v._begin, n, position, x);
		ft_vector_swap(_v, &new_v);
		_ft_vector_destroy(&new_v);
	}
	_v->_end = _ft_pointer_add(_v->_end, n, _v->type_size);
}

void	ft_vector_insert_range(ft_vector *_v, size_t position, pointer first, pointer last)
{
	size_t n = 0;
	for (pointer tmp = first; tmp != last; _ft_pointer_inc(tmp, _v->type_size))
		n++;
	if (n <= (size_t)_ft_pointer_subp(_v->_end_cap, _v->_end))
	{
		_insert_in_array_range(_v, _v->_begin, position, first, last);
	}
	else
	{
		ft_vector   new_v = { .type_size = _v->type_size, .alloc = _v->alloc };
		
		ft_vector_reserve(&new_v, ft_vector_size(_v) + n);
		ft_vector_copy(&new_v, _v);
		_insert_in_array_range(_v, new_v._begin, position, first, last);
		
		ft_vector_swap(_v, &new_v);
		_ft_vector_destroy(&new_v);
	}
	_v->_end = _ft_pointer_add(_v->_end, n, _v->type_size);
}

pointer	ft_vector_erase(ft_vector *_v, size_t position)
{
	return (ft_vector_erase_range(_v, ft_vector_at(_v, position), ft_vector_at(_v, position + 1)));
}

pointer ft_vector_erase_range(ft_vector *_v, pointer first, pointer last)
{
	pointer r = first;
	size_t n = 0;
	for (pointer tmp = first; tmp != last; _ft_pointer_inc(tmp, _v->type_size))
		n++;
	for (; last != _v->_end; _ft_pointer_inc(first, _v->type_size), _ft_pointer_inc(last, _v->type_size))
		_v->alloc.construct(first, last, _v->type_size);
	while (n--)
		_ft_vector_destruct_at_end(_v, _ft_pointer_sub(_v->_end, 1, _v->type_size));
	return (r);
}

void	ft_vector_swap(ft_vector *_v, ft_vector *_x)
{
	_ft_vector_swap(&_v->_begin, &_x->_begin);
	_ft_vector_swap(&_v->_end, &_x->_end);
	_ft_vector_swap(&_v->_end_cap, &_x->_end_cap);
	_ft_vector_swap((pointer)&_v->type_size, (pointer)&_x->type_size);
}

pointer	ft_vector_begin(const ft_vector *_v)
{
	return _v->_begin;
}

pointer	ft_vector_end(const ft_vector *_v)
{
	return _v->_end;
}
