/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   executor_command_wrapper.c                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: mikuiper <mikuiper@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/29 18:35:13 by mikuiper      #+#    #+#                 */
/*   Updated: 2022/10/29 20:41:25 by mikuiper      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "execute.h"

void	executor_cmd_wrapper(t_ms *ms, char **cmd, int quit)
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
		ms_exit(cmd);
	else
		ft_execve(ms, cmd);
	if (quit)
		exit(g_global.status);
}
