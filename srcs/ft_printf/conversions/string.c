/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ugdaniel <ugdaniel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/18 11:56:58 by ugdaniel          #+#    #+#             */
/*   Updated: 2023/11/29 12:05:17 by ugdaniel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "_libft_printf.h"

/* The function _ft_printf_out_s() writes the string pointed to by s to the file
 * descriptor fd.
 * @returns The number of characters written. */
size_t	_ft_printf_out_s(const char *s, int fd)
{
	size_t	len;

	if (!s)
		return _ft_printf_out_s("(null)", fd);
	len = ft_strlen(s);
	return (write(fd, s, len));
}
