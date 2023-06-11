/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _char.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ugdaniel <ugdaniel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/22 12:19:26 by ugdaniel          #+#    #+#             */
/*   Updated: 2023/02/22 12:20:09 by ugdaniel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef _LIBFT_CHAR_H
# define _LIBFT_CHAR_H

/* The ft_islower() function tests for any lower-case letters */
int			ft_islower(int c);

/* The ft_isupper() function tests for any upper-case letter. */
int			ft_isupper(int c);

/* The ft_tolower() function converts an upper-case letter to the corresponding
 * lower-case letter. The argument must be representable as an unsigned char.*/
int			ft_tolower(int c);

/* The ft_toupper() function converts an lower-case letter to the corresponding
 * upper-case letter. The argument must be representable as an unsigned char.*/
int			ft_toupper(int c);

/** The ft_isalpha() function tests for any character
 * for which isupper(3) or islower(3) is true.
 *
 * @return Zero if the character tests false and non-zero if the
 * character tests true.
 */
int			ft_isalpha(int c);

/** The ft_isdigit() function tests for a decimal digit character. 
 *
 * This includes the following characters only:
 * '0', '1', '2', '3', '4', '5', '6', '7', '8', '9'
 * 
 * @return Zero if the character tests false and return non-zero if the
 * character tests true.
 */
int			ft_isdigit(int c);

/* The ft_isalnum() function tests for any character for which
 * ft_isalpha() or ft_isdigit() is true. */
int			ft_isalnum(int c);

/* The isascii() function tests for an ASCII character, which is any character
 * between 0 and decimal 127 inclusive. */
int			ft_isascii(int c);

/* The ft_isprint() function tests for any printing character,
 * including space (' '). */
int			ft_isprint(int c);

/* The ft_isspace() function tests for the white-space characters.
 * This includes the following standard characters:
 * '\\t'   '\\n'    '\\v'    '\\f'    '\\r'    ' ' */
int			ft_isspace(int c);

#endif // _LIBFT_CHAR_H
