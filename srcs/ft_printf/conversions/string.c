/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ugdaniel <ugdaniel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/18 11:56:58 by ugdaniel          #+#    #+#             */
/*   Updated: 2023/11/28 20:08:54 by ugdaniel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "_libft_printf.h"

/* The function _ft_printf_out_s() writes the string pointed to by s to the file
 * descriptor fd.
 * @returns The number of characters written. */
size_t	_ft_printf_out_s(char *s, int fd)
{
	size_t	i;

	if (!s)
		return (write(fd, "(null)", 6));
	i = 0;
	while (s[i])
		write(fd, &s[i++], 1);
	return (i);
}
