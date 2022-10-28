/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: rkieboom <rkieboom@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/23 22:40:21 by rkieboom      #+#    #+#                 */
/*   Updated: 2022/10/29 00:12:04 by mikuiper      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"
#include <stdio.h>
#include <signal.h>

t_global	g_global;

//Loop where minishell will be in continous
static void	loop(t_ms *ms)
{
	while (1)
	{
		read_input(ms, 0);
		check_input_quotes(ms);
		if (!ms->gnl.buf)
			continue ;
		add_history(ms->gnl.buf);
		if (check_input(ms))
			continue ;
		if (!new_parse(ms) && !ms->hdoc_break)//heredoc break before here
		{
			create_cmd(ms, 0);
			if (!syntax_error(ms->cmd, 0))
				execution(ms, ms->cmd, 0);
		}
		free_all(ms);
	}
}

//Increases the ENV SHLVL
static void	increase_shlvl(t_ms *ms)
{
	int		shlvl;
	char	*newnum;

	if (!ms->env)
		return ;
	if (!env_exist(ms->env, "SHLVL") && !env_has_data(ms->env, "SHLVL"))
		return ;
	shlvl = ft_atoi(env_get_content(ms->env, "SHLVL"));
	shlvl++;
	newnum = ft_itoa(shlvl);
	if (!newnum)
		ft_ret_exit(1, 1);
	env_change_content(ms->env, "SHLVL", newnum);
	free(newnum);
}

// Handles SIGUSR1 SIGNAL
static void	sighand(int signum)
{
	(void)signum;
	if (g_global.__dup__ == 1)
	{
		g_global.__dup__ = 0;
		return ;
	}
	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
}

// Fixing signals in multiple minishells
static void	fix_signals(t_env **env)
{
	signal(SIGUSR1, sighand);
	if (env_exist(*env, __DUP__))
	{
		g_global.__dup__ = 1;
		env_lst_remove(env, __DUP__);
	}
	kill(g_global.pid, SIGUSR1);
}

int	main(int argc, char **argv, char **envp)
{
	t_ms	ms;

	(void)argc;
	(void)argv;
	ft_bzero(&ms, sizeof(t_ms));
	ft_bzero(&g_global, sizeof(t_global));
	ms.env = create_envp(ms.env, envp);
	fix_signals(&ms.env);
	increase_shlvl(&ms);
	tcgetattr(0, &g_global.termios_save);
	g_global.termios_new = g_global.termios_save;
	g_global.termios_new.c_lflag &= ~ECHOCTL;
	loop(&ms);
	return (0);
}
