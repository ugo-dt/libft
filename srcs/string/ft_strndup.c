#include "libft.h"

char	*ft_strndup(const char *s, size_t n)
{
	size_t	len;
	char	*d;

	len = ft_strlen(s) + 1;
	if (len > n)
		len = n;
	d = LIBFT_MALLOC(sizeof(*d) * len);
	if (!d)
		return (NULL);
	return (ft_memcpy(d, s, len));
}
