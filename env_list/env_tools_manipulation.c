/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   env_tools_manipulation.c                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: mikuiper <mikuiper@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/29 15:07:13 by mikuiper      #+#    #+#                 */
/*   Updated: 2022/10/30 13:17:17 by mikuiper      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "env_list.h"
#include <stdio.h>
#include "../header.h"

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
