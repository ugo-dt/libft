/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ugdaniel <ugdaniel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/16 12:54:18 by ugdaniel          #+#    #+#             */
/*   Updated: 2022/02/06 11:46:40 by ugdaniel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#define _LIBFT_HEADER_IMPLEMENTATION	1
#include "_ft_mem.h"

void	*ft_memccpy(void *dest, const void *src, int c, size_t n)
{
	unsigned char	*d;
	unsigned char	*s;

	if (!dest && !src)
		return (NULL);
	d = (unsigned char *)dest;
	s = (unsigned char *)src;
	while (n-- > 0)
	{
		*d++ = *s;
		if (*s++ == (unsigned char)c)
			return (d);
	}
	return (NULL);
}
