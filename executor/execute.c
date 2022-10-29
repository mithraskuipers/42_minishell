/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   execute.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: rkieboom <rkieboom@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/11 15:26:49 by rkieboom      #+#    #+#                 */
/*   Updated: 2022/10/29 18:28:25 by mikuiper      ########   odam.nl         */
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
	int	i;
	int	cmd_i;

	i = 0;
	cmd_i = 0;
	while (ms->parse.commands[cmd_i])
		cmd_i++;
	tcsetattr(0, 0, &g_global.termios_save);
	update_signals_handler();
	while (i < cmd_i)
	{
		if (!cmd[i].next)
			executor_single_cmd(ms, &cmd[i]);
		else
			executor_pipe_cmd(ms, &cmd[i]);
		i++;
	}
}
