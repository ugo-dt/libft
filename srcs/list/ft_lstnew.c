#include "libft.h"

t_list	*ft_lstnew(void *content)
{
	t_list	*elem;

	elem = LIBFT_MALLOC(sizeof(*elem));
	if (!elem)
		return (NULL);
	elem->content = content;
	elem->next = NULL;
	return (elem);
}
