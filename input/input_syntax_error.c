/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   input_syntax_error.c                               :+:    :+:            */
/*                                                     +:+                    */
/*   By: mikuiper <mikuiper@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/29 15:55:39 by mikuiper      #+#    #+#                 */
/*   Updated: 2022/10/30 13:57:27 by mikuiper      ########   odam.nl         */
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
	if (ms->tokens[vars->cmd_i].token_pos[vars->j] + 1 == \
	ms->tokens[vars->cmd_i].token_pos[vars->j + 1] && \
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

//Checks if 2 tokens are next to each other
static int	tokens_syntax_neighboring(t_vars *vars, t_ms *ms)
{
	while (vars->j < ms->tokens[vars->cmd_i].n_tokens)
	{
		if (ms->tokens[vars->cmd_i].token_pos[vars->j] + 1 == \
		ms->tokens[vars->cmd_i].token_pos[vars->j + 1] && \
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
	&& ms->tokens[vars->cmd_i].token_pos[vars->j] == 0)
	{
		ft_putendl_fd(\
"minishell-4.2$: syntax error near unexpected token `|'", 2);
		g_global.status = 258;
		return (2);
	}
	return (3);
}

//Check for syntax errors otherwise quit
int	syntax_error_parse(t_ms *ms)
{
	t_vars	vars;

	ft_bzero(&vars, sizeof(t_vars));
	while (ms->parse.commands[vars.n_cmds])
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

// parser_syntax_tokens() checks if the tokens respect the syntax rules of bash.
// It is not allowed to have two tokens next to eachother, nor is it allowed
// to end the command with a token without a corresponding argument.
// In the first half it checks if the token position is not the last position
// of the entire command. In the second half it checks if there are two tokens
// next to eachother.
int	parser_syntax_tokens(t_cmdlist *cmd, int i)
{
	if (!cmd->tokens || cmd->tokens->n_tokens == 0)
		return (0);
	while (i < cmd->tokens->n_tokens)
	{
		if (i + 1 == cmd->tokens->n_tokens)
		{
			if (cmd->tokens->token_pos[i] == cmd_len(cmd->command) - 1) 
			{
				ft_putendl_fd(\
"minishell-4.2$: syntax error near unexpected token `newline'", 2);
				g_global.status = 258;
				return (1);
			}
		}
		else if (cmd->tokens->token_pos[i] + 1 == cmd->tokens->token_pos[i + 1])
		{
			ft_putstr_fd("minishell-4.2$: syntax error near token ", 2);
			ft_putendl_fd(cmd->tokens->token[i + 1], 2);
			g_global.status = 258;
			return (1);
		}
		i++;
	}
	return (0);
}
