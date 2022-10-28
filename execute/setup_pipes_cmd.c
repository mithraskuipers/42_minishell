/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   setup_pipes_cmd.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: rkieboom <rkieboom@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/12 01:09:17 by rkieboom      #+#    #+#                 */
/*   Updated: 2022/10/29 00:11:22 by mikuiper      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "execute.h"

static int	get_cmd_len(t_newcommand *temp)
{
	int	i;

	i = 0;
	while (temp)
	{
		i++;
		temp = temp->next;
	}
	return (i);
}

static int	start_commands(t_ms *ms, t_newcommand *temp, pid_t *pids, int i)
{
	while (temp->next)
	{
		if (ft_pipe(temp->fd) || ft_fork(&pids[i], temp->fd)) //ft_fork miss pipes cleanen
		{
			close(temp->read_pipe);
			pids[i] = 0;
			return (1);
		}
		if (!pids[i])
		{
			signals_dfl();
			dup2(temp->fd[1], STDOUT_FILENO);
			close(temp->fd[1]);
			close(temp->fd[0]);
			dup2(temp->read_pipe, 0);
			close(temp->read_pipe);
			if (redirections(temp))
				ft_ret_exit(1, 0);
			run_cmd(ms, set_cmd(temp), 1);
		}
		else
		{
			i++;
			close(temp->fd[1]);
			close(temp->read_pipe);
			temp->next->read_pipe = temp->fd[0];
		}
		temp = temp->next;
	}
	return (0);
}

static int	last_command(t_ms *ms, t_newcommand *temp, pid_t *pids, int len)
{
	int	i;
	int	status;

	i = 0;
	status = 0;
	while (temp->next)
		temp = temp->next;
	if (ft_fork(&pids[len], NULL))
	{
		close(temp->read_pipe);
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
		signals_dfl();
		dup2(temp->read_pipe, 0);
		close(temp->read_pipe);
		if (redirections(temp))
			ft_ret_exit(1, 0);
		run_cmd(ms, set_cmd(temp), 1);
	}
	else
	{
		close(temp->read_pipe);
		while (i < (len + 1))
		{
			waitpid(pids[i], &status, WUNTRACED);
			i++;
		}
	}
	return (get_return_status(status));
}

//Multiple commands with Pipes execution
void	setup_pipe_cmd(t_ms *ms, t_newcommand *cmd)
{
	pid_t		*pids;
	const int	len = get_cmd_len(cmd);
	int i = 0;

	pids = ft_calloc(len + 1, sizeof(pid_t));
	if (!pids)
		ft_ret_exit(1, 1);
	pids[len] = 0;
	cmd->read_pipe = dup(0);
	if (start_commands(ms, cmd, pids, 0))
	{
		while (pids[i])
		{
			waitpid(pids[i], NULL, WUNTRACED);
			i++;
		}
	}
	else
		g_global.status = last_command(ms, cmd, pids, len - 1);
	free(pids);
}


/*




*/