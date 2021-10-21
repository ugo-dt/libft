/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin_3.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ugdaniel <ugdaniel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/29 12:18:38 by ugdaniel          #+#    #+#             */
/*   Updated: 2021/10/21 19:48:54 by ugdaniel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin_3(const char *a, const char *b, const char *c)
{
	unsigned int	i;
	char			*d;

	if (!a || !b || !c)
		return (NULL);
	d = malloc(sizeof(char) * (ft_strlen(a) + ft_strlen(b) + ft_strlen(c)) + 1);
	if (!d)
		return (NULL);
	i = 0;
	while (*a)
		d[i++] = *a++;
	while (*b)
		d[i++] = *b++;
	while (*c)
		d[i++] = *c++;
	d[i] = '\0';
	return (d);
}
