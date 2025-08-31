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

int	main(void)
{
	Tester_Describe("Vector Test", &(TestDesc){
		.count = 1,
		.contexts = (TesterContext[]){
			{
				.count = 4,
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
					}
				},
			},
		}
	}
);
	return (0);
}
