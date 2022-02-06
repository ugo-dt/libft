/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _ft_printf.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ugdaniel <ugdaniel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/08 17:07:00 by ugdaniel          #+#    #+#             */
/*   Updated: 2022/02/06 11:40:11 by ugdaniel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* The ft_printf function is a basic recreation of printf. */

#ifndef _FT_PRINTF_H
# define _FT_PRINTF_H	1

# if !defined _LIBFT_HEADER_IMPLEMENTATION
#  error "Do not include "_ft_printf.h" directly. Use "libft.h" instead."
# endif

# include "_ft_char.h"
# include "_ft_mem.h"
# include "_ft_string.h"
# include "_ft_write.h"
# include <stdarg.h>
# include <stdlib.h>

# define NB_SPECS	8
# define NB_FLAGS	8

# define SPEC_CHAR	0
# define SPEC_STR	1
# define SPEC_PTR	2
# define SPEC_INT	3
# define SPEC_UINT	4
# define SPEC_HEX	5
# define SPEC_PCENT	6
# define SPEC_NONE	7

# define FLAG_ZERO	0
# define FLAG_MINUS	1
# define FLAG_PLUS	2
# define FLAG_SPACE	3
# define FLAG_HASH	4
# define FLAG_LEFT	5
# define FLAG_PREC	6
# define FLAG_UPPER	7

typedef struct s_flags
{
	unsigned int	specs[NB_SPECS];
	unsigned int	flags[NB_FLAGS];
	int				width;
	int				precision;
}t_flags;

extern int	ft_dprintf(int fd, const char *format, ...);
extern int	ft_printf(const char *format, ...);

/* _FT_PRINTF_H */
#endif
