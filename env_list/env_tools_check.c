/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   env_tools_check.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: rkieboom <rkieboom@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/23 22:52:25 by rkieboom      #+#    #+#                 */
/*   Updated: 2022/10/29 21:06:17 by mikuiper      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "env_list.h"
#include "../header.h"

int	env_has_data(t_env *v, char *key)
{
	while (v)
	{
		if (!ft_strncmp(v->name, key, ft_strlen(key) + 1))
		{
			if (v->content)
				return (1);
			else
				return (0);
		}
		v = v->next;
	}
	return (0);
}

int	env_exist(t_env *v, char *key)
{
	while (v)
	{
		if (!ft_strncmp(v->name, key, ft_strlen(key) + 1))
			return (1);
		v = v->next;
	}
	return (0);
}
