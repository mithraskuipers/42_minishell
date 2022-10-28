/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   execute.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: rkieboom <rkieboom@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/11 15:26:49 by rkieboom      #+#    #+#                 */
/*   Updated: 2022/10/29 00:11:22 by mikuiper      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "execute.h"

//This is were we execute our Command
/**
 * todo Redirections in pipes
**/
void	execution(t_ms *ms, t_newcommand *cmd, int k)
{
	int	i;

	i = 0;
	while (ms->parse.commands[k])
		k++;
	tcsetattr(0, 0, &g_global.termios_save);
	signals();
	while (i < k)
	{
		if (!cmd[i].next)
			setup_single_cmd(ms, &cmd[i]);
		else
			setup_pipe_cmd(ms, &cmd[i]);
		i++;
	}
}
