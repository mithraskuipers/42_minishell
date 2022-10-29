/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   expander_tools.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: mikuiper <mikuiper@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/29 20:08:58 by mikuiper      #+#    #+#                 */
/*   Updated: 2022/10/29 20:15:00 by mikuiper      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../parser/parse.h"
#include "expander.h"

void	init_vars(t_ms *ms, t_varsexp *vars, int length, char *str)
{
	ft_bzero(vars, sizeof(t_varsexp));
	vars->length = length;
	vars->str = str;
	vars->newstr = ft_calloc(vars->length + 1, sizeof(char));
	if (!vars->newstr)
		return_exit(1, PRNT_ERRNO_NL);
	ms->parse.squote = 0;
	ms->parse.dquote = 0;
	vars->i = -1;
}

void	return_ret_status(t_varsexp *vars)
{
	vars->temp = ft_itoa(g_global.status);
	if (!vars->temp)
		return_exit(1, PRNT_ERRNO_NL);
	ft_memcpy(vars->newstr + vars->x, vars->temp, ft_strlen(vars->temp));
	vars->length -= ft_strlen(vars->newstr);
	vars->length++;
	while (vars->newstr[vars->x])
		vars->x++;
	vars->x--;
	vars->i++;
}

void	set_env_value(t_ms *ms, t_varsexp *vars)
{
	vars->length -= ft_strlen(\
	search_env(ms->env, vars->str + vars->i, 0, 0));
	vars->length++;
	vars->temp = ft_strdup(search_env(ms->env, vars->str + vars->i, 0, 0));
	if (!vars->temp)
		return_exit(1, PRNT_ERRNO_NL);
	ft_memcpy(vars->newstr + vars->x, vars->temp, ft_strlen(vars->temp));
	while (vars->newstr[vars->x])
		vars->x++;
	vars->x--;
	vars->i++;
	while (vars->str[vars->i] && (ft_isdigit(vars->str[vars->i]) || \
	ft_isalpha(vars->str[vars->i]) || (vars->str[vars->i] == '_')))
		vars->i++;
	vars->i--;
}
