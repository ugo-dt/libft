/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   array_size.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ugdaniel <ugdaniel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/23 08:43:37 by ugdaniel          #+#    #+#             */
/*   Updated: 2021/09/29 13:42:48 by ugdaniel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "_ft_array.h"

int	array_size(char **arr)
{
	int		size;

	if (!arr || !(*arr))
		return (0);
	size = 0;
	while (arr[size])
		size++;
	return (size);
}
