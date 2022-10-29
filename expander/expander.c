/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   expander.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: mikuiper <mikuiper@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/24 14:35:44 by mikuiper      #+#    #+#                 */
/*   Updated: 2022/10/29 00:11:22 by mikuiper      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../parser/parse.h"
#include "expander.h"

//Expands string to new value
char	*expander_wrapper(t_ms *ms, char *str)
{
	int		length;
	char	*expanded_dollar;

	if (!ft_strchr(str, '$') && !ft_strchr(str, '\'') && !ft_strchr(str, '\"'))
		return (str);
	length = expander_calclen(ms, str, 0, 0);
	if (length == 0)
	{
		free(str);
		return (ft_strdup(""));
	}
	expanded_dollar = expander_expand_dollar(ms, str, length);
	free(str);
	return (expanded_dollar);
}

static void	expander_get_value(t_ms *ms, t_varsexp *vars)
{
	if (vars->str[vars->i + 1] == '?')
		return_ret_status(vars);
	else if (vars->str[vars->i + 1] == '\0' || \
	(!ft_isdigit(vars->str[vars->i + 1]) && \
	!ft_isalpha(vars->str[vars->i + 1]) && vars->str[vars->i + 1] != '_'))
	{
		vars->newstr[vars->x] = '$';
		return ;
	}
	else
		set_env_value(ms, vars);
	free(vars->temp);
}

char	*expander_expand_dollar(t_ms *ms, char *s, int length)
{
	t_varsexp	vars;

	init_vars(ms, &vars, length, s);
	while (vars.length > 0)
	{
		vars.i++;
		quote_toggle(ms, &s[vars.i]);
		if (s[vars.i] == '$' && ms->parse.squote == 0)
			expander_get_value(ms, &vars);
		else if (s[vars.i] == '\"' && ((ms->parse.squote == 0 \
		&& ms->parse.dquote == 1) || (ms->parse.squote == 0 \
		&& ms->parse.dquote == 0)))
			continue ;
		else if (s[vars.i] == '\'' && ((ms->parse.dquote == 0 \
		&& ms->parse.squote == 1) || (ms->parse.squote == 0 \
		&& ms->parse.dquote == 0)))
			continue ;
		else
			vars.newstr[vars.x] = s[vars.i];
		vars.length--;
		vars.x++;
	}
	return (vars.newstr);
}
