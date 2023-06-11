/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_len_to_space.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ugdaniel <ugdaniel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/03 12:51:29 by ugdaniel          #+#    #+#             */
/*   Updated: 2023/02/22 13:10:38 by ugdaniel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "_libft_string.h"

size_t	ft_len_to_space(const char *s)
{
	size_t	n;

	n = 0;
	while (s[n] && !ft_isspace(s[n]))
		n++;
	return (n);
}
