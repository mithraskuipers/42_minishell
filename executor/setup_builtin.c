/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   setup_builtin.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: rkieboom <rkieboom@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/17 15:28:34 by rkieboom      #+#    #+#                 */
/*   Updated: 2022/10/29 13:58:39 by mikuiper      ########   odam.nl         */
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

static void	reset_fds(t_ms *ms, t_cmdlist *cmdlist)
{
	if (cmdlist->tokens->last_l != -1)
		dup2(ms->stdin_cpy, STDIN_FILENO);
	if (cmdlist->tokens->last_r != -1)
		dup2(ms->stdout_cpy, STDOUT_FILENO);
	close(ms->stdin_cpy);
	close(ms->stdout_cpy);
}

static void	with_tokens(t_ms *ms, t_cmdlist *cmdlist, char **command)
{
	cpy_fds(ms);
	if (loop_over_redirs(cmdlist, 0, cmdlist->tokens->total))
	{
		reset_fds(ms, cmdlist);
		g_global.status = 1;
		return ;
	}
	if (cmdlist->tokens->last_l != -1 && redir_left(cmdlist))
	{
		reset_fds(ms, cmdlist);
		g_global.status = 1;
		return ;
	}
	if (cmdlist->tokens->last_r != -1 && redir_right(cmdlist))
	{
		reset_fds(ms, cmdlist);
		g_global.status = 1;
		return ;
	}
	run_cmd(ms, command, 0);
	reset_fds(ms, cmdlist);
}

void	setup_builtin(t_ms *ms, \
t_cmdlist *cmdlist, char **command, int token_exist)
{
	if (token_exist)
		with_tokens(ms, cmdlist, command);
	else
		run_cmd(ms, command, 0);
}
