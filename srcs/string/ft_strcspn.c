/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcspn.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ugdaniel <ugdaniel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/27 11:14:55 by ugdaniel          #+#    #+#             */
/*   Updated: 2024/07/27 11:53:18 by ugdaniel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strcspn(const char *s1, const char *s2)
{
	const char	*s;
	const char	*c;

	s = s1;
	while (*s1)
	{
		c = s2;
		while (*c)
		{
			if (*s1 == *c)
				break ;
			c++;
		}
		if (*c)
			break ;
		s1++;
	}
	return (s1 - s);
}
