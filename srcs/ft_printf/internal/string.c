#include "_libft_printf.h"

/** The function _ft_printf_create_s() writes the string pointed to by str to the file
 * descriptor fd.
 * @returns The number of characters written. */
char	*_ft_printf_create_s(const char *str, struct _libft_printf_specs *specs)
{
	int arg_length;
	int arg_start;
	char *s;

	if (str)
	{
		if (specs->info.precision > -1)
			arg_length = min((int)ft_strlen(str), specs->info.precision);
		else
			arg_length = ft_strlen(str);
		s = _ft_printf_create_string_helper(specs, arg_length, &arg_start);
		if (!s)
			return (NULL);
		ft_memcpy(s + arg_start, str, arg_length);
	}
	else
	{
		arg_length = sizeof(LIBFT_PRINTF_NULL_STRING) - 1; // Remove the null character
		s = _ft_printf_create_string_helper(specs, arg_length, &arg_start);
		if (!s)
			return (NULL);
		ft_memcpy(s + arg_start, LIBFT_PRINTF_NULL_STRING, arg_length);
	}
	return (s);
}
