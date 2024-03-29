/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   input_syntax_error.c                               :+:    :+:            */
/*                                                     +:+                    */
/*   By: mikuiper <mikuiper@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/29 15:55:39 by mikuiper      #+#    #+#                 */
/*   Updated: 2022/10/31 16:55:53 by rkieboom      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../header.h"

typedef struct s_vars
{
	int	cmd_i;
	int	j;
	int	n_cmds;
	int	tmp;
}				t_vars;

//Checks for double tokens
static int	check_double_pipe_error(t_vars *vars, t_ms *ms)
{
	if (ms->tokens[vars->cmd_i].tkn_pos[vars->j] + 1 == \
	ms->tokens[vars->cmd_i].tkn_pos[vars->j + 1] && \
	!ft_strncmp(ms->tokens[vars->cmd_i].token[vars->j], "|", 2) && \
	!ft_strncmp(ms->tokens[vars->cmd_i].token[vars->j + 1], "|", 2))
	{
		ft_putstr_fd(\
"minishell-4.2$: syntax error near unexpected token `|'\n", 2);
		g_global.status = 258;
		return (1);
	}
	return (0);
}

static int	ends_with_token(t_vars *vars, t_ms *ms)
{
	if (ms->tokens[vars->cmd_i].tkn_pos[vars->j] \
	== cmd_len(ms->parser.commands[vars->cmd_i]) - 1)
	{
		ft_putendl_fd(\
"minishell-4.2$: syntax error near unexpected token `newline'", 2);
				g_global.status = 258;
		return (1);
	}
	return (0);
}

//Checks if 2 tokens are next to each other
static int	tokens_syntax_neighboring(t_vars *vars, t_ms *ms)
{
	while (vars->j < ms->tokens[vars->cmd_i].n_tokens)
	{
		if (ms->tokens[vars->cmd_i].tkn_pos[vars->j] + 1 == \
		ms->tokens[vars->cmd_i].tkn_pos[vars->j + 1] && \
		ft_strncmp(ms->tokens[vars->cmd_i].token[vars->j], "|", 2))
		{
			ft_putstr_fd(\
"minishell-4.2$: syntax error near unexpected token `", 2);
			ft_putstr_fd(ms->tokens[vars->cmd_i].token[vars->j + 1], 2);
			ft_putendl_fd("'", 2);
			g_global.status = 258;
			return (1);
		}
		else if (check_double_pipe_error(vars, ms))
			return (1);
		else if (ends_with_token(vars, ms))
			return (1);
		vars->j++;
	}
	return (0);
}

// Checks if in the command if [0] is '|'.
static int	first(t_vars *vars, t_ms *ms)
{
	vars->j = 0;
	while (vars->cmd_i < vars->n_cmds && (&ms->tokens[vars->cmd_i] == NULL \
	|| ms->tokens[vars->cmd_i].n_tokens == 0))
		vars->cmd_i++;
	if (vars->cmd_i == vars->n_cmds)
		return (1);
	if (!ft_strncmp(ms->tokens[vars->cmd_i].token[0], "|", 2) \
	&& ms->tokens[vars->cmd_i].tkn_pos[vars->j] == 0)
	{
		ft_putendl_fd(\
"minishell-4.2$: syntax error near unexpected token `|'", 2);
		g_global.status = 258;
		return (2);
	}
	return (3);
}

//Check for syntax errors otherwise quit
int	parser_syntax_tokens(t_ms *ms)
{
	t_vars	vars;

	ft_bzero(&vars, sizeof(t_vars));
	while (ms->parser.commands[vars.n_cmds])
		vars.n_cmds++;
	while (vars.cmd_i < vars.n_cmds)
	{
		vars.tmp = first(&vars, ms);
		if (vars.tmp == 1)
			return (0);
		else if (vars.tmp == 2)
			return (1);
		if (tokens_syntax_neighboring(&vars, ms))
			return (1);
		vars.cmd_i++;
	}
	return (0);
}
