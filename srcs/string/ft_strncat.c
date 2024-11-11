#include "libft.h"

char	*ft_strncat(char *restrict s1, const char *restrict s2, size_t n)
{
	char	*s;
	size_t	ss;

	s = s1;
	s1 += ft_strlen(s1);
	ss = ft_strnlen(s2, n);
	s1[ss] = '\0';
	ft_memcpy(s1, s2, ss);
	return (s);
}
