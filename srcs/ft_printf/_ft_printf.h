/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _ft_printf.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ugdaniel <ugdaniel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/08 17:07:00 by ugdaniel          #+#    #+#             */
/*   Updated: 2021/10/01 15:45:53 by ugdaniel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef _FT_PRINTF_H
# define _FT_PRINTF_H	1

# include <stdarg.h>
# include "_ft_write.h"
# include "_ft_string.h"

extern int	ft_dprintf(int fd, const char *format, ...);
extern int	ft_printf(const char *format, ...);

/* _FT_PRINTF_H */
#endif
