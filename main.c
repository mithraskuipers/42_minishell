/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: rkieboom <rkieboom@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/23 22:40:21 by rkieboom      #+#    #+#                 */
/*   Updated: 2022/10/29 09:51:53 by mikuiper      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"
#include <stdio.h>
#include <signal.h>

t_global	g_global;

//loop where minishell will be in continous
static void	minishell(t_ms *ms)
{
	while (1)
	{
		input_read(ms, 0);
		input_syntax_quotes(ms);
		if (!ms->line.array)
			continue ;
		add_history(ms->line.array);
		if (input_syntax_semicolons(ms))
			continue ;
		if (!parser_wrapper(ms) && !ms->hdoc_break)//heredoc break before here
		{
			create_cmd(ms, 0);
			if (!syntax_error(ms->cmd, 0))
				execution(ms, ms->cmd, 0);
		}
		free_all(ms);
	}
}

//Increases the ENV SHLVL
static void	init_shell_level(t_ms *ms)
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

int	main(int argc, char **argv, char **envp)
{
	t_ms	ms;

	init_minishell(argc, argv, &ms);
	ms.env = create_envp(ms.env, envp);
	init_signals(&ms.env);
	init_shell_level(&ms);
	tcgetattr(0, &g_global.termios_save);
	g_global.termios_new = g_global.termios_save;
	g_global.termios_new.c_lflag &= ~ECHOCTL;
	minishell(&ms);
	return (0);
}

// TODO:
// combine the first few initalization lines in separate function
// rename fix_signals
// combine terminal parameters configuration lines in separate function
