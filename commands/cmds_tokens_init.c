/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cmds_tokens_init.c                                 :+:    :+:            */
/*                                                     +:+                    */
/*   By: mikuiper <mikuiper@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/31 07:40:55 by mikuiper      #+#    #+#                 */
/*   Updated: 2022/10/31 07:42:16 by mikuiper      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cmds_tokens.h"

//Allocate the token variables
void	cmds_tokens_init(t_cmdlist *cmd)
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
			temp->tokens->tkn_pos = \
			ft_calloc(temp->tokens->n_tokens + 1, sizeof(int));
			if (!temp->tokens->tkn_pos)
				return_exit(1, PRNT_ERRNO_NL);
			temp->tokens->tkn_pos[temp->tokens->n_tokens] = 0;
		}
		temp = temp->next;
	}
}
