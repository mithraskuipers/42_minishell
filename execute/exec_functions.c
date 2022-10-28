/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   exec_functions.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: rkieboom <rkieboom@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/24 12:02:32 by rkieboom      #+#    #+#                 */
/*   Updated: 2022/10/24 12:04:44 by rkieboom      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "execute.h"

int	ft_fork(pid_t *pid)
{
	*pid = fork();
	if (*pid < 0)
	{
		dprintf(2, "Fork failed!\n");
		ft_ret_exit(0, 1);
		g_global.status = 1;
		return (1);
	}
	return(0);
}

int	ft_pipe(t_newcommand *temp)
{
	if (pipe(temp->fd) < 0)
	{
		dprintf(2, "Pipe failed!\n");
		ft_ret_exit(0, 1);
		g_global.status = 1;
		return (1);
	}
	return (0);
}
