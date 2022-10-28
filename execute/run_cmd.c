/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   run_cmd.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: rkieboom <rkieboom@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/11 15:34:15 by rkieboom      #+#    #+#                 */
/*   Updated: 2022/10/29 00:11:25 by mikuiper      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "execute.h"

void	run_cmd(t_ms *ms, char **cmd, int quit)
{
	if ((!cmd || !cmd[0]) && quit == 1)
		exit(0);
	else if (!cmd || !cmd[0])
		return ;
	if (!ft_strncmp(cmd[0], "echo", 5))
		g_global.status = echo(cmd);
	else if (!ft_strncmp(cmd[0], "cd", 3))
		g_global.status = cd(ms, cmd);
	else if (!ft_strncmp(cmd[0], "pwd", 4))
		g_global.status = pwd();
	else if (!ft_strncmp(cmd[0], "export", 7))
		g_global.status = export(&ms->env, cmd);
	else if (!ft_strncmp(cmd[0], "unset", 6))
		g_global.status = unset(&ms->env, cmd);
	else if (!ft_strncmp(cmd[0], "env", 4))
		g_global.status = env(ms->env);
	else if (!ft_strncmp(cmd[0], "exit", 5))
		ft_exit(cmd);
	else
		ft_execve(ms, cmd);
	if (quit)
		exit(g_global.status);
}
