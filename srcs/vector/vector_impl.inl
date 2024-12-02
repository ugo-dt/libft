#define ft_allocator(Type) ft_allocator_(Type)
#define ft_allocator_(Type) ft_allocator##_##Type

#define _DECL_ALLOCATOR_FUNCTION(ft_vector_type_name, ReturnType, Name, ...) ReturnType ft_allocator_##ft_vector_type_name##_##Name(__VA_ARGS__)
#define DECL_ALLOCATOR_FUNCTION(ft_vector_type_name, ReturnType, Name, ...) _DECL_ALLOCATOR_FUNCTION(ft_vector_type_name, ReturnType, Name, __VA_ARGS__)

DECL_ALLOCATOR_FUNCTION(ft_vector_type_name, void*, allocate, size_t n);
DECL_ALLOCATOR_FUNCTION(ft_vector_type_name, void, deallocate, void *p, size_t n);
DECL_ALLOCATOR_FUNCTION(ft_vector_type_name, void, construct, ft_vector_type *p, ft_vector_const_value_type value);
DECL_ALLOCATOR_FUNCTION(ft_vector_type_name, void, destroy, ft_vector_type *p);

#define _DEF_ALLOCATOR_FUNCTION(ft_vector_type_name, Name) ft_allocator_##ft_vector_type_name##_##Name
#define DEF_ALLOCATOR_FUNCTION(ft_vector_type_name, Name) _DEF_ALLOCATOR_FUNCTION(ft_vector_type_name, Name)

#define ft_allocator_allocate(_n)			DEF_ALLOCATOR_FUNCTION(ft_vector_type_name, allocate)((_n))
#define ft_allocator_deallocate(_p, _n)		DEF_ALLOCATOR_FUNCTION(ft_vector_type_name, deallocate)((_p), (_n))
#define ft_allocator_construct(_p, _x)		DEF_ALLOCATOR_FUNCTION(ft_vector_type_name, construct)((_p), (_x))
#define ft_allocator_destroy(_p)			DEF_ALLOCATOR_FUNCTION(ft_vector_type_name, destroy)((p))

/**
 * ft_allocator_allocate()
 */
void*	DEF_ALLOCATOR_FUNCTION(ft_vector_type_name, allocate)(size_t n)
{
	return LIBFT_MALLOC(n * sizeof(ft_vector_type));
}

/**
 * ft_allocator_deallocate()
 */
void	DEF_ALLOCATOR_FUNCTION(ft_vector_type_name, deallocate)(void *p, size_t n)
{
	(void)n;
	LIBFT_FREE(p);
}

/**
 * ft_allocator_construct()
 */ 
void	DEF_ALLOCATOR_FUNCTION(ft_vector_type_name, construct)(ft_vector_type *p, ft_vector_const_value_type value)
{
	ft_memcpy(p, value, sizeof(ft_vector_type));
}

/**
 * ft_allocator_destroy
 */
void	DEF_ALLOCATOR_FUNCTION(ft_vector_type_name, destroy)(ft_vector_type *p)
{
	(void)p;
}

#define ft_allocator_default(VectorType)									\
	(ft_allocator){															\
			.allocate = DEF_ALLOCATOR_FUNCTION(VectorType, allocate),		\
			.deallocate = DEF_ALLOCATOR_FUNCTION(VectorType, deallocate),	\
			.construct = DEF_ALLOCATOR_FUNCTION(VectorType, construct),		\
			.destroy = DEF_ALLOCATOR_FUNCTION(VectorType, destroy),			\
		};

typedef struct ft_allocator(ft_vector_type_name) ft_allocator(ft_vector_type_name);

struct ft_allocator(ft_vector_type_name)
{
	void*	(*allocate)(size_t n);
	void	(*deallocate)(void* p, size_t n);
	void	(*construct)(ft_vector_pointer p, ft_vector_const_value_type value);
	void	(*destroy)(ft_vector_pointer p);
};

#define ft_vector(Type) ft_vector_(Type)
#define ft_vector_(Type) ft_vector##_##Type

typedef struct ft_vector(ft_vector_type_name) ft_vector(ft_vector_type_name);

struct ft_vector(ft_vector_type_name)
{
	ft_allocator(ft_vector_type_name)	alloc;
	ft_vector_pointer					_begin;
	ft_vector_pointer					_end;
	ft_vector_pointer					_end_cap;

#ifndef FT_VECTOR_NO_FUNCTION_POINTERS
	// ft_vector(ft_vector_type_name)* (*create)(void);
	ft_vector(ft_vector_type_name)*	(*copy)(ft_vector(ft_vector_type_name) *vector, const ft_vector(ft_vector_type_name) *_src);
	ft_vector_pointer			(*data)(ft_vector(ft_vector_type_name) *vector);
	ft_vector_value_type		(*at)(ft_vector(ft_vector_type_name) *vector, size_t n);
	LIBFT_BOOL					(*empty)(const ft_vector(ft_vector_type_name) *vector);
	size_t						(*size)(const ft_vector(ft_vector_type_name) *vector);
	size_t						(*capacity)(const ft_vector(ft_vector_type_name) *vector);
	void						(*reserve)(ft_vector(ft_vector_type_name) *vector, size_t n);
	void						(*resize)(ft_vector(ft_vector_type_name) *vector, size_t n, ft_vector_const_value_type value);
	void						(*assign)(ft_vector(ft_vector_type_name) *vector, size_t n, ft_vector_const_value_type value_ptr);
	void						(*assign_range)(ft_vector(ft_vector_type_name) *vector, ft_vector_pointer first, ft_vector_pointer last);
	void						(*push_back)(ft_vector(ft_vector_type_name) *vector, ft_vector_const_value_type value_ptr);
	ft_vector_value_type		(*insert)(ft_vector(ft_vector_type_name) *vector, size_t position, ft_vector_const_value_type value_ptr);
	void						(*insert_count)(ft_vector(ft_vector_type_name) *vector, size_t position, size_t n, ft_vector_const_value_type value_ptr);
	void						(*insert_range)(ft_vector(ft_vector_type_name) *vector, size_t position, ft_vector_pointer first, ft_vector_pointer last);
	void						(*clear)(ft_vector(ft_vector_type_name) *vector);
	void						(*destroy)(ft_vector(ft_vector_type_name) *vector);
	void						(*pop_back)(ft_vector(ft_vector_type_name) *vector);
	ft_vector_value_type		(*erase)(ft_vector(ft_vector_type_name) *vector, size_t position);
	ft_vector_value_type		(*erase_range)(ft_vector(ft_vector_type_name) *vector, ft_vector_pointer first, ft_vector_pointer last);
	void						(*swap)(ft_vector_pointer *a, ft_vector_pointer *b);
	ft_vector_pointer			(*begin)(const ft_vector(ft_vector_type_name) *vector);
	ft_vector_pointer			(*end)(const ft_vector(ft_vector_type_name) *vector);
#endif
};

struct ft_allocator;
typedef struct ft_allocator ft_allocator;
struct ft_vector;
typedef struct ft_vector ft_vector;

#define _DECL_VECTOR_FUNCTION(ft_vector_type_name, ReturnType, Name, ...) ReturnType ft_vector_##ft_vector_type_name##_##Name(__VA_ARGS__)
#define DECL_VECTOR_FUNCTION(ft_vector_type_name, ReturnType, Name, ...) _DECL_VECTOR_FUNCTION(ft_vector_type_name, ReturnType, Name, __VA_ARGS__)

DECL_VECTOR_FUNCTION(ft_vector_type_name, ft_vector*, create, const ft_allocator(ft_vector_type_name)* alloc);
DECL_VECTOR_FUNCTION(ft_vector_type_name, ft_vector(ft_vector_type_name)*, copy, ft_vector(ft_vector_type_name) *vector, const ft_vector(ft_vector_type_name) *_src);
DECL_VECTOR_FUNCTION(ft_vector_type_name, ft_vector_pointer, data, ft_vector(ft_vector_type_name) *vector);
DECL_VECTOR_FUNCTION(ft_vector_type_name, ft_vector_value_type, at, ft_vector(ft_vector_type_name) *vector, size_t n);
DECL_VECTOR_FUNCTION(ft_vector_type_name, LIBFT_BOOL, empty, const ft_vector(ft_vector_type_name) *vector);
DECL_VECTOR_FUNCTION(ft_vector_type_name, size_t, size, const ft_vector(ft_vector_type_name) *vector);
DECL_VECTOR_FUNCTION(ft_vector_type_name, size_t, capacity, const ft_vector(ft_vector_type_name) *vector);
DECL_VECTOR_FUNCTION(ft_vector_type_name, void, reserve, ft_vector(ft_vector_type_name) *vector, size_t n);
DECL_VECTOR_FUNCTION(ft_vector_type_name, void, resize, ft_vector(ft_vector_type_name) *vector, size_t n, ft_vector_const_value_type value);
DECL_VECTOR_FUNCTION(ft_vector_type_name, void, assign, ft_vector(ft_vector_type_name) *vector, size_t n, ft_vector_const_value_type value_ptr);
DECL_VECTOR_FUNCTION(ft_vector_type_name, void, assign_range, ft_vector(ft_vector_type_name) *vector, ft_vector_pointer first, ft_vector_pointer last);
DECL_VECTOR_FUNCTION(ft_vector_type_name, void, push_back, ft_vector(ft_vector_type_name) *vector, ft_vector_const_value_type value_ptr);
DECL_VECTOR_FUNCTION(ft_vector_type_name, ft_vector_value_type, insert, ft_vector(ft_vector_type_name) *vector, size_t position, ft_vector_const_value_type value_ptr);
DECL_VECTOR_FUNCTION(ft_vector_type_name, void, insert_count, ft_vector(ft_vector_type_name) *vector, size_t position, size_t n, ft_vector_const_value_type value_ptr);
DECL_VECTOR_FUNCTION(ft_vector_type_name, void, insert_range, ft_vector(ft_vector_type_name) *vector, size_t position, ft_vector_pointer first, ft_vector_pointer last);
DECL_VECTOR_FUNCTION(ft_vector_type_name, void, clear, ft_vector(ft_vector_type_name) *vector);
DECL_VECTOR_FUNCTION(ft_vector_type_name, void, destroy, ft_vector(ft_vector_type_name) *vector);
DECL_VECTOR_FUNCTION(ft_vector_type_name, void, pop_back, ft_vector(ft_vector_type_name) *vector);
DECL_VECTOR_FUNCTION(ft_vector_type_name, ft_vector_value_type, erase, ft_vector(ft_vector_type_name) *vector, size_t position);
DECL_VECTOR_FUNCTION(ft_vector_type_name, ft_vector_value_type, erase_range, ft_vector(ft_vector_type_name) *vector, ft_vector_pointer first, ft_vector_pointer last);
DECL_VECTOR_FUNCTION(ft_vector_type_name, void, swap, ft_vector_pointer *a, ft_vector_pointer *b);
DECL_VECTOR_FUNCTION(ft_vector_type_name, ft_vector_pointer, begin, const ft_vector(ft_vector_type_name) *vector);
DECL_VECTOR_FUNCTION(ft_vector_type_name, ft_vector_pointer, end, const ft_vector(ft_vector_type_name) *vector);

#define _DEF_VECTOR_FUNCTION(ft_vector_type_name, Name) ft_vector_##ft_vector_type_name##_##Name
#define DEF_VECTOR_FUNCTION(ft_vector_type_name, Name) _DEF_VECTOR_FUNCTION(ft_vector_type_name, Name)

#define ft_vector_create(_alloc)									DEF_VECTOR_FUNCTION(ft_vector_type_name, create)((_alloc))
#define ft_vector_copy(_dest, _src)									DEF_VECTOR_FUNCTION(ft_vector_type_name, copy)((_dest), (_src))
#define ft_vector_data(_vec)										DEF_VECTOR_FUNCTION(ft_vector_type_name, data)((_vec))
#define ft_vector_at(_vec, _n)										DEF_VECTOR_FUNCTION(ft_vector_type_name, at)((_vec), (_n))
#define ft_vector_empty(_vec)										DEF_VECTOR_FUNCTION(ft_vector_type_name, empty)((_vec))
#define ft_vector_size(_vec)										DEF_VECTOR_FUNCTION(ft_vector_type_name, size)((_vec))
#define ft_vector_capacity(_vec)									DEF_VECTOR_FUNCTION(ft_vector_type_name, capacity)((_vec))
#define ft_vector_reserve(_vec, _n)									DEF_VECTOR_FUNCTION(ft_vector_type_name, reserve)((_vec), (_n))
#define ft_vector_resize(_vec, _n, _value)							DEF_VECTOR_FUNCTION(ft_vector_type_name, resize)((_vec), (_n), (_value))
#define ft_vector_assign(_vec, _n, _value_ptr)						DEF_VECTOR_FUNCTION(ft_vector_type_name, assign)((_vec), (_n), (_value_ptr))
#define ft_vector_assign_range(_vec, _first, _last)					DEF_VECTOR_FUNCTION(ft_vector_type_name, assign_range)((_vec), (_first), (_last))
#define ft_vector_push_back(_vec, _value_ptr)						DEF_VECTOR_FUNCTION(ft_vector_type_name, push_back)((_vec), (_value_ptr))
#define ft_vector_insert(_vec, _position, _value_ptr)				DEF_VECTOR_FUNCTION(ft_vector_type_name, insert)((_vec), (_position), (_value_ptr))
#define ft_vector_insert_count(_vec, _position, _n, _value_ptr)		DEF_VECTOR_FUNCTION(ft_vector_type_name, insert_count)((_vec), (_position), (_n), (_value_ptr))
#define ft_vector_insert_range(_vec, _position, _first, _last)		DEF_VECTOR_FUNCTION(ft_vector_type_name, insert_range)((_vec), (_position), (_first), (_last))
#define ft_vector_clear(_vec)										DEF_VECTOR_FUNCTION(ft_vector_type_name, clear)((_vec))
#define ft_vector_destroy(_vec)										DEF_VECTOR_FUNCTION(ft_vector_type_name, destroy)((_vec))
#define ft_vector_pop_back(_vec)									DEF_VECTOR_FUNCTION(ft_vector_type_name, pop_back)((_vec))
#define ft_vector_erase(_vec, _position)							DEF_VECTOR_FUNCTION(ft_vector_type_name, erase)((_vec), (_position))
#define ft_vector_erase_range(_vec, _first, _last)					DEF_VECTOR_FUNCTION(ft_vector_type_name, erase_range)((_vec), (_first), (_last))
#define ft_vector_swap(_a, _b)										DEF_VECTOR_FUNCTION(ft_vector_type_name, swap)((_a), (_b))
#define ft_vector_begin(_vec)										DEF_VECTOR_FUNCTION(ft_vector_type_name, begin)((_vec))
#define ft_vector_end(_vec)											DEF_VECTOR_FUNCTION(ft_vector_type_name, end)((_vec))
#define ft_vector_swap_vectors(_vec, _x)							DEF_VECTOR_FUNCTION(ft_vector_type_name, swap_vectors)((_vec), (_x))

#define _ft_vector_destruct_at_end(_vec, _new_last)					DEF_VECTOR_FUNCTION(ft_vector_type_name, destruct_at_end)((_vec), (_new_last))
#define _ft_vector_destroy_impl(_vec)								DEF_VECTOR_FUNCTION(ft_vector_type_name, destroy_impl)((_vec))
#define _ft_vector_vallocate(_vec, _n)								DEF_VECTOR_FUNCTION(ft_vector_type_name, vallocate)((_vec), (_n))
#define _ft_vector_vdeallocate(_vec)								DEF_VECTOR_FUNCTION(ft_vector_type_name, vdeallocate)((_vec))
#define _ft_vector_construct_at_end(_vec, _n, _x)					DEF_VECTOR_FUNCTION(ft_vector_type_name, construct_at_end)((_vec), (_n), (_x))
#define _ft_vector_construct_at_end_range(_vec, _first, _last, _n)	DEF_VECTOR_FUNCTION(ft_vector_type_name, construct_at_end_range)((_vec), (_first), (_last), (_n))
#define _ft_vector_recommend(_vec, _newsize)						DEF_VECTOR_FUNCTION(ft_vector_type_name, recommend)((_vec), (_newsize))
#define _ft_vector_append(_vec, _n, _x)								DEF_VECTOR_FUNCTION(ft_vector_type_name, append)((_vec), (_n), (_x))
#define _ft_fill_n(_alloc, _first, _n, _x)							DEF_VECTOR_FUNCTION(ft_vector_type_name, fill_n)((_alloc), (_first), (_n), (_x))
#define _ft_fill_n(_alloc, _first, _n, _x)							DEF_VECTOR_FUNCTION(ft_vector_type_name, fill_n)((_alloc), (_first), (_n), (_x))
#define _insert_in_array(_vec, _p, _n, _position, _x)				DEF_VECTOR_FUNCTION(ft_vector_type_name, insert_in_array)((_vec), (_p), (_n), (_position), (_x))
#define _insert_in_array_range(_vec, _p, _position, _first, _last)	DEF_VECTOR_FUNCTION(ft_vector_type_name, insert_in_array_range)((_vec), (_p), (_position), (_first), (_last))

void	DEF_VECTOR_FUNCTION(ft_vector_type_name, swap_vectors)(ft_vector(ft_vector_type_name) *_v, ft_vector(ft_vector_type_name) *_x)
{
	ft_vector_swap(&_v->_begin, &_x->_begin);
	ft_vector_swap(&_v->_end, &_x->_end);
	ft_vector_swap(&_v->_end_cap, &_x->_end_cap);
}

void*	DEF_VECTOR_FUNCTION(ft_vector_type_name, fill_n)(const ft_allocator(ft_vector_type_name) *_a, ft_vector_pointer first, size_t n, ft_vector_const_value_type x)
{
	for (; n > 0; first++, (void)--n)
		_a->construct(first, x);
	return first;
}

void	DEF_VECTOR_FUNCTION(ft_vector_type_name, destruct_at_end)(ft_vector(ft_vector_type_name) *_v, ft_vector_pointer new_last)
{
	ft_vector_pointer soon_to_be_end = _v->_end;

	while (new_last != soon_to_be_end)
		_v->alloc.destroy(--soon_to_be_end);
	_v->_end = new_last;
}

void	DEF_VECTOR_FUNCTION(ft_vector_type_name, destroy_impl)(ft_vector(ft_vector_type_name) *_v)
{
	if (_v->_begin != NULL)
	{
		ft_vector_clear(_v);
		_v->alloc.deallocate(_v->_begin, ft_vector_capacity(_v));
	}
}

void	DEF_VECTOR_FUNCTION(ft_vector_type_name, vallocate)(ft_vector(ft_vector_type_name) *_v, size_t n)
{
	LIBFT_ASSERT(n <= SIZE_MAX);
	_v->_begin = _v->_end = _v->alloc.allocate(n);
	_v->_end_cap = _v->_begin + n;
}

void	DEF_VECTOR_FUNCTION(ft_vector_type_name, vdeallocate)(ft_vector(ft_vector_type_name) *_v)
{
	if (_v->_begin != 0)
	{
		ft_vector_clear(_v);
		_v->alloc.deallocate(_v->_begin, ft_vector_capacity(_v));
		_v->_begin = _v->_end = _v->_end_cap = 0;
	}
}

void	DEF_VECTOR_FUNCTION(ft_vector_type_name, construct_at_end)(ft_vector(ft_vector_type_name) *_v, size_t n, ft_vector_const_pointer _x)
{
	if (ft_vector_size(_v) + n > ft_vector_capacity(_v))
		return ;
	while (n-- > 0)
	{
		_v->alloc.construct(_v->_end, _x);
		_v->_end++;
	}
}

void	DEF_VECTOR_FUNCTION(ft_vector_type_name, construct_at_end_range)(ft_vector(ft_vector_type_name) *_v, ft_vector_pointer first, ft_vector_pointer last, size_t n)
{
	if (ft_vector_size(_v) + n > ft_vector_capacity(_v) || n == 0)
		return ;
	for (; first != last; first++)
	{
		_v->alloc.construct(_v->_end, (ft_vector_const_pointer)first);
		_v->_end++;
	}
}

size_t	DEF_VECTOR_FUNCTION(ft_vector_type_name, recommend)(const ft_vector(ft_vector_type_name) *_v, size_t new_size)
{
	LIBFT_ASSERT(new_size < SIZE_MAX);
    const size_t cap = ft_vector_capacity(_v);
    if (cap >= SIZE_MAX / 2)
        return SIZE_MAX;
    return max(2 * cap, new_size);
}

void	DEF_VECTOR_FUNCTION(ft_vector_type_name, append)(ft_vector(ft_vector_type_name) *_v, size_t n, ft_vector_const_value_type x)
{
	if (_v->_end_cap - _v->_end >= n)
		_ft_vector_construct_at_end(_v, n, x);
	else
	{
		size_t cs = ft_vector_size(_v);
		ft_vector(ft_vector_type_name) new_v = { .alloc = _v->alloc };

		_ft_vector_vallocate(&new_v, _ft_vector_recommend(_v, cs + n));
		_ft_vector_construct_at_end_range(&new_v, _v->_begin, _v->_begin + cs, cs);
		_ft_vector_construct_at_end(&new_v, n, x);
		ft_vector_swap_vectors(_v, &new_v);
		_ft_vector_destroy_impl(&new_v);
	}
}

void	DEF_VECTOR_FUNCTION(ft_vector_type_name, insert_in_array)(ft_vector(ft_vector_type_name) *_v, ft_vector_pointer p, size_t n, size_t position, ft_vector_const_value_type x)
{
	size_t	size;
	ft_vector_pointer data;
	ft_vector_pointer _dst;
	ft_vector_pointer _src;
	ft_vector_pointer _pos;
	ft_vector_pointer _end;

	size = ft_vector_size(_v);
	data = NULL;
	if (p >= _v->_begin && p <= _v->_end)
	{
		data = _v->alloc.allocate(size);
		ft_memcpy(data, _v->_begin, size * sizeof(ft_vector_type));
		_src = data;
	}
	else
	{
		_src = _v->_begin;
	}

	_dst = p;
	_pos = _src + position;
	_end = _src + size;
	for (; _src != _pos; _src++)
	{
		if (_src)
			_v->alloc.construct(_dst, (ft_vector_const_pointer)_src);
		_dst++;
	}
	while (n--)
	{
		_v->alloc.construct(_dst, x);
		_dst++;
	}
	for (; _src != _end; _src++)
	{
		if (_src)
			_v->alloc.construct(_dst,(ft_vector_const_pointer) _src);
		_dst++;
	}
	if (data)
		_v->alloc.deallocate(data, size);
}

void	DEF_VECTOR_FUNCTION(ft_vector_type_name, insert_in_array_range)(ft_vector(ft_vector_type_name) *_v, ft_vector_pointer p, size_t position, ft_vector_pointer first, ft_vector_pointer last)
{
	size_t	size;
	ft_vector_pointer data;
	ft_vector_pointer _dst;
	ft_vector_pointer _src;
	ft_vector_pointer _pos;
	ft_vector_pointer _end;

	size = ft_vector_size(_v);
	data = NULL;
	if (p >= _v->_begin && p <= _v->_end)
	{
		data = _v->alloc.allocate(size);
		ft_memcpy(data, _v->_begin, size * sizeof(ft_vector_type));
		_src = data;
	}
	else
	{
		_src = _v->_begin;
	}

	_dst = p;
	_pos = _src + position;
	_end = _src + size;
	for (; _src != _pos; _src++)
	{
		if (_src)
			_v->alloc.construct(_dst, (ft_vector_const_pointer)_src);
		_dst++;
	}
	for (; first != last; first++)
	{
		_v->alloc.construct(_dst, (ft_vector_const_pointer)first);
		_dst++;
	}
	for (; _src != _end; _src++)
	{
		if (_src)
			_v->alloc.construct(_dst, (ft_vector_const_pointer)_src);
		_dst++;
	}
	if (data)
		_v->alloc.deallocate(data, size);
}


/**
 * ft_vector_create(ft_allocator alloc)
 */
ft_vector	*DEF_VECTOR_FUNCTION(ft_vector_type_name, create)(const ft_allocator(ft_vector_type_name)* alloc)
{
	ft_vector(ft_vector_type_name)	*v = LIBFT_MALLOC(sizeof(struct ft_vector(ft_vector_type_name)));

	LIBFT_ASSERT(v);
	if (alloc)
	{
		v->alloc = *(ft_allocator(ft_vector_type_name)*)alloc;
	}
	else
	{
		v->alloc = (ft_allocator(ft_vector_type_name)){
				.allocate = DEF_ALLOCATOR_FUNCTION(ft_vector_type_name, allocate),
				.deallocate = DEF_ALLOCATOR_FUNCTION(ft_vector_type_name, deallocate),
				.construct = DEF_ALLOCATOR_FUNCTION(ft_vector_type_name, construct),
				.destroy = DEF_ALLOCATOR_FUNCTION(ft_vector_type_name, destroy),
			};
	}
	v->_begin = v->_end = v->_end_cap = NULL;

#ifndef FT_VECTOR_NO_FUNCTION_POINTERS
	v->copy = DEF_VECTOR_FUNCTION(ft_vector_type_name, copy);
	v->data = DEF_VECTOR_FUNCTION(ft_vector_type_name, data);
	v->at = DEF_VECTOR_FUNCTION(ft_vector_type_name, at);
	v->empty = DEF_VECTOR_FUNCTION(ft_vector_type_name, empty);
	v->size = DEF_VECTOR_FUNCTION(ft_vector_type_name, size);
	v->capacity = DEF_VECTOR_FUNCTION(ft_vector_type_name, capacity);
	v->reserve = DEF_VECTOR_FUNCTION(ft_vector_type_name, reserve);
	v->resize = DEF_VECTOR_FUNCTION(ft_vector_type_name, resize);
	v->assign = DEF_VECTOR_FUNCTION(ft_vector_type_name, assign);
	v->assign_range = DEF_VECTOR_FUNCTION(ft_vector_type_name, assign_range);
	v->push_back = DEF_VECTOR_FUNCTION(ft_vector_type_name, push_back);
	v->insert = DEF_VECTOR_FUNCTION(ft_vector_type_name, insert);
	v->insert_count = DEF_VECTOR_FUNCTION(ft_vector_type_name, insert_count);
	v->insert_range = DEF_VECTOR_FUNCTION(ft_vector_type_name, insert_range);
	v->clear = DEF_VECTOR_FUNCTION(ft_vector_type_name, clear);
	v->destroy = DEF_VECTOR_FUNCTION(ft_vector_type_name, destroy);
	v->pop_back = DEF_VECTOR_FUNCTION(ft_vector_type_name, pop_back);
	v->erase = DEF_VECTOR_FUNCTION(ft_vector_type_name, erase);
	v->erase_range = DEF_VECTOR_FUNCTION(ft_vector_type_name, erase_range);
	v->swap = DEF_VECTOR_FUNCTION(ft_vector_type_name, swap);
	v->begin = DEF_VECTOR_FUNCTION(ft_vector_type_name, begin);
	v->end = DEF_VECTOR_FUNCTION(ft_vector_type_name, end);
#endif // FT_VECTOR_NO_FUNCTION_POINTERS
	return (ft_vector*)v;
}

/**
 * ft_vector_swap
 */
void	DEF_VECTOR_FUNCTION(ft_vector_type_name, swap)(ft_vector_pointer *a, ft_vector_pointer *b)
{
	ft_vector_pointer tmp;

	// TDOO: avoid shallow copy
	// this should construct the object
	tmp = *a;
	*a = *b;
	*b = tmp;
}

/**
 * ft_vector_capacity
 */
size_t	DEF_VECTOR_FUNCTION(ft_vector_type_name, capacity)(const ft_vector(ft_vector_type_name) *_v)
{
	return _v->_end_cap - _v->_begin;
}

/**
 * ft_vector_size
 */
size_t	DEF_VECTOR_FUNCTION(ft_vector_type_name, size)(const ft_vector(ft_vector_type_name) *_v)
{
	return _v->_end - _v->_begin;
}

/**
 * ft_vector_clear
 */
void	DEF_VECTOR_FUNCTION(ft_vector_type_name, clear)(ft_vector(ft_vector_type_name) *_v)
{
	if (_v->_begin != NULL)
		_ft_vector_destruct_at_end(_v, _v->_begin);
}

/**
 * ft_vector_copy
 */
ft_vector(ft_vector_type_name)	*DEF_VECTOR_FUNCTION(ft_vector_type_name, copy)(ft_vector(ft_vector_type_name) *_v, const ft_vector(ft_vector_type_name) *_src)
{
	if (_v != _src)
	{
		// _copy_assign_alloc(_v, _src);
		ft_vector_reserve(_v, ft_vector_capacity(_src));
		ft_vector_assign_range(_v, _src->_begin, _src->_end);
	}
	return _v;
}

/**
 * ft_vector_empty
 */
LIBFT_BOOL	DEF_VECTOR_FUNCTION(ft_vector_type_name, empty)(const ft_vector(ft_vector_type_name) *_v)
{
	return _v->_begin == _v->_end;
}

/**
 * ft_vector_data
 */
ft_vector_value_type	DEF_VECTOR_FUNCTION(ft_vector_type_name, data)(ft_vector(ft_vector_type_name) *_v)
{
	return _v->_begin;
}

/**
 * ft_vector_at
 */
ft_vector_value_type	DEF_VECTOR_FUNCTION(ft_vector_type_name, at)(ft_vector(ft_vector_type_name) *_v, size_t n)
{
	return _v->_begin + n;
}

/**
 * ft_vector_destroy
 */
void	DEF_VECTOR_FUNCTION(ft_vector_type_name, destroy)(ft_vector(ft_vector_type_name) *_v)
{
	_ft_vector_destroy_impl(_v);
	LIBFT_FREE(_v);
}

/**
 * ft_vector_pop_back
 */
void	DEF_VECTOR_FUNCTION(ft_vector_type_name, pop_back)(ft_vector(ft_vector_type_name) *_v)
{
	_ft_vector_destruct_at_end(_v, _v->_end - 1);
}

/**
 * ft_vector_reserve
 */
void	DEF_VECTOR_FUNCTION(ft_vector_type_name, reserve)(ft_vector(ft_vector_type_name) *_v, size_t n)
{
	if (n > ft_vector_capacity(_v))
	{
		size_t cs = ft_vector_size(_v);
		ft_vector(ft_vector_type_name)	new_v = { .alloc = _v->alloc };

		_ft_vector_vallocate(&new_v, n);
		_ft_vector_construct_at_end_range(&new_v, _v->_begin, _v->_begin + cs, cs);
		ft_vector_swap_vectors(_v, &new_v);
		_ft_vector_destroy_impl(&new_v);
	}
}

/**
 * ft_vector_resize
 */
void	DEF_VECTOR_FUNCTION(ft_vector_type_name, resize)(ft_vector(ft_vector_type_name) *_v, size_t n, ft_vector_const_value_type value)
{
	size_t cs = ft_vector_size(_v);
	if (cs < n)
		_ft_vector_append(_v, n - cs, value);
	else if (cs > n)
		_ft_vector_destruct_at_end(_v, ft_vector_at(_v, n));
}

/**
 * ft_vector_assign
 */
void	DEF_VECTOR_FUNCTION(ft_vector_type_name, assign)(ft_vector(ft_vector_type_name) *_v, size_t n, ft_vector_const_value_type x)
{
	if (n <= ft_vector_capacity(_v))
	{
		size_t s = ft_vector_size(_v);
		_ft_fill_n(&_v->alloc, _v->_begin, min(n, s), x);
		if (n > s)
			_ft_vector_construct_at_end(_v, n - s, x);
		else
			_ft_vector_destruct_at_end(_v, _v->_begin + n);
	}
	else
	{
		_ft_vector_vdeallocate(_v);
		_ft_vector_vallocate(_v, n);
		_ft_vector_construct_at_end(_v, n, x);
	}
}

/**
 * ft_vector_assign_range
 */
void	DEF_VECTOR_FUNCTION(ft_vector_type_name, assign_range)(ft_vector(ft_vector_type_name) *_v, ft_vector_pointer first, ft_vector_pointer last)
{
	ft_vector_clear(_v);
	for (; first != last; first++)
		ft_vector_push_back(_v, (ft_vector_const_pointer)first);
}

/**
 * ft_vector_push_back
 */
void	DEF_VECTOR_FUNCTION(ft_vector_type_name, push_back)(ft_vector(ft_vector_type_name) *_v, ft_vector_const_value_type x)
{
	if (_v->_end != _v->_end_cap)
		_ft_vector_construct_at_end(_v, 1, x);
	else
	{
		ft_vector(ft_vector_type_name)	new_v = { .alloc = _v->alloc };

		ft_vector_reserve(&new_v, _ft_vector_recommend(_v, ft_vector_size(_v) + 1));

		ft_vector_assign_range(&new_v, _v->_begin, _v->_end);
		_v->alloc.construct(new_v._end, x);
		new_v._end++;
		ft_vector_swap_vectors(_v, &new_v);
		_ft_vector_destroy_impl(&new_v);
	}
}

/**
 * ft_vector_insert
 */
ft_vector_pointer	DEF_VECTOR_FUNCTION(ft_vector_type_name, insert)(ft_vector(ft_vector_type_name) *_v, size_t position, ft_vector_const_value_type x)
{
	LIBFT_ASSERT(position <= ft_vector_size(_v));

	ptrdiff_t d = ft_vector_at(_v, position) - _v->_begin;
	ft_vector_pointer p = _v->_begin + d;

	if (_v->_end < _v->_end_cap)
	{
		if (p == _v->_end)
			ft_vector_push_back(_v, x);
		else
			_insert_in_array(_v, _v->_begin, 1, position, x);
	}
	else
	{
		ft_vector(ft_vector_type_name)   new_v = { .alloc = _v->alloc };

		ft_vector_reserve(&new_v, ft_vector_size(_v) + 1);
		ft_vector_copy(&new_v, _v);
		_insert_in_array(_v, new_v._begin, 1, position, x);
		ft_vector_swap_vectors(_v, &new_v);
		_ft_vector_destroy_impl(&new_v);
	}
	_v->_end++;
	return _v->_begin + d;
}

/**
 * ft_vector_insert_count
 */
void	DEF_VECTOR_FUNCTION(ft_vector_type_name, insert_count)(ft_vector(ft_vector_type_name) *_v, size_t position, size_t n, ft_vector_const_value_type x)
{
	if (n <= _v->_end_cap - _v->_end)
	{
		_insert_in_array(_v, _v->_begin, n, position, x);
	}
	else
	{
		ft_vector(ft_vector_type_name)   new_v = { .alloc = _v->alloc };

		ft_vector_reserve(&new_v, ft_vector_size(_v) + n);
		ft_vector_copy(&new_v, _v);
		_insert_in_array(_v, new_v._begin, n, position, x);
		ft_vector_swap_vectors(_v, &new_v);
		_ft_vector_destroy_impl(&new_v);
	}
	_v->_end += n;
}

/**
 * ft_vector_insert_range
 */
void	DEF_VECTOR_FUNCTION(ft_vector_type_name, insert_range)(ft_vector(ft_vector_type_name) *_v, size_t position, ft_vector_pointer first, ft_vector_pointer last)
{
	size_t n = 0;
	for (ft_vector_pointer tmp = first; tmp != last; tmp++)
		n++;
	if (n <= _v->_end_cap - _v->_end)
	{
		_insert_in_array_range(_v, _v->_begin, position, first, last);
	}
	else
	{
		ft_vector(ft_vector_type_name)   new_v = { .alloc = _v->alloc };
		
		ft_vector_reserve(&new_v, ft_vector_size(_v) + n);
		ft_vector_copy(&new_v, _v);
		_insert_in_array_range(_v, new_v._begin, position, first, last);
		
		ft_vector_swap_vectors(_v, &new_v);
		_ft_vector_destroy_impl(&new_v);
	}
	_v->_end += n;
}

/**
 * ft_vector_erase
 */
ft_vector_pointer	DEF_VECTOR_FUNCTION(ft_vector_type_name, erase)(ft_vector(ft_vector_type_name) *_v, size_t position)
{
	return (ft_vector_erase_range(_v, ft_vector_at(_v, position), ft_vector_at(_v, position + 1)));
}

/**
 * ft_vector_erase_range
 */
ft_vector_pointer	DEF_VECTOR_FUNCTION(ft_vector_type_name, erase_range)(ft_vector(ft_vector_type_name) *_v, ft_vector_pointer first, ft_vector_pointer last)
{
	ft_vector_pointer r = first;
	size_t n = 0;
	for (ft_vector_pointer tmp = first; tmp != last; tmp++)
		n++;
	for (; last != _v->_end; first++, last++)
		_v->alloc.construct(first, (ft_vector_const_pointer)last);
	while (n--)
		_ft_vector_destruct_at_end(_v, _v->_end - 1);
	return (r);
}

/**
 * ft_vector_begin
 */
ft_vector_pointer	DEF_VECTOR_FUNCTION(ft_vector_type_name, begin)(const ft_vector(ft_vector_type_name) *_v)
{
	return _v->_begin;
}

/**
 * ft_vector_end
 */
ft_vector_pointer	DEF_VECTOR_FUNCTION(ft_vector_type_name, end)(const ft_vector(ft_vector_type_name) *_v)
{
	return _v->_end;
}

#undef ft_vector_create
#undef ft_vector_copy
#undef ft_vector_data
#undef ft_vector_at
#undef ft_vector_empty
#undef ft_vector_size
#undef ft_vector_capacity
#undef ft_vector_reserve
#undef ft_vector_resize
#undef ft_vector_assign
#undef ft_vector_assign_range
#undef ft_vector_push_back
#undef ft_vector_insert
#undef ft_vector_insert_count
#undef ft_vector_insert_range
#undef ft_vector_clear
#undef ft_vector_destroy
#undef ft_vector_pop_back
#undef ft_vector_erase
#undef ft_vector_erase_range
#undef ft_vector_swap
#undef ft_vector_begin
#undef ft_vector_end
#undef ft_vector_swap_vectors
#undef _ft_vector_destruct_at_end
#undef _ft_vector_destroy_impl
#undef _ft_vector_vallocate
#undef _ft_vector_vdeallocate
#undef _ft_vector_construct_at_end
#undef _ft_vector_construct_at_end_range
#undef _ft_vector_recommend
#undef _ft_vector_append
#undef _ft_fill_n
#undef _ft_fill_n
#undef _insert_in_array
#undef _insert_in_array_range
