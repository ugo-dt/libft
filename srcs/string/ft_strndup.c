#include "libft.h"

char	*ft_strndup(const char *s, size_t n)
{
	size_t	len;
	char	*d;

	len = ft_strnlen(s, n);
	d = malloc(sizeof(*d) * len + 1);
	if (!d)
		return (NULL);
	ft_memcpy(d, s, len);
	d[len] = '\0';
	return d;
}
