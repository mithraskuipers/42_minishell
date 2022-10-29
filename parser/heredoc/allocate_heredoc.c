/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   allocate_heredoc.c                                 :+:    :+:            */
/*                                                     +:+                    */
/*   By: mikuiper <mikuiper@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/28 21:57:24 by mikuiper      #+#    #+#                 */
/*   Updated: 2022/10/29 18:15:07 by mikuiper      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../parse.h"

//Allocates heredoc struct * the double redir left
static void	heredoc_allocation(t_ms *ms, int k)
{
	int	i;

	i = 0;
	while (i < k)
	{
		if (ms->tokens[i].double_redirection_left)
		{
			ms->tokens[i].heredoc = \
			ft_calloc(sizeof(t_heredoc), \
			ms->tokens[i].double_redirection_left);
			if (!ms->tokens[i].heredoc)
				return_exit(1, PRNT_ERRNO_NL);
		}
		i++;
	}
}

/*We see if the EOF is in between quotes
If it is we should not expand anything
We do this here because after the parser 
it removes the quotes*/
static void	get_heredoc_q(t_ms *ms, int k)
{
	int	i;
	int	current;
	int	pos;

	i = 0;
	current = 0;
	while (i < ms->tokens[k].n_tokens)
	{
		if (!ft_strncmp(ms->tokens[k].token[i], "<<", 3))
		{
			pos = ms->tokens[k].token_pos[i] + 1;
			if (!ms->parse.commands[k][pos])
				return ;
			if (ms->parse.commands[k][pos][0] == '\"' \
			|| ms->parse.commands[k][pos][0] == '\'')
				ms->tokens[k].heredoc[current].heredoc_q = 1;
			current++;
		}
		i++;
	}
}

//Allocates the heredoc struct
//And sets if the EOF has quotes
void	allocate_heredoc(t_ms *ms, int k)
{
	int	i;

	i = 0;
	heredoc_allocation(ms, k);
	while (i < k)
	{
		if (ms->tokens[i].double_redirection_left)
			get_heredoc_q(ms, i);
		i++;
	}
}
