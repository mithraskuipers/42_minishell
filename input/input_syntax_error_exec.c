/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   input_syntax_error_exec.c                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: rkieboom <rkieboom@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/31 16:55:27 by rkieboom      #+#    #+#                 */
/*   Updated: 2022/10/31 17:11:59 by rkieboom      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../header.h"

// cmds_cmdlist_syntax_tokens() checks if the tokens respect the syntax 
// rules of bash. It is not allowed to have two tokens next to eachother, nor 
// is it allowed to end the command with a token without a corresponding arg.
// In the first half it checks if the token position is not the last position
// of the entire command. In the second half it checks if there are two tokens
// next to eachother.
int	cmds_cmdlist_syntax_tokens(t_cmdlist *cmdlist, int i)
{
	if (!cmdlist->tokens || cmdlist->tokens->n_tokens == 0)
		return (0);
	while (i < cmdlist->tokens->n_tokens)
	{
		if (i + 1 == cmdlist->tokens->n_tokens)
		{
			if (cmdlist->tokens->tkn_pos[i] == cmd_len(cmdlist->cmd_array) - 1)
			{
				ft_putendl_fd(\
"minishell-4.2$: syntax error near unexpected token `newline'", 2);
				g_global.status = 258;
				return (1);
			}
		}
		else if (cmdlist->tokens->tkn_pos[i] + 1 == \
		cmdlist->tokens->tkn_pos[i + 1])
		{
			ft_putstr_fd("minishell-4.2$: syntax error near token ", 2);
			ft_putendl_fd(cmdlist->tokens->token[i + 1], 2);
			g_global.status = 258;
			return (1);
		}
		i++;
	}
	return (0);
}
