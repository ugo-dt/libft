/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ugdaniel <ugdaniel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/17 14:41:36 by ugdaniel          #+#    #+#             */
/*   Updated: 2023/02/22 13:10:38 by ugdaniel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "_libft_string.h"

char	*ft_strdup(const char *s)
{
	size_t	len;
	char	*d;

	len = ft_strlen(s) + 1;
	d = malloc(sizeof(*d) * len);
	if (!d)
		return (NULL);
	return (ft_memcpy(d, s, len));
}
