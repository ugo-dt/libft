/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_array.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ugdaniel <ugdaniel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/23 08:43:37 by ugdaniel          #+#    #+#             */
/*   Updated: 2024/07/26 13:08:30 by ugdaniel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_sort_array(char **array)
{
	int		i;
	char	*temp;

	i = 0;
	while (array[i + 1])
	{
		if (ft_strcmp(array[i], array[i + 1]) > 0)
		{
			temp = ft_strdup(array[i]);
			LIBFT_FREE(array[i]);
			array[i] = ft_strdup(array[i + 1]);
			LIBFT_FREE(array[i + 1]);
			array[i + 1] = ft_strdup(temp);
			LIBFT_FREE(temp);
			i = 0;
		}
		else
			i++;
	}
}

char	**ft_copy_array(char **arr)
{
	size_t	i;
	size_t	size;
	char	**copy;

	size = ft_array_size((void **)arr);
	copy = LIBFT_MALLOC(sizeof(char *) * (size + 1));
	if (!copy)
		return (NULL);
	i = 0;
	while (arr[i] && i < size)
	{
		copy[i] = ft_strdup(arr[i]);
		if (!copy[i])
		{
			ft_free_array_n((void **)copy, i);
			return (NULL);
		}
		i++;
	}
	copy[i] = NULL;
	return (copy);
}
