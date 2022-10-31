/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   executor_single_cmd.c                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: mikuiper <mikuiper@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/30 18:14:56 by mikuiper      #+#    #+#                 */
/*   Updated: 2022/10/30 18:14:57 by mikuiper      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"

static int	executor_cmd_is_builtin(char *cmd_array_first)
{
	if (!cmd_array_first || !cmd_array_first[0])
		return (0);
	if (!ft_strncmp(cmd_array_first, "echo", 5))
		return (1);
	else if (!ft_strncmp(cmd_array_first, "cd", 3))
		return (1);
	else if (!ft_strncmp(cmd_array_first, "pwd", 4))
		return (1);
	else if (!ft_strncmp(cmd_array_first, "export", 7))
		return (1);
	else if (!ft_strncmp(cmd_array_first, "unset", 6))
		return (1);
	else if (!ft_strncmp(cmd_array_first, "env", 4))
		return (1);
	else if (!ft_strncmp(cmd_array_first, "exit", 5))
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

static void	executor_execve(t_ms *ms, t_cmdlist *cmdlist, char **command)
{
	int	status;

	status = 0;
	g_global.pid = fork();
	if (g_global.pid < 0)
		return_exit(1, PRNT_ERRNO_NL);
	if (g_global.pid == 0)
	{
		update_signals_default();
		env_lstadd_back(&ms->env, \
		env_lst_new(ft_strdup(__DUP__), ft_strdup("")));
		if (redirs(cmdlist))
			return_exit(1, NO_PRNT);
		executor_cmd_portal(ms, command, 1);
	}
	else
		waitpid(g_global.pid, &status, 0);
	g_global.status = return_status(status);
}

// Executes one command no Pipes
// Command is the temp command with the redirs removed as arguments
void	executor_run_single_command(t_ms *ms, t_cmdlist *cmdlist)
{
	char	**cmd_array;

	cmd_array = executor_get_command(cmdlist);
	if (executor_cmd_is_builtin(cmd_array[0]))
		executor_run_builtin(ms, cmdlist, cmd_array, tokens_present(cmdlist));
	else
		executor_execve(ms, cmdlist, cmd_array);
	if (cmd_array && tokens_present(cmdlist))
		free(cmd_array);
}
