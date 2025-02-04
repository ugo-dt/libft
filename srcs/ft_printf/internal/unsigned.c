#include "internal/_libft_printf.h"

#define _UNSIGNED_CONVERSION_DEF(_name, _type)											\
	char	*_ft_printf_create_##_name(_type nb, struct _libft_printf_specs *specs)		\
	{																					\
		int arg_length;																	\
		int arg_start;																	\
		char *s;																		\
																						\
		GET_UNSIGNED_NUMBER_LENGTH(&arg_length, nb, 10, specs->info.precision, _type);	\
		s = _ft_printf_create_string_helper(specs, arg_length, &arg_start);				\
		if (!s)																			\
			return (NULL);																\
		MAKE_UNSIGNED_NUMBER_STRING(s + arg_start, nb, arg_length, _type);				\
		return (s);																		\
	}

_UNSIGNED_CONVERSION_DEF(u, unsigned int)
_UNSIGNED_CONVERSION_DEF(ul, unsigned long)
_UNSIGNED_CONVERSION_DEF(ull, unsigned long long)
