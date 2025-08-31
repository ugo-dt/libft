#include "libft/libft.h"

long double	ft_fabsl(long double x)
{
	if (x < 0)
		return (-x);
	return (x);
}
