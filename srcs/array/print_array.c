/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_array.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ugdaniel <ugdaniel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/28 14:05:00 by ugdaniel          #+#    #+#             */
/*   Updated: 2021/09/28 14:05:00 by ugdaniel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "_ft_array.h"

void	print_array_fd(const char **arr, int __fd)
{
	if (!arr || !(*arr))
		return ;
	while (*arr)
		ft_putstr_fd((*arr)++, __fd);
}
