/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   executor_multiple_cmds.c                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: mikuiper <mikuiper@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/30 18:14:52 by mikuiper      #+#    #+#                 */
/*   Updated: 2022/10/30 18:14:53 by mikuiper      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"

static int	get_cmd_len(t_cmdlist *cmdlist)
{
	int	i;

	i = 0;
	while (cmdlist)
	{
		i++;
		cmdlist = cmdlist->next;
	}
	return (i);
}

static int	start_commands(t_ms *ms, t_cmdlist *cmdlist, pid_t *pids, int i)
{
	while (cmdlist->next)
	{
		if (ft_pipe(cmdlist->fd) || ft_fork(&pids[i], cmdlist->fd)) //ft_fork miss pipes cleanen
		{
			close(cmdlist->read_pipe);
			pids[i] = 0;
			return (1);
		}
		if (!pids[i])
		{
			update_signals_default();
			dup2(cmdlist->fd[1], STDOUT_FILENO);
			close(cmdlist->fd[1]);
			close(cmdlist->fd[0]);
			dup2(cmdlist->read_pipe, 0);
			close(cmdlist->read_pipe);
			if (redirs(cmdlist))
				return_exit(1, NO_PRNT);
			executor_cmd_portal(ms, executor_get_command(cmdlist), 1);
		}
		else
		{
			i++;
			close(cmdlist->fd[1]);
			close(cmdlist->read_pipe);
			cmdlist->next->read_pipe = cmdlist->fd[0];
		}
		cmdlist = cmdlist->next;
	}
	return (0);
}

static int	last_command(t_ms *ms, t_cmdlist *cmdlist, pid_t *pids, int len)
{
	int	i;
	int	status;

	i = 0;
	status = 0;
	while (cmdlist->next)
		cmdlist = cmdlist->next;
	if (ft_fork(&pids[len], NULL))
	{
		close(cmdlist->read_pipe);
		pids[len] = 0;
		while (pids[i])
		{
			waitpid(pids[i], NULL, WUNTRACED);
			i++;
		}
		return (1);
	}
	if (!pids[len])
	{
		update_signals_default();
		dup2(cmdlist->read_pipe, 0);
		close(cmdlist->read_pipe);
		if (redirs(cmdlist))
			return_exit(1, NO_PRNT);
		executor_cmd_portal(ms, executor_get_command(cmdlist), 1);
	}
	else
	{
		close(cmdlist->read_pipe);
		while (i < (len + 1))
		{
			waitpid(pids[i], &status, WUNTRACED);
			i++;
		}
	}
	return (get_return_status(status));
}

//Multiple commands with Pipes executor
void	executor_run_multiple_cmds(t_ms *ms, t_cmdlist *cmdlist)
{
	pid_t		*pids;
	const int	len = get_cmd_len(cmdlist);
	int			i;

	i = 0;
	pids = ft_calloc(len + 1, sizeof(pid_t));
	if (!pids)
		return_exit(1, PRNT_ERRNO_NL);
	pids[len] = 0;
	cmdlist->read_pipe = dup(0);
	if (start_commands(ms, cmdlist, pids, 0))
	{
		while (pids[i])
		{
			waitpid(pids[i], NULL, WUNTRACED);
			i++;
		}
	}
	else
		g_global.status = last_command(ms, cmdlist, pids, len - 1);
	free(pids);
}
