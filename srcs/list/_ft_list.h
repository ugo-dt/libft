/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _ft_list.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ugdaniel <ugdaniel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/22 16:33:19 by ugdaniel          #+#    #+#             */
/*   Updated: 2021/09/25 20:33:54 by ugdaniel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef _FT_LIST_H
# define _FT_LIST_H

# include <stdlib.h>

typedef struct s_list
{
	void			*content;
	struct s_list	*next;
}t_list;

/* Adds a new element at the end of the list. */
void	ft_lstadd_back(t_list **lst, t_list *new);

/* Adds a new element at the start of the list. */
void	ft_lstadd_front(t_list **lst, t_list *new);

/* Clears the list.
 * @param lst first element of the list to be deleted;
 * @param del appropriate function to delete the contents of the element. */
void	ft_lstclear(t_list **lst, void (*del)(void *));

/* Deletes an element, without relinking the list.
 * @param lst element to be deleted;
 * @param del appropriate function to delete the contents of the element. */
void	ft_lstdelone(t_list *lst, void (*del)(void *));

/* Applies the function f to each element in the list. */
void	ft_lstiter(t_list *lst, void (*f)(void *));

/* Returns the address of the last element in a given list. */
t_list	*ft_lstlast(t_list *lst);

/* Creates a copy of the list with the function f applied to each element. */
t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *));

/* Creates a new element. */
t_list	*ft_lstnew(void *content);

/* Returns the numbers of elements in a list. */
int		ft_lstsize(t_list *lst);

/* _FT_LIST_H */
#endif
