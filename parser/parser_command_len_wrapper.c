/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parser_command_len_wrapper.c                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: mikuiper <mikuiper@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/30 13:18:10 by mikuiper      #+#    #+#                 */
/*   Updated: 2022/10/30 14:54:26 by mikuiper      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

typedef struct s_vars
{
	int	i;
	int	j;
	int	p;
	int	len;
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
	vars->len++;
	if (char_is_token(&str[vars->j][vars->i]))
		vars->p = 1;
	else
		vars->p = 0;
	while (str[vars->j][vars->i])
	{	
		quote_toggle(ms, &str[vars->j][vars->i]);
		if (ms->parser.squote == 0 && ms->parser.dquote == 0 \
		&& ((vars->p == 1 && !char_is_token(&str[vars->j][vars->i]) \
		&& binary_toggler(&vars->p))))
			vars->len++;
		else if (ms->parser.squote == 0 && ms->parser.dquote == 0 \
		&& (((vars->p == 0 && char_is_token(&str[vars->j][vars->i]) \
		&& binary_toggler(&vars->p)))))
			vars->len++;
		vars->i++;
	}
}

// parser_len_wrapper() determines the number of words in a command, 
int	parser_command_len_wrapper(char **str, t_ms *ms)
{
	t_vars	vars;

	ft_bzero(&vars, sizeof(t_vars));
	while (str[vars.j])
	{
		if (str_has_token(ms, str[vars.j]) == 0)
			vars.len++;
		else
			check_len(ms, &vars, str);
		vars.i = 0;
		vars.j++;
	}
	return (vars.len);
}
