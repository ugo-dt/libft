#include "libft.h"
#include <stdio.h>

#define ft_vector_type	int
#include "srcs/vector/vector.h"
#define ft_vector_type	char
#include "srcs/vector/vector.h"

#define VEC_DEBUG(Type, _v)								\
{														\
	printf("---- VECTOR ---\n");						\
	printf("SIZE: %zu\n", _v->size(_v));				\
	printf("CAP : %zu\n", _v->capacity(_v));			\
	printf("BEGIN : %p\n", _v->begin(_v));				\
	printf("END   : %p\n", _v->end(_v));				\
	printf("ENDCAP: %p\n", _v->_end_cap);				\
														\
	for (Type *it = _v->_begin; it != _v->_end; it++)	\
		printf("it    : %p -- %d\n", it, *it);			\
	printf("----\n");									\
}

#define DEFINE_BASIC_TEST(Type)							\
void	basic_test_ ## Type(ft_vector *v)				\
{														\
	printf("=== VECTOR TEST - %s ===\n", #Type);		\
	Type	array[5] = {0, 2, 4, 6, 8};					\
	Type	array2[5] = {10, 12, 14, 16, 18};			\
														\
	v->assign_range(v, array, array + 5);				\
	VEC_DEBUG(Type, v);									\
														\
	v->insert(v, 1, &(Type){1});						\
	v->insert(v, 3, &(Type){3});						\
	v->insert(v, 5, &(Type){5});						\
	v->insert(v, 7, &(Type){7});						\
	VEC_DEBUG(Type, v);									\
	v->assign(v, 3, &(Type){3});						\
	VEC_DEBUG(Type, v);									\
	v->resize(v, 10, &(Type){0});						\
	VEC_DEBUG(Type, v);									\
	v->resize(v, 1, &(Type){0});						\
	VEC_DEBUG(Type, v);									\
	v->resize(v, 0, &(Type){0});						\
	VEC_DEBUG(Type, v);									\
														\
	for (Type i = 0; i < 5; i++)						\
		v->push_back(v, &i);							\
	VEC_DEBUG(Type, v);									\
														\
	v->insert(v, 3, &(Type){3});						\
	VEC_DEBUG(Type, v);									\
	v->insert_count(v, 3, 3, &(Type){3});				\
	VEC_DEBUG(Type, v);									\
	v->insert_range(v, 0, array2, array2 + 5);			\
	VEC_DEBUG(Type, v);									\
}

typedef struct test
{
	int a, b;
}TestStruct;

#define ft_vector_type	TestStruct
#include "srcs/vector/vector.h"

DEFINE_BASIC_TEST(int)
DEFINE_BASIC_TEST(char)

void	test_struct(void)
{
	ft_vector_TestStruct *v = ft_vector_TestStruct_create();

	v->push_back(v, &(TestStruct){1, 2});
	v->push_back(v, &(TestStruct){3, 4});

	for (TestStruct *it = v->_begin; it != v->_end; it++)
		printf("it    : %p -- %d %d\n", it, it->a, it->b);
	v->destroy(v);
}

// static unsigned int allocations;
// static unsigned int frees;

// void	*allocate(size_t n, size_t int_size)
// {
// 	allocations++;
// 	return _ft_allocator_allocate(n, int_size);
// }

// void	deallocate(void *ptr, size_t int_size)
// {
// 	frees++;
// 	_ft_allocator_deallocate(ptr, int_size);
// }

// void	test_alloc(void)
// {
// 	ft_allocator alloc = {
// 		.allocate = allocate,
// 		.deallocate = deallocate,
// 		.construct = _ft_allocator_construct,
// 		.destroy = _ft_allocator_destroy,
// 	};
// 	ft_vector	*v = ft_vector_create_alloc(int, alloc);

// 	allocations = 0;
// 	frees = 0;
// 	basic_test(v);
// 	ft_vector_destroy(v);
// 	printf("Allocations: %u\nFrees: %u\n----\n", allocations, frees);
// }



// void	string_alloc_construct(ft_string **s, const ft_string **x, size_t int_size)
// {
// 	printf("push: %p\n", x);
// 	*s = ft_string_create_from_str(ft_string_data(*x));
// }

// void	string_alloc_destroy(ft_string **s)
// {
// 	ft_string_destroy(*s);
// }

// void	test_ft_string(void)
// {
// 	ft_vector	*v;
// 	ft_string	*s;

// 	v = ft_vector_create_alloc(ft_string*, ft_allocator(0, 0, string_alloc_construct, string_alloc_destroy));
// 	s = make_ft_string("hello");
// 	printf("s : %s|p: %p|addr: %p|data: %p\n", ft_string_data(s), s, &s, ft_string_data(s));

// 	ft_vector_push_back(v, &s);
// 	ft_string_assign(s, "world");

// 	ft_vector_push_back(v, &s);
// 	ft_string_destroy(s);

// 	for (ft_vector_iterate(it, v, ft_string*))
// 		printf("it: %s|p: %p|data: %p\n", ft_string_data(*it), *it, ft_string_data(*it));

// 	ft_vector_destroy(v);
// }

int	main(void)
{
	{
		ft_vector_int	*v = ft_vector_int_create();

		basic_test_int((ft_vector *)v);
		v->destroy(v);
	}
	{
		ft_vector_char	*v = ft_vector_char_create();

		basic_test_char((ft_vector *)v);
		ft_vector_char_destroy(v);
	}

	test_struct();
	// test_alloc();
	// test_ft_string();
	return (0);
}
