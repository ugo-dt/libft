/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ugdaniel <ugdaniel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/16 13:01:24 by ugdaniel          #+#    #+#             */
/*   Updated: 2024/07/26 13:09:30 by ugdaniel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	size_t	i;
	char	*d;
	char	*s;

	if (!dest && !src)
		return (NULL);
	d = (char *)dest;
	s = (char *)src;
	i = 0;
	if (d < s)
		while (n-- > 0)
			*d++ = *s++;
	else
		while (++i <= n)
			d[n - i] = s[n - i];
	return (dest);
}
