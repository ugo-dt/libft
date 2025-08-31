#include "libft/libft.h"

long long	ft_llabs(long long i)
{
	if (i < 0)
		return (-i);
	return (i);
}
