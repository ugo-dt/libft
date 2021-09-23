/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _ft_write.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ugdaniel <ugdaniel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/22 15:40:43 by ugdaniel          #+#    #+#             */
/*   Updated: 2021/09/23 17:53:28 by ugdaniel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef _FT_WRITE_H
# define _FT_WRITE_H

# include <unistd.h>

/* Print a character to the file descriptor fd. */
void	ft_putchar_fd(const char c, int fd);

/* Print a string to the file descriptor fd */
void	ft_putstr_fd(const char *s, int fd);

/* Print a string followed by a newline, to the file descriptor fd. */
void	ft_putendl_fd(const char *s, int fd);

/* Print a number to the file descriptor fd. */
void	ft_putnbr_fd(int n, int fd);

#endif /* _FT_WRITE_H */