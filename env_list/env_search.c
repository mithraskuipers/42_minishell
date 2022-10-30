/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   env_search.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: rkieboom <rkieboom@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/19 17:27:24 by rkieboom      #+#    #+#                 */
/*   Updated: 2022/10/30 14:51:13 by mikuiper      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../parser/parser.h"

char	*search_env(t_env *v, char *name, int length, char *temp)
{
	if (length == 0)
	{
		if (*name == '$')
			name++;
		while (name[length] && (ft_isdigit(name[length]) || \
				ft_isalpha(name[length]) || (name[length] == '_')))
			length++;
	}
	temp = ft_substr(name, 0, length);
	if (!temp)
		return_exit(1, PRNT_ERRNO_NL);
	while (v)
	{
		if (ft_strncmp(temp, v->name, length + 1) == 0)
		{
			free(temp);
			if (!v->content)
				return ("");
			return (v->content);
		}
		v = v->next;
	}
	free(temp);
	return ("");
}
