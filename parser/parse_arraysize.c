/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parse_arraysize.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: rkieboom <rkieboom@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/09/06 00:34:52 by rkieboom      #+#    #+#                 */
/*   Updated: 2022/10/29 20:30:54 by mikuiper      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"

typedef struct s_vars
{
	int	i;
	int	j;
	int	p;
	int	length;
}				t_vars;

static int	binary_toggler(int *p)
{
	if (*p == 1)
		*p = 0;
	else if (*p == 0)
		*p = 1;
	return (1);
}

static void	check_len(t_ms *ms, t_vars *vars, char **str)
{
	vars->length++;
	if (check_char(&str[vars->j][vars->i]))
		vars->p = 1;
	else
		vars->p = 0;
	while (str[vars->j][vars->i])
	{	
		quote_toggle(ms, &str[vars->j][vars->i]);
		if (ms->parse.squote == 0 && ms->parse.dquote == 0 \
		&& ((vars->p == 1 && !check_char(&str[vars->j][vars->i]) \
		&& binary_toggler(&vars->p))))
			vars->length++;
		else if (ms->parse.squote == 0 && ms->parse.dquote == 0 \
		&& (((vars->p == 0 && check_char(&str[vars->j][vars->i]) \
		&& binary_toggler(&vars->p)))))
			vars->length++;
		vars->i++;
	}
}

//Calculates what the size should be
int	parse_arraysize(char **str, t_ms *ms)
{
	t_vars	vars;

	ft_bzero(&vars, sizeof(t_vars));
	while (str[vars.j])
	{
		if (check_char_str(ms, str[vars.j]) == 0)
			vars.length++;
		else
			check_len(ms, &vars, str);
		vars.i = 0;
		vars.j++;
	}
	return (vars.length);
}
