#include "libft.h"

char	*ft_strtrim(char *s1, char *set)
{
	size_t	size_s;
	char	*dest;

	if (!s1 || !set)
		return (NULL);
	while (*s1 && ft_strchr(set, *s1))
		s1++;
	size_s = ft_strlen(s1);
	while (size_s && ft_strchr(set, s1[size_s]))
		size_s--;
	dest = ft_substr(s1, 0, size_s + 1);
	return (dest);
}
