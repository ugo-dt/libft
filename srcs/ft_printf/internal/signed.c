#include "internal/_libft_printf.h"

#define _ft_printf__abs(x)	_Generic((x),	\
	int:       ft_abs,						\
	long:      ft_labs,						\
	long long: ft_llabs						\
	)(x)

#define _SIGNED_CONVERSION_DEF(_name, _type)										\
	char	*_ft_printf_create_##_name(_type nb, struct _libft_printf_specs *specs)	\
	{																				\
		int arg_length;																\
		int arg_start;																\
		char *s;																	\
		GET_NUMBER_LENGTH(&arg_length, nb, 10, specs->info.precision, _type);		\
		int	showfront = (nb >= 0 && (specs->flags.space || specs->flags.showsign));	\
		arg_length += showfront;													\
		s = _ft_printf_create_string_helper(specs, arg_length, &arg_start);			\
		if (!s)																		\
			return (NULL);															\
		MAKE_NUMBER_STRING(s + arg_start, _type, _ft_printf__abs, nb, arg_length);	\
		if (showfront)																\
		{																			\
			if (specs->flags.space)													\
				s[0] = ' ';															\
			else if (specs->flags.showsign)											\
				s[0] = '+';															\
		}																			\
		return (s);																	\
	}

_SIGNED_CONVERSION_DEF(di, int)
_SIGNED_CONVERSION_DEF(l, long)
_SIGNED_CONVERSION_DEF(ll, long long)
