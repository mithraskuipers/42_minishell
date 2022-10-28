/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   set_heredoc.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: mikuiper <mikuiper@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/28 21:57:47 by mikuiper      #+#    #+#                 */
/*   Updated: 2022/10/28 21:57:48 by mikuiper      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../parse.h"

//sets the EOF in the heredoc struct
void	get_heredoc_eof(t_list *list, int k)
{
	int	total;
	int	c;
	int	token_c;

	c = 0;
	token_c = 0;
	total = list->tokens[k].double_redirection_left;
	while (total)
	{
		if (!ft_strncmp(list->tokens[k].token[token_c], "<<", 3))
		{
			list->tokens[k].heredoc[c].eof = \
			list->parse.commands[k][list->tokens[k].token_pos[token_c] + 1];
			total--;
			c++;
		}
		token_c++;
	}
}

//Here we set all heredoc information
void	set_heredoc(t_list *list, int k)
{
	int	i;

	i = 0;
	while (i < k)
	{
		if (list->tokens[i].double_redirection_left)
		{
			get_heredoc_eof(list, i);
			if (get_heredoc_input(list, i))
			{
				list->hdoc_break = 1;
				break ;
			}
		}
		i++;
	}
}
