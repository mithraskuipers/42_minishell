/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   set_heredoc_tokens.c                               :+:    :+:            */
/*                                                     +:+                    */
/*   By: rkieboom <rkieboom@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/09/08 15:13:45 by rkieboom      #+#    #+#                 */
/*   Updated: 2022/10/29 00:11:22 by mikuiper      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "tokens.h"

//Init heredoc tokens
void	set_heredoc_tokens(t_ms *ms, t_newcommand *cmd, int k)
{
	int	i;
	int	heredoc_c;

	i = 0;
	heredoc_c = 0;
	while (i < ms->tokens[k].total)
	{
		if (!ft_strncmp(ms->tokens[k].token[i], "|", 2))
		{
			cmd = cmd->next;
		}
		else if (!ft_strncmp(ms->tokens[k].token[i], "<<", 3))
		{
			if (!cmd->tokens->heredoc)
				cmd->tokens->heredoc = &ms->tokens[k].heredoc[heredoc_c];
			heredoc_c++;
		}
		i++;
	}
}
