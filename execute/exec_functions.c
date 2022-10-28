/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   exec_functions.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: rkieboom <rkieboom@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/24 12:02:32 by rkieboom      #+#    #+#                 */
/*   Updated: 2022/10/28 21:59:40 by mikuiper      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "execute.h"

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
		dprintf(2, "Fork failed!\n");
		ft_ret_exit(0, 1);
		g_global.status = 1;
		return (1);
	}
	return(0);
}

int	ft_pipe(int *fd)
{
	if (pipe(fd) < 0)
	{
		dprintf(2, "Pipe failed!\n");
		ft_ret_exit(0, 1);
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