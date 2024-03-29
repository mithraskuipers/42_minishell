/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   clean_ms.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: mikuiper <mikuiper@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/29 13:13:29 by mikuiper      #+#    #+#                 */
/*   Updated: 2022/10/31 17:03:52 by rkieboom      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../header.h"

static void	clean_tokens(t_ms *ms)
{
	int	i;

	i = 0;
	while (ms->parser.commands[i])
	{
		while (ms->tokens[i].n_tokens)
		{
			free(ms->tokens[i].token[ms->tokens[i].n_tokens - 1]);
			ms->tokens[i].n_tokens--;
		}
		free(ms->tokens[i].token);
		free(ms->tokens[i].tkn_pos);
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
	while (ms->parser.commands[n_cmds])
		n_cmds++;
	clean_line_array(ms);
	free_heredoc(ms, n_cmds);
	clean_tokens(ms);
	clean_commands(ms);
	if (ms->cmdlists)
		clean_cmdlist(ms, n_cmds);
	ms->cmdlists = 0;
	ms->tokens = 0;
}

//ls | cat | | |;