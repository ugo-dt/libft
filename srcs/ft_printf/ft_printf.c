/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ugdaniel <ugdaniel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/18 11:48:29 by ugdaniel          #+#    #+#             */
/*   Updated: 2023/06/11 22:18:57 by ugdaniel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "_libft_printf.h"

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
