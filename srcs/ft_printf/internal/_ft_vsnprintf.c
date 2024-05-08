/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _ft_vsnprintf.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ugdaniel <ugdaniel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/05 20:33:46 by ugdaniel          #+#    #+#             */
/*   Updated: 2024/05/08 16:55:25 by ugdaniel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "conversions/_conversions.h"
	
int	ft_vsnprintf_internal(char *string, size_t maxlen, const char *format, va_list ap)
{
	unsigned char	*f;
	unsigned char	*lead_str_end;
	size_t			curlen;
	long			len;

	ft_memset(string, 0, maxlen);
	curlen = 0;
	f = lead_str_end = (unsigned char *)_ft_find_spec((const unsigned char *)format);
	len = min((const unsigned char *)lead_str_end - (const unsigned char *)format, (long)maxlen - 1);
	ft_strncat(string, format, len);
	curlen += len;
	while (*f != '\0' && curlen < maxlen)
	{
		if (*f != '%')
		{
			ft_strncat(string, (const char *)f++, 1);
			curlen++;
		}
		else
		{
			struct _specs specs = { 0 };

			FIND_FLAGS(f, specs);
			FIND_WIDTH(f, specs, ap);
			FIND_PRECISION(f, specs, ap);

			char	*s = NULL;
			DO_POSITIONAL(f, s, specs, ap);

			len = min(maxlen - 1 - curlen, specs.info.width + curlen);
			ft_strncat(string, s, len);
			free(s);
			curlen += len;

			f++;
		}
	}
	return (curlen);
}
