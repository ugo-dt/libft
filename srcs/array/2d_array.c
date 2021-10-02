/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   2d_array.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ugdaniel <ugdaniel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/23 08:43:37 by ugdaniel          #+#    #+#             */
/*   Updated: 2021/10/02 19:25:55 by ugdaniel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "_ft_array.h"

int	ft_array_size(char **arr)
{
	int		size;

	if (!arr || !(*arr))
		return (0);
	size = 0;
	while (arr[size])
		size++;
	return (size);
}

void	ft_free_array(void **arr)
{
	int		i;

	if (!arr)
		return ;
	i = -1;
	while (arr[++i])
	{
		free(arr[i]);
		arr[i] = NULL;
	}
	free(arr);
	arr = NULL;
}

void	*ft_free_array_n(void **tab, size_t n)
{
	size_t	i;

	i = 0;
	while (i < n)
		free(tab[i++]);
	free(tab);
	return (NULL);
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

char	**ft_copy_array(char **arr)
{
	size_t	i;
	size_t	size;
	char	**copy;

	size = ft_array_size(arr);
	copy = malloc(sizeof(char *) * (size + 1));
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
