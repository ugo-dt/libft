#include "libft/libft.h"

void	ft_lstiter(t_list *lst, void (*f)(void *))
{
	t_list	*temp;

	temp = lst;
	while (temp != NULL)
	{
		if (f)
			f(temp->content);
		temp = temp->next;
	}
}
