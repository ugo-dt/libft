/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _libft_printf.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ugdaniel <ugdaniel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/22 12:25:07 by ugdaniel          #+#    #+#             */
/*   Updated: 2023/11/29 13:46:40 by ugdaniel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef _LIBFT_PRINTF_H
# define _LIBFT_PRINTF_H

# include "_libft_math.h"
# include "_libft_string.h"
# include <stdlib.h>
# include <stdarg.h>
# include <unistd.h>
# include <stddef.h>

# if defined(__linux__)
#  include <stdint.h>
# endif

# if !defined(BUFSIZ)
#  define BUFSIZ 1024
# endif

__extern_always_inline const unsigned char	*_ft__find_spec(const unsigned char *format)
{
	const unsigned char	*c = (const unsigned char *)ft_strchr((const char *)format, '%');
	if (!c)
		return format + ft_strlen((const char *)format);
	return (c);
}

/** Write formatted output to the file descriptor fd
 * from the format string FORMAT.
 * @returns The number of written characters. */
int			ft_dprintf(int fd, const char *restrict format, ...) \
	__attribute__((__format__ (__printf__, 2, 3)));

/** Write formatted output to stdout from the format string FORMAT.
 * @returns The number of written characters. */
int			ft_printf(const char *restrict format, ...) \
	__attribute__((__format__ (__printf__, 1, 2)));

#endif /* _LIBFT_PRINTF_H */
