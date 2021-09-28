/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _ft_array.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ugdaniel <ugdaniel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/22 16:36:11 by ugdaniel          #+#    #+#             */
/*   Updated: 2021/09/28 14:22:33 by ugdaniel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef _FT_ARRAY_H
# define _FT_ARRAY_H

# include "_ft_write.h"
# include <stdlib.h>

/* Returns the size of an NULL terminated two-dimensional array. */
int		array_size(char **arr);

/* 
 * The free_array() function frees a two-dimensional array, starting
 * from the index 0 up to the first NULL encountered.
 * 
 * The free_array_size() function frees up to n elements from a
 * two-dimensional array.
 */
void	free_array(void **arr);
void	*free_array_size(void **tab, size_t n);

/* 
 * The ft_split() function splits a string it into words, and returns them as
 * a NULL-terminated array of strings.
 * 
 * A "word" is defined as a part of a string delimited by the character c,
 * or by the start/end of the string.
 */
char	**ft_split(const char *s, char c);

/* Prints an array of strings*/
void	print_array_fd(const char **arr, int __fd);

/* _FT_ARRAY_H */
#endif
