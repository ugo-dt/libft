#include "libft/libft.h"

static int	_ft_itoa_digits(unsigned int n)
{
	unsigned int	i;

	i = 0;
	while (n >= 10)
	{
		n /= 10;
		i++;
	}
	return (i + 1);
}

static int	_ft_itoa_get_nb(int n)
{
	if (n < 0)
		return (-n);
	return (n);
}

static char	*_ft_itoa_create_string(int len, int nb, int n)
{
	char	*dest;
	int		i;

	i = 0;
	dest = malloc(sizeof(*dest) * len + 1 + (nb < 0));
	if (dest)
	{
		if (n < 0)
		{
			dest[i] = '-';
			len++;
		}
		i = len - 1;
		while (nb >= 10)
		{
			dest[i] = nb % 10 + 48;
			nb /= 10;
			i--;
		}
		dest[i] = nb % 10 + 48;
		dest[len] = '\0';
	}
	return (dest);
}

char	*ft_itoa(int n)
{
	unsigned int	len;
	unsigned int	nb;

	nb = _ft_itoa_get_nb(n);
	len = _ft_itoa_digits(nb);
	return (_ft_itoa_create_string(len, nb, n));
}
