#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void*))
{
	t_list	*temp;
	t_list	*temp_next;

	temp = *lst;
	while (temp)
	{
		temp_next = temp->next;
		del(temp->content);
		free(temp);
		temp = temp_next;
	}
	*lst = NULL;
}
