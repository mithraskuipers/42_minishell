/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   env_lst_remove.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: rkieboom <rkieboom@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/22 17:40:45 by rkieboom      #+#    #+#                 */
/*   Updated: 2022/10/29 00:12:30 by mikuiper      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "env_list.h"

void	env_lst_remove(t_env **v, char *find)
{
	t_env	*cur;

	cur = env_get(*v, find);
	if (!cur)
		return ;
	if (!cur->prev)
	{
		*v = cur->next;
		if (cur->next)
			cur->next->prev = 0;
		free(cur->name);
		free(cur->content);
		free(cur);
	}
	else
	{
		cur->prev->next = cur->next;
		if (cur->next)
			cur->next->prev = cur->prev;
		free(cur->name);
		free(cur->content);
		free(cur);
	}
}
