#include "libft.h"

char	*ft_strdup(const char *s)
{
	size_t	len;
	char	*d;

	len = ft_strlen(s) + 1;
	d = LIBFT_MALLOC(sizeof(*d) * len);
	if (!d)
		return (NULL);
	return (ft_memcpy(d, s, len));
}
