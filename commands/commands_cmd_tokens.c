/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   commands_cmd_tokens.c                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: mikuiper <mikuiper@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/30 17:26:48 by mikuiper      #+#    #+#                 */
/*   Updated: 2022/10/30 17:26:50 by mikuiper      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "tokens.h"

//Sets the tokens to CMD
void	commands_cmd_tokens(t_ms *v, t_cmdlist *cmdlist, int k)
{
	t_cmdlist	*temp;

	temp = cmdlist;
	if (v->tokens[k].n_tokens == 0)
		return ;
	while (temp)
	{
		temp->tokens = ft_calloc(1, sizeof(t_tokens));
		if (!temp->tokens)
			return_exit(1, PRNT_ERRNO_NL);
		temp = temp->next;
	}
	commands_cmd_tokens_count(v, cmdlist, k);
	commands_cmd_tokens_init(cmdlist);
	commands_tokens_dup(v, cmdlist, k);
}
