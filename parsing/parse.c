/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parse.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: mikuiper <mikuiper@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/24 14:34:50 by mikuiper      #+#    #+#                 */
/*   Updated: 2022/10/29 00:11:22 by mikuiper      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"

typedef struct s_vars
{
	int		i;
	int		length;
	char	**splitted;
}				t_vars;

//Free the temporily struct
static void	freemem(char **result)
{
	int	i;

	i = 0;
	while (result[i])
	{
		free(result[i]);
		i++;
	}
	if (result)
		free(result);
}

//The actual big parsing and expanding
static void	parsing(t_ms *ms)
{
	int	i;
	int	j;
	int	x;

	j = 0;
	x = 0;
	while (ms->parse.commands[j])
	{
		i = 0;
		x = 0;
		while (ms->parse.commands[j][i] != NULL)
		{
			ms->parse.commands[j][i - x] = \
			checkword(ms, ms->parse.commands[j][i]);
			if (!ms->parse.commands[j][i])
				x++;
			i++;
		}
		j++;
	}
}

static void	init_allocate(t_ms *ms, t_vars *vars)
{
	ft_bzero(vars, sizeof(t_vars));
	vars->splitted = parse_split_commands(ms, ';');
	while (vars->splitted[vars->length])
		vars->length++;
	ms->parse.commands = ft_calloc(vars->length + 1, sizeof(char **));
	if (!ms->parse.commands)
		ft_ret_exit(1, 1);
	ms->parse.commands[vars->length] = 0;
	ms->tokens = ft_calloc(vars->length, sizeof(t_tokens));
	if (!ms->tokens)
		ft_ret_exit(1, 1);
	while (vars->length)
	{
		ms->parse.commands[vars->i] = \
		parse_split_spaces(ms, vars->splitted[vars->i], ' ');
		parse_split_tokens(ms, \
		parse_arraysize(ms->parse.commands[vars->i], ms), vars->i);
		vars->length--;
		vars->i++;
	}
}

// (1) scans input and allocates memory
// (2) adjusts input for easy parsing
// (3) extracts and stores tokens
int	new_parse(t_ms *ms)
{
	t_vars	vars;

	init_allocate(ms, &vars);
	tokens(ms);
	while (vars.splitted[vars.length])
		vars.length++;
	tilde_expansion(ms, vars.length);
	if (syntax_error_parse(ms))
	{
		freemem(vars.splitted);
		return (1);
	}
	allocate_heredoc(ms, vars.length);
	freemem(vars.splitted);
	parsing(ms);
	set_heredoc(ms, vars.length);
	return (0);
}
