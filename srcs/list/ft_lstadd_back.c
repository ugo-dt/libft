#include "libft/libft.h"

void	ft_lstadd_back(t_list **lst, t_list *new_elem)
{
	t_list	*temp;

	temp = *lst;
	if (temp == NULL)
		*lst = new_elem;
	else
	{
		temp = *lst;
		while (temp->next != NULL)
			temp = temp->next;
		temp->next = new_elem;
	}
}
