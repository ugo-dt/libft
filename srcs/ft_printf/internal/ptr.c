#include "internal/_libft_printf.h"

void	_ft_printf_create_hex_internal(char *s, char x, unsigned int nb, int alt, int length);

/** The function _ft_printf_create_p() writes the address addr in hexadecimal
 * to the file descriptor fd.
 * @returns The number of characters written. */
char	*_ft_printf_create_p(size_t addr, struct _libft_printf_specs *specs)
{
	int		arg_length;
	int		arg_start;
	char	*s;

	if (addr)
	{
		GET_UNSIGNED_NUMBER_LENGTH(&arg_length, addr, 16, specs->info.precision, size_t);
		arg_length += 2;
		s = _ft_printf_create_string_helper(specs, arg_length, &arg_start);
		if (!s)
			return (NULL);
		_ft_printf_create_hex_internal(s + arg_start,  'x', addr, 1, arg_length);
	}
	else
	{
		arg_length = (sizeof(LIBFT_PRINTF_NULL_PTR) - 1); // Remove null character
		s = _ft_printf_create_string_helper(specs, arg_length, &arg_start);
		if (!s)
			return (NULL);
		ft_memcpy(s + arg_start, LIBFT_PRINTF_NULL_PTR, arg_length);
	}
	return (s);
}
