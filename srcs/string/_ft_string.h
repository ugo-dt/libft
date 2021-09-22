/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _ft_string.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ugdaniel <ugdaniel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/22 15:42:46 by ugdaniel          #+#    #+#             */
/*   Updated: 2021/09/22 19:53:05 by ugdaniel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef _FT_STRING_H
# define _FT_STRING_H

# include "../mem/_ft_mem.h"

/* The ft_atoi() function converts the initial portion
 * of the string pointed to by str to int representation.
 *
 * The ft_itoa() function converts an integer value to
 * a null-terminated string.
 */
int		ft_atoi(const char *str);
char	*ft_itoa(int n);

/* The ft_strchr() function locates the first occurrence of the char cin the
 * string pointed to by s. The terminating null character is considered to
 * be part of the string; therefore if c is '\\0', the functions locate the
 * terminating '\\0'.
 */
char	*ft_strchr(const char *s, int c);

/* The ft_strcmp() and ft_strncmp() functions lexicographically compare the
 * null-terminated strings s1 and s2.
 */
int		ft_strcmp(const char *s1, const char *s2);
int		ft_strncmp(const char *s1, const char *s2, size_t n);

/* The ft_strdup() function allocates sufficient memory for a copy of the string
 * s1, does the copy, and returns a pointer to it. The pointer may subsequently
 * be used as an argument tothe function free(3).
 * 
 * If insufficient memory is available, NULL is returned.
 *
 * The ft_strndup() function copies at most n characters from the string s1
 * always null-terminating the copied string.
 */
char	*ft_strdup(const char *s);
char	*ft_strndup(const char *s, size_t n);

/* The ft_strjoin() function appends the src string to the dest string,
 * overwriting the terminating null byte ('\0') at the end of dest,
 * and then adds a terminating null byte.
 * 
 * If either of the strings is NULL, the function returns NULL.
 * 
 * Memory for the new string is obtained with malloc(3),
 * and can be freed with free(3);
 */
char	*ft_strjoin(const char *s1, const char *s2);

/* The ft_strlcat() function appends the NUL-terminated
 * string src to the end of dst.
 * It will append at most size - ft_strlen(dst) - 1 bytes,
 * null-terminating the result.
 */
size_t	ft_strlcat(char *dst, const char *src, size_t size);

/* The ft_strlcpy() function copies up to size - 1 characters from
 * the NUL-terminated string src to dst, NUL-terminating the result.
*/
size_t	ft_strlcpy(char *dst, const char *src, size_t size);

/* The ft_strlen() function computes the length of the string s. 
 * The ft_strnlen() function attempts to compute the length of s,
 * but never scans beyond the first maxlen bytes of s.
 */
size_t	ft_strlen(const char *s);
size_t	ft_strnlen(const char *s, size_t maxlen);

/* The ft_strmapi() applies the given function f to each character of the
 * string s to create a new string (with malloc(3))
 * resulting from successive applications of f.
 */
char	*ft_strmapi(const char *s, char (*f)(unsigned int, char));

/* The ft_strstr() function locates the first occurrence of the null-terminated
 * string needle in the null-terminated string haystack.
 *
 * The ft_strnstr() function locates the first occurrence of the null-terminated
 * string needle in the string haystack, where not more than len characters are
 * searched. Characters that appear after a '\\0' character are not searched.
 */
char	*ft_strnstr(const char *haystack, const char *needle, size_t len);

/* The ft_strchr() function locates the first occurrence of the char c in the
 * string pointed to by s. The terminating null character is considered to be
 * part of the string; therefore if c is '\\0', the functions locate the
 * terminating '\\0'.
 * 
 * The ft_strrchr() function is identical to ft_strchr(),
 * except it locates the last occurrence of c.
 */
char	*ft_strchr(const char *s, int c);
char	*ft_strrchr(const char *s, int c);

char	*ft_strtrim(char *s1, char *set);
char	*ft_substr(char *s, unsigned int start, size_t len);

#endif /* _FT_STRING_H */
