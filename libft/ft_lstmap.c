#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*new_elt;
	t_list	*new_lst;
	t_list	*temp;

	if (!lst)
		return (NULL);
	temp = lst;
	new_lst = NULL;
	while (temp)
	{
		new_elt = ft_lstnew(f(temp->content));
		if (!new_elt)
		{
			ft_lstclear(&new_lst, del);
			return (NULL);
		}
		ft_lstadd_back(&new_lst, new_elt);
		temp = temp->next;
	}
	return (new_lst);
}
