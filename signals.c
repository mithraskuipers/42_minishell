/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   signals.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: mikuiper <mikuiper@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/29 09:32:40 by mikuiper      #+#    #+#                 */
/*   Updated: 2022/10/29 09:47:37 by mikuiper      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

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
void	init_signals(t_env **env)
{
	signal(SIGUSR1, sighand);
	if (env_exist(*env, __DUP__))
	{
		g_global.__dup__ = 1;
		env_lst_remove(env, __DUP__);
	}
	kill(g_global.pid, SIGUSR1);
}
