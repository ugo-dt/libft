#include "libft.h"

void	ft_putendl(const char *restrict s)
{
	ft_putendl_fd(s, STDOUT_FILENO);
}
