#pragma once

#include "libft/libft.h"

typedef enum
{
	TesterStatus_Success,
	TesterStatus_Failure,
	TesterStatus_Error,
	TesterStatus_ToDo,
}TesterStatus;

typedef void (*TestCallback)(void* param);

typedef struct
{
	const char* name;
	TestCallback callback;
	void* param;
}TestIt;

typedef struct
{
	const char* name;
	TestIt* it;
	size_t count;
}TesterContext;

typedef struct
{
	void (*before)(void* param);
	void (*before_each)(void* param);
	void (*after)(void* param);
	void (*after_each)(void* param);
	TesterContext* contexts;
	size_t count;
}TestDesc;

typedef enum
{
	Tester_ValueType_Int,
	Tester_ValueType_UInt,
	Tester_ValueType_Long,
	Tester_ValueType_ULong,
	Tester_ValueType_Float,
	Tester_ValueType_Double,
	Tester_ValueType_Pointer,
	Tester_ValueType_String,
}TesterValueType;

typedef struct TesterExpect
{
	void (*ToBe)(const void* value, size_t sizeof_value, TesterValueType type);
	void (*ToNotBe)(const void* value, size_t sizeof_value, TesterValueType type);
}TesterExpect;

void Tester_Describe(const char* name, const TestDesc* desc);
void Tester_SetStatus(TesterStatus status);

void _Tester_Log(const char* file, const char* format, ...);
const TesterExpect*	_Tester_Expect(
	const char *value_name,
	const char* file,
	int line,
	const void* value,
	size_t sizeof_value
);
void _TesterExpect_ToBe(const void* value, size_t sizeof_value, TesterValueType type);

// _Tester_Expect((&(__value)), sizeof((__value)))
#define Tester_Expect(__v)	({ _Tester_Expect(#__v, __FILE__, __LINE__, &(__typeof__((__v))){(__v)}, sizeof((__v))); })
#define _Tester_ValueType(__v) _Generic((__v), \
	int: Tester_ValueType_Int, \
	unsigned int: Tester_ValueType_UInt, \
	long: Tester_ValueType_Long, \
	unsigned long: Tester_ValueType_ULong, \
	float: Tester_ValueType_Float, \
	double: Tester_ValueType_Double, \
	char *: Tester_ValueType_String, \
	const char *: Tester_ValueType_String, \
	void *: Tester_ValueType_Pointer, \
	const void *: Tester_ValueType_Pointer, \
	default: Tester_ValueType_Pointer \
)
#define Tester_Log(fmt, ...) _Tester_Log(__func__, fmt, ##__VA_ARGS__)

#if defined LIBFT_TESTER_MACROS
	#define ToBe(__v) ToBe(&(__typeof__((__v))){(__v)}, sizeof((__v)), _Tester_ValueType((__v)))
	#define ToNotBe(__v) ToNotBe(&(__typeof__((__v))){(__v)}, sizeof((__v)), _Tester_ValueType((__v)))
#endif // LIBFT_TESTER_MACROS
