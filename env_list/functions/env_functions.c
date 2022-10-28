/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   env_functions.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: rkieboom <rkieboom@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/05/17 12:47:05 by rkieboom      #+#    #+#                 */
/*   Updated: 2022/10/29 01:09:30 by mikuiper      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../env_list.h"
#include <stdio.h>
#include "../../header.h"

void	env_add_content(t_env **v, char *envname, char *envcontent)
{
	char	*name;
	char	*content;

	name = ft_strdup(envname);
	if (!name)
		return_exit(1, PRNT_ERRNO_NL);
	if (envcontent)
	{
		content = ft_strdup(envcontent);
		if (!content)
			return_exit(1, PRNT_ERRNO_NL);
	}
	else
		content = 0;
	env_lstadd_back(v, env_lst_new(name, content));
}

void	env_change_content(t_env *v, char *envname, char *envcontent)
{
	t_env	*temp;

	temp = env_get(v, envname);
	if (temp)
	{
		if (temp->content)
			free(temp->content);
		if (envcontent)
		{
			temp->content = ft_strdup(envcontent);
			if (!temp->content)
				return_exit(1, PRNT_ERRNO_NL);
		}
		else
			temp->content = 0;
	}
}

char	*env_get_name(t_env *v, char *find)
{
	while (v)
	{
		if (!ft_strncmp(v->name, find, ft_strlen(find) + 1))
			return (v->name);
		v = v->next;
	}
	return (NULL);
}

char	*env_get_content(t_env *v, char *find)
{
	while (v)
	{
		if (!ft_strncmp(v->name, find, ft_strlen(find) + 1))
			return (v->content);
		v = v->next;
	}
	return (NULL);
}

t_env	*env_get(t_env *v, char *find)
{
	while (v)
	{
		if (!ft_strncmp(v->name, find, ft_strlen(find) + 1))
			return (v);
		v = v->next;
	}
	return (NULL);
}
