#define LIBFT_TESTER_MACROS
#include <libft/libft.h>
#include <libft/tester.h>
#include <libft/iterator.h>

// >>ft_string

static void test_basic_string_create(void* param)
{
	ft_string s = ftstr_create();

	ftt_expect(s._capacity)->to_be(LIBFT_STRING_DEFAULT_CAPACITY);
	ftstr_destroy(&s);

	s = ft_string("Hello, world!");
	ftt_expect(ftstr_size(&s))->to_be(13);
	ftt_expect(ftstr_capacity(&s))->to_be(14);
	ftt_expect(ftstr_equals(&s, "Hello, world!"))->to_be_true();

	ft_string s2 = ft_string(&s);
	ftt_expect(ftstr_size(&s2))->to_be(13);
	ftt_expect(ftstr_capacity(&s2))->to_be(14);
	ftt_expect(ftstr_equals(&s, &s2))->to_be_true();
	ftt_expect(ftstr_equals(&s2, "Hello, world!"))->to_be_true();
	ftstr_destroy(&s2);
	ftstr_destroy(&s);

	s = ft_string('A', 5);
	ftt_expect(ftstr_size(&s))->to_be(5);
	ftt_expect(ftstr_capacity(&s))->to_be(6);
	ftt_expect(ftstr_equals(&s, "AAAAA"))->to_be_true();
	ftstr_destroy(&s);
}

static void test_basic_string_append(void* param)
{
	ft_string s = ft_string("Hello");
	ftstr_append(&s, ", ");
	ftstr_append(&s, 'W', 1);
	ftstr_append(&s, "orld");
	ftstr_append(&s, '!', 1);

	ftt_expect(ftstr_size(&s))->to_be(13);
	ftt_expect(ftstr_equals(&s, "Hello, World!"))->to_be_true();
	ftstr_destroy(&s);

	ft_string s2 = ft_string('X', 3);
	ftt_expect(ftstr_size(&s2))->to_be(3);
	ftt_expect(ftstr_equals(&s2, "XXX"))->to_be_true();
	ftt_expect(ftstr_capacity(&s2))->to_be(4);
	ftstr_append(&s2, &s2);
	ftstr_append(&s2, 'Y', 2);
	ftstr_append(&s2, "Z");
	ftt_expect(ftstr_size(&s2))->to_be(ft_strlen("XXXXXXYYZ")); // 9
	ftt_expect(ftstr_equals(&s2, "XXXXXXYYZ"))->to_be_true();
	ftt_expect(ftstr_capacity(&s2))->to_be_greater_than(10);
	ftt_expect(ftstr_data(&s2))->to_be("XXXXXXYYZ");
	ftstr_destroy(&s2);
}

static void test_basic_string_assign(void* param)
{
	ft_string s = ft_string("Initial");
	ftt_expect(ftstr_size(&s))->to_be(7);
	ftt_expect(ftstr_equals(&s, "Initial"))->to_be_true();

	ftstr_assign(&s, "New value");
	ftt_expect(ftstr_size(&s))->to_be(9);
	ftt_expect(ftstr_equals(&s, "New value"))->to_be_true();

	ftstr_assign(&s, 'A', 4);
	ftt_expect(ftstr_size(&s))->to_be(4);
	ftt_expect(ftstr_equals(&s, "AAAA"))->to_be_true();

	ftstr_assign(&s, "Short", 3);
	ftt_expect(ftstr_data(&s))->to_be("Sho");
	ftt_expect(ftstr_size(&s))->to_be(3);
	ftt_expect(ftstr_equals(&s, "Sho"))->to_be_true();
	ftstr_destroy(&s);
}

static const ftt_context basic_string_ctx = {
	.name = "basic_string",
	.count = 3,
	.it = (ftt_it_t[]){
		{
			.name = "create",
			.callback = test_basic_string_create,
			.param = NULL,
		},
		{
			.name = "append",
			.callback = test_basic_string_append,
			.param = NULL,
		},
		{
			.name = "assign",
			.callback = test_basic_string_assign,
			.param = NULL,
		}
	}
};

// >>fileparse

typedef enum
{
	TEST_FILEPARSE_TOKEN_EQUAL = 1,
	TEST_FILEPARSE_TOKEN_COLON,
	TEST_FILEPARSE_TOKEN_NEWLINE,
}test_fileparse_token_type;

static void test_fileparse(void* param)
{
	ftfp_state state = ftfp_parse("Makefile", &(ftfp_desc){
		.isspace = NULL,
		.isseparator = NULL,
		.skip_newlines = false,
		.token_count = 2,
		.tokens = (ftfp_token_desc[]){
			{ .type = TEST_FILEPARSE_TOKEN_EQUAL, .value = "=" },
			{ .type = TEST_FILEPARSE_TOKEN_COLON, .value = ":" },
		},
	});

	ftv_each(state.tokens, it)
	{
		ftfp_token* token = &FT_ITER_VALUE(it, ftfp_token);
		// ftt_log("Token %llu: type=%llu, value='%s', row=%d, col=%d\n",
		// 	i, token->type, token->value, token->row, token->col);
		if (ft_strcmp(token->value, "=") == 0)
			ftt_expect(token->type)->to_be(TEST_FILEPARSE_TOKEN_EQUAL);
		else if (ft_strcmp(token->value, ":") == 0)
			ftt_expect(token->type)->to_be(TEST_FILEPARSE_TOKEN_COLON);
	}

	ftfp_clear(&state);
}

static const ftt_context fileparse_ctx = {
	.name = "fileparse",
	.count = 1,
	.it = (ftt_it_t[]){
		{
			.name = "parse",
			.callback = test_fileparse,
			.param = NULL,
		}
	}
};

// >>vector

static void test_vector_create(void* param)
{
	ft_vector v = ftv_create(&(ftv_desc){
		.alloc = (ft_allocator){
			.sizeof_type = sizeof(int),
		},
	});

	ftt_expect(v.alloc.sizeof_type)->to_be(sizeof(int));
	ftt_expect(ftv_size(&v))->to_be(0);
	ftt_expect(ftv_capacity(&v))->to_be(0);
	ftt_expect(ftv_empty(&v))->to_be_true();
	ftv_destroy(&v);
	ftt_expect(v.begin)->to_be(NULL);
	ftt_expect(v.end)->to_be(NULL);
	ftt_expect(v.end_cap)->to_be(NULL);
}

static void test_vector_reserve(void* param)
{
	ft_vector v = ftv_create(&(ftv_desc){
		.alloc = (ft_allocator){
			.sizeof_type = sizeof(int),
		},
	});

	ftt_expect(ftv_size(&v))->to_be(0);
	ftt_expect(ftv_capacity(&v))->to_be(0);
	ftt_expect(ftv_empty(&v))->to_be_true();
	ftv_reserve(&v, 200);
	ftt_expect(ftv_size(&v))->to_be(0);
	ftt_expect(ftv_capacity(&v))->to_be(200);
	ftt_expect(ftv_empty(&v))->to_be_true();
	ftv_destroy(&v);
}

static void test_vector_push_back(void* param)
{
	ft_vector v = ftv_create(&(ftv_desc){
		.alloc = (ft_allocator){
			.sizeof_type = sizeof(int),
		},
	});

	ftt_expect(ftv_size(&v))->to_be(0);
	ftt_expect(ftv_capacity(&v))->to_be(0);
	ftt_expect(ftv_empty(&v))->to_be_true();

	ftv_push_backv(&v, 42);
	ftt_expect(ftv_size(&v))->to_be(1);
	ftt_expect(ftv_capacity(&v))->to_be(1);
	ftt_expect(ftv_at(&v, 0, int))->to_be(42);

	ftv_push_backv(&v, 21);
	ftt_expect(ftv_size(&v))->to_be(2);
	ftt_expect(ftv_capacity(&v))->to_be(2);
	ftt_expect(ftv_at(&v, 0, int))->to_be(42);
	ftt_expect(ftv_at(&v, 1, int))->to_be(21);

	ftv_clear(&v);
	ftt_expect(ftv_size(&v))->to_be(0);
	ftt_expect(ftv_capacity(&v))->to_be(2);
	ftt_expect(ftv_empty(&v))->to_be_true();

	for (int i = 0; i < 100; i++)
		ftv_push_back(&v, i);
	ftt_expect(ftv_size(&v))->to_be(100);
	ftt_expect(ftv_capacity(&v))->to_be(128);
	for (int i = 0; i < 100; i++)
		ftt_expect(ftv_at(&v, i, int))->to_be(i);
	ftt_expect(ftv_size(&v))->to_be(100);
	
	ftv_reserve(&v, 200);
	ftt_expect(ftv_size(&v))->to_be(100);
	ftt_expect(ftv_capacity(&v))->to_be(200);
	for (int i = 0; i < 100; i++)
		ftv_push_back(&v, i);
	ftt_expect(ftv_size(&v))->to_be(200);
	ftv_pop_back(&v);
	ftt_expect(ftv_size(&v))->to_be(199);
	for (int i = 0; i < 199; i++)
		ftt_expect(ftv_at(&v, i, int))->to_be(i < 100 ? i : i - 100);

	ftv_clear(&v);
	ftt_expect(ftv_size(&v))->to_be(0);
	ftt_expect(ftv_empty(&v))->to_be_true();
	ftv_destroy(&v);
}

static void	test_iterator(void* param)
{
	ft_vector v = ftv_create(&(ftv_desc){
		.alloc = (ft_allocator){
			.sizeof_type = sizeof(int),
		},
	});

	ftv_reserve(&v, 10);
	for (int i = 0; i < 10; i++)
		ftv_push_back(&v, i);
	ftt_expect(ftv_size(&v))->to_be(10);

	ft_iterator it = ftv_begin(&v);
	for (int i = 0; i < 10; i++, FT_ITER_INC(it))
		ftt_expect(FT_ITER_VALUE(it, int))->to_be(i);
	ftt_expect(FT_ITER_EQ(it, ftv_end(&v)))->to_be_true();

	it = ftv_rbegin(&v);
	for (int i = 9; i >= 0; i--, FT_ITER_INC(it))
		ftt_expect(FT_ITER_VALUE(it, int))->to_be(i);
	ftt_expect(FT_ITER_EQ(it, ftv_rend(&v)))->to_be_true();

	int i = 9;
	for (ft_iterator it = ftv_rbegin(&v); FT_ITER_NEQ(it, ftv_rend(&v)); FT_ITER_INC(it), i--)
		ftt_expect(FT_ITER_VALUE(it, int))->to_be(i);
	ftt_expect(FT_ITER_EQ(it, ftv_rend(&v)))->to_be_true();

	i = 0;
	ftv_each(v, it)
		ftt_expect(FT_ITER_VALUE(it, int))->to_be(i++);
	ftv_each_reverse(v, it)
		ftt_expect(FT_ITER_VALUE(it, int))->to_be(--i);

	i = 0;
	ftv_each(v, it)
	{
		int value = FT_ITER_VALUE(it, int);
		ftt_expect(value)->to_be(i++);
	}
	ftv_each_reverse(v, it)
	{
		int value = FT_ITER_VALUE(it, int);
		ftt_expect(value)->to_be(--i);
	}
	ftv_destroy(&v);
}

static void test_vector_insert(void* param)
{
	ft_vector v = ftv_create(&(ftv_desc){
		.alloc = (ft_allocator){
			.sizeof_type = sizeof(int),
		},
	});

	ftv_reserve(&v, 12);
	for (int i = 0; i < 10; i++)
		ftv_push_back(&v, i);
	ftt_expect(ftv_size(&v))->to_be(10);

	ft_iterator it = ftv_begin(&v);
	for (int i = 0; i < 10; i++, FT_ITER_INC(it))
		ftt_expect(FT_ITER_VALUE(it, int))->to_be(i);
	ftt_expect(FT_ITER_EQ(it, ftv_end(&v)))->to_be_true();

	ftv_insert_atv(&v, FT_ITER_ADD_NEW(ftv_begin(&v), 5), 100);
	ftt_expect(ftv_size(&v))->to_be(11);
	ftt_expect(ftv_at(&v, 5, int))->to_be(100);
	ftv_insert_atv(&v, FT_ITER_ADD_NEW(ftv_begin(&v), 5), 200);
	ftt_expect(ftv_size(&v))->to_be(12);
	ftt_expect(ftv_at(&v, 5, int))->to_be(200);
	ftv_insert_atv(&v, ftv_end(&v), 300);
	ftt_expect(ftv_size(&v))->to_be(13);
	ftt_expect(ftv_at(&v, 12, int))->to_be(300);

	ftv_at(&v, 0, int) = 100;
	ftt_expect(ftv_at(&v, 0, int))->to_be(100);
	ftv_destroy(&v);
}

struct vector_test_struct { int a, b; };

static void	test_allocator_construct(const ft_allocator* alloc, void *p, const void* value)
{
	struct vector_test_struct* obj = p;
	const struct vector_test_struct* val = value;

	obj->a = val->a + 42;
	obj->b = val->b + 42;
}

static void	test_allocator(void* param)
{
	ft_vector	v = ftv_create(&(ftv_desc){
		.alloc = {
			.sizeof_type = sizeof(struct vector_test_struct),
			.construct = test_allocator_construct,
		},
	});

	ftt_expect(v.alloc.sizeof_type)->to_be(sizeof(struct vector_test_struct));
	ftv_reserve(&v, 2);
	ftt_expect(ftv_capacity(&v))->to_be(2);
	ftv_push_back(&v, (struct vector_test_struct){42, 21});
	ftv_push_back(&v, (struct vector_test_struct){20, 43});
	ftt_expect(ftv_size(&v))->to_be(2);

	// The constructed values should have +42 in each member
	ftt_expect(ftv_at(&v, 0, struct vector_test_struct).a)->to_be(42 + 42);
	ftt_expect(ftv_at(&v, 0, struct vector_test_struct).b)->to_be(21 + 42);
	ftt_expect(ftv_at(&v, 1, struct vector_test_struct).a)->to_be(20 + 42);
	ftt_expect(ftv_at(&v, 1, struct vector_test_struct).b)->to_be(43 + 42);
	for (ft_iterator it = ftv_begin(&v); !FT_ITER_EQ(it, ftv_end(&v)); FT_ITER_INC(it))
	{
		struct vector_test_struct val = FT_ITER_VALUE(it, struct vector_test_struct);
		// 63 is the sum of original a and b, for both structs
		ftt_expect(val.a + val.b)->to_be(63 + 42 + 42);
	}

	ftv_each(v, it)
	{
		struct vector_test_struct val = FT_ITER_VALUE(it, struct vector_test_struct);
		// 63 is the sum of original a and b, for both structs
		ftt_expect(val.a + val.b)->to_be(63 + 42 + 42);
	}
	ftv_destroy(&v);
}

static void test_vector_resize(void* param)
{
	ftt_set_status(FTT_STATUS_TODO);
}

static const ftt_context vector_ctx = {
	.name = "vector",
	.count = 7,
	.it = (ftt_it_t[]){
		{
			.name = "create",
			.callback = test_vector_create,
			.param = NULL,
		},
		{
			.name = "reserve",
			.callback = test_vector_reserve,
			.param = NULL,
		},
		{
			.name = "push_back",
			.callback = test_vector_push_back,
			.param = NULL,
		},
		{
			.name = "iterator",
			.callback = test_iterator,
			.param = NULL,
		},
		{
			.name = "insert",
			.callback = test_vector_insert,
			.param = NULL,
		},
		{
			.name = "allocator",
			.callback = test_allocator,
			.param = NULL,
		},
		{
			.name = "resize",
			.callback = test_vector_resize,
			.param = NULL,
		}
	},
};

// >>write

static void test_ft_putchar(void* param)
{
	int saved_stdout = dup(STDOUT_FILENO);

	int pipefd[2];
	pipe(pipefd);
	dup2(pipefd[1], STDOUT_FILENO);
	close(pipefd[1]);

	for (char i = 0; i < 127; i++)
		ft_putchar((char)i);
	
	dup2(saved_stdout, STDOUT_FILENO);
	close(saved_stdout);

	char buffer[128];
	ssize_t bytes_read = read(pipefd[0], buffer, sizeof(buffer));
	buffer[bytes_read] = '\0';
	close(pipefd[0]);

	ftt_expect(bytes_read)->to_be(127);
	for (ssize_t i = 0; i < bytes_read; i++)
		ftt_expect(buffer[i])->to_be((char)(i));
}

static void test_ft_putchar_fd(void* param)
{
	for (int fd = 1; fd <= 2; fd++)
	{
		int saved_fd = dup(fd);

		int pipefd[2];
		pipe(pipefd);
		dup2(pipefd[1], fd);
		close(pipefd[1]);

		for (char i = 0; i < 127; i++)
			ft_putchar_fd((char)i, fd);
		
		dup2(saved_fd, fd);
		close(saved_fd);

		char buffer[128];
		ssize_t bytes_read = read(pipefd[0], buffer, sizeof(buffer));
		buffer[bytes_read] = '\0';
		close(pipefd[0]);

		ftt_expect(bytes_read)->to_be(127);
		for (ssize_t i = 0; i < bytes_read; i++)
			ftt_expect(buffer[i])->to_be((char)(i));
	}
}

static void test_ft_putnbr(void* param)
{
	int saved_stdout = dup(STDOUT_FILENO);

	int pipefd[2];
	pipe(pipefd);
	dup2(pipefd[1], STDOUT_FILENO);
	close(pipefd[1]);

	for (int i = -1000; i <= 1000; i++)
		ft_putnbr(i);
	
	dup2(saved_stdout, STDOUT_FILENO);
	close(saved_stdout);

	char buffer[8192];
	ssize_t bytes_read = read(pipefd[0], buffer, sizeof(buffer) - 1);
	buffer[bytes_read] = '\0';
	close(pipefd[0]);

	char* line = buffer;
	for (int i = -1000; i <= 1000; i++)
	{
		char expected[16];
		int len = ft_snprintf(expected, sizeof(expected), "%d", i);
		ftt_expect(ft_strncmp(line, expected, len))->to_be(0);
		line += len;
	}
}

static void test_ft_putnbr_fd(void* param)
{
	for (int fd = 1; fd <= 2; fd++)
	{
		int saved_fd = dup(fd);

		int pipefd[2];
		pipe(pipefd);
		dup2(pipefd[1], fd);
		close(pipefd[1]);

		for (int i = -1000; i <= 1000; i++)
			ft_putnbr_fd(i, fd);
		
		dup2(saved_fd, fd);
		close(saved_fd);

		char buffer[8192];
		ssize_t bytes_read = read(pipefd[0], buffer, sizeof(buffer) - 1);
		buffer[bytes_read] = '\0';
		close(pipefd[0]);

		char* line = buffer;
		for (int i = -1000; i <= 1000; i++)
		{
			char expected[16];
			int len = ft_snprintf(expected, sizeof(expected), "%d", i);
			ftt_expect(ft_strncmp(line, expected, len))->to_be(0);
			line += len;
		}
	}
}

static void test_ft_putstr(void* param)
{
	int saved_stdout = dup(STDOUT_FILENO);

	int pipefd[2];
	pipe(pipefd);
	dup2(pipefd[1], STDOUT_FILENO);
	close(pipefd[1]);

	const char* test_strings[] = {
		"Hello, World!",
		"",
		"Lorem ipsum dolor sit amet, consectetur adipiscing elit.",
		"0123456789",
		"!@#$%^&*()_+-=[]{}|;':\",.<>/?`~D3UD893YF9832YHF8939FH3890PYHF89hyf_çàpéhz",
	};

	for (size_t i = 0; i < sizeof(test_strings) / sizeof(test_strings[0]); i++)
		ft_putstr(test_strings[i]);
	
	dup2(saved_stdout, STDOUT_FILENO);
	close(saved_stdout);

	char buffer[1024];
	ssize_t bytes_read = read(pipefd[0], buffer, sizeof(buffer) - 1);
	buffer[bytes_read] = '\0';
	close(pipefd[0]);

	char* ptr = buffer;
	for (size_t i = 0; i < sizeof(test_strings) / sizeof(test_strings[0]); i++)
	{
		size_t len = ft_strlen(test_strings[i]);
		if (len > 0)
			ftt_expect(ft_strncmp(ptr, test_strings[i], len))->to_be(0);
		ptr += len;
	}
}

static void test_ft_putstr_fd(void* param)
{
	for (int fd = 1; fd <= 2; fd++)
	{
		int saved_fd = dup(fd);

		int pipefd[2];
		pipe(pipefd);
		dup2(pipefd[1], fd);
		close(pipefd[1]);

		const char* test_strings[] = {
			"Hello, World!",
			"",
			"Lorem ipsum dolor sit amet, consectetur adipiscing elit.",
			"0123456789",
			"!@#$%^&*()_+-=[]{}|;':\",.<>/?`~D3UD893YF9832YHF8939FH3890PYHF89hyf_çàpéhz",
		};

		for (size_t i = 0; i < sizeof(test_strings) / sizeof(test_strings[0]); i++)
			ft_putstr_fd(test_strings[i], fd);
		
		dup2(saved_fd, fd);
		close(saved_fd);

		char buffer[1024];
		ssize_t bytes_read = read(pipefd[0], buffer, sizeof(buffer) - 1);
		buffer[bytes_read] = '\0';
		close(pipefd[0]);

		char* ptr = buffer;
		for (size_t i = 0; i < sizeof(test_strings) / sizeof(test_strings[0]); i++)
		{
			size_t len = ft_strlen(test_strings[i]);
			if (len > 0)
				ftt_expect(ft_strncmp(ptr, test_strings[i], len))->to_be(0);
			ptr += len;
		}
	}
}

static void test_ft_putendl(void* param)
{
	int saved_stdout = dup(STDOUT_FILENO);

	int pipefd[2];
	pipe(pipefd);
	dup2(pipefd[1], STDOUT_FILENO);
	close(pipefd[1]);

	const char* test_strings[] = {
		"Hello, World!",
		"",
		"Lorem ipsum dolor sit amet, consectetur adipiscing elit.",
		"0123456789",
		"!@#$%^&*()_+-=[]{}|;':\",.<>/?`~D3UD893YF9832YHF8939FH3890PYHF89hyf_çàpéhz",
	};

	for (size_t i = 0; i < sizeof(test_strings) / sizeof(test_strings[0]); i++)
		ft_putendl(test_strings[i]);
	
	dup2(saved_stdout, STDOUT_FILENO);
	close(saved_stdout);

	char buffer[1024];
	ssize_t bytes_read = read(pipefd[0], buffer, sizeof(buffer) - 1);
	buffer[bytes_read] = '\0';
	close(pipefd[0]);

	char* ptr = buffer;
	for (size_t i = 0; i < sizeof(test_strings) / sizeof(test_strings[0]); i++)
	{
		size_t len = ft_strlen(test_strings[i]);
		if (len > 0)
			ftt_expect(ft_strncmp(ptr, test_strings[i], len))->to_be(0);
		ptr += len;
		ftt_expect((char)*ptr)->to_be((char)'\n');
		ptr++;
	}
}

static void test_ft_putendl_fd(void* param)
{
	for (int fd = 1; fd <= 2; fd++)
	{
		int saved_fd = dup(fd);

		int pipefd[2];
		pipe(pipefd);
		dup2(pipefd[1], fd);
		close(pipefd[1]);

		const char* test_strings[] = {
			"Hello, World!",
			"",
			"Lorem ipsum dolor sit amet, consectetur adipiscing elit.",
			"0123456789",
			"!@#$%^&*()_+-=[]{}|;':\",.<>/?`~D3UD893YF9832YHF8939FH3890PYHF89hyf_çàpéhz",
		};

		for (size_t i = 0; i < sizeof(test_strings) / sizeof(test_strings[0]); i++)
			ft_putendl_fd(test_strings[i], fd);
		
		dup2(saved_fd, fd);
		close(saved_fd);

		char buffer[1024];
		ssize_t bytes_read = read(pipefd[0], buffer, sizeof(buffer) - 1);
		buffer[bytes_read] = '\0';
		close(pipefd[0]);

		char* ptr = buffer;
		for (size_t i = 0; i < sizeof(test_strings) / sizeof(test_strings[0]); i++)
		{
			size_t len = ft_strlen(test_strings[i]);
			if (len > 0)
				ftt_expect(ft_strncmp(ptr, test_strings[i], len))->to_be(0);
			ptr += len;
			ftt_expect((char)*ptr)->to_be((char)'\n');
			ptr++;
		}
	}
}

static const ftt_context write_ctx = {
	.name = "write",
	.count = 8,
	.it = (ftt_it_t[]){
		{
			.name = "ft_putchar",
			.callback = test_ft_putchar,
			.param = NULL,
		},
		{
			.name = "ft_putchar_fd",
			.callback = test_ft_putchar_fd,
			.param = NULL
		},
		{
			.name = "ft_putnbr",
			.callback = test_ft_putnbr,
			.param = NULL,
		},
		{
			.name = "ft_putnbr_fd",
			.callback = test_ft_putnbr_fd,
			.param = NULL,
		},
		{
			.name = "ft_putstr",
			.callback = test_ft_putstr,
			.param = NULL,
		},
		{
			.name = "ft_putstr_fd",
			.callback = test_ft_putstr_fd,
			.param = NULL,
		},
		{
			.name = "ft_putendl",
			.callback = test_ft_putendl,
			.param = NULL,
		},
		{
			.name = "ft_putendl_fd",
			.callback = test_ft_putendl_fd,
			.param = NULL,
		}
	}
};

// >>main

static const char* usage = "\
Available tests:\n\
  - all\n\
  - basic_string\n\
  - fileparse\n\
  - vector\n\
  - write\n\
";

int	main(int argc, char **argv)
{
	ftap_state state = ftap_parse(argc, argv, &(ftap_desc){
		.opt_count = 0,
		.options = NULL,
	});

	if (!ftap_valid(&state))
	{
		ft_dprintf(STDERR_FILENO, "Error\n");
		return (1);
	}

	if (state.arguments == NULL)
		ft_printf("%s", usage);
	else
	{
		ftt_context contexts[8];
		size_t ctx_count = 0;

		argc = 0;
		while (state.arguments[argc] != NULL)
			argc++;
		for (int i = 0; state.arguments[i] != NULL; i++)
		{
			if (ft_strcmp(state.arguments[i], "all") == 0)
			{
				ctx_count = 0;
				contexts[ctx_count++] = basic_string_ctx;
				contexts[ctx_count++] = fileparse_ctx;
				contexts[ctx_count++] = vector_ctx;
				contexts[ctx_count++] = write_ctx;
				break ;
			}
			else if (ft_strcmp(state.arguments[i], "basic_string") == 0)
			{
				contexts[ctx_count++] = basic_string_ctx;
			}
			else if (ft_strcmp(state.arguments[i], "fileparse") == 0)
			{
				contexts[ctx_count++] = fileparse_ctx;
			}
			else if (ft_strcmp(state.arguments[i], "vector") == 0)
			{
				contexts[ctx_count++] = vector_ctx;
			}
			else if (ft_strcmp(state.arguments[i], "write") == 0)
			{
				contexts[ctx_count++] = write_ctx;
			}
			else
			{
				ft_dprintf(STDERR_FILENO, "Unknown test: %s\n", state.arguments[i]);
				ft_dprintf(STDERR_FILENO, "%s", usage);
				ftap_clear(&state);
				return (1);
			}
		}

		ft_printf("Running tests.\n");
		ftt_describe("LIBFT", &(ftt_desc){
			.count = ctx_count,
			.contexts = contexts,
		});
		ft_printf("Tests finished.\n");
	}
	ftap_clear(&state);
	return (0);
}
