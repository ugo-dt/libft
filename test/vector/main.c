#include "libft.h"
#include <stdio.h>

#define TYPE	int

void	vec_debug(const ft_vector *v);

void	basic_test(ft_vector *v)
{
	TYPE	array[5] = {0, 2, 4, 6, 8};
	TYPE	array2[5] = {10, 12, 14, 16, 18};

	ft_vector_assign_range(v, array, array + 5);
	vec_debug(v);
	
	// ft_vector_insert(v, 1, ft_value_type(TYPE, 1));
	// ft_vector_insert(v, 3, ft_value_type(TYPE, 3));
	// ft_vector_insert(v, 5, ft_value_type(TYPE, 5));
	// ft_vector_insert(v, 7, ft_value_type(TYPE, 7));
	// vec_debug(v);

	// ft_vector_assign(v, 3, ft_value_type(TYPE, 3));
	// vec_debug(v);
	// ft_vector_resize(v, 10, ft_value_type(TYPE, 0));
	// vec_debug(v);
	// ft_vector_resize(v, 1, ft_value_type(TYPE, 0));
	// vec_debug(v);
	// ft_vector_resize(v, 0, ft_value_type(TYPE, 0));
	// vec_debug(v);

	// for (TYPE i = 0; i < 5; i++)
	// 	ft_vector_push_back(v, ft_value_type(TYPE, i));
	// vec_debug(v);

	// ft_vector_insert(v, 3, ft_value_type(TYPE, 3));
	// vec_debug(v);
	// ft_vector_insert_count(v, 3, 3, ft_value_type(TYPE, -3));
	// vec_debug(v);
	// ft_vector_insert_range(v, 0, array2, array2 + 5);
	// vec_debug(v);
}

void	test_struct(void)
{
	struct test
	{
		int a, b;
	};

	ft_vector *v = ft_vector_create(struct test);

	ft_vector_push_back(v, &(struct test){1, 2});
	ft_vector_push_back(v, ft_value_type(struct test, 3, 4));

	for (ft_vector_iterate(it, v, struct test))
		printf("%d %d\n", it->a, it->b);

	ft_vector_destroy(v);
}

static unsigned int allocations;
static unsigned int frees;

void	*allocate(size_t n, size_t type_size)
{
	allocations++;
	return _ft_allocator_allocate(n, type_size);
}

void	deallocate(void *ptr, size_t type_size)
{
	frees++;
	_ft_allocator_deallocate(ptr, type_size);
}

void	test_alloc(void)
{
	ft_allocator alloc = {
		.allocate = allocate,
		.deallocate = deallocate,
		.construct = _ft_allocator_construct,
		.destroy = _ft_allocator_destroy,
	};
	ft_vector	*v = ft_vector_create_alloc(TYPE, alloc);

	allocations = 0;
	frees = 0;
	basic_test(v);
	ft_vector_destroy(v);
	printf("Allocations: %u\nFrees: %u\n----\n", allocations, frees);
}

void	vec_debug(const ft_vector *v)
{
	printf("---- VECTOR ---\n");
	printf("SIZE: %zu\n", ft_vector_size(v));
	printf("CAP : %zu\n", ft_vector_capacity(v));
	printf("BEGIN : %p\n", ft_vector_begin(v));
	printf("END   : %p\n", ft_vector_end(v));

	for (ft_vector_iterate(it, v, TYPE))
		printf("%d\n", *it);
	
	printf("----\n");
}

void	string_alloc_construct(ft_string **s, const ft_string **x, size_t type_size)
{
	printf("push: %p\n", x);
	*s = ft_string_create_from_str(ft_string_data(*x));
}

void	string_alloc_destroy(ft_string **s)
{
	ft_string_destroy(*s);
}

void	test_ft_string(void)
{
	ft_vector	*v;
	ft_string	*s;

	v = ft_vector_create_alloc(ft_string*, ft_allocator(0, 0, string_alloc_construct, string_alloc_destroy));
	s = make_ft_string("hello");
	printf("s : %s|p: %p|addr: %p|data: %p\n", ft_string_data(s), s, &s, ft_string_data(s));

	ft_vector_push_back(v, &s);
	ft_string_assign(s, "world");

	ft_vector_push_back(v, &s);
	ft_string_destroy(s);

	for (ft_vector_iterate(it, v, ft_string*))
		printf("it: %s|p: %p|data: %p\n", ft_string_data(*it), *it, ft_string_data(*it));

	ft_vector_destroy(v);
}

int	main(void)
{
	ft_vector	*v;

	v = ft_vector_create(TYPE);
	basic_test(v);
	ft_vector_destroy(v);

	test_struct();
	test_alloc();
	test_ft_string();
	return (0);
}
