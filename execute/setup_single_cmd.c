/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   setup_single_cmd.c                                 :+:    :+:            */
/*                                                     +:+                    */
/*   By: rkieboom <rkieboom@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/12 00:44:55 by rkieboom      #+#    #+#                 */
/*   Updated: 2022/10/29 01:06:46 by mikuiper      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "execute.h"

static int	is_builtin(char *cmd)
{
	if (!cmd || !cmd[0])
		return (0);
	if (!ft_strncmp(cmd, "echo", 5))
		return (1);
	else if (!ft_strncmp(cmd, "cd", 3))
		return (1);
	else if (!ft_strncmp(cmd, "pwd", 4))
		return (1);
	else if (!ft_strncmp(cmd, "export", 7))
		return (1);
	else if (!ft_strncmp(cmd, "unset", 6))
		return (1);
	else if (!ft_strncmp(cmd, "env", 4))
		return (1);
	else if (!ft_strncmp(cmd, "exit", 5))
		return (1);
	return (0);
}

static int	return_status(int status)
{
	if (WIFEXITED(status))
		return (WEXITSTATUS(status));
	else if (WIFSIGNALED(status))
		return (WTERMSIG(status) + 128);
	return (1);
}

static void	setup_execve(t_ms *ms, t_newcommand *cmd, char **command)
{
	int	status;

	status = 0;
	g_global.pid = fork();
	if (g_global.pid < 0)
		return_exit(1, PRNT_ERRNO_NL);
	if (g_global.pid == 0)
	{
		signals_dfl();
		env_lstadd_back(&ms->env, \
		env_lst_new(ft_strdup(__DUP__), ft_strdup("")));
		if (redirections(cmd))
			return_exit(1, 0);
		run_cmd(ms, command, 1);
	}
	else
		waitpid(g_global.pid, &status, 0);
	g_global.status = return_status(status);
}

// Executes one command no Pipes
// Command is the temp command with the redirections removed as arguments
void	setup_single_cmd(t_ms *ms, t_newcommand *cmd)
{
	char	**command;

	command = set_cmd(cmd);
	if (is_builtin(command[0]))
		setup_builtin(ms, cmd, command, tokens_exist(cmd));
	else
		setup_execve(ms, cmd, command);
	if (command && tokens_exist(cmd))
		free(command);
}
