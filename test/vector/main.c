#include "libft.h"
#include <stdio.h>

#define TYPE	int

void	vec_debug(const ft_vector *v);
void	basic_test(ft_vector *v);

void	test_struct(void)
{
	struct test
	{
		int a, b;
		ft_vector	v;
	};

	ft_vector(v, struct test);

	ft_vector_push_back(&v, &(struct test){1, 2});
	ft_vector_push_back(&v, value_type(struct test, 3, 4));

	for (iterator(it, struct test) = v._begin; it != v._end; iterator_inc(it, &v))
		printf("%d %d\n", it->a, it->b);

	ft_vector_destroy(&v);
}

static unsigned int allocations;

pointer	allocate(size_t n, size_t type_size)
{
	allocations++;
	return _ft_allocator_allocate(n, type_size);
}

void	test_alloc(void)
{
	ft_allocator alloc = {
		.allocate = allocate,
		.deallocate = _ft_allocator_deallocate,
		.construct = _ft_allocator_construct,
		.destroy = _ft_allocator_destroy,
	};
	ft_vector_alloc(v, TYPE, alloc);

	allocations = 0;
	basic_test(&v);
	ft_printf("Allocations: %u\n----\n", allocations);
}

void	vec_debug(const ft_vector *v)
{
	printf("---- VECTOR ---\n");
	printf("SIZE: %zu\n", ft_vector_size(v));
	printf("CAP : %zu\n", ft_vector_capacity(v));
	printf("BEGIN : %p\n", v->_begin);
	printf("END   : %p\n", v->_end);
	printf("ENDCAP: %p\n", v->_end_cap);

	// for (int *i = v->_begin; i != v->_end; _ft_pointer_inc(i, sizeof(int)))
	// 	printf("%c\n", *i);
	for (iterator(it, TYPE) = v->_begin; it != v->_end; iterator_inc(it, v))
		printf("%d\n", *it);
	
	printf("----\n");
}

void	basic_test(ft_vector *v)
{
	TYPE	array[5] = {0, 2, 4, 6, 8};
	TYPE	array2[5] = {10, 12, 14, 16, 18};

	ft_vector_assign_range(v, array, array + 5);
	vec_debug(v);
	
	ft_vector_insert(v, 1, value_type(TYPE, 1));
	ft_vector_insert(v, 3, value_type(TYPE, 3));
	ft_vector_insert(v, 5, value_type(TYPE, 5));
	ft_vector_insert(v, 7, value_type(TYPE, 7));
	vec_debug(v);

	ft_vector_assign(v, 3, value_type(TYPE, 3));
	vec_debug(v);
	ft_vector_resize(v, 10, value_type(TYPE, 0));
	vec_debug(v);
	ft_vector_resize(v, 1, value_type(TYPE, 0));
	vec_debug(v);
	ft_vector_resize(v, 0, value_type(TYPE, 0));
	vec_debug(v);

	for (TYPE i = 0; i < 5; i++)
		ft_vector_push_back(v, value_type(TYPE, i));
	vec_debug(v);

	ft_vector_insert(v, 3, value_type(TYPE, 3));
	vec_debug(v);
	ft_vector_insert_count(v, 3, 3, value_type(TYPE, -3));
	vec_debug(v);
	ft_vector_insert_range(v, 0, array2, array2 + 5);
	vec_debug(v);

	ft_vector_destroy(v);
}

int	main(void)
{
	ft_vector(v, TYPE);

	basic_test(&v);

	test_alloc();
	test_struct();
	return (0);
}
