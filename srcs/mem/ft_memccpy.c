#include "libft.h"

void	*ft_memccpy(void *dest, const void *src, int c, size_t n)
{
	unsigned char	*d;
	unsigned char	*s;

	if (!dest && !src)
		return (NULL);
	d = (unsigned char *)dest;
	s = (unsigned char *)src;
	while (n-- > 0)
	{
		*d++ = *s;
		if (*s++ == (unsigned char)c)
			return (d);
	}
	return (NULL);
}
