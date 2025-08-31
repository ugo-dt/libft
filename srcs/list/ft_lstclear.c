#include "libft/libft.h"

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
