/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   set_heredoc_tokens.c                               :+:    :+:            */
/*                                                     +:+                    */
/*   By: rkieboom <rkieboom@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/09/08 15:13:45 by rkieboom      #+#    #+#                 */
/*   Updated: 2022/10/31 07:42:16 by mikuiper      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cmds_tokens.h"

//Init heredoc tokens
void	set_heredoc_tokens(t_ms *ms, t_cmdlist *cmd, int k)
{
	int	i;
	int	heredoc_c;

	i = 0;
	heredoc_c = 0;
	while (i < ms->tokens[k].n_tokens)
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
