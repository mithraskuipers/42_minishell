/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   allocate_heredoc.c                                 :+:    :+:            */
/*                                                     +:+                    */
/*   By: mikuiper <mikuiper@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/28 21:57:24 by mikuiper      #+#    #+#                 */
/*   Updated: 2022/10/28 21:57:26 by mikuiper      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../parse.h"

//Allocates heredoc struct * the double redir left
static void	heredoc_allocation(t_list *list, int k)
{
	int	i;

	i = 0;
	while (i < k)
	{
		if (list->tokens[i].double_redirection_left)
		{
			list->tokens[i].heredoc = \
			ft_calloc(sizeof(t_heredoc), \
			list->tokens[i].double_redirection_left);
			if (!list->tokens[i].heredoc)
				ft_ret_exit(1, 1);
		}
		i++;
	}
}

/*We see if the EOF is in between quotes
If it is we should not expand anything
We do this here because after the parsing 
it removes the quotes*/
static void	get_heredoc_q(t_list *list, int k)
{
	int	i;
	int	current;
	int	pos;

	i = 0;
	current = 0;
	while (i < list->tokens[k].total)
	{
		if (!ft_strncmp(list->tokens[k].token[i], "<<", 3))
		{
			pos = list->tokens[k].token_pos[i] + 1;
			if (!list->parse.commands[k][pos])
				return ;
			if (list->parse.commands[k][pos][0] == '\"' \
			|| list->parse.commands[k][pos][0] == '\'')
				list->tokens[k].heredoc[current].heredoc_q = 1;
			current++;
		}
		i++;
	}
}

//Allocates the heredoc struct
//And sets if the EOF has quotes
void	allocate_heredoc(t_list *list, int k)
{
	int	i;

	i = 0;
	heredoc_allocation(list, k);
	while (i < k)
	{
		if (list->tokens[i].double_redirection_left)
			get_heredoc_q(list, i);
		i++;
	}
}
