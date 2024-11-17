#include "libft.h"

pointer	_allocator_allocate(size_t n, size_t type_size)
{
	return LIBFT_MALLOC(n * type_size);
}

void	_allocator_deallocate(pointer p, size_t n)
{
	(void)n;
	LIBFT_FREE(p);
}

void	_allocator_construct(pointer p, const_value_type value, size_t type_size)
{
	ft_memcpy(p, value, type_size);
}

void	_allocator_destroy(pointer p)
{
	(void)p;
}

void	_swap(pointer *a, pointer *b)
{
	pointer tmp;

	tmp = *a;
	*a = *b;
	*b = tmp;
}

void	*_fill_n(pointer first, size_t n, const_value_type x, size_t type_size)
{
	for (; n > 0; _ft_pointer_inc(first, type_size), (void)--n)
		_allocator_construct(first, x, type_size);
	return first;
}

size_t	_capacity(const ft_vector *_v)
{
	return (size_t)pointer_subp(_v->_end_cap, _v->_begin);
}

size_t	_size(const ft_vector *_v)
{
	return (size_t)pointer_subp(_v->_end, _v->_begin);
}

size_t	_recommend(const ft_vector *_v, size_t new_size)
{
	assert(new_size < SIZE_MAX);
    const size_t cap = ft_vector_capacity(_v);
    if (cap >= SIZE_MAX / 2)
        return SIZE_MAX;
    return max(2 * cap, new_size);
}

void	_destruct_at_end(ft_vector *_v, pointer new_last)
{
	pointer soon_to_be_end = _v->_end;

	while (new_last != soon_to_be_end)
	{
		_ft_pointer_dec(soon_to_be_end, _v->type_size);
		_allocator_destroy(soon_to_be_end);
	}
	_v->_end = new_last;
}

void	_clear(ft_vector *_v)
{
	_destruct_at_end(_v, _v->_begin);
}

void	_vallocate(ft_vector *_v, size_t n)
{
	assert(n <= SIZE_MAX);
	_v->_begin = _v->_end = _allocator_allocate(n, _v->type_size);
	_v->_end_cap = pointer_add(_v->_begin, n, _v->type_size);
}

void	_vdeallocate(ft_vector *_v)
{
	if (_v->_begin != 0)
	{
		_clear(_v);
		_allocator_deallocate(_v->_begin, _capacity(_v));
		_v->_begin = _v->_end = _v->_end_cap = 0;
	}
}

void	_construct_at_end(ft_vector *_v, size_t n, const_pointer _x)
{
	if (_size(_v) + n * _v->type_size > _capacity(_v))
		return ;
	while (n-- > 0)
	{
		_allocator_construct(_v->_end, _x, _v->type_size);
		_ft_pointer_inc(_v->_end, _v->type_size);
	}
}

void	_construct_at_end_range(ft_vector *_v, pointer first, pointer last, size_t n)
{
	if (_size(_v) + n * _v->type_size > _capacity(_v) || n == 0)
		return ;
	for (; first != last; _ft_pointer_inc(first, _v->type_size))
	{
		_allocator_construct(_v->_end, first, _v->type_size);
		_ft_pointer_inc(_v->_end, _v->type_size);
	}
}

ft_vector	*ft_vector_copy(ft_vector *_v, const ft_vector *_src)
{
	if (_v != _src)
	{
		//_copy_assign_alloc(_v, _src);
		ft_vector_reserve(_v, _capacity(_src));
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
	assert(_v->type_size > 0);
	return (_size(_v) / _v->type_size);
}

size_t	ft_vector_capacity(const ft_vector *_v)
{
	assert(_v->type_size > 0);
	return (_capacity(_v) / _v->type_size);
}

value_type	ft_vector_data(ft_vector *_v)
{
	return _v->_begin;
}

value_type	ft_vector_at(ft_vector *_v, size_t n)
{
	return pointer_add(_v->_begin, n, _v->type_size);
}

void	ft_vector_clear(ft_vector *_v)
{
	_clear(_v);
}

void	ft_vector_destroy(ft_vector *_v)
{
	if (_v->_begin != NULL)
	{
		_clear(_v);
		_allocator_deallocate(_v->_begin, _capacity(_v));
	}
}

void	ft_vector_pop_back(ft_vector *_v)
{
	_destruct_at_end(_v, pointer_sub(_v->_end, 1, _v->type_size));
}

void	ft_vector_reserve(ft_vector *_v, size_t n)
{
	if (n * _v->type_size > _capacity(_v))
	{
		size_t cs = ft_vector_size(_v);
		ft_vector	new_v = { .type_size = _v->type_size };

		_vallocate(&new_v, n);
		_construct_at_end_range(&new_v, _v->_begin, pointer_add(_v->_begin, cs, _v->type_size), cs);
		ft_vector_swap(_v, &new_v);
		ft_vector_destroy(&new_v);
	}
}

void	_append(ft_vector *_v, size_t n, const_value_type x)
{
	if ((size_t)pointer_subp(_v->_end_cap, _v->_end) >= n)
		_construct_at_end(_v, n, x);
	else
	{
		size_t cs = ft_vector_size(_v);
		ft_vector new_v = { .type_size = _v->type_size };

		_vallocate(&new_v, _recommend(_v, cs + n));
		_construct_at_end_range(&new_v, _v->_begin, pointer_add(_v->_begin, cs, _v->type_size), cs);
		_construct_at_end(&new_v, n, x);
		ft_vector_swap(_v, &new_v);
		ft_vector_destroy(&new_v);
	}
}

void	ft_vector_resize(ft_vector *_v, size_t n, const_value_type value)
{
	size_t cs = ft_vector_size(_v);
	if (cs < n)
		_append(_v, n - cs, value);
	else if (cs > n)
		_destruct_at_end(_v, ft_vector_at(_v, n));
}

void	ft_vector_assign(ft_vector *_v, size_t n, const_value_type x)
{
	if (n *_v->type_size <= _capacity(_v))
	{
		size_t s = ft_vector_size(_v);
		_fill_n(_v->_begin, min(n, s), x, _v->type_size);
		if (n > s)
			_construct_at_end(_v, n - s, x);
		else
			_destruct_at_end(_v, pointer_add(_v->_begin, n, _v->type_size));
	}
	else
	{
		_vdeallocate(_v);
		_vallocate(_v, n);
		_construct_at_end(_v, n, x);
	}
}

void	ft_vector_assign_range(ft_vector *_v, pointer first, pointer last)
{
	_clear(_v);
	for (; first != last; _ft_pointer_inc(first, _v->type_size))
		ft_vector_push_back(_v, first);
}

void	ft_vector_push_back(ft_vector *_v, const_value_type x)
{
	if (_v->_end != _v->_end_cap)
		_construct_at_end(_v, 1, x);
	else
	{
		ft_vector	new_v = { .type_size = _v->type_size };

		ft_vector_reserve(&new_v, _recommend(_v, ft_vector_size(_v) + 1));
		ft_vector_assign_range(&new_v, _v->_begin, _v->_end);
		_allocator_construct(new_v._end, x, new_v.type_size);
		_ft_pointer_inc(new_v._end, new_v.type_size);
		ft_vector_swap(_v, &new_v);
		ft_vector_destroy(&new_v);
	}
}

void	_insert_in_array(ft_vector *_v, pointer p, size_t n, size_t position, const_value_type x)
{
	size_t	size;
	pointer data;
	pointer _dst, _src, _pos, _end;

	size = _size(_v);
	data = NULL;
	if (p >= _v->_begin && p <= _v->_end)
	{
		data = _allocator_allocate(size, 1);
		ft_memcpy(data, _v->_begin, size);
		_src = data;
	}
	else
	{
		_src = _v->_begin;
	}

	_dst = p;
	_pos = pointer_add(_src, position, _v->type_size);
	_end = pointer_add(_src, size, 1);
	for (; _src != _pos; _ft_pointer_inc(_src, _v->type_size))
	{
		if (_src)
			_allocator_construct(_dst, _src, _v->type_size);
		_ft_pointer_inc(_dst, _v->type_size);
	}
	while (n--)
	{
		_allocator_construct(_dst, x, _v->type_size);
		_ft_pointer_inc(_dst, _v->type_size);
	}
	for (; _src != _end; _ft_pointer_inc(_src, _v->type_size))
	{
		if (_src)
			_allocator_construct(_dst, _src, _v->type_size);
		_ft_pointer_inc(_dst, _v->type_size);
	}
	if (data)
		_allocator_deallocate(data, size);
}

void	_insert_in_array_range(ft_vector *_v, pointer p, size_t position, pointer first, pointer last)
{
	size_t	size;
	pointer data;
	pointer _dst, _src, _pos, _end;

	size = _size(_v);
	data = NULL;
	if (p >= _v->_begin && p <= _v->_end)
	{
		data = _allocator_allocate(size, 1);
		ft_memcpy(data, _v->_begin, size);
		_src = data;
	}
	else
	{
		_src = _v->_begin;
	}

	_dst = p;
	_pos = pointer_add(_src, position, _v->type_size);
	_end = pointer_add(_src, size, 1);
	for (; _src != _pos; _ft_pointer_inc(_src, _v->type_size))
	{
		if (_src)
			_allocator_construct(_dst, _src, _v->type_size);
		_ft_pointer_inc(_dst, _v->type_size);
	}
	for (; first != last; _ft_pointer_inc(first, _v->type_size))
	{
		_allocator_construct(_dst, first, _v->type_size);
		_ft_pointer_inc(_dst, _v->type_size);
	}
	for (; _src != _end; _ft_pointer_inc(_src, _v->type_size))
	{
		if (_src)
			_allocator_construct(_dst, _src, _v->type_size);
		_ft_pointer_inc(_dst, _v->type_size);
	}
	if (data)
		_allocator_deallocate(data, size);
}

pointer	ft_vector_insert(ft_vector *_v, size_t position, const_value_type x)
{
	LIBFT_ASSERT(position <= ft_vector_size(_v));

	ptrdiff_t d = (ptrdiff_t)pointer_subp(ft_vector_at(_v, position), _v->_begin);
	pointer p = pointer_add(_v->_begin, d, _v->type_size);

	if (_v->_end < _v->_end_cap)
	{
		if (p == _v->_end)
			ft_vector_push_back(_v, x);
		else
			_insert_in_array(_v, _v->_begin, 1, position, x);
	}
	else
	{
		ft_vector   new_v = { .type_size = _v->type_size };

		ft_vector_reserve(&new_v, ft_vector_size(_v) + 1);
		ft_vector_copy(&new_v, _v);
		_insert_in_array(_v, new_v._begin, 1, position, x);
		ft_vector_swap(_v, &new_v);
		ft_vector_destroy(&new_v);
	}
	_ft_pointer_inc(_v->_end, _v->type_size);
	return pointer_add(_v->_begin, d, _v->type_size);
}

void	ft_vector_insert_count(ft_vector *_v, size_t position, size_t n, const_value_type x)
{
	if (n < 0)
		return ;
	if (n <= (size_t)pointer_subp(_v->_end_cap, _v->_end))
	{
		_insert_in_array(_v, _v->_begin, n, position, x);
	}
	else
	{
		ft_vector   new_v = { .type_size = _v->type_size };

		ft_vector_reserve(&new_v, ft_vector_size(_v) + n);
		ft_vector_copy(&new_v, _v);
		_insert_in_array(_v, new_v._begin, n, position, x);
		ft_vector_swap(_v, &new_v);
		ft_vector_destroy(&new_v);
	}
	_v->_end = pointer_add(_v->_end, n, _v->type_size);
}

void	ft_vector_insert_range(ft_vector *_v, size_t position, pointer first, pointer last)
{
	size_t n = 0;
	for (pointer tmp = first; tmp != last; _ft_pointer_inc(tmp, _v->type_size))
		n++;
	if (n < 0)
		return ;
	if (n <= (size_t)pointer_subp(_v->_end_cap, _v->_end))
	{
		_insert_in_array_range(_v, _v->_begin, position, first, last);
	}
	else
	{
		ft_vector   new_v = { .type_size = _v->type_size };
		
		ft_vector_reserve(&new_v, ft_vector_size(_v) + n);
		ft_vector_copy(&new_v, _v);
		_insert_in_array_range(_v, new_v._begin, position, first, last);
		
		ft_vector_swap(_v, &new_v);
		ft_vector_destroy(&new_v);
	}
	_v->_end = pointer_add(_v->_end, n, _v->type_size);
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
		_allocator_construct(first, last, _v->type_size);
	while (n--)
		_destruct_at_end(_v, pointer_sub(_v->_end, 1, _v->type_size));
	return (r);
}

void	ft_vector_swap(ft_vector *_v, ft_vector *_x)
{
	_swap(&_v->_begin, &_x->_begin);
	_swap(&_v->_end, &_x->_end);
	_swap(&_v->_end_cap, &_x->_end_cap);
	_swap((pointer)&_v->type_size, (pointer)&_x->type_size);
}

pointer	ft_vector_begin(ft_vector *_v)
{
	return _v->_begin;
}

pointer	ft_vector_end(ft_vector *_v)
{
	return _v->_end;
}
