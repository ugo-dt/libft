#pragma once

#include "libft/libft.h"

typedef enum
{
	FTT_STATUS_SUCCESS,
	FTT_STATUS_FAILURE,
	FTT_STATUS_ERROR,
	FTT_STATUS_TODO,
}ftt_status_t;

typedef void (*ftt_callback_fn)(void* param);

typedef struct ftt_it_s
{
	const char* name;
	ftt_callback_fn callback;
	void* param;
}ftt_it_t;

typedef struct
{
	const char* name;
	ftt_it_t* it;
	size_t count;
}ftt_context;

typedef struct
{
	void (*before)(void* param);
	void (*before_each)(void* param);
	void (*after)(void* param);
	void (*after_each)(void* param);
	ftt_context* contexts;
	size_t count;
}ftt_desc;

typedef enum
{
	FTT_VALUE_TYPE_INT,
	FTT_VALUE_TYPE_UINT,
	FTT_VALUE_TYPE_LONG,
	FTT_VALUE_TYPE_ULONG,
	FTT_VALUE_TYPE_FLOAT,
	FTT_VALUE_TYPE_DOUBLE,
	FTT_VALUE_TYPE_POINTER,
	FTT_VALUE_TYPE_STRING,
}ftt_value_type;

typedef struct ftt_expect_s
{
	void (*to_be)(const void* value, size_t sizeof_value, ftt_value_type type);
	void (*to_not_be)(const void* value, size_t sizeof_value, ftt_value_type type);
}ftt_expect_t;

void ftt_describe(const char* name, const ftt_desc* desc);
void ftt_set_status(ftt_status_t status);

void _ftt_log(const char* file, const char* format, ...);
const ftt_expect_t*	_ftt_expect(
	const char *value_name,
	const char* file,
	int line,
	const void* value,
	size_t sizeof_value
);
void _ftt_expect_to_be(const void* value, size_t sizeof_value, ftt_value_type type);

// _ftt_expect((&(__value)), sizeof((__value)))
#define ftt_expect(__v)	({ _ftt_expect(#__v, __FILE__, __LINE__, &(__typeof__((__v))){(__v)}, sizeof((__v))); })
#define FTT_VALUE_TYPE(__v) _Generic((__v), \
	int: FTT_VALUE_TYPE_INT, \
	unsigned int: FTT_VALUE_TYPE_UINT, \
	long: FTT_VALUE_TYPE_LONG, \
	unsigned long: FTT_VALUE_TYPE_ULONG, \
	float: FTT_VALUE_TYPE_FLOAT, \
	double: FTT_VALUE_TYPE_DOUBLE, \
	char *: FTT_VALUE_TYPE_STRING, \
	const char *: FTT_VALUE_TYPE_STRING, \
	void *: FTT_VALUE_TYPE_POINTER, \
	const void *: FTT_VALUE_TYPE_POINTER, \
	default: FTT_VALUE_TYPE_POINTER \
)
#define ftt_log(fmt, ...) _ftt_log(__func__, fmt, ##__VA_ARGS__)

#if defined LIBFT_TESTER_MACROS
	#define to_be(__v) to_be(&(__typeof__((__v))){(__v)}, sizeof((__v)), FTT_VALUE_TYPE((__v)))
	#define to_not_be(__v) to_not_be(&(__typeof__((__v))){(__v)}, sizeof((__v)), FTT_VALUE_TYPE((__v)))
#endif // LIBFT_TESTER_MACROS
