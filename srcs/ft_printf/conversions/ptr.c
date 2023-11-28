/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ptr.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ugdaniel <ugdaniel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/18 15:39:36 by ugdaniel          #+#    #+#             */
/*   Updated: 2023/11/28 16:04:00 by ugdaniel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "_libft_printf.h"

ssize_t	ft_putstr_size(char *s, int fd);
ssize_t	ft_puthex_size(char x, unsigned int nb, int fd);

/** The function ft_putaddr_size() writes the address addr in hexadecimal
 * to the file descriptor fd.
 * @returns The number of characters written. */
ssize_t	ft_putaddr_size(size_t addr, int fd)
{
	return (ft_putstr_size("0x\0", fd) + ft_puthex_size('x', addr, fd));
}
