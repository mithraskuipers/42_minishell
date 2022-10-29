/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: rkieboom <rkieboom@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/23 22:40:21 by rkieboom      #+#    #+#                 */
/*   Updated: 2022/10/29 20:48:06 by mikuiper      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"
#include <stdio.h>
#include <signal.h>

t_global	g_global;

static void	minishell_start(t_ms *ms)
{
	splash();
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
			parser_command_creation(ms, 0);
			if (!parser_syntax_tokens(ms->cmd, 0))
				executor(ms, ms->cmd);
		}
		clean_ms(ms);
	}
}

int	main(int argc, char **argv, char **envp)
{
	t_ms	ms;

	init_minishell(argc, argv, &ms);
	ms.env = create_envp(ms.env, envp);
	init_signals(&ms.env);
	init_shell_level(&ms);
	init_terminal_params();
	minishell_start(&ms);
	return (0);
}
