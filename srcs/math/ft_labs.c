#include "libft.h"

long	ft_labs(long x)
{
	if (x < 0)
		return (-x);
	return (x);
}
