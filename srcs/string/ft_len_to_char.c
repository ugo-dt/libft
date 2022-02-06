/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_len_to_char.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ugdaniel <ugdaniel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/02 14:48:19 by ugdaniel          #+#    #+#             */
/*   Updated: 2022/02/06 11:46:40 by ugdaniel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#define _LIBFT_HEADER_IMPLEMENTATION	1
#include "_ft_string.h"

size_t	ft_len_to_char(const char *s, char c)
{
	int	n;

	n = 0;
	while (s[n] && s[n] != c)
		n++;
	return (n);
}
