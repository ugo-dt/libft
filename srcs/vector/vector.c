#include "libft/libft.h"
#include "libft/iterator.h"

#define ft_def(__a, __b) (((__a) == 0) ? (__b) : (__a))

static inline ft_iterator	_make_iter(size_t sizeof_type, void* p, IteratorType type)
{
	return (ft_iterator){
		._p = p,
		._sizeof_type = sizeof_type,
		._type = type,
	};
}

static void	_swap(void **a, void **b)
{
	void* tmp;

	tmp = *a;
	*a = *b;
	*b = tmp;
}

ft_allocator	_ft_allocator_defaults(const ft_allocator* alloc)
{
	assert(alloc->sizeof_type != 0);

	ft_allocator	def = *alloc;

	def.max_size = ft_def(def.max_size, ft_allocator_max_size);
	def.allocate = ft_def(def.allocate, ft_allocator_allocate);
	def.deallocate = ft_def(def.deallocate, ft_allocator_deallocate);
	def.construct = ft_def(def.construct, ft_allocator_construct);
	def.destroy = ft_def(def.destroy, ft_allocator_destroy);
	return def;
}

void	_construct_at_end(ft_vector* vector, size_t n, const void* value)
{
	assert(_ftv_size(vector) + n <= _ftv_capacity(vector));
	while (n-- > 0)
	{
		vector->alloc.construct(&vector->alloc, vector->end, value);
		POINTER_INC(vector, vector->end);
	}
}

void	_construct_at_end_iter(ft_vector* vector, ft_iterator first, ft_iterator last, size_t n)
{
	assert(_ftv_size(vector) + n <= _ftv_capacity(vector));

	if (n == 0)
		return ;
	for (; !FT_ITER_EQ(first, last); FT_ITER_INC(first))
	{
		vector->alloc.construct(&vector->alloc, vector->end, FT_ITER_REF(first));
		POINTER_INC(vector, vector->end);
	}
}

void	_destruct_at_end(ft_vector* vector, void* new_last)
{
	void* soon_to_be_end = vector->end;
	while (new_last != soon_to_be_end)
	{
		POINTER_DEC(vector, soon_to_be_end);
		vector->alloc.destroy(&vector->alloc, soon_to_be_end);
	}
	vector->end = new_last;
}

void	_vallocate(ft_vector* vector, size_t n)
{
	assert(n <= vector->alloc.max_size(&vector->alloc));

	vector->begin = vector->end = vector->alloc.allocate(&vector->alloc, n);
	vector->end_cap = POINTER_ADD(vector, vector->begin, n);
}

void	_ftv_swap(ft_vector* _v, ft_vector* _x)
{
	ft_allocator tmp = _v->alloc;
	_v->alloc = _x->alloc;
	_x->alloc = tmp;

	_swap(&_v->begin, &_x->begin);
	_swap(&_v->end, &_x->end);
	_swap(&_v->end_cap, &_x->end_cap);
}

size_t	_ftv_recommend(const ft_vector* vector, size_t new_size)
{
	size_t max_size = vector->alloc.max_size(&vector->alloc);
	
	assert(new_size < vector->alloc.max_size(&vector->alloc));
    const size_t cap = _ftv_capacity(vector);
    if (cap >= max_size / 2)
        return max_size;
    return max(2 * cap, new_size);
}

ft_vector	ftv_create(const ftv_desc* desc)
{
	return (ft_vector){
		.alloc = _ft_allocator_defaults(&desc->alloc),
		.begin = NULL,
		.end = NULL,
		.end_cap = NULL,
	};
}

void	_ftv_destroy(ft_vector* vector)
{
	if (vector->begin)
	{
		_ftv_clear(vector);
		vector->alloc.deallocate(&vector->alloc, vector->begin, _ftv_capacity(vector));
		vector->begin = vector->end = vector->end_cap = NULL;
	}
}

void*	_ftv_data(const ft_vector* vector)
{
	return vector->begin;
}

void*	_ftv_at(const ft_vector* vector, size_t n)
{
	assert(n < _ftv_size(vector));
	return POINTER_ADD(vector, vector->begin, n);
}

ft_iterator	_ftv_begin(const ft_vector* vector)
{
	return _make_iter(vector->alloc.sizeof_type, vector->begin, IteratorType_Random);
}

ft_iterator	_ftv_end(const ft_vector* vector)
{
	return _make_iter(vector->alloc.sizeof_type, vector->end, IteratorType_Random);
}

ft_iterator	_ftv_rbegin(const ft_vector* vector)
{
	return _make_iter(vector->alloc.sizeof_type, vector->end, IteratorType_Reverse);
}

ft_iterator	_ftv_rend(const ft_vector* vector)
{
	return _make_iter(vector->alloc.sizeof_type, vector->begin, IteratorType_Reverse);
}

size_t	_ftv_max_size(const ft_vector* vector)
{
	return vector->alloc.max_size(&vector->alloc);
}

size_t	_ftv_size(const ft_vector* vector)
{
	return ((char*)vector->end - (char*)vector->begin) / vector->alloc.sizeof_type;
}

size_t	_ftv_capacity(const ft_vector* vector)
{
	return ((char*)vector->end_cap - (char*)vector->begin) / vector->alloc.sizeof_type;
}

size_t	_ftv_empty(const ft_vector* vector)
{
	return vector->begin == vector->end;
}

void	_ftv_reserve(ft_vector* vector, size_t n)
{
	if (n > _ftv_capacity(vector))
	{
		size_t size = _ftv_size(vector);
		ft_vector v = ftv_create(&(ftv_desc){
			.alloc = vector->alloc,
		});
		_vallocate(&v, n);

		ft_iterator begin = _ftv_begin(vector);
		ft_iterator up_to = FT_ITER_ADD_NEW(begin, size);

		_construct_at_end_iter(&v, begin, up_to, size);

		_ftv_swap(vector, &v);
		_ftv_destroy(&v);
	}
}

void	_ftv_assign(ft_vector* vector, ft_iterator first, ft_iterator last)
{
	_ftv_clear(vector);
	for (; !FT_ITER_EQ(first, last); FT_ITER_INC(first))
		_ftv_push_back(vector, FT_ITER_REF(first));
}

void	_ftv_push_back(ft_vector* vector, const void* value)
{
	if (vector->end != vector->end_cap)
		_construct_at_end(vector, 1, value);
	else
	{
		ft_vector v = ftv_create(&(ftv_desc){
			.alloc = vector->alloc,
		});

		_ftv_reserve(&v, _ftv_recommend(vector, _ftv_size(vector) + 1));
		_ftv_assign(&v, _ftv_begin(vector), _ftv_end(vector));
		v.alloc.construct(&v.alloc, v.end, value);
		POINTER_INC(vector, v.end);
		_ftv_swap(vector, &v);

		_ftv_destroy(&v);
	}
}

void	_ftv_pop_back(ft_vector* vector)
{
	assert(!_ftv_empty(vector));
	_destruct_at_end(vector, POINTER_SUB(vector, vector->end, 1));
}

void	_ftv_clear(ft_vector* vector)
{
	_destruct_at_end(vector, vector->begin);
}

ft_iterator	_ftv_erase_at(ft_vector* vector, ft_iterator pos)
{
	return _ftv_erase(vector, pos, FT_ITER_ADD_NEW(pos, 1));
}

ft_iterator	_ftv_erase(ft_vector* vector, ft_iterator first, ft_iterator last)
{
	ft_iterator r = first;
	size_t n = 0;

	for (ft_iterator tmp = first; FT_ITER_NEQ(tmp,last); FT_ITER_INC(tmp))
		n++;
	for (; FT_ITER_NEQ(last, _ftv_end(vector)); FT_ITER_INC(first), FT_ITER_INC(last))
		vector->alloc.construct(&vector->alloc, first._p, last._p);
	while (n--)
		_destruct_at_end(vector, POINTER_SUB(vector, vector->end, 1));
	return r;
}

static void _insert_in_array(ft_vector* vector, void* p, size_t n, ft_iterator position, const void* value)
{
	ft_iterator it;
	size_t step = vector->alloc.sizeof_type;

	/* If destination is the same buffer as the source, do a backward move to avoid
	   overwriting source elements; otherwise copy forward into the separate buffer. */
	if (p == vector->begin)
	{
		void* posp = position._p;
		size_t tail = ((char*)vector->end - (char*)posp) / step;

		/* Move elements from the end backwards to make room for n new elements. */
		for (size_t i = tail; i > 0; --i)
		{
			void* src = (char*)posp + (i - 1) * step;
			void* dest = (char*)posp + (i - 1 + n) * step;
			vector->alloc.construct(&vector->alloc, dest, src);
			vector->alloc.destroy(&vector->alloc, src);
		}

		/* Construct the inserted values at the position. */
		for (size_t i = 0; i < n; ++i)
		{
			void* dest = (char*)posp + i * step;
			vector->alloc.construct(&vector->alloc, dest, value);
		}
	}
	else
	{
		/* Copy into a separate buffer (no overlap). */
		char* dest = p;
		for (it = _ftv_begin(vector); !FT_ITER_EQ(it, position); FT_ITER_INC(it))
		{
			vector->alloc.construct(&vector->alloc, dest, FT_ITER_REF(it));
			dest += step;
		}
		for (size_t i = 0; i < n; ++i)
		{
			vector->alloc.construct(&vector->alloc, dest, value);
			dest += step;
		}
		for (; !FT_ITER_EQ(it, _ftv_end(vector)); FT_ITER_INC(it))
		{
			vector->alloc.construct(&vector->alloc, dest, FT_ITER_REF(it));
			dest += step;
		}
	}
}

ft_iterator _ftv_insert_element(ft_vector* vector, ft_iterator pos, const void* value)
{
	ptrdiff_t d = ((char*)pos._p - (char*)(vector->begin)) / vector->alloc.sizeof_type;
	void* p = POINTER_ADD(vector, vector->begin, d);

	if (vector->end < vector->end_cap)
	{
		if (p == vector->end)
			_ftv_push_back(vector, value);
		else
		{
			_insert_in_array(vector, vector->begin, 1, pos, value);
			POINTER_INC(vector, vector->end);
		}
	}
	else
	{
		ft_vector v = ftv_create(&(ftv_desc){
			.alloc = vector->alloc,
		});

		_ftv_reserve(&v, _ftv_recommend(vector, _ftv_size(vector) + 1));
		_ftv_assign(&v, _ftv_begin(vector), _ftv_end(vector));
		_ftv_insert_element(&v, FT_ITER_ADD_NEW(_ftv_begin(&v), d), value);
		_ftv_swap(vector, &v);

		_ftv_destroy(&v);
	}
	return FT_ITER_ADD_NEW(_ftv_begin(vector), d);
}
