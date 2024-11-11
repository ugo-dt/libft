#include "libft.h"

size_t	ft_len_to_char(const char *s, char c)
{
	int	n;

	n = 0;
	while (s[n] && s[n] != c)
		n++;
	return (n);
}
