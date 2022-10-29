
#include "libft.h"

t_libft	*ft_lstmap(t_libft *lst, void *(*f)(void *), void (*del)(void *))
{
	t_libft	*new;

	while (lst->next != NULL)
	{
		new = f(lst);
		if (!new)
			del(new->content);
	}
	return (new);
}
