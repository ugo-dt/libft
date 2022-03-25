/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _ft_write.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ugdaniel <ugdaniel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/22 15:40:43 by ugdaniel          #+#    #+#             */
/*   Updated: 2022/03/25 11:54:31 by ugdaniel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef _FT_WRITE_H
# define _FT_WRITE_H	1

# if !defined _LIBFT_HEADER
#  error "Do not include "_ft_write.h" directly. Use "libft.h" instead."
#  define _LIBFT_HEADER_IMPLEMENTATION
# endif

# include <unistd.h>

/* Write a character on the standard output. */
extern void	ft_putchar(char c);

/* Write a character on the file descriptor fd. */
extern void	ft_putchar_fd(char c, int fd);

/* Print a number on the standard output. */
extern void	ft_putnbr(int n);

/* Print a number on the file descriptor fd. */
extern void	ft_putnbr_fd(int n, int fd);

/* Print the string s on the standard output. */
extern void	ft_putstr(const char *restrict s);

/* Print the string s on the file descriptor fd. */
extern void	ft_putstr_fd(const char *s, int fd);

/* Print the string s followed by a newline, on the standard output. */
extern void	ft_putendl(const char *restrict s);

/* Print a string followed by a newline, on the file descriptor fd. */
extern void	ft_putendl_fd(const char *s, int fd);

#endif /* !defined _FT_WRITE_H */
