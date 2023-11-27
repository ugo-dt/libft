/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _libft_printf.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ugdaniel <ugdaniel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/22 12:25:07 by ugdaniel          #+#    #+#             */
/*   Updated: 2023/11/27 19:45:50 by ugdaniel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef _LIBFT_PRINTF_H
# define _LIBFT_PRINTF_H

# include "_libft_math.h"
# include <stdlib.h>
# include <stdarg.h>
# include <unistd.h>

# ifndef ____FILE_defined
# define ____FILE_defined 1
struct _IO_FILE;
/* The opaque type of streams.  This is the definition used elsewhere.  */
typedef struct _IO_FILE FILE;
# endif

# if defined(__linux__)
#  include <stdint.h>
# endif

# if !defined(BUFSIZ)
#  define BUFSIZ 1024
# endif

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
