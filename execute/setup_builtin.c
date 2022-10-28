/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   setup_builtin.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: rkieboom <rkieboom@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/17 15:28:34 by rkieboom      #+#    #+#                 */
/*   Updated: 2022/10/29 01:06:46 by mikuiper      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "execute.h"

static void	cpy_fds(t_ms *ms)
{
	ms->stdin_cpy = dup(0);
	ms->stdout_cpy = dup(1);
	if (ms->stdin_cpy < 0 || ms->stdout_cpy < 0)
		return_exit(1, PRNT_ERRNO_NL);
}

static void	reset_fds(t_ms *ms, t_newcommand *cmd)
{
	if (cmd->tokens->last_l != -1)
		dup2(ms->stdin_cpy, STDIN_FILENO);
	if (cmd->tokens->last_r != -1)
		dup2(ms->stdout_cpy, STDOUT_FILENO);
	close(ms->stdin_cpy);
	close(ms->stdout_cpy);
}

static void	with_tokens(t_ms *ms, t_newcommand *cmd, char **command)
{
	cpy_fds(ms);
	if (loop_over_redirs(cmd, 0, cmd->tokens->total))
	{
		reset_fds(ms, cmd);
		g_global.status = 1;
		return ;
	}
	if (cmd->tokens->last_l != -1 && redir_left(cmd))
	{
		reset_fds(ms, cmd);
		g_global.status = 1;
		return ;
	}
	if (cmd->tokens->last_r != -1 && redir_right(cmd))
	{
		reset_fds(ms, cmd);
		g_global.status = 1;
		return ;
	}
	run_cmd(ms, command, 0);
	reset_fds(ms, cmd);
}

void	setup_builtin(t_ms *ms, \
t_newcommand *cmd, char **command, int token_exist)
{
	if (token_exist)
		with_tokens(ms, cmd, command);
	else
		run_cmd(ms, command, 0);
}
