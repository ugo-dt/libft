#include "libft/libft.h"

char	*ft_strncpy(char *s1, const char *s2, size_t n)
{
	size_t	size;

	size = ft_strnlen(s2, n);
	if (size != n)
		ft_memset(s1 + size, '\0', n - size);
	return (ft_memcpy(s1, s2, size));
}
