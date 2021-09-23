/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ugdaniel <ugdaniel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/23 20:04:05 by ugdaniel          #+#    #+#             */
/*   Updated: 2021/09/23 21:40:57 by ugdaniel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "_ft_string.h"

/*
 * The ft_strncat() function appends not more than n characters from s2,
 * and then adds a terminating '\\0'.
 */
char	*ft_strncat(char *s1, const char *s2, size_t n)
{
	char	*s;
	size_t	ss;

	s = s1;
	s1 += ft_strlen(s1);
	ss = ft_strnlen(s2, n);
	s1[ss] = '\0';
	ft_memcpy(s1, s2, ss);
	return (s);
}
