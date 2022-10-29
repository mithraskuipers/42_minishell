/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   execute.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: rkieboom <rkieboom@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/11 15:26:49 by rkieboom      #+#    #+#                 */
/*   Updated: 2022/10/29 12:35:18 by mikuiper      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "execute.h"

//This is were we execute our Command
/**
 * TODO: Redirections in pipes
**/
void	executor(t_ms *ms, t_newcommand *cmd, int cmd_i)
{
	int	i;

	i = 0;
	while (ms->parse.commands[cmd_i])
		cmd_i++;
	tcsetattr(0, 0, &g_global.termios_save);
	signals();
	while (i < cmd_i)
	{
		if (!cmd[i].next)
			setup_single_cmd(ms, &cmd[i]);
		else
			setup_pipe_cmd(ms, &cmd[i]);
		i++;
	}
}
