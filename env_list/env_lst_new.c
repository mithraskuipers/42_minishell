/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   env_lst_new.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: spelle <spelle@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/03/09 14:53:58 by spelle        #+#    #+#                 */
/*   Updated: 2022/10/29 00:13:40 by mikuiper      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "env_list.h"

//Create new t_env object
t_env	*env_lst_new(void *name, void *content)
{
	t_env	*ms;

	ms = ft_calloc(1, sizeof(t_env));
	if (!ms)
		return (NULL);
	ms->name = name;
	ms->content = content;
	ms->next = NULL;
	ms->prev = NULL;
	return (ms);
}
