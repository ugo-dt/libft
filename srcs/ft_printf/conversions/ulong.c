/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ulong.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ugdaniel <ugdaniel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/18 15:56:35 by ugdaniel          #+#    #+#             */
/*   Updated: 2024/02/02 13:00:52 by ugdaniel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "_libft_printf.h"

size_t	_ft_printf_out_c(char c, int fd);

size_t	_ft_printf_out_ul(unsigned long nb, int fd)
{
	int		done;

	done = 0;
	if (nb < 10)
		done += _ft_printf_out_c(nb + 48, fd);
	else
	{
		done += _ft_printf_out_ul(nb / 10, fd);
		done += _ft_printf_out_ul(nb % 10, fd);
	}
	return (done);
}

size_t	_ft_printf_out_ull(unsigned long long nb, int fd)
{
	int		done;

	done = 0;
	if (nb < 10)
		done += _ft_printf_out_c(nb + 48, fd);
	else
	{
		done += _ft_printf_out_ull(nb / 10, fd);
		done += _ft_printf_out_ull(nb % 10, fd);
	}
	return (done);
}
