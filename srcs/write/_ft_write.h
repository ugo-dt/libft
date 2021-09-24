/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _ft_write.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ugdaniel <ugdaniel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/22 15:40:43 by ugdaniel          #+#    #+#             */
/*   Updated: 2021/09/24 15:39:06 by ugdaniel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef _FT_WRITE_H
# define _FT_WRITE_H

# include <unistd.h>

/* Print the character c on the standard output. */
void	ft_putchar(const char c);

/* Print the  character c on the file descriptor fd. */
void	ft_putchar_fd(const char c, int fd);

/* Print the string s on the standard output. */
void	ft_putstr(const char *s);

/* Print the string s on the file descriptor fd. */
void	ft_putstr_fd(const char *s, int fd);

/* Print the string s followed by a newline, on the standard output. */
void	ft_putendl(const char *s);

/* Print a string followed by a newline, on the file descriptor fd. */
void	ft_putendl_fd(const char *s, int fd);

/* Print a number on the standard output. */
void	ft_putnbr(int n);

/* Print a number on the file descriptor fd. */
void	ft_putnbr_fd(int n, int fd);

#endif /* _FT_WRITE_H */
