#define LIBFT_TESTER_MACROS
#include <libft/tester.h>
#include <libft/iterator.h>

void	test_vector_create(void* param)
{
	ft_vector v = ft_vector_create(&(ft_vector_desc){
		.alloc = (ft_allocator){
			.sizeof_type = sizeof(int),
		},
	});

	Tester_Expect(v.alloc.sizeof_type)->ToBe(sizeof(int));
	Tester_Expect(ft_vector_size(&v))->ToBe(0);
	Tester_Expect(ft_vector_capacity(&v))->ToBe(0);
	Tester_Expect(ft_vector_empty(&v))->ToBe(true);
	ft_vector_destroy(&v);
	Tester_Expect(v.begin)->ToBe(NULL);
	Tester_Expect(v.end)->ToBe(NULL);
	Tester_Expect(v.end_cap)->ToBe(NULL);
}

void	test_vector_reserve(void* param)
{
	ft_vector v = ft_vector_create(&(ft_vector_desc){
		.alloc = (ft_allocator){
			.sizeof_type = sizeof(int),
		},
	});

	Tester_Expect(ft_vector_size(&v))->ToBe(0);
	Tester_Expect(ft_vector_capacity(&v))->ToBe(0);
	Tester_Expect(ft_vector_empty(&v))->ToBe(true);
	ft_vector_reserve(&v, 200);
	Tester_Expect(ft_vector_size(&v))->ToBe(0);
	Tester_Expect(ft_vector_capacity(&v))->ToBe(200);
	Tester_Expect(ft_vector_empty(&v))->ToBe(true);
	ft_vector_destroy(&v);
}

void	test_vector_push_back(void* param)
{
	ft_vector v = ft_vector_create(&(ft_vector_desc){
		.alloc = (ft_allocator){
			.sizeof_type = sizeof(int),
		},
	});

	Tester_Expect(ft_vector_size(&v))->ToBe(0);
	Tester_Expect(ft_vector_capacity(&v))->ToBe(0);
	Tester_Expect(ft_vector_empty(&v))->ToBe(true);

	ft_vector_push_back(&v, &(int){42});
	Tester_Expect(ft_vector_size(&v))->ToBe(1);
	Tester_Expect(ft_vector_capacity(&v))->ToBe(1);
	Tester_Expect((*(int*)ft_vector_at(&v, 0)))->ToBe(42);

	ft_vector_push_back(&v, &(int){21});
	Tester_Expect(ft_vector_size(&v))->ToBe(2);
	Tester_Expect(ft_vector_capacity(&v))->ToBe(2);
	Tester_Expect((*(int*)ft_vector_at(&v, 0)))->ToBe(42);
	Tester_Expect((*(int*)ft_vector_at(&v, 1)))->ToBe(21);

	ft_vector_clear(&v);
	Tester_Expect(ft_vector_size(&v))->ToBe(0);
	Tester_Expect(ft_vector_capacity(&v))->ToBe(2);
	Tester_Expect(ft_vector_empty(&v))->ToBe(true);

	for (int i = 0; i < 100; i++)
		ft_vector_push_back(&v, &i);
	Tester_Expect(ft_vector_size(&v))->ToBe(100);
	Tester_Expect(ft_vector_capacity(&v))->ToBe(128);
	for (int i = 0; i < 100; i++)
		Tester_Expect((*(int*)ft_vector_at(&v, i)))->ToBe(i);
	Tester_Expect(ft_vector_size(&v))->ToBe(100);
	
	ft_vector_reserve(&v, 200);
	Tester_Expect(ft_vector_size(&v))->ToBe(100);
	Tester_Expect(ft_vector_capacity(&v))->ToBe(200);
	for (int i = 0; i < 100; i++)
		ft_vector_push_back(&v, &i);
	Tester_Expect(ft_vector_size(&v))->ToBe(200);
	ft_vector_pop_back(&v);
	Tester_Expect(ft_vector_size(&v))->ToBe(199);
	for (int i = 0; i < 199; i++)
		Tester_Expect((*(int*)ft_vector_at(&v, i)))->ToBe(i < 100 ? i : i - 100);

	ft_vector_clear(&v);
	Tester_Expect(ft_vector_size(&v))->ToBe(0);
	Tester_Expect(ft_vector_empty(&v))->ToBe(true);
	ft_vector_destroy(&v);
}

static void	test_iterator(void* param)
{
	ft_vector v = ft_vector_create(&(ft_vector_desc){
		.alloc = (ft_allocator){
			.sizeof_type = sizeof(int),
		},
	});

	ft_vector_reserve(&v, 10);
	for (int i = 0; i < 10; i++)
		ft_vector_push_back(&v, &i);
	Tester_Expect(ft_vector_size(&v))->ToBe(10);

	ft_iterator it = ft_vector_begin(&v);
	for (int i = 0; i < 10; i++, FT_ITER_INC(it))
		Tester_Expect(FT_ITER_VALUE(it, int))->ToBe(i);
	Tester_Expect(FT_ITER_EQ(it, ft_vector_end(&v)))->ToBe(true);

	it = ft_vector_rbegin(&v);
	for (int i = 9; i >= 0; i--, FT_ITER_INC(it))
		Tester_Expect(FT_ITER_VALUE(it, int))->ToBe(i);
	Tester_Expect(FT_ITER_EQ(it, ft_vector_rend(&v)))->ToBe(true);

	int i = 9;
	for (ft_iterator it = ft_vector_rbegin(&v); FT_ITER_NEQ(it, ft_vector_rend(&v)); FT_ITER_INC(it), i--)
		Tester_Expect(FT_ITER_VALUE(it, int))->ToBe(i);
	Tester_Expect(FT_ITER_EQ(it, ft_vector_rend(&v)))->ToBe(true);

	ft_vector_destroy(&v);
}

static void test_vector_insert(void* param)
{
	ft_vector v = ft_vector_create(&(ft_vector_desc){
		.alloc = (ft_allocator){
			.sizeof_type = sizeof(int),
		},
	});

	ft_vector_reserve(&v, 12);
	for (int i = 0; i < 10; i++)
		ft_vector_push_back(&v, &i);
	Tester_Expect(ft_vector_size(&v))->ToBe(10);

	ft_iterator it = ft_vector_begin(&v);
	for (int i = 0; i < 10; i++, FT_ITER_INC(it))
		Tester_Expect(FT_ITER_VALUE(it, int))->ToBe(i);
	Tester_Expect(FT_ITER_EQ(it, ft_vector_end(&v)))->ToBe(true);

	ft_vector_insert_element(&v, FT_ITER_ADD_NEW(ft_vector_begin(&v), 5), &(int){100});
	Tester_Expect(ft_vector_size(&v))->ToBe(11);
	Tester_Expect((*(int*)ft_vector_at(&v, 5)))->ToBe(100);
	ft_vector_insert_element(&v, FT_ITER_ADD_NEW(ft_vector_begin(&v), 5), &(int){200});
	Tester_Expect(ft_vector_size(&v))->ToBe(12);
	Tester_Expect((*(int*)ft_vector_at(&v, 5)))->ToBe(200);
	ft_vector_insert_element(&v, ft_vector_end(&v), &(int){300});
	Tester_Expect(ft_vector_size(&v))->ToBe(13);
	Tester_Expect((*(int*)ft_vector_at(&v, 12)))->ToBe(300);

	ft_vector_destroy(&v);
}

struct test { int a, b; };

static void	test_allocator_construct(const ft_allocator* alloc, void *p, const void* value)
{
	struct test* obj = p;
	const struct test* val = value;

	obj->a = val->a + 42;
	obj->b = val->b + 42;
}

static void	test_allocator(void* param)
{
	ft_vector	v = ft_vector_create(&(ft_vector_desc){
		.alloc = {
			.sizeof_type = sizeof(struct test),
			.construct = test_allocator_construct,
		},
	});

	Tester_Expect(v.alloc.sizeof_type)->ToBe(sizeof(struct test));
	ft_vector_reserve(&v, 2);
	Tester_Expect(ft_vector_capacity(&v))->ToBe(2);
	ft_vector_push_back(&v, &(struct test){42, 21});
	ft_vector_push_back(&v, &(struct test){20, 43});
	Tester_Expect(ft_vector_size(&v))->ToBe(2);

	// The constructed values should have +42 in each member
	Tester_Expect((*(struct test*)ft_vector_at(&v, 0)).a)->ToBe(42 + 42);
	Tester_Expect((*(struct test*)ft_vector_at(&v, 0)).b)->ToBe(21 + 42);
	Tester_Expect((*(struct test*)ft_vector_at(&v, 1)).a)->ToBe(20 + 42);
	Tester_Expect((*(struct test*)ft_vector_at(&v, 1)).b)->ToBe(43 + 42);
	for (ft_iterator it = ft_vector_begin(&v); !FT_ITER_EQ(it, ft_vector_end(&v)); FT_ITER_INC(it))
	{
		struct test val = FT_ITER_VALUE(it, struct test);
		// 63 is the sum of original a and b, for both structs
		Tester_Expect(val.a + val.b)->ToBe(63 + 42 + 42);
	}
	ft_vector_destroy(&v);
}

static void test_vector_resize(void* param)
{
	Tester_SetStatus(TesterStatus_ToDo);
}

int	main(void)
{
	Tester_Describe("Vector Test", &(TestDesc){
		.count = 1,
		.contexts = (TesterContext[]){
			{
				.count = 7,
				.it = (TestIt[]){
					{
						.name = "Create",
						.callback = test_vector_create,
						.param = NULL,
					},
					{
						.name = "Reserve",
						.callback = test_vector_reserve,
						.param = NULL,
					},
					{
						.name = "Push Back",
						.callback = test_vector_push_back,
						.param = NULL,
					},
					{
						.name = "Iterator",
						.callback = test_iterator,
						.param = NULL,
					},
					{
						.name = "Insert",
						.callback = test_vector_insert,
						.param = NULL,
					},
					{
						.name = "Allocator",
						.callback = test_allocator,
						.param = NULL,
					},
					{
						.name = "Resize",
						.callback = test_vector_resize,
						.param = NULL,
					}
				},
			},
		}
	}
);
	return (0);
}
