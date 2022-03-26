/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ulong.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ugdaniel <ugdaniel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/18 15:56:35 by ugdaniel          #+#    #+#             */
/*   Updated: 2022/03/26 13:10:30 by ugdaniel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

#if !defined ASCII_0
# define ASCII_0	48
#endif 

ssize_t	ft_putchar_len(char c, int fd);

ssize_t	ft_putulong_len(size_t nb, int fd)
{
	int		done;

	done = 0;
	if (nb < 10)
		done += ft_putchar_len(nb + ASCII_0, fd);
	else
	{
		done += ft_putulong_len(nb / 10, fd);
		done += ft_putulong_len(nb % 10, fd);
	}
	return (done);
}
