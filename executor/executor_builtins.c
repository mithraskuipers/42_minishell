/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   executor_builtins.c                                :+:    :+:            */
/*                                                     +:+                    */
/*   By: mikuiper <mikuiper@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/31 07:43:44 by mikuiper      #+#    #+#                 */
/*   Updated: 2022/10/31 07:43:46 by mikuiper      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"

static void	filedescriptors_copy(t_ms *ms)
{
	ms->stdin_cpy = dup(0);
	ms->stdout_cpy = dup(1);
	if (ms->stdin_cpy < 0 || ms->stdout_cpy < 0)
		return_exit(1, PRNT_ERRNO_NL);
}

static void	filedescriptors_reset(t_ms *ms, t_cmdlist *cmdlist)
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
	filedescriptors_copy(ms);
	if (redirs_looper(cmdlist, 0, cmdlist->tokens->n_tokens))
	{
		filedescriptors_reset(ms, cmdlist);
		g_global.status = 1;
		return ;
	}
	if (cmdlist->tokens->last_l != -1 && redir_left(cmdlist))
	{
		filedescriptors_reset(ms, cmdlist);
		g_global.status = 1;
		return ;
	}
	if (cmdlist->tokens->last_r != -1 && redir_right(cmdlist))
	{
		filedescriptors_reset(ms, cmdlist);
		g_global.status = 1;
		return ;
	}
	executor_cmd_portal(ms, command, 0);
	filedescriptors_reset(ms, cmdlist);
}

void	executor_builtins(\
t_ms *ms, t_cmdlist *cmdlist, char **command, int token_exist)
{
	if (token_exist)
		with_tokens(ms, cmdlist, command);
	else
		executor_cmd_portal(ms, command, 0);
}
