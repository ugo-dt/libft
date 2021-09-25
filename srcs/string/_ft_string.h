/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _ft_string.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ugdaniel <ugdaniel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/22 15:42:46 by ugdaniel          #+#    #+#             */
/*   Updated: 2021/09/25 20:34:09 by ugdaniel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef _FT_STRING_H
# define _FT_STRING_H

# include "_ft_mem.h"
# include <stdio.h>

/* string.h functions */

/* The ft_atoi() function converts the initial portion
 * of the string pointed to by str to int representation.
 */
int		ft_atoi(const char *str);

/* The ft_itoa() function converts an integer value to
 * a null-terminated string.
 */
char	*ft_itoa(int n);

/* The ft_strchr() function locates the first occurrence of the char cin the
 * string pointed to by s. The terminating null character is considered to
 * be part of the string; therefore if c is '\\0', the functions locate the
 * terminating '\\0'.
 */
char	*ft_strchr(const char *s, int c);

/* The ft_strcmp() and ft_strncmp() functions lexicographically compare the
 * null-terminated strings s1 and s2.
 * 
 * The ft_strncmp() function compares not more than n characters.
 * Because ft_strncmp() is designed for comparing strings rather than binary
 * data, characters that appear after a '\\0' character are not compared.
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

/* The ft_strcat() and function append a copy of the null-terminated
 * string s2 to the end of the null-terminated string s1, then add a terminating
 * '\\0'. The string s1 must have sufficient space to hold the result. 
 * 
 * The ft_strncat function appends not more than n characters from s2,
 * and then adds a terminating '\\0'.
 */
char	*ft_strcat(char *s1, const char *s2);
char	*ft_strncat(char *s1, const char *s2, size_t n);

/* The ft_strlcat() function appends the NUL-terminated
 * string src to the end of dst.
 * It will append at most size - ft_strlen(dst) - 1 bytes,
 * null-terminating the result.
 * 
 * The function returns the total length of the string it tried to create.
 */
size_t	ft_strlcat(char *dst, const char *src, size_t size);

/* The ft_strcpy() function copy the string src to dst
 * (including the terminating '\\0' character.)
 *
 * The ft_strncpy() function copy at most len characters from src into dst.
 * If src is less than len characters long, the remainder of dst is filled with
 * '\\0' characters. Otherwise, dst is not terminated. */
char	*ft_strcpy(char *dest, const char *src);
char	*ft_strncpy(char *s1, const char *s2, size_t n);

/* The ft_strlcpy() function copies up to size - 1 characters from
 * the NUL-terminated string src to dst, NUL-terminating the result.
*/
size_t	ft_strlcpy(char *dst, const char *src, size_t size);

/* The ft_strlen() function computes the length of the string s.
 *  
 * The ft_strnlen() function attempts to compute the length of s,
 * but never scans beyond the first maxlen bytes of s.
 */
size_t	ft_strlen(const char *s);
size_t	ft_strnlen(const char *s, size_t maxlen);

/* The ft_strnstr() function locates the first occurrence of the null-terminated
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

/* libft exclusive functions */

/* The ft_strmapi() applies the given function f to each character of the
 * string s to create a new string (with malloc(3))
 * resulting from successive applications of f.
 */
char	*ft_strmapi(const char *s, char (*f)(unsigned int, char));

char	*ft_substr(char *s, unsigned int start, size_t len);

char	*ft_strtrim(char *s1, char *set);

/* _FT_STRING_H */
#endif
