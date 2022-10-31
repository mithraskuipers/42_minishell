/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   executor.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: mikuiper <mikuiper@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/30 17:22:17 by mikuiper      #+#    #+#                 */
/*   Updated: 2022/10/31 15:55:53 by rkieboom      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"

void	executor(t_ms *ms, t_cmdlist *cmdlist)
{
	int	cmdlist_i;
	int	n_cmds;

	cmdlist_i = 0;
	n_cmds = 0;
	while (ms->parser.commands[n_cmds])
		n_cmds++;
	tcsetattr(0, 0, &g_global.termios_save);
	update_signals_handler();
	while (cmdlist_i < n_cmds)
	{
		if (!cmdlist[cmdlist_i].next)
			executor_run_single_command(ms, &cmdlist[cmdlist_i]);
		else
			executor_run_multiple_cmds(ms, &cmdlist[cmdlist_i]);
		cmdlist_i++;
	}
}
