/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ugdaniel <ugdaniel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/18 14:37:09 by ugdaniel          #+#    #+#             */
/*   Updated: 2021/10/01 11:05:29 by ugdaniel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "_ft_write.h"

void	ft_putstr_fd(const char *s, int fd)
{
	if (s)
		while (*s)
			ft_putchar_fd(*s++, fd);
}
