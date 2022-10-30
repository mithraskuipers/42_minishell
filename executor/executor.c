/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   executor.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: rkieboom <rkieboom@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/11 15:26:49 by rkieboom      #+#    #+#                 */
/*   Updated: 2022/10/30 12:34:46 by mikuiper      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"

//This is were we execute our Command
/**
 * TODO: redirs in pipes
 * @Rowan, I removed the unnecessary 3rd argument, as it made the code
 * more difficult to read.
**/
void	executor(t_ms *ms, t_cmdlist *cmdlist)
{
	int	cmd_i;
	int	n_cmds;

	cmd_i = 0;
	n_cmds = 0;
	while (ms->parse.commands[n_cmds])
		n_cmds++;
	tcsetattr(0, 0, &g_global.termios_save);
	update_signals_handler();
	while (cmd_i < n_cmds)
	{
		if (!cmdlist[cmd_i].next)
			executor_run_single_command(ms, &cmdlist[cmd_i]);
		else
			executor_multiple_cmds(ms, &cmdlist[cmd_i]);
		cmd_i++;
	}
}
