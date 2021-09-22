/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ugdaniel <ugdaniel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/17 16:31:22 by ugdaniel          #+#    #+#             */
/*   Updated: 2021/09/22 16:25:41 by ugdaniel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "_ft_string.h"

char	*ft_strjoin(const char *s1, const char *s2)
{
	unsigned int	i;
	char			*d;

	if (!s1 || !s2)
		return (NULL);
	d = malloc(sizeof(*d) * (ft_strlen(s1) + ft_strlen(s2)) + 1);
	if (!d)
		return (NULL);
	i = 0;
	while (*s1)
		d[i++] = *s1++;
	while (*s2)
		d[i++] = *s2++;
	d[i] = '\0';
	return (d);
}
