#include "libft/libft.h"

void	ft_str_toupper(char *s)
{
	int		i;

	if (!s)
		return ;
	i = 0;
	while (s[i])
	{
		if (ft_islower(s[i]))
			s[i] = (char)ft_toupper(s[i]);
		i++;
	}
}
