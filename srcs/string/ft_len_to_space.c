#include "libft/libft.h"

size_t	ft_len_to_space(const char *s)
{
	size_t	n;

	n = 0;
	while (s[n] && !ft_isspace(s[n]))
		n++;
	return (n);
}
