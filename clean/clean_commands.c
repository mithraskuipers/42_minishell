/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   clean_commands.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: mikuiper <mikuiper@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/29 13:04:03 by mikuiper      #+#    #+#                 */
/*   Updated: 2022/10/29 22:36:20 by mikuiper      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../header.h"

void	clean_commands(t_ms *ms)
{
	int	cmd;
	int	wrd;

	cmd = 0;
	if (ms->parse.commands)
	{
		while (ms->parse.commands[cmd])
		{
			wrd = 0;
			while (ms->parse.commands[cmd][wrd])
			{
				free(ms->parse.commands[cmd][wrd]);
				wrd++;
			}
			free(ms->parse.commands[cmd]);
			cmd++;
		}
		free(ms->parse.commands);
	}
}
