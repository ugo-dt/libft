/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ugdaniel <ugdaniel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/18 17:01:59 by ugdaniel          #+#    #+#             */
/*   Updated: 2023/02/22 13:10:38 by ugdaniel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "_libft_list.h"

void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list	*temp;

	if (!lst || !(*lst))
		return ;
	while (*lst != NULL)
	{
		if (del)
			del((*lst)->content);
		temp = (*lst);
		(*lst) = (*lst)->next;
		free(temp);
	}
}
