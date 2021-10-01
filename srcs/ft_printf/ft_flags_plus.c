/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_flags_plus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ugdaniel <ugdaniel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/08 17:50:36 by ugdaniel          #+#    #+#             */
/*   Updated: 2021/10/01 15:30:37 by ugdaniel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "_ft_printf.h"

#define NB_SPECS	8
#define NB_FLAGS	8

#define SPEC_CHAR	0
#define SPEC_STR	1
#define SPEC_PTR	2
#define SPEC_INT	3
#define SPEC_UINT	4
#define SPEC_HEX	5
#define SPEC_PCENT	6
#define SPEC_NONE	7

#define FLAG_ZERO	0
#define FLAG_MINUS	1
#define FLAG_PLUS	2
#define FLAG_SPACE	3
#define FLAG_HASH	4
#define FLAG_LEFT	5
#define FLAG_PREC	6
#define FLAG_UPPER	7

typedef struct s_flags
{
	unsigned int	specs[NB_SPECS];
	unsigned int	flags[NB_FLAGS];
	int				width;
	int				precision;
}t_flags;

void	check_flags(t_flags *flags)
{
	if (flags->specs[SPEC_INT])
	{
		flags->specs[SPEC_PTR] = 0;
		flags->flags[FLAG_HASH] = 0;
		flags->flags[FLAG_PLUS] = 0;
		flags->flags[FLAG_SPACE] = 0;
	}
	if (flags->width < 0)
	{
		flags->flags[FLAG_LEFT] = 1;
		flags->width *= -1;
	}
	if (flags->specs[SPEC_HEX])
	{
		flags->specs[SPEC_INT] = 0;
		flags->specs[SPEC_UINT] = 0;
	}
	if (flags->flags[FLAG_MINUS])
		flags->flags[FLAG_ZERO] = 0;
}
