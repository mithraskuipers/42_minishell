/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   exec_functions.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: rkieboom <rkieboom@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/24 12:02:32 by rkieboom      #+#    #+#                 */
/*   Updated: 2022/10/31 17:09:45 by rkieboom      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"

int	ft_fork(pid_t *pid, int *fd)
{
	*pid = fork();
	if (*pid < 0)
	{
		if (fd)
		{
			close(fd[0]);
			close(fd[1]);
		}
		return_exit(0, 1);
		g_global.status = 1;
		return (1);
	}
	return (0);
}

int	ft_pipe(int *fd)
{
	if (pipe(fd) < 0)
	{
		return_exit(0, 1);
		g_global.status = 1;
		return (1);
	}
	return (0);
}

int	get_return_status(int status)
{
	if (WIFEXITED(status))
		return (WEXITSTATUS(status));
	else if (WIFSIGNALED(status))
		return (WTERMSIG(status) + 128);
	return (1);
}
