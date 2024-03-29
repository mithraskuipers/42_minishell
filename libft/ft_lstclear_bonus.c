/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_lstclear_bonus.c                                :+:    :+:            */
/*                                                     +:+                    */
/*   By: mikuiper <mikuiper@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/29 15:50:06 by mikuiper      #+#    #+#                 */
/*   Updated: 2022/10/29 15:50:08 by mikuiper      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_libft **lst, void (*del)(void*))
{
	t_libft	*temp;
	t_libft	*list;

	list = *lst;
	while (list)
	{
		ft_lstdelone(list, del);
		temp = list->next;
		list = temp;
	}
	*lst = NULL;
}
