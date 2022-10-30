/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   execute.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: rkieboom <rkieboom@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/11 15:26:49 by rkieboom      #+#    #+#                 */
/*   Updated: 2022/10/30 12:34:46 by mikuiper      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "execute.h"

//This is were we execute our Command
/**
 * TODO: redirs in pipes
 * @Rowan, I removed the unnecessary 3rd argument, as it made the code
 * more difficult to read.
**/
void	executor(t_ms *ms, t_cmdlist *cmd)
{
	int	cur_cmd;
	int	n_cmds;

	cur_cmd = 0;
	n_cmds = 0;
	while (ms->parse.commands[n_cmds])
		n_cmds++;
	tcsetattr(0, 0, &g_global.termios_save);
	update_signals_handler();
	while (cur_cmd < n_cmds)
	{
		if (!cmd[cur_cmd].next)
			executor_run_single_command(ms, &cmd[cur_cmd]);
		else
			executor_multiple_cmds(ms, &cmd[cur_cmd]);
		cur_cmd++;
	}
}
