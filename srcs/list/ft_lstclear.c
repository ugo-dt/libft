/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ugdaniel <ugdaniel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/18 17:01:59 by ugdaniel          #+#    #+#             */
/*   Updated: 2021/09/22 16:36:00 by ugdaniel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "_ft_list.h"

void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list	*temp;

	if (!del || !lst || !(*lst))
		return ;
	while (*lst != NULL)
	{
		del((*lst)->content);
		temp = (*lst);
		(*lst) = (*lst)->next;
		free(temp);
	}
}
