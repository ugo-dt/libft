/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ugdaniel <ugdaniel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/18 12:05:25 by ugdaniel          #+#    #+#             */
/*   Updated: 2021/09/22 15:56:51 by ugdaniel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "_ft_array.h"

static unsigned int	words(char *s, char c)
{
	int		i;
	int		words;

	i = 0;
	while (s[i] && s[i] == c)
		i++;
	words = 0;
	while (s[i])
	{
		if (s[i] == c)
			i++;
		else
		{
			words++;
			while (s[i] != c && s[i])
				i++;
		}
	}
	return (words);
}

static int	len_to_sep(char *s, char c, unsigned int i)
{
	int		len;

	len = 0;
	while (s[i + len] && s[i + len] != c)
		len++;
	return (len);
}

static void	*free_tab(char **tab, unsigned int max)
{
	unsigned int		i;

	i = 0;
	while (i < max)
		free(tab[i++]);
	free(tab);
	return (NULL);
}

char	**ft_split(char *s, char c)
{
	char			**tab;
	unsigned int	i;
	unsigned int	j;
	unsigned int	k;

	tab = malloc(sizeof(*tab) * (words(s, c) + 1));
	if (!s || !tab)
		return (NULL);
	i = 0;
	j = 0;
	while (i < words(s, c))
	{
		while (s[j] == c && s[j])
			j++;
		tab[i] = malloc(sizeof(*tab[i]) * len_to_sep(s, c, j) + 1);
		if (!tab[i])
			return (free_tab(tab, i));
		k = 0;
		while (s[j] && s[j] != c)
			if (s[j] != c)
				tab[i][k++] = s[j++];
		tab[i++][k] = '\0';
	}
	tab[i] = NULL;
	return (tab);
}
