/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _ft_array.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ugdaniel <ugdaniel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/22 16:36:11 by ugdaniel          #+#    #+#             */
/*   Updated: 2021/09/23 08:46:02 by ugdaniel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef _FT_ARRAY_H
# define _FT_ARRAY_H

# include <stdlib.h>

/* Returns the size of an NULL terminated two-dimensional array. */
int		array_size(char **arr);

/* The free_array() function frees a two-dimensional array, starting
 * from the index 0 up to the first NULL encountered.
 * 
 * The free_array_size() function frees up to n elements from a
 * two-dimensional array. */
void	free_array(void **arr);
void	*free_array_size(void **tab, size_t n);

/* Converts a string to an array of strings,
 * split each time the character c is encountered. */
char	**ft_split(char *s, char c);

#endif /* _FT_ARRAY_H */
