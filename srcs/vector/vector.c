#include "libft/libft.h"
#include "libft/iterator.h"

#define ft_def(__a, __b) (((__a) == 0) ? (__b) : (__a))

#define POINTER_ADD(__v, __p, __n) _POINTER_ADD((__p), ((__v)->alloc.sizeof_type), (__n))
#define POINTER_SUB(__v, __p, __n) _POINTER_SUB((__p), ((__v)->alloc.sizeof_type), (__n))
#define POINTER_INC(__v, __p) ((__p) = (POINTER_ADD(__v, __p, 1)))
#define POINTER_DEC(__v, __p) ((__p) = (POINTER_SUB(__v, __p, 1)))

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
	assert(ft_vector_size(vector) + n <= ft_vector_capacity(vector));
	while (n-- > 0)
	{
		vector->alloc.construct(&vector->alloc, vector->end, value);
		POINTER_INC(vector, vector->end);
	}
}

void	_construct_at_end_iter(ft_vector* vector, ft_iterator first, ft_iterator last, size_t n)
{
	assert(ft_vector_size(vector) + n <= ft_vector_capacity(vector));

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

void	_ft_vector_swap(ft_vector *_v, ft_vector *_x)
{
	ft_allocator tmp = _v->alloc;
	_v->alloc = _x->alloc;
	_x->alloc = tmp;

	_swap(&_v->begin, &_x->begin);
	_swap(&_v->end, &_x->end);
	_swap(&_v->end_cap, &_x->end_cap);
}

size_t	_ft_vector_recommend(const ft_vector *vector, size_t new_size)
{
	size_t max_size = vector->alloc.max_size(&vector->alloc);
	
	assert(new_size < vector->alloc.max_size(&vector->alloc));
    const size_t cap = ft_vector_capacity(vector);
    if (cap >= max_size / 2)
        return max_size;
    return max(2 * cap, new_size);
}

ft_vector	ft_vector_create(const ft_vector_desc* desc)
{
	return (ft_vector){
		.alloc = _ft_allocator_defaults(&desc->alloc),
		.begin = NULL,
		.end = NULL,
		.end_cap = NULL,
	};
}

void	ft_vector_destroy(ft_vector* vector)
{
	if (vector->begin)
	{
		ft_vector_clear(vector);
		vector->alloc.deallocate(&vector->alloc, vector->begin, ft_vector_capacity(vector));
		vector->begin = vector->end = vector->end_cap = NULL;
	}
}

void*	ft_vector_data(const ft_vector* vector)
{
	return vector->begin;
}

void*	ft_vector_at(const ft_vector* vector, size_t n)
{
	assert(n < ft_vector_size(vector));
	return POINTER_ADD(vector, vector->begin, n);
}

ft_iterator	ft_vector_begin(const ft_vector* vector)
{
	return _make_iter(vector->alloc.sizeof_type, vector->begin, IteratorType_Random);
}

ft_iterator	ft_vector_end(const ft_vector* vector)
{
	return _make_iter(vector->alloc.sizeof_type, vector->end, IteratorType_Random);
}

ft_iterator	ft_vector_rbegin(const ft_vector* vector)
{
	return _make_iter(vector->alloc.sizeof_type, vector->end, IteratorType_Reverse);
}

ft_iterator	ft_vector_rend(const ft_vector* vector)
{
	return _make_iter(vector->alloc.sizeof_type, vector->begin, IteratorType_Reverse);
}

size_t	ft_vector_max_size(const ft_vector* vector)
{
	return vector->alloc.max_size(&vector->alloc);
}

size_t	ft_vector_size(const ft_vector* vector)
{
	return ((char*)vector->end - (char*)vector->begin) / vector->alloc.sizeof_type;
}

size_t	ft_vector_capacity(const ft_vector* vector)
{
	return ((char*)vector->end_cap - (char*)vector->begin) / vector->alloc.sizeof_type;
}

size_t	ft_vector_empty(const ft_vector* vector)
{
	return vector->begin == vector->end;
}

void	ft_vector_reserve(ft_vector* vector, size_t n)
{
	if (n > ft_vector_capacity(vector))
	{
		size_t size = ft_vector_size(vector);
		ft_vector v = ft_vector_create(&(ft_vector_desc){
			.alloc = vector->alloc,
		});
		_vallocate(&v, n);

		ft_iterator begin = ft_vector_begin(vector);
		ft_iterator up_to = FT_ITER_ADD_NEW(begin, size);

		_construct_at_end_iter(&v, begin, up_to, size);

		_ft_vector_swap(vector, &v);
		ft_vector_destroy(&v);
	}
}

void	ft_vector_assign(ft_vector* vector, ft_iterator first, ft_iterator last)
{
	ft_vector_clear(vector);
	for (; !FT_ITER_EQ(first, last); FT_ITER_INC(first))
		ft_vector_push_back(vector, FT_ITER_REF(first));
}

void	ft_vector_push_back(ft_vector* vector, const void* value)
{
	if (vector->end != vector->end_cap)
		_construct_at_end(vector, 1, value);
	else
	{
		ft_vector v = ft_vector_create(&(ft_vector_desc){
			.alloc = vector->alloc,
		});

		ft_vector_reserve(&v, _ft_vector_recommend(vector, ft_vector_size(vector) + 1));
		ft_vector_assign(&v, ft_vector_begin(vector), ft_vector_end(vector));
		v.alloc.construct(&v.alloc, v.end, value);
		POINTER_INC(vector, v.end);
		_ft_vector_swap(vector, &v);

		ft_vector_destroy(&v);
	}
}

void	ft_vector_pop_back(ft_vector* vector)
{
	assert(!ft_vector_empty(vector));
	_destruct_at_end(vector, POINTER_SUB(vector, vector->end, 1));
}

void	ft_vector_clear(ft_vector* vector)
{
	_destruct_at_end(vector, vector->begin);
}
