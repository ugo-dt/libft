/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _libft_write.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ugdaniel <ugdaniel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/22 12:36:03 by ugdaniel          #+#    #+#             */
/*   Updated: 2024/06/15 15:56:52 by ugdaniel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef _LIBFT_WRITE_H
# define _LIBFT_WRITE_H

# include "_libft_math.h"
# include <unistd.h>

# ifdef __cplusplus
extern "C" {
# endif

/* Write a character on the standard output. */
void		ft_putchar(char c);

/* Write a character on the file descriptor fd. */
void		ft_putchar_fd(char c, int fd);

/* Print a number on the standard output. */
void		ft_putnbr(int n);

/* Print a number on the file descriptor fd. */
void		ft_putnbr_fd(int n, int fd);

/* Print the string s on the standard output. */
void		ft_putstr(const char *restrict s);

/* Print the string s on the file descriptor fd. */
void		ft_putstr_fd(const char *s, int fd);

/* Print the string s followed by a newline, on the standard output. */
void		ft_putendl(const char *restrict s);

/* Print a string followed by a newline, on the file descriptor fd. */
void		ft_putendl_fd(const char *s, int fd);

# ifdef __cplusplus
}
# endif

#endif // _LIBFT_WRITE_H
