/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   syntax_error.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: rkieboom <rkieboom@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/05/18 10:21:40 by rkieboom      #+#    #+#                 */
/*   Updated: 2022/10/29 12:42:28 by mikuiper      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../header.h"

typedef struct s_vars
{
	int	i;
	int	j;
	int	k;
	int	temp;
}				t_vars;

//Checks for double tokens
static int	check_double_pipe_error(t_vars *vars, t_ms *ms)
{
	if (ms->tokens[vars->i].token_pos[vars->j] + 1 == \
	ms->tokens[vars->i].token_pos[vars->j + 1] && \
	!ft_strncmp(ms->tokens[vars->i].token[vars->j], "|", 2) && \
	!ft_strncmp(ms->tokens[vars->i].token[vars->j + 1], "|", 2))
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
	while (vars->j < ms->tokens[vars->i].total)
	{
		if (ms->tokens[vars->i].token_pos[vars->j] + 1 == \
		ms->tokens[vars->i].token_pos[vars->j + 1] && \
		ft_strncmp(ms->tokens[vars->i].token[vars->j], "|", 2))
		{
			ft_putstr_fd(\
"minishell-4.2$: syntax error near unexpected token `", 2);
			ft_putstr_fd(ms->tokens[vars->i].token[vars->j + 1], 2);
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

//Checks if CMD arg0 = '|'
static int	first(t_vars *vars, t_ms *ms)
{
	vars->j = 0;
	while (vars->i < vars->k && (&ms->tokens[vars->i] == NULL \
	|| ms->tokens[vars->i].total == 0))
		vars->i++;
	if (vars->i == vars->k)
		return (1);
	if (!ft_strncmp(ms->tokens[vars->i].token[0], "|", 2) \
	&& ms->tokens[vars->i].token_pos[vars->j] == 0)
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
	while (ms->parse.commands[vars.k])
		vars.k++;
	while (vars.i < vars.k)
	{
		vars.temp = first(&vars, ms);
		if (vars.temp == 1)
			return (0);
		else if (vars.temp == 2)
			return (1);
		if (tokens_syntax_neighboring(&vars, ms))
			return (1);
		vars.i++;
	}
	return (0);
}

//Checks syntax errors for tokens
int	parser_syntax_tokens(t_cmdlist *cmd, int i)
{
	if (!cmd->tokens || cmd->tokens->total == 0)
		return (0);
	while (i < cmd->tokens->total)
	{
		if (i + 1 == cmd->tokens->total)
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
