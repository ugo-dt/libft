#include "tester.h"

#define COLOR_DEFAULT	"\033[39m"
#define COLOR_DARK_RED	"\033[31m"
#define COLOR_GREY		"\033[90m"
#define COLOR_RED		"\033[91m"
#define COLOR_GREEN		"\033[92m"
#define COLOR_YELLOW	"\033[93m"
#define COLOR_MAGENTA	"\033[95m"

typedef struct _TesterExpect
{
	struct TesterExpect	__properties;
	const void*		_value;
	struct {
		const char*		_value_name;
		const char*		_file;
		int				_line;
	};
	size_t			_sizeof_value;
	TesterStatus	_status;
	char			_error[512];
}_TesterExpect;

_TesterExpect tester_expect;

void	_TesterExpect_ToBe(const void* value, size_t sizeof_value, TesterValueType type)
{
	if (tester_expect._status != TesterStatus_Success)
		return ;

	if (ft_memcmp(tester_expect._value, value, sizeof_value) != 0)
	{
		tester_expect._status = TesterStatus_Failure;
		switch (type)
		{
			case Tester_ValueType_Int:
				ft_snprintf(tester_expect._error, sizeof(tester_expect._error),
				"expected %s to be %d, got %d", tester_expect._value_name, *(int*)value, *(int*) tester_expect._value);
				break ;
			case Tester_ValueType_UInt:
				ft_snprintf(tester_expect._error, sizeof(tester_expect._error),
					"expected %s to be %u, got %u", tester_expect._value_name, *(unsigned int*)value, *(unsigned int*) tester_expect._value);
				break ;
			case Tester_ValueType_Long:
				ft_snprintf(tester_expect._error, sizeof(tester_expect._error),
					"expected %s to be %ld, got %ld", tester_expect._value_name, *(long*)value, *(long*) tester_expect._value);
				break ;
			case Tester_ValueType_ULong:
				ft_snprintf(tester_expect._error, sizeof(tester_expect._error),
					"expected %s to be %lu, got %lu", tester_expect._value_name, *(unsigned long*)value, *(unsigned long*) tester_expect._value);
				break ;
			case Tester_ValueType_Float:
				ft_snprintf(tester_expect._error, sizeof(tester_expect._error),
					"expected %s to be %f, got %f", tester_expect._value_name, *(float*)value, *(float*) tester_expect._value);
				break ;
			case Tester_ValueType_Double:
				ft_snprintf(tester_expect._error, sizeof(tester_expect._error),
					"expected %s to be %lf, got %lf", tester_expect._value_name, *(double*)value, *(double*) tester_expect._value);
				break ;
			case Tester_ValueType_String:
				ft_snprintf(tester_expect._error, sizeof(tester_expect._error),
					"expected %s to be \"%s\", got \"%s\"", tester_expect._value_name, (char*)value, (char*) tester_expect._value);
				break ;
			case Tester_ValueType_Pointer:
			default:
				ft_snprintf(tester_expect._error, sizeof(tester_expect._error),
					"expected %s to be %p, got %p", tester_expect._value_name, value, tester_expect._value);
				break ;
		}
	}
}

void	_TesterExpect_ToNotBe(const void* value, size_t sizeof_value, TesterValueType type)
{
	if (tester_expect._status != TesterStatus_Success)
		return ;

	if (ft_memcmp(tester_expect._value, value, sizeof_value) == 0)
	{
		tester_expect._status = TesterStatus_Failure;
		switch (type)
		{
			case Tester_ValueType_Int:
				ft_snprintf(tester_expect._error, sizeof(tester_expect._error),
				"expected %s to not be %d, got %d", tester_expect._value_name, *(int*)value, *(int*) tester_expect._value);
				break ;
			case Tester_ValueType_UInt:
				ft_snprintf(tester_expect._error, sizeof(tester_expect._error),
					"expected %s to not be %u, got %u", tester_expect._value_name, *(unsigned int*)value, *(unsigned int*) tester_expect._value);
				break ;
			case Tester_ValueType_Long:
				ft_snprintf(tester_expect._error, sizeof(tester_expect._error),
					"expected %s to not be %ld, got %ld", tester_expect._value_name, *(long*)value, *(long*) tester_expect._value);
				break ;
			case Tester_ValueType_ULong:
				ft_snprintf(tester_expect._error, sizeof(tester_expect._error),
					"expected %s to not be %lu, got %lu", tester_expect._value_name, *(unsigned long*)value, *(unsigned long*) tester_expect._value);
				break ;
			case Tester_ValueType_Float:
				ft_snprintf(tester_expect._error, sizeof(tester_expect._error),
					"expected %s to not be %f, got %f", tester_expect._value_name, *(float*)value, *(float*) tester_expect._value);
				break ;
			case Tester_ValueType_Double:
				ft_snprintf(tester_expect._error, sizeof(tester_expect._error),
					"expected %s to not be %lf, got %lf", tester_expect._value_name, *(double*)value, *(double*) tester_expect._value);
				break ;
			case Tester_ValueType_String:
				ft_snprintf(tester_expect._error, sizeof(tester_expect._error),
					"expected %s to not be \"%s\", got \"%s\"", tester_expect._value_name, (char*)value, (char*) tester_expect._value);
				break ;
			case Tester_ValueType_Pointer:
			default:
				ft_snprintf(tester_expect._error, sizeof(tester_expect._error),
					"expected %s to not be %p, got %p", tester_expect._value_name, value, tester_expect._value);
				break ;
		}
	}
}

const TesterExpect*	_Tester_Expect(
	const char *value_name,
	const char* file,
	int line,
	const void* value,
	size_t sizeof_value
)
{
	if (tester_expect._status != TesterStatus_Success)
		return (const TesterExpect*)&tester_expect;

	tester_expect._value = value;
	tester_expect._value_name = value_name;
	tester_expect._file = file;
	tester_expect._line = line;
	tester_expect._sizeof_value = sizeof_value;
	tester_expect._error[0] = '\0';
	return (const TesterExpect*)&tester_expect;
}

static void	Tester_PrintStatus(const char*name)
{
	switch (tester_expect._status)
	{
		case TesterStatus_Success:
			ft_printf(COLOR_GREEN "  ✓ %s: Pass\n" COLOR_DEFAULT, name);
			break;
		case TesterStatus_Failure:
			ft_printf(COLOR_RED "  x %s: Fail\n" COLOR_DEFAULT, name);
			ft_printf(COLOR_RED "    - %s:%d: %s\n" COLOR_DEFAULT,
				tester_expect._file, tester_expect._line, tester_expect._error);
			break;
		case TesterStatus_Error:
			ft_printf(COLOR_DARK_RED "  x %s: Error\n" COLOR_DEFAULT, name);
			break;
		case TesterStatus_ToDo:
			ft_printf(COLOR_YELLOW "  - %s: To Do\n" COLOR_DEFAULT, name);
			break;
		default:
			ft_printf(" - UNKNOWN STATUS\n");
			break;
	}
}

void	Tester_SetStatus(TesterStatus status)
{
	tester_expect._file = "";
	tester_expect._line = 0;
	tester_expect._status = status;
}

static void	RunTest(const TestIt* it, const TestDesc* desc)
{
	Tester_SetStatus(TesterStatus_Success);
	if (desc->before_each)
		desc->before_each(NULL);
	if (it->callback)
	{
		it->callback(it->param);
		Tester_PrintStatus(it->name);
	}
	if (desc->after_each)
		desc->after_each(NULL);
}

static void	Tester_SetProperties(void)
{
	tester_expect.__properties.ToBe = _TesterExpect_ToBe;
	tester_expect.__properties.ToNotBe = _TesterExpect_ToNotBe;
}

void	Tester_Describe(const char* name, const TestDesc* desc)
{
	Tester_SetProperties();

	for (size_t i = 0; i < desc->count; i++)
	{
		TesterContext* ctx = &desc->contexts[i];

		ft_printf(COLOR_MAGENTA "=== %s ===\n", name);
		if (desc->before)
			desc->before(NULL);
		for (size_t j = 0; j < ctx->count; j++)
			RunTest(&ctx->it[j], desc);
		if (desc->after)
			desc->after(NULL);
	}
}
