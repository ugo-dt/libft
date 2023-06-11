/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _libft_array.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ugdaniel <ugdaniel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/22 12:18:04 by ugdaniel          #+#    #+#             */
/*   Updated: 2023/02/22 12:49:44 by ugdaniel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef _LIBFT_ARRAY_H
# define _LIBFT_ARRAY_H

# include "_libft_write.h"
# include "_libft_string.h"
# include <stdlib.h>

/* The ft_array_size() function returns the size of a NULL terminated
 * two-dimensional array. */
size_t		ft_array_size(void **arr);

/* The ft_free_array() function frees a each element from a two-dimensional
 * array, starting from index 0 up to the first NULL element encountered. */
void		ft_free_array(void **arr);

/* The ft_free_array_n() function frees up to n elements from a
 * two-dimensional array, then frees the pointer to the array. */
void		ft_free_array_n(void **tab, size_t n);

/*
 * The ft_copy_array() function returns a copy of the NULL-terminated
 * two-dimensional array arr. The function only copies up to the first
 * NULL encountered.
 * 
 * The memory for the copy is obtained using malloc(3),
 * and can be freed with free(3);
 */
char		**ft_copy_array(char **arr);

/* 
 * The ft_split() function splits a string it into words, and returns them as
 * a NULL-terminated array of strings.
 * 
 * A "word" is defined as a part of a string delimited by the character c,
 * or by the start/end of the string.
 * 
 * The memory for the array is obtained using malloc(3),
 * and can be freed with free(3);
 */
char		**ft_split(const char *s, char c);

/*
 * Print every string in the array arr, followed by a newline,
 * on the file descriptor fd.
 * 
 * The function stops at the first NULL string encountered.
 */
void		ft_print_array_fd(const char **arr, int fd);

/* Sort an array of strings using ft_strcmp(). */
void		ft_sort_array(char **array);

#endif // _LIBFT_ARRAY_H
