#include "libft/libft.h"

void	ft_str_tolower(char *s)
{
	int		i;

	if (!s)
		return ;
	i = 0;
	while (s[i])
	{
		if (ft_isupper(s[i]))
			s[i] = (char)ft_tolower(s[i]);
		i++;
	}
}
