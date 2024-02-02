/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   char.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ugdaniel <ugdaniel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/18 12:06:10 by ugdaniel          #+#    #+#             */
/*   Updated: 2024/02/02 11:41:38 by ugdaniel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "_libft_printf.h"

/** The function _ft_printf_out_c() writes the character c to the file descriptor
 * fd.
 * @returns The number of characters written. */
ssize_t	_ft_printf_out_c(char c, int fd)
{
	return (write(fd, &c, sizeof(c)));
}
