/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ugdaniel <ugdaniel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/16 12:43:27 by ugdaniel          #+#    #+#             */
/*   Updated: 2023/02/22 13:10:38 by ugdaniel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "_libft_mem.h"

void	*ft_memcpy(void *restrict dst, const void *restrict src, size_t n)
{
	char	*d;
	char	*s;

	if (!src && !dst)
		return (NULL);
	d = (char *)dst;
	s = (char *)src;
	while (n-- > 0)
		*d++ = *s++;
	return (dst);
}
