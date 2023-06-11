/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dprintf.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ugdaniel <ugdaniel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/18 16:46:27 by ugdaniel          #+#    #+#             */
/*   Updated: 2023/06/11 22:19:00 by ugdaniel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "_libft_printf.h"

int	ft_dprintf_internal(int fd, const char *f, va_list *ap);

int	ft_dprintf(int fd, const char *restrict format, ...)
{
	int		done;
	va_list	ap;

	va_start(ap, format);
	done = ft_dprintf_internal(fd, format, &ap);
	va_end(ap);
	return (done);
}
