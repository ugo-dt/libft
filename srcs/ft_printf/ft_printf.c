/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ugdaniel <ugdaniel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/18 11:48:29 by ugdaniel          #+#    #+#             */
/*   Updated: 2022/03/25 12:07:08 by ugdaniel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/* Write formatted output to stdout from the format string FORMAT.
 * @returns The number of written characters. */
int	ft_printf(const char *restrict format, ...)
{
	int		done;
	va_list	ap;

	va_start(ap, format);
	done = ft_dprintf_internal(STDOUT_FILENO, format, &ap);
	va_end(ap);
	return (done);
}
