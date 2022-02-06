/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_out_plus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ugdaniel <ugdaniel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/08 19:59:09 by ugdaniel          #+#    #+#             */
/*   Updated: 2022/02/06 11:46:40 by ugdaniel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#define _LIBFT_HEADER_IMPLEMENTATION	1
#include "_ft_printf.h"

static char	*get_temp(int size)
{
	char	*temp;

	temp = (char *)malloc(sizeof(char) * size + 1);
	if (!temp)
		return (NULL);
	ft_memset(temp, '0', size);
	temp[size] = '\0';
	return (temp);
}

static char	*add_zeros_int3(t_flags *flags, char *s, char *temp, char *dest)
{
	char	*temp2;
	char	*dest2;

	dest2 = dest;
	temp2 = ft_strdup(temp);
	if (dest[0] == '-')
	{
		if (flags->flags[FLAG_PREC])
		{
			dest[0] = '0';
			free(temp2);
			temp2 = ft_strjoin("-", temp);
		}
		else if (flags->width)
		{
			free(temp2);
			temp2 = ft_strjoin("-", temp);
			dest++;
		}
	}
	free(s);
	s = ft_strjoin(temp2, dest);
	free(temp2);
	free(dest2);
	return (s);
}

static char	*add_zeros_int2(t_flags *flags, int len, char *s, int size)
{
	char	*temp;

	temp = get_temp(size);
	if (!temp)
		return (s);
	if ((len < flags->precision || len < flags->width) && temp)
		s = add_zeros_int3(flags, s, temp, ft_strdup(s));
	free(temp);
	return (s);
}

char	*add_zeros_int(t_flags *flags, char *s)
{
	int		len;
	int		size;

	if (!s)
		return (NULL);
	if (flags->flags[FLAG_PREC])
		size = flags->precision - ft_strlen(s);
	else
		size = flags->width - ft_strlen(s);
	if (size < 0)
		size = -size;
	if ((flags->flags[FLAG_MINUS] || flags->flags[FLAG_LEFT])
		&& !flags->flags[FLAG_PREC])
		size = 0;
	if (flags->flags[FLAG_PREC] && flags->precision < flags->width
		&& flags->precision < (int)ft_strlen(s))
		return (s);
	len = ft_strlen(s);
	if (s[0] == '-')
		len--;
	return (add_zeros_int2(flags, len, s, size));
}
