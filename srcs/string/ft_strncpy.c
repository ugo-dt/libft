/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ugdaniel <ugdaniel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/23 20:06:56 by ugdaniel          #+#    #+#             */
/*   Updated: 2021/09/25 20:34:26 by ugdaniel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "_ft_string.h"

/*
 * The ft_strncpy() function copy at most len characters from src into dst.
 * If src is less than len characters long, the remainder of dst is filled with
 * '\\0' characters. Otherwise, dst is not terminated. */
char	*ft_strncpy(char *s1, const char *s2, size_t n)
{
	size_t	size;

	size = ft_strnlen(s2, n);
	if (size != n)
		ft_memset(s1 + size, '\0', n - size);
	return (ft_memcpy(s1, s2, size));
}
