/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   free_heredoc.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: rkieboom <rkieboom@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/09/21 04:04:12 by rkieboom      #+#    #+#                 */
/*   Updated: 2022/10/29 00:11:22 by mikuiper      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../header.h"

static void	free_heredoc_data(t_heredoc_data *data)
{
	t_heredoc_data	*tmp;

	while (data)
	{
		if (data->str)
			free(data->str);
		tmp = data->next;
		free(data);
		data = tmp;
	}
}

void	free_heredoc(t_ms *ms, int totalcommands)
{
	int				i;
	int				j;

	i = 0;
	while (totalcommands)
	{
		j = 0;
		while (ms->tokens != NULL && &ms->tokens[i] != NULL && \
		ms->tokens[i].double_redirection_left)
		{
			if (ms->tokens != NULL && &ms->tokens[i] != NULL && \
			ms->tokens[i].heredoc && ms->tokens[i].heredoc[j].data)
				free_heredoc_data(ms->tokens[i].heredoc[j].data);
			ms->tokens[i].double_redirection_left--;
			j++;
		}
		if (ms->tokens != NULL && \
		&ms->tokens[i] != NULL && ms->tokens[i].heredoc)
			free(ms->tokens[i].heredoc);
		i++;
		totalcommands--;
	}
}
