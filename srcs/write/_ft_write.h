/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _ft_write.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ugdaniel <ugdaniel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/22 15:40:43 by ugdaniel          #+#    #+#             */
/*   Updated: 2021/10/01 19:24:01 by ugdaniel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef _FT_WRITE_H
# define _FT_WRITE_H	1

# include <unistd.h>

/* Write a character on the standard output. */
extern void	ft_putchar(char c);

/* Write a character on the file descriptor fd. */
extern void	ft_putchar_fd(char c, int fd);

/* Prints the string s on the standard output. */
extern void	ft_putstr(const char *s);

/* Prints the string s on the file descriptor fd. */
extern void	ft_putstr_fd(const char *s, int fd);

/* Prints the string s followed by a newline, on the standard output. */
extern void	ft_putendl(const char *s);

/* Prints a string followed by a newline, on the file descriptor fd. */
extern void	ft_putendl_fd(const char *s, int fd);

/* Prints a number on the standard output. */
extern void	ft_putnbr(int n);

/* Prints a number on the file descriptor fd. */
extern void	ft_putnbr_fd(int n, int fd);

/* _FT_WRITE_H */
#endif
