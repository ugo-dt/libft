#include "libft.h"

char	*ft_strmapi(const char *s, char (*f)(unsigned int, char))
{
	char			*d;
	unsigned int	i;

	if (!s)
		return (NULL);
	d = LIBFT_MALLOC(sizeof(*d) * ft_strlen(s) + 1);
	if (!d)
		return (NULL);
	i = 0;
	while (s[i] != '\0')
	{
		d[i] = f(i, s[i]);
		i++;
	}
	d[i] = '\0';
	return (d);
}
