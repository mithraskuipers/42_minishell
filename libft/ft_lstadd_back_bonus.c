/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_lstadd_back_bonus.c                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: mikuiper <mikuiper@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/29 15:51:08 by mikuiper      #+#    #+#                 */
/*   Updated: 2022/10/29 15:51:10 by mikuiper      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_back(t_libft **alst, t_libft *new)
{
	t_libft	*nlist;

	if (!alst)
		return ;
	else if (*alst)
	{
		nlist = *alst;
		nlist = ft_lstlast(*alst);
		nlist->next = new;
		new = nlist->next;
	}
	else
		ft_lstadd_front(alst, new);
}
