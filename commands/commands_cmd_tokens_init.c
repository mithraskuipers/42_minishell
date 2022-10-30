/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   commands_tokens_init.c                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: mikuiper <mikuiper@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/30 14:32:04 by mikuiper      #+#    #+#                 */
/*   Updated: 2022/10/30 14:36:23 by mikuiper      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "tokens.h"

//Allocate the token variables
void	commands_cmd_tokens_init(t_cmdlist *cmd)
{
	t_cmdlist	*temp;

	temp = cmd;
	while (temp)
	{
		if (temp->tokens && temp->tokens->n_tokens > 0)
		{
			temp->tokens->token = \
			ft_calloc(temp->tokens->n_tokens + 1, sizeof(char *));
			if (!temp->tokens->token)
				return_exit(1, PRNT_ERRNO_NL);
			temp->tokens->token[temp->tokens->n_tokens] = 0;
			temp->tokens->token_pos = \
			ft_calloc(temp->tokens->n_tokens + 1, sizeof(int));
			if (!temp->tokens->token_pos)
				return_exit(1, PRNT_ERRNO_NL);
			temp->tokens->token_pos[temp->tokens->n_tokens] = 0;
		}
		temp = temp->next;
	}
}
