/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ugdaniel <ugdaniel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/18 11:48:29 by ugdaniel          #+#    #+#             */
/*   Updated: 2022/04/28 11:00:49 by ugdaniel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_dprintf_internal(int fd, const char *f, va_list *ap);

int	ft_printf(const char *restrict format, ...)
{
	int		done;
	va_list	ap;

	va_start(ap, format);
	done = ft_dprintf_internal(STDOUT_FILENO, format, &ap);
	va_end(ap);
	return (done);
}
