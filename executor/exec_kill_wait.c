/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   exec_kill_wait.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: rkieboom <rkieboom@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/31 15:06:55 by rkieboom      #+#    #+#                 */
/*   Updated: 2022/10/31 15:11:31 by rkieboom      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"

void	exec_kill_wait(pid_t *pids)
{
	int	i;

	i = 0;
	while (pids[i])
	{
		kill(pids[i], 9);
		i++;
	}
	i = 0;
	while (pids[i])
	{
		waitpid(pids[i], NULL, WUNTRACED);
		i++;
	}
}
