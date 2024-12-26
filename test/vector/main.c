#include <libft/libft.h>

#define LIBFT_VECTOR_TYPE	int
#include <libft/ft_vector.h>
#define LIBFT_VECTOR_TYPE	char
#include <libft/ft_vector.h>
#define LIBFT_VECTOR_TYPE	ft_string
#include <libft/ft_vector.h>

#define VEC_DEBUG(Type, _v)								\
{														\
	ft_printf("---- VECTOR ---\n");						\
	ft_printf("SIZE: %zu\n", _v->size(_v));				\
	ft_printf("CAP : %zu\n", _v->capacity(_v));			\
	ft_printf("BEGIN : %p\n", _v->begin(_v));			\
	ft_printf("END   : %p\n", _v->end(_v));				\
	ft_printf("ENDCAP: %p\n", _v->_end_cap);			\
														\
	for (Type *it = _v->_begin; it != _v->_end; it++)	\
		ft_printf("it    : %p -- %d\n", it, *it);		\
	ft_printf("----\n");								\
}

#define DEFINE_BASIC_TEST(Type)							\
void	basic_test_ ## Type(ft_vector *v)				\
{														\
	ft_printf("=== VECTOR TEST - %s ===\n", #Type);		\
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

#define LIBFT_VECTOR_TYPE	TestStruct
#include <libft/ft_vector.h>

DEFINE_BASIC_TEST(int)
DEFINE_BASIC_TEST(char)

void	test_struct(void)
{
	ft_vector *v = ft_vector_TestStruct_create(0);

	v->push_back(v, &(TestStruct){1, 2});
	v->push_back(v, &(TestStruct){3, 4});

	for (TestStruct *it = v->_begin; it != v->_end; it++)
		ft_printf("it    : %p -- %d %d\n", it, it->a, it->b);
	v->destroy(v);
}

static unsigned int allocations;
static unsigned int frees;

void	*allocate(size_t n)
{
	allocations++;
	return ft_allocator_int_allocate(n);
}

void	deallocate(void *ptr, size_t n)
{
	frees++;
	ft_allocator_int_deallocate(ptr, n);
}

void	test_alloc(void)
{
	ft_vector	*v = ft_vector_int_create(&(ft_allocator_int){
		.allocate = allocate,
		.deallocate = deallocate,
		.construct = ft_allocator_int_construct,
		.destroy = ft_allocator_int_destroy,
	});

	allocations = 0;
	frees = 0;
	basic_test_int(v);
	v->destroy(v);
	ft_printf("Allocations: %u\nFrees: %u\n----\n", allocations, frees);
}

void	string_alloc_construct(ft_string *s, const ft_string *x)
{
	*s = ft_string_create_from_str(ft_string_data(*x));
}

void	string_alloc_destroy(ft_string *s)
{
	ft_printf("destroy %s\n", ft_string_data(*s));
	ft_string_destroy(*s);
}

void	test_ft_string(void)
{
	ft_vector	*v = ft_vector_ft_string_create(&(ft_allocator_ft_string){
		.allocate = ft_allocator_ft_string_allocate,
		.deallocate = ft_allocator_ft_string_deallocate,
		.construct = string_alloc_construct,
		.destroy = string_alloc_destroy,
	});
	ft_string	s = ft_string("hello");

	v->push_back(v, &s);
	ft_string_assign(s, "world");
	v->push_back(v, &s);
	ft_string_destroy(s);

	for (ft_string* it = v->_begin; it != v->_end; it++)
		ft_printf("it: %s\n", ft_string_data(*it));

	v->destroy(v);
}

int	main(void)
{
	{
		ft_vector	*v = ft_vector_int_create(0);

		basic_test_int((ft_vector *)v);
		v->destroy(v);
	}
	{
		ft_vector	*v = ft_vector_char_create(0);

		basic_test_char(v);
		v->destroy(v);
	}
	{
		test_struct();
		test_alloc();
		test_ft_string();
	}
	return (0);
}
