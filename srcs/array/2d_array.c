/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   2d_array.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ugdaniel <ugdaniel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/10 11:26:05 by ugdaniel          #+#    #+#             */
/*   Updated: 2024/07/26 13:08:33 by ugdaniel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_array_size(void **arr)
{
	size_t	i;

	if (!arr || !(*arr))
		return (0);
	i = 0;
	while (arr[i])
		i++;
	return (i);
}

void	ft_free_array(void **arr)
{
	size_t	i;

	if (!arr)
		return ;
	i = 0;
	while (arr[i])
	{
		LIBFT_FREE(arr[i]);
		arr[i] = NULL;
		i++;
	}
	LIBFT_FREE(arr);
	arr = NULL;
}

void	ft_free_array_n(void **tab, size_t n)
{
	size_t	i;

	i = 0;
	while (i < n)
		LIBFT_FREE(tab[i++]);
	LIBFT_FREE(tab);
}

void	ft_print_array_fd(const char **arr, int fd)
{
	int		i;

	if (!arr)
		return ;
	i = 0;
	while (arr[i])
		ft_putendl_fd(arr[i++], fd);
}
