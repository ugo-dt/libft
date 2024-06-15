/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _libft_printf.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ugdaniel <ugdaniel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/22 12:25:07 by ugdaniel          #+#    #+#             */
/*   Updated: 2024/06/15 15:57:01 by ugdaniel         ###   ########.fr       */
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

# ifdef __cplusplus
extern "C" {
# endif

/* Maximum chars of output to write in MAXLEN.  */
int	ft_snprintf(char *str, size_t maxlen, const char *restrict format, ...)
	__attribute__ ((__format__ (__printf__, 3, 4)));

/** Write formatted output to the file descriptor fd
 * from the format string FORMAT.
 * @returns The number of written characters. */
int	ft_dprintf(int fd, const char *restrict format, ...) \
	__attribute__((__format__ (__printf__, 2, 3)));

/** Write formatted output to stdout from the format string FORMAT.
 * @returns The number of written characters. */
int	ft_printf(const char *restrict format, ...) \
	__attribute__((__format__ (__printf__, 1, 2)));

# ifdef __cplusplus
}
# endif

#endif /* _LIBFT_PRINTF_H */
