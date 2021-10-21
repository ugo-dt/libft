/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _ft_printf.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ugdaniel <ugdaniel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/08 17:07:00 by ugdaniel          #+#    #+#             */
/*   Updated: 2021/10/21 20:25:15 by ugdaniel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef _FT_PRINTF_H
# define _FT_PRINTF_H	1

# ifndef _LIBFT_HEADER_IMPLEMENTATION
#  error "Do not include <_ft_printf.h> directly. Use <libft.h> instead."
#  define _LIBFT_HEADER_IMPLEMENTATION
# endif

# include "_ft_write.h"
# include "_ft_string.h"
# include <stdarg.h>

extern int	ft_dprintf(int fd, const char *format, ...);
extern int	ft_printf(const char *format, ...);

#else
# ifndef _LIBFT_HEADER_IMPLEMENTATION
#  error "Do not include <_ft_printf.h> directly. Use <libft.h> instead."
#  define _LIBFT_HEADER_IMPLEMENTATION
# endif

/* _FT_PRINTF_H */
#endif
