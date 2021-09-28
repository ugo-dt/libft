/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _ft_write.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ugdaniel <ugdaniel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/22 15:40:43 by ugdaniel          #+#    #+#             */
/*   Updated: 2021/09/28 14:18:33 by ugdaniel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef _FT_WRITE_H
# define _FT_WRITE_H

# include <unistd.h>

/* Prints the character c on the standard output. */
void	ft_putchar(const char c);

/* Prints the  character c on the file descriptor fd. */
void	ft_putchar_fd(const char c, int __fd);

/* Prints the string s on the standard output. */
void	ft_putstr(const char *s);

/* Prints the string s on the file descriptor fd. */
void	ft_putstr_fd(const char *s, int __fd);

/* Prints the string s followed by a newline, on the standard output. */
void	ft_putendl(const char *s);

/* Prints a string followed by a newline, on the file descriptor fd. */
void	ft_putendl_fd(const char *s, int __fd);

/* Prints a number on the standard output. */
void	ft_putnbr(int n);

/* Prints a number on the file descriptor fd. */
void	ft_putnbr_fd(int n, int __fd);

/* _FT_WRITE_H */
#endif
