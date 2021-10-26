/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _ft_printf.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ugdaniel <ugdaniel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/08 17:07:00 by ugdaniel          #+#    #+#             */
/*   Updated: 2021/10/26 22:07:00 by ugdaniel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* The ft_printf function is a basic recreation of printf. */

#ifndef _FT_PRINTF_H
# define _FT_PRINTF_H	1

# ifndef _LIBFT_HEADER_IMPLEMENTATION
#  error "Do not include <_ft_printf.h> directly. Use <libft.h> instead."
#  define _LIBFT_HEADER_IMPLEMENTATION
# endif

extern int	ft_dprintf(int fd, const char *format, ...);
extern int	ft_printf(const char *format, ...);

#else
# ifndef _LIBFT_HEADER_IMPLEMENTATION
#  error "Do not include <_ft_printf.h> directly. Use <libft.h> instead."
#  define _LIBFT_HEADER_IMPLEMENTATION
# endif

/* _FT_PRINTF_H */
#endif
