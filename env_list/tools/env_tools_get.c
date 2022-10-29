/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   env_tools_get.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: mikuiper <mikuiper@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/29 15:05:19 by mikuiper      #+#    #+#                 */
/*   Updated: 2022/10/29 19:51:04 by mikuiper      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../env_list.h"
#include <stdio.h>
#include "../../header.h"

char	*env_get_name(t_env *v, char *key)
{
	while (v)
	{
		if (!ft_strncmp(v->name, key, ft_strlen(key) + 1))
			return (v->name);
		v = v->next;
	}
	return (NULL);
}

char	*env_get_content(t_env *v, char *key)
{
	while (v)
	{
		if (!ft_strncmp(v->name, key, ft_strlen(key) + 1))
			return (v->content);
		v = v->next;
	}
	return (NULL);
}

t_env	*env_get(t_env *v, char *key)
{
	while (v)
	{
		if (!ft_strncmp(v->name, key, ft_strlen(key) + 1))
			return (v);
		v = v->next;
	}
	return (NULL);
}
