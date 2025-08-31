#include "libft/internal/_libft_printf.h"

char	*_ft_printf_create_c(char c, struct _libft_printf_specs *specs)
{
	int		arg_length;
	int		arg_start;
	char	*s;
	
	arg_length = 1;
	s = _ft_printf_create_string_helper(specs, arg_length, &arg_start);
	if (!s)
		return (NULL);
	ft_memset(s + arg_start, c, arg_length);
	return (s);
}
