/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   clean_commands.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: mikuiper <mikuiper@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/29 13:04:03 by mikuiper      #+#    #+#                 */
/*   Updated: 2022/10/29 13:04:41 by mikuiper      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../header.h"

void	clean_commands(t_ms *ms)
{
	int	i;
	int	j;

	i = 0;
	if (ms->parse.commands)
	{
		while (ms->parse.commands[i])
		{
			j = 0;
			while (ms->parse.commands[i][j])
			{
				free(ms->parse.commands[i][j]);
				j++;
			}
			free(ms->parse.commands[i]);
			i++;
		}
		free(ms->parse.commands);
	}
}
