/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   createstring.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: rkieboom <rkieboom@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/11/28 15:03:53 by rkieboom      #+#    #+#                 */
/*   Updated: 2022/10/29 01:06:46 by mikuiper      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"

typedef struct s_vars
{
	int		i;
	int		x;
	int		length;
	char	*str;
	char	*newstr;
	char	*temp;
}				t_vars;

static void	return_ret_status(t_vars *vars)
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

static void	set_env_value(t_ms *ms, t_vars *vars)
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

static void	return_dollar_value(t_ms *ms, t_vars *vars)
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

static void	init_vars(t_ms *ms, t_vars *vars, int length, char *str)
{
	ft_bzero(vars, sizeof(t_vars));
	vars->length = length;
	vars->str = str;
	vars->newstr = ft_calloc(vars->length + 1, sizeof(char));
	if (!vars->newstr)
		return_exit(1, PRNT_ERRNO_NL);
	ms->parse.comma1 = 0;
	ms->parse.comma2 = 0;
	vars->i = -1;
}

char	*createstring(t_ms *ms, char *str, int length)
{
	t_vars	vars;

	init_vars(ms, &vars, length, str);
	while (vars.length > 0)
	{
		vars.i++;
		check_quote(ms, &str[vars.i]);
		if (str[vars.i] == '$' && ms->parse.comma1 == 0)
			return_dollar_value(ms, &vars);
		else if (str[vars.i] == '\"' && ((ms->parse.comma1 == 0 \
		&& ms->parse.comma2 == 1) || (ms->parse.comma1 == 0 \
		&& ms->parse.comma2 == 0)))
			continue ;
		else if (str[vars.i] == '\'' && ((ms->parse.comma2 == 0 \
		&& ms->parse.comma1 == 1) || (ms->parse.comma1 == 0 \
		&& ms->parse.comma2 == 0)))
			continue ;
		else
			vars.newstr[vars.x] = str[vars.i];
		vars.length--;
		vars.x++;
	}
	return (vars.newstr);
}
