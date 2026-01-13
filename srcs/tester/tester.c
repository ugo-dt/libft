#include "libft/tester.h"

#define COLOR_DEFAULT	"\033[39m"
#define COLOR_DARK_RED	"\033[31m"
#define COLOR_GREY		"\033[90m"
#define COLOR_RED		"\033[91m"
#define COLOR_GREEN		"\033[92m"
#define COLOR_YELLOW	"\033[93m"
#define COLOR_BLUE		"\033[94m"
#define COLOR_MAGENTA	"\033[95m"
#define COLOR_WHITE		"\033[97m"

typedef struct _ftt_expect_t
{
	ftt_expect_t _properties; // MUST be first
	const void* _value;
	struct {
		const char* _value_name;
		const char* _file;
		int _line;
	};
	size_t _sizeof_value;
	ftt_status_t _status;
	char _error[512];
	size_t ctx_tests_passed;
}_ftt_expect_t;

_ftt_expect_t tester_expect;

static void _ftt_set_error(const char* format, ...)
{
	va_list args;
	va_start(args, format);
	ft_vsnprintf(tester_expect._error, sizeof(tester_expect._error), format, args);
	va_end(args);
}
LIBFT_FORCE_INLINE const char* _ftt_get_error(void) { return tester_expect._error; }
LIBFT_FORCE_INLINE const char* _ftt_get_value_name(void) { return tester_expect._value_name; }
LIBFT_FORCE_INLINE const char* _ftt_get_file(void) { return tester_expect._file; }
LIBFT_FORCE_INLINE int _ftt_get_line(void) { return tester_expect._line; }

void	_ftt_expect_to_be(const void* value, size_t sizeof_value, ftt_value_type type)
{
	if (tester_expect._status != FTT_STATUS_SUCCESS)
		return ;
	
	if (ft_memcmp(tester_expect._value, value, sizeof_value) != 0)
	{
		tester_expect._status = FTT_STATUS_FAILURE;
		switch (type)
		{
			case FTT_VALUE_TYPE_INT:
				_ftt_set_error("expected %s to be %d, got %d", tester_expect._value_name, *(int*)value, *(int*) tester_expect._value);
				break ;
			case FTT_VALUE_TYPE_UINT:
				_ftt_set_error("expected %s to be %u, got %u", tester_expect._value_name, *(unsigned int*)value, *(unsigned int*) tester_expect._value);
				break ;
			case FTT_VALUE_TYPE_LONG:
				_ftt_set_error("expected %s to be %ld, got %ld", tester_expect._value_name, *(long*)value, *(long*) tester_expect._value);
				break ;
			case FTT_VALUE_TYPE_ULONG:
				_ftt_set_error("expected %s to be %lu, got %lu", tester_expect._value_name, *(unsigned long*)value, *(unsigned long*) tester_expect._value);
				break ;
			case FTT_VALUE_TYPE_FLOAT:
				_ftt_set_error("expected %s to be %f, got %f", tester_expect._value_name, *(float*)value, *(float*) tester_expect._value);
				break ;
			case FTT_VALUE_TYPE_DOUBLE:
				_ftt_set_error("expected %s to be %lf, got %lf", tester_expect._value_name, *(double*)value, *(double*) tester_expect._value);
				break ;
			case FTT_VALUE_TYPE_STRING:
				_ftt_set_error("expected %s to be \"%s\", got \"%s\"", tester_expect._value_name, (char*)value, (char*) tester_expect._value);
				break ;
			case FTT_VALUE_TYPE_POINTER:
			default:
				_ftt_set_error("expected %s to be %p, got %p", tester_expect._value_name, value, tester_expect._value);
				break ;
		}
	}
}

void	_ftt_expect_not_to_be(const void* value, size_t sizeof_value, ftt_value_type type)
{
	if (tester_expect._status != FTT_STATUS_SUCCESS)
		return ;

	if (ft_memcmp(tester_expect._value, value, sizeof_value) == 0)
	{
		tester_expect._status = FTT_STATUS_FAILURE;
		switch (type)
		{
			case FTT_VALUE_TYPE_INT:
				_ftt_set_error("expected %s to not be %d, got %d", tester_expect._value_name, *(int*)value, *(int*) tester_expect._value);
				break ;
			case FTT_VALUE_TYPE_UINT:
				_ftt_set_error("expected %s to not be %u, got %u", tester_expect._value_name, *(unsigned int*)value, *(unsigned int*) tester_expect._value);
				break ;
			case FTT_VALUE_TYPE_LONG:
				_ftt_set_error("expected %s to not be %ld, got %ld", tester_expect._value_name, *(long*)value, *(long*) tester_expect._value);
				break ;
			case FTT_VALUE_TYPE_ULONG:
				_ftt_set_error("expected %s to not be %lu, got %lu", tester_expect._value_name, *(unsigned long*)value, *(unsigned long*) tester_expect._value);
				break ;
			case FTT_VALUE_TYPE_FLOAT:
				_ftt_set_error("expected %s to not be %f, got %f", tester_expect._value_name, *(float*)value, *(float*) tester_expect._value);
				break ;
			case FTT_VALUE_TYPE_DOUBLE:
				_ftt_set_error("expected %s to not be %lf, got %lf", tester_expect._value_name, *(double*)value, *(double*) tester_expect._value);
				break ;
			case FTT_VALUE_TYPE_STRING:
				_ftt_set_error("expected %s to not be \"%s\", got \"%s\"", tester_expect._value_name, (char*)value, (char*) tester_expect._value);
				break ;
			case FTT_VALUE_TYPE_POINTER:
			default:
				_ftt_set_error("expected %s to not be %p, got %p", tester_expect._value_name, value, tester_expect._value);
				break ;
		}
	}
}

// void (*to_be_greater_than)(const void* value, size_t sizeof_value, ftt_value_type type);
// void (*to_be_less_than)(const void* value, size_t sizeof_value, ftt_value_type type);
// void (*to_be_between)(const void* min, const void* max, size_t sizeof_value, ftt_value_type type);
// void (*to_be_null)(void);
// void (*to_not_be_null)(void);

void _ftt_expect_to_be_greater_than_int(const int value)
{
	if (tester_expect._status != FTT_STATUS_SUCCESS)
		return ;
	if (*(int*)tester_expect._value <= value)
	{
		tester_expect._status = FTT_STATUS_FAILURE;
		_ftt_set_error("expected %s to be greater than %d, got %d", tester_expect._value_name, value, *(int*)tester_expect._value);
	}
}

void _ftt_expect_to_be_greater_than_float(const float value)
{
	if (tester_expect._status != FTT_STATUS_SUCCESS)
		return ;
	if (*(float*)tester_expect._value <= value)
	{
		tester_expect._status = FTT_STATUS_FAILURE;
		_ftt_set_error("expected %s to be greater than %f, got %f", tester_expect._value_name, value, *(float*)tester_expect._value);
	}
}

void _ftt_expect_to_be_greater_than(const void* value, size_t sizeof_value, ftt_value_type type)
{
	if (tester_expect._status != FTT_STATUS_SUCCESS)
		return ;
	if (sizeof_value == sizeof(int) && type == FTT_VALUE_TYPE_INT)
		_ftt_expect_to_be_greater_than_int(*(int*)value);
	else if (sizeof_value == sizeof(float) && type == FTT_VALUE_TYPE_FLOAT)
		_ftt_expect_to_be_greater_than_float(*(float*)value);
	else
	{
		tester_expect._status = FTT_STATUS_FAILURE;
		_ftt_set_error("to_be_greater_than(): invalid type");
	}
}

void _ftt_expect_to_be_true(void)
{
	if (tester_expect._status != FTT_STATUS_SUCCESS)
		return ;

	if (*(bool*)tester_expect._value != true)
	{
		tester_expect._status = FTT_STATUS_FAILURE;
		_ftt_set_error("expected %s to be true, got false", tester_expect._value_name);
	}
}

void _ftt_expect_to_be_false(void)
{
	if (tester_expect._status != FTT_STATUS_SUCCESS)
		return ;

	if (*(bool*)tester_expect._value != false)
	{
		tester_expect._status = FTT_STATUS_FAILURE;
		_ftt_set_error("expected %s to be false, got true", tester_expect._value_name);
	}
}

void _ftt_expect_to_be_null(void)
{
	if (tester_expect._status != FTT_STATUS_SUCCESS)
		return ;

	if (tester_expect._value != NULL)
	{
		tester_expect._status = FTT_STATUS_FAILURE;
		_ftt_set_error("expected %s to be NULL, got %p", tester_expect._value_name, tester_expect._value);
	}
}

void _ftt_expect_not_to_be_null(void)
{
	if (tester_expect._status != FTT_STATUS_SUCCESS)
		return ;

	if (tester_expect._value == NULL)
	{
		tester_expect._status = FTT_STATUS_FAILURE;
		_ftt_set_error("expected %s to not be NULL", tester_expect._value_name);
	}
}

const ftt_expect_t*	_ftt_expect(
	const char *value_name,
	const char* file,
	int line,
	const void* value,
	size_t sizeof_value
)
{
	if (tester_expect._status != FTT_STATUS_SUCCESS)
		return (const ftt_expect_t*)&tester_expect;

	tester_expect._value = value;
	tester_expect._value_name = value_name;
	tester_expect._file = file;
	tester_expect._line = line;
	tester_expect._sizeof_value = sizeof_value;
	tester_expect._error[0] = '\0';
	return (const ftt_expect_t*)&tester_expect;
}

static void	ftt_print_status(const char*name)
{
	switch (tester_expect._status)
	{
		case FTT_STATUS_SUCCESS:
			ft_printf(COLOR_GREEN "  ✓ %s: PASS\n" COLOR_DEFAULT, name);
			break;
		case FTT_STATUS_FAILURE:
			ft_printf(COLOR_RED "  x %s: FAIL\n" COLOR_DEFAULT, name);
			ft_printf(COLOR_RED "    - %s:%d: %s\n" COLOR_DEFAULT,
				_ftt_get_file(), _ftt_get_line(), _ftt_get_error());
			break;
		case FTT_STATUS_ERROR:
			ft_printf(COLOR_DARK_RED "  x %s: ERROR\n" COLOR_DEFAULT, name);
			break;
		case FTT_STATUS_TODO:
			ft_printf(COLOR_YELLOW "  - %s: TODO\n" COLOR_DEFAULT, name);
			break;
		default:
			ft_printf(" - UNKNOWN STATUS\n");
			break;
	}
}

void	ftt_set_status(ftt_status_t status)
{
	tester_expect._file = "";
	tester_expect._line = 0;
	tester_expect._status = status;
}

void	_ftt_log(const char *func, const char* format, ...)
{
	va_list args;
	const char buffer[1024];

	va_start(args, format);
	ft_vsnprintf((char*)buffer, sizeof(buffer), format, args);
	ft_printf(COLOR_WHITE "  [LOG][%s] %s\n" COLOR_DEFAULT, func, buffer);
	va_end(args);
}

static void	_ftt_run_test(const ftt_it_t* it, const ftt_desc* desc)
{
	ftt_set_status(FTT_STATUS_SUCCESS);

	if (desc->before_each)
		desc->before_each(NULL);
	if (it->callback)
	{
		it->callback(it->param);
		ftt_print_status(it->name);
	}
	if (desc->after_each)
		desc->after_each(NULL);

	if (tester_expect._status == FTT_STATUS_SUCCESS || tester_expect._status == FTT_STATUS_TODO)
		tester_expect.ctx_tests_passed++;
}

static void	_ftt_set_properties(void)
{
	tester_expect._properties.to_be = _ftt_expect_to_be;
	tester_expect._properties.to_not_be = _ftt_expect_not_to_be;
	tester_expect._properties.to_be_true = _ftt_expect_to_be_true;
	tester_expect._properties.to_be_false = _ftt_expect_to_be_false;
	tester_expect._properties.to_be_greater_than = _ftt_expect_to_be_greater_than;
	tester_expect._properties.to_be_less_than = NULL; // To be implemented
	tester_expect._properties.to_be_between = NULL; // To be implemented
	tester_expect._properties.to_be_null = _ftt_expect_to_be_null;
	tester_expect._properties.to_not_be_null = _ftt_expect_not_to_be_null;
}

void	ftt_describe(const char* name, const ftt_desc* desc)
{
	assert(desc != NULL);
	size_t total_tests = 0;
	size_t total_tests_passed = 0;

	_ftt_set_properties();

	if (name && *name)
		ft_printf(COLOR_MAGENTA "=== %s ===\n" COLOR_DEFAULT, name);
	for (size_t i = 0; i < desc->count; i++)
	{
		ftt_context* ctx = &desc->contexts[i];
		
		tester_expect.ctx_tests_passed = 0;
		if (desc->before)
			desc->before(NULL);
		if (ctx->name && *ctx->name)
			ft_printf(COLOR_YELLOW "--- %s ---\n" COLOR_DEFAULT, ctx->name);
		for (size_t j = 0; j < ctx->count; j++)
			_ftt_run_test(&ctx->it[j], desc);
		if (desc->after)
			desc->after(NULL);
		if (tester_expect.ctx_tests_passed == ctx->count)
			ft_printf(COLOR_YELLOW);
		else
			ft_printf(COLOR_RED);
		
		total_tests += ctx->count;
		total_tests_passed += tester_expect.ctx_tests_passed;

		ft_printf("RESULT: %d/%d PASSED\n" COLOR_DEFAULT, (int)tester_expect.ctx_tests_passed, (int)ctx->count);
		if (i + 1 < desc->count)
			ft_printf("\n");
	}
	ft_printf(COLOR_MAGENTA "=== %s RESULT: %d/%d PASSED ===\n" COLOR_DEFAULT,
		name && *name ? name : "TEST", (int)total_tests_passed, (int)total_tests);
}
