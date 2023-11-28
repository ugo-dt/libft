/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _libft_list.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ugdaniel <ugdaniel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/22 12:20:30 by ugdaniel          #+#    #+#             */
/*   Updated: 2023/11/28 20:22:12 by ugdaniel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef _LIBFT_LIST_H
# define _LIBFT_LIST_H

# include <stdlib.h>

/**
 * struct s_list
 * 
 * @param content Pointer to any type of data;
 * @param next The address of the next link of the list (NULL if last).
 */
typedef struct s_list
{
	void			*content;
	struct s_list	*next;
}t_list;

/** Adds a new element at the end of the list.
 * 
 * @param lst The first element of the list.
 */
void		ft_lstadd_back(t_list **lst, t_list *new);

/** Adds a new element at the start of the list.
 * 
 * @param lst The first element of the list. Can be NULL. 
 * @param new The new element to be added at the front of the list. Can be NULL.
 */
void		ft_lstadd_front(t_list **lst, t_list *new);

/** Clears a linked list.
 * 
 * @param lst The first element of the list. Can be NULL.
 * @param del The function to delete the contents of the element. Can be NULL.
 */
void		ft_lstclear(t_list **lst, void (*del)(void *));

/** Deletes an element, without relinking the list.
 *
 * @param lst The element to be deleted. Can be NULL.
 * @param del The function to delete the contents of the element. Can be NULL.
 */
void		ft_lstdelone(t_list *lst, void (*del)(void *));

/** Applies the function f to each element in the list. 
 *
 * @param lst The first element of the list. Can be NULL.
 * @param f The function to apply to each element. Can be NULL.
 */
void		ft_lstiter(t_list *lst, void (*f)(void *));

/** 
 * @param lst The first element of the list. Can be NULL.
 *
 * @returns The address of the last element in a given list. */
t_list		*ft_lstlast(t_list *lst);

/** Creates a copy of the list with the function f applied to each element.
 * 
 * @param lst The first element of the list. Can be NULL.
 *
 * @returns A pointer to the first element of the copy. 
 */
t_list		*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *));

/** Creates a new t_list element.
 * 
 * @param content A pointer to any type of data. Can be NULL.
 *
 * @returns A pointer to the new element, or NULL if the allocation failed.
 */
t_list		*ft_lstnew(void *content);

/**
 * @param lst The first element of the list. Can be NULL.
 * 
 * @returns The numbers of elements in the list.
 */
int			ft_lstsize(t_list *lst);

#endif // _LIBFT_LIST_H
