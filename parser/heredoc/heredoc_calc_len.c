/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   heredoc_calc_len.c                                 :+:    :+:            */
/*                                                     +:+                    */
/*   By: mikuiper <mikuiper@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/28 21:57:34 by mikuiper      #+#    #+#                 */
/*   Updated: 2022/10/30 14:50:15 by mikuiper      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../parser.h"

static void	heredoc_env(char *str, t_env *env, int *length, int *i)
{
	char	*env_str;

	env_str = search_env(env, str + (*i), 0, 0);
	(*length) += ft_strlen(env_str);
	while (str[*i] && (ft_isalnum(str[*i]) || str[*i] == '_'))
		(*i)++;
}

int	heredoc_get_str_len(t_ms *ms, char *str)
{
	int	i;
	int	newlength;

	i = 0;
	newlength = 0;
	while (str[i])
	{
		if (str[i] == '$')
		{
			i++;
			if (str[i] && (ft_isalnum(str[i]) || str[i] == '_'))
				heredoc_env(str, ms->env, &newlength, &i);
			else
				newlength++;
		}
		else
		{
			newlength++;
			i++;
		}
	}
	return (newlength);
}
