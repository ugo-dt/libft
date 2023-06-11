/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _libft_string.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ugdaniel <ugdaniel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/22 12:31:02 by ugdaniel          #+#    #+#             */
/*   Updated: 2023/02/22 12:50:00 by ugdaniel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef _LIBFT_STRING_H
# define _LIBFT_STRING_H

# include "_libft_char.h"
# include "_libft_math.h"
# include "_libft_mem.h"
# include <stdlib.h>

/* The ft_atoi() function converts the initial portion
 * of the string pointed by str to an int representation. */
int			ft_atoi(const char *str);

/* The ft_itoa() function converts an integer value to
 * a null-terminated string. */
char		*ft_itoa(int n);

/* Returns the length from s to the next character c
 * or the next '\\0' character. */
size_t		ft_len_to_char(const char *s, char c);

/* Returns the length from s to the next space character (using ft_isspace())
 * or the next '\\0' character. */
size_t		ft_len_to_space(const char *s);

/* The ft_str_tolower() function converts each uppercase letter to the 
 * corresponding lowercase letter in the null-terminated string s. */
void		ft_str_tolower(char *s);

/* The ft_str_toupper() function converts each lowercase letter to the 
 * corresponding uppercase letter in the null-terminated string s. */
void		ft_str_toupper(char *s);

/** 
 * The ft_strcmp() and ft_strncmp() functions lexicographically compare the
 * null-terminated strings s1 and s2.
 * 
 * @returns 0 if the strings are identical.
 */
int			ft_strcmp(const char *s1, const char *s2);

/** 
 * The ft_strcmp() and ft_strncmp() functions lexicographically compare the
 * null-terminated strings s1 and s2.
 * 
 * The ft_strncmp() function compares not more than n characters.
 * Because ft_strncmp() is designed for comparing strings rather than binary
 * data, characters that appear after a '\\0' character are not compared.
 * 
 * @returns 0 if the strings are identical.
 */
int			ft_strncmp(const char *s1, const char *s2, size_t n);

/* 
 * The ft_strdup() function allocates sufficient memory for a copy of the string
 * s1, does the copy, and returns a pointer to it. The pointer may subsequently
 * be used as an argument tothe function free(3).
 * 
 * If insufficient memory is available, NULL is returned.
 */
char		*ft_strdup(const char *s);

/* 
 * The ft_strndup() function allocates sufficient memory for a copy of the string
 * s1, does the copy, and returns a pointer to it. The pointer may subsequently
 * be used as an argument tothe function free(3).
 * 
 * The function copies at most n characters from the string s1 and always
 * NULL-terminates the copied string.
 * 
 * If insufficient memory is available, NULL is returned.
 */
char		*ft_strndup(const char *s, size_t n);

/* 
 * The ft_strjoin() function appends the string s2 to the end of s1,
 * overwriting the terminating null character ('\\0') at the end of s1,
 * then adds a terminating null character.
 * 
 * If either of the strings is NULL, the function returns NULL.
 * 
 * Memory for the new string is obtained with malloc(3),
 * and can be freed with free(3);
 */
char		*ft_strjoin(const char *s1, const char *s2);

/* 
 * The ft_strjoin_3() function appends a copy of the null-terminated strings
 * s2 and s3 to the end of the null-terminated string s1, overwriting the
 * terminating null character ('\\0') at the end of s1, then adds a
 * terminating null character.
 * 
 * If one of the strings is NULL, the function returns NULL.
 * 
 * Memory for the new string is obtained with malloc(3),
 * and can be freed with free(3);
 */
char		*ft_strjoin_3(const char *s1, const char *s2, const char *s3);

/* 
 * The ft_strcat() and function append a copy of the null-terminated
 * string s2 to the end of the null-terminated string s1, then add a terminating
 * '\\0'. The string s1 must have sufficient space to hold the result.
 */
char		*ft_strcat(char *s1, const char *s2);

/* 
 * The ft_strcat() and function append a copy of the null-terminated
 * string s2 to the end of the null-terminated string s1, then add a terminating
 * '\\0'. The string s1 must have sufficient space to hold the result. 
 * 
 * The ft_strncat function appends not more than n characters from s2,
 * and then adds a terminating '\\0'.
 */
char		*ft_strncat(char *s1, const char *s2, size_t n);

/* 
 * The ft_strlcat() function appends the NUL-terminated
 * string src to the end of dst.
 * It will append at most size - ft_strlen(dst) - 1 bytes,
 * null-terminating the result.
 * 
 * The function returns the total length of the string it tried to create.
 */
size_t		ft_strlcat(char *dst, const char *src, size_t size);

/* The ft_strcpy() function copy the string src to dst
 * (including the terminating '\\0' character.) */
char		*ft_strcpy(char *dest, const char *src);

/* 
 * The ft_strncpy() function copy the string src to dst
 * (including the terminating '\\0' character.)
 *
 * The function copy at most len characters from src into dst.
 * If src is less than n characters long, the remainder of dst is filled with
 * '\\0' characters. Otherwise, dst is not terminated.
 */
char		*ft_strncpy(char *s1, const char *s2, size_t n);

/* The ft_strlcpy() function copies up to size - 1 characters from
 * the NUL-terminated string src to dst, NUL-terminating the result. */
size_t		ft_strlcpy(char *dst, const char *src, size_t size);

/* The ft_strlen() function computes the length of the string s. */
size_t		ft_strlen(const char *s);

/* The ft_strnlen() function attempts to compute the length of s,
 * but never scans beyond the first maxlen bytes of s. */
size_t		ft_strnlen(const char *s, size_t maxlen);

/* 
 * The ft_strnstr() function locates the first occurrence of the null-terminated
 * string needle in the string haystack, where not more than len characters are
 * searched. Characters that appear after a '\\0' character are not searched.
 */
char		*ft_strnstr(const char *haystack, const char *needle, size_t n);

/* 
 * The ft_strchr() function locates the first occurrence of the char c in the
 * string pointed to by s. The terminating null character is considered to be
 * part of the string; therefore if c is '\\0', the function locates the
 * terminating '\\0'.
 * 
 * The function returns NULL if it cannot find the character c in the string s.
 */
char		*ft_strchr(const char *s, int c);

/* 
 * The ft_strchr() function locates the first occurrence of the char c in the
 * string pointed to by s. The terminating null character is considered to be
 * part of the string; therefore if c is '\\0', the function locates the
 * terminating '\\0'.
 * 
 * The function returns NULL if it cannot find the character c in the string s.
 *
 * The ft_strrchr() function is identical to ft_strchr(),
 * except it locates the last occurrence of c.
 */
char		*ft_strrchr(const char *s, int c);

/* 
 * The ft_strmapi() applies the given function f to each character of the
 * string s to create a new string (with malloc(3))
 * resulting from successive applications of f.
 */
char		*ft_strmapi(const char *s, char (*f)(unsigned int, char));

/* 
 * The ft_substr() function allocates memory with malloc(3) then returns a
 * string of len characters (or up to the first '\\0' encountered), and starting
 * from index start of s.
 */
char		*ft_substr(char *s, unsigned int start, size_t len);

/*
 * The ft_strtrim() function allocates memory with malloc(3) then returns the
 * same string as s1, without the characters specified in set, at the start
 * and at the end of s1.
 */
char		*ft_strtrim(char *s1, char *set);

#endif /* _LIBFT_STRING_H */