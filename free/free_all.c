/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   free_all.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: rkieboom <rkieboom@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/11/29 10:34:48 by rkieboom      #+#    #+#                 */
/*   Updated: 2022/10/29 00:29:51 by mikuiper      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../header.h"

static void	free_tokens(t_ms *ms)
{
	int	i;

	i = 0;
	while (ms->parse.commands[i])
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

static void	free_parse_commands(t_ms *ms)
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

static void	free_line_buf(t_ms *ms)
{
	if (ms->line.array)
	{
		free(ms->line.array);
		ms->line.array = NULL;
	}
}

//Frees all stuff
void	free_all(t_ms *ms)
{
	int	totalcommands;

	totalcommands = 0;
	while (ms->parse.commands[totalcommands])
		totalcommands++;
	free_line_buf(ms);
	free_heredoc(ms, totalcommands);
	free_tokens(ms);
	free_parse_commands(ms);
	free_commands(ms, 0, 0, totalcommands);
	ms->cmd = 0;
	ms->tokens = 0;
}
