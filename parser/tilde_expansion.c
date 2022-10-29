/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   tilde_expansion.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: mikuiper <mikuiper@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/24 14:35:52 by mikuiper      #+#    #+#                 */
/*   Updated: 2022/10/29 13:35:24 by mikuiper      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"

static int	is_tilde(char *str)
{
	if (str[0] == '~' && (!str[1] \
	|| str[1] == ' ' || str[1] == ':' || \
	str[1] == '/'))
		return (1);
	return (0);
}

static int	calc_len(t_env *env, char *str)
{
	int		i;
	char	*temp;
	int		length;

	i = 1;
	temp = env_get_content(env, "HOME");
	length = ft_strlen(temp);
	while (str[i])
		i++;
	length += i;
	return (length);
}

static char	*expand(t_env *env, char *str)
{
	int		length;
	char	*newstr;
	char	*temp;
	int		i;

	if (!env_exist(env, "HOME") || !env_has_data(env, "HOME"))
		return (str);
	length = calc_len(env, str);
	newstr = ft_calloc(length + 1, sizeof(char));
	if (!newstr)
		return_exit(1, PRNT_ERRNO_NL);
	temp = env_get_content(env, "HOME");
	i = ft_strlcpy(newstr, temp, ft_strlen(temp) + 1);
	ft_strlcpy(newstr + i, str + 1, ft_strlen(str + 1) + 1);
	free(str);
	return (newstr);
}

void	tilde_expansion(t_ms *ms, int length)
{
	int	i;
	int	k;

	k = 0;
	while (k < length)
	{
		i = 0;
		while (ms->input.cmds[k][i])
		{
			if (is_tilde(ms->input.cmds[k][i]))
				ms->input.cmds[k][i] = \
				expand(ms->env, ms->input.cmds[k][i]);
			i++;
		}
		k++;
	}
}
