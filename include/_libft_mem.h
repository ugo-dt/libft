/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _libft_mem.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ugdaniel <ugdaniel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/22 12:33:12 by ugdaniel          #+#    #+#             */
/*   Updated: 2024/06/15 15:57:03 by ugdaniel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef _LIBFT_MEM_H
# define _LIBFT_MEM_H

# include <stdlib.h>

# ifdef __cplusplus
extern "C" {
# endif

/* The ft_bzero() function writes n zeroed bytes to the string s.
 * If n is zero, ft_bzero() does nothing. */
void		ft_bzero(void *s, size_t n);

/* The ft_calloc() function allocates enough space for count objects
 * that are size bytes of memory each and returns a pointer to the allocated
 * memory.  The allocated memory is filled with bytes of value zero. */
void		*ft_calloc(size_t count, size_t size);

/* The ft_memccpy() function copies bytes from string src to string dst. 
 * If the character c (converted to an unsigned char) occurs in the string
 * src, the copy stops and a pointer to the byte after the copy of c in the
 * string dst is returned. Otherwise, n bytes are copied, and a NULL pointer is
 * returned.
 *
 * The source and destination strings should not overlap,
 * as the behavior is undefined. */
void		*ft_memccpy(void *dest, const void *src, int c, size_t n);

/* The ft_memchr() function locates the first occurrence of c
 * (as converted to an unsigned char) in the string s. */
void		*ft_memchr(const void *s, int c, size_t n);

/* The ft_memcmp() function compares byte string s1 against byte string s2.
 * Both strings are assumed to be n bytes long. */
int			ft_memcmp(const void *s1, const void *s2, size_t n);

/* The memmove() function copies len bytes from string src to string dst.
 * The two strings may overlap; the copy is always done in a non-destructive
 * manner. */
void		*ft_memmove(void *dest, const void *src, size_t n);

/* The ft_memcpy() function copies n bytes from memory area src to memory
 * area dst. If dst and src overlap, behavior is undefined. Applications in
 * which dst and src might overlap should use ft_memmove instead. */
void		*ft_memcpy(void *restrict dst, const void *restrict src, size_t n);

/* The ft_memset() function writes len bytes of value c (converted to an
 * unsigned char) to the string s. */
void		*ft_memset(void *s, int c, size_t n);

# ifdef __cplusplus
}
# endif

#endif // _LIBFT_MEM_H
