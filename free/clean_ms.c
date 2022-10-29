/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   clean_ms.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: mikuiper <mikuiper@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/29 13:13:29 by mikuiper      #+#    #+#                 */
/*   Updated: 2022/10/29 13:42:42 by mikuiper      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../header.h"

static void	clean_tokens(t_ms *ms)
{
	int	i;

	i = 0;
	while (ms->input.cmds[i])
	{
		while (ms->tokens[i].total)
		{
			free(ms->tokens[i].token[ms->tokens[i].total - 1]);
			ms->tokens[i].total--;
		}
		free(ms->tokens[i].token);
		free(ms->tokens[i].token_pos);
		i++;
	}
	free(ms->tokens);
}

static void	clean_line_array(t_ms *ms)
{
	if (ms->line.array)
	{
		free(ms->line.array);
		ms->line.array = NULL;
	}
}

//Frees all stuff
void	clean_ms(t_ms *ms)
{
	int	n_cmds;

	n_cmds = 0;
	while (ms->input.cmds[n_cmds])
		n_cmds++;
	clean_line_array(ms);
	free_heredoc(ms, n_cmds);
	clean_tokens(ms);
	clean_cmds(ms);
	clean_cmdlist(ms, n_cmds);
	ms->cmdlist = 0;
	ms->tokens = 0;
}