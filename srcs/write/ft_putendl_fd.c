/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putendl_fd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ugdaniel <ugdaniel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/18 14:38:08 by ugdaniel          #+#    #+#             */
/*   Updated: 2021/09/23 17:53:10 by ugdaniel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "_ft_write.h"

void	ft_putendl_fd(const char *s, int fd)
{
	if (s)
		while (*s)
			ft_putchar_fd(*s++, fd);
	ft_putchar_fd('\n', fd);
}
