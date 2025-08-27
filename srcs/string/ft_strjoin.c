#include "libft.h"

char	*ft_strjoin(const char *s1, const char *s2)
{
	char			*d;

	if (!s1 || !s2)
		return (NULL);
	d = malloc(sizeof(*d) * (ft_strlen(s1) + ft_strlen(s2)) + 1);
	if (!d)
		return (NULL);
	return (ft_strcat(ft_strcpy(d, s1), s2));
}
