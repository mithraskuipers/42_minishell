/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   clean_cmds.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: mikuiper <mikuiper@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/29 13:04:03 by mikuiper      #+#    #+#                 */
/*   Updated: 2022/10/29 13:35:24 by mikuiper      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../header.h"

void	clean_cmds(t_ms *ms)
{
	int	i;
	int	j;

	i = 0;
	if (ms->input.cmds)
	{
		while (ms->input.cmds[i])
		{
			j = 0;
			while (ms->input.cmds[i][j])
			{
				free(ms->input.cmds[i][j]);
				j++;
			}
			free(ms->input.cmds[i]);
			i++;
		}
		free(ms->input.cmds);
	}
}
