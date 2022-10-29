/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   init.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: mikuiper <mikuiper@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/29 10:08:10 by mikuiper      #+#    #+#                 */
/*   Updated: 2022/10/29 10:08:38 by mikuiper      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../header.h"
#include <stdio.h>
#include <signal.h>

//Increases the ENV SHLVL
void	init_shell_level(t_ms *ms)
{
	int		current_level;
	char	*incremented_level;

	if (!ms->env)
		return ;
	if (!env_exist(ms->env, "SHLVL") && !env_has_data(ms->env, "SHLVL"))
		return ;
	current_level = ft_atoi(env_get_content(ms->env, "SHLVL"));
	current_level++;
	incremented_level = ft_itoa(current_level);
	if (!incremented_level)
		return_exit(1, PRNT_ERRNO_NL);
	env_change_content(ms->env, "SHLVL", incremented_level);
	free(incremented_level);
}

void	init_minishell(int argc, char **argv, t_ms *ms)
{
	(void)argc;
	(void)argv;
	ft_bzero(ms, sizeof(t_ms));
	ft_bzero(&g_global, sizeof(t_global));
}

void	init_terminal_params(void)
{
	tcgetattr(0, &g_global.termios_save);
	g_global.termios_new = g_global.termios_save;
	g_global.termios_new.c_lflag &= ~ECHOCTL;
}
