#include "libft/libft.h"

void	ft_putstr(const char *restrict s)
{
	ft_putstr_fd(s, STDOUT_FILENO);
}
