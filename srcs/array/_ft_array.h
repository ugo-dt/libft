/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _ft_array.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ugdaniel <ugdaniel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/22 16:36:11 by ugdaniel          #+#    #+#             */
/*   Updated: 2021/10/01 16:10:46 by ugdaniel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef _FT_ARRAY_H
# define _FT_ARRAY_H	1

# include "_ft_write.h"
# include <stdlib.h>

/* Returns the size of an NULL terminated two-dimensional array. */
extern int	array_size(char **arr);

/* The free_array() function frees a each element from a two-dimensional array,
 * starting from the index 0 up to the first NULL element encountered. */
extern void	free_array(void **arr);

/* The free_array_n() function frees up to n elements from a
 * two-dimensional array, then frees the pointer to the array. */
extern void	*free_array_n(void **tab, size_t n);

/* 
 * The ft_split() function splits a string it into words, and returns them as
 * a NULL-terminated array of strings.
 * 
 * A "word" is defined as a part of a string delimited by the character c,
 * or by the start/end of the string.
 */
extern char	**ft_split(const char *s, char c);

/* Prints an array of strings*/
extern void	print_array_fd(const char **arr, int fd);

/* _FT_ARRAY_H */
#endif
