/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   set_heredoc.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: mikuiper <mikuiper@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/28 21:57:47 by mikuiper      #+#    #+#                 */
/*   Updated: 2022/10/29 00:11:22 by mikuiper      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../parse.h"

//sets the EOF in the heredoc struct
void	get_heredoc_eof(t_ms *ms, int k)
{
	int	total;
	int	c;
	int	token_c;

	c = 0;
	token_c = 0;
	total = ms->tokens[k].double_redirection_left;
	while (total)
	{
		if (!ft_strncmp(ms->tokens[k].token[token_c], "<<", 3))
		{
			ms->tokens[k].heredoc[c].eof = \
			ms->parse.commands[k][ms->tokens[k].token_pos[token_c] + 1];
			total--;
			c++;
		}
		token_c++;
	}
}

//Here we set all heredoc information
void	set_heredoc(t_ms *ms, int k)
{
	int	i;

	i = 0;
	while (i < k)
	{
		if (ms->tokens[i].double_redirection_left)
		{
			get_heredoc_eof(ms, i);
			if (get_heredoc_input(ms, i))
			{
				ms->hdoc_break = 1;
				break ;
			}
		}
		i++;
	}
}
