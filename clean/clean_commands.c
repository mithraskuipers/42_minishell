/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   clean_commands.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: mikuiper <mikuiper@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/29 13:04:03 by mikuiper      #+#    #+#                 */
/*   Updated: 2022/10/30 14:50:10 by mikuiper      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../header.h"

void	clean_commands(t_ms *ms)
{
	int	cmd;
	int	wrd;

	cmd = 0;
	if (ms->parser.commands)
	{
		while (ms->parser.commands[cmd])
		{
			wrd = 0;
			while (ms->parser.commands[cmd][wrd])
			{
				free(ms->parser.commands[cmd][wrd]);
				wrd++;
			}
			free(ms->parser.commands[cmd]);
			cmd++;
		}
		free(ms->parser.commands);
	}
}
