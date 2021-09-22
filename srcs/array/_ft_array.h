/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _ft_array.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ugdaniel <ugdaniel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/22 16:36:11 by ugdaniel          #+#    #+#             */
/*   Updated: 2021/09/22 19:17:47 by ugdaniel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef _FT_ARRAY_H
# define _FT_ARRAY_H

# include <stdlib.h>

/* The free_array() function frees a two-dimensional array, starting
 * from the index 0 up to the first NULL encountered.
 * 
 * The free_array_size() function frees up to n elements from a
 * two-dimensional array. */
void	free_array(void **arr);
void	*free_array_size(void **tab, size_t n);

char	**ft_split(char *s, char c);

#endif /* _FT_ARRAY_H */
