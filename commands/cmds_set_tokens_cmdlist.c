/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cmds_set_tokens_cmdlist.c                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: mikuiper <mikuiper@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/31 07:40:38 by mikuiper      #+#    #+#                 */
/*   Updated: 2022/10/31 07:42:16 by mikuiper      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cmds_tokens.h"

//Sets the tokens to CMD
void	cmds_set_tokens_cmdlist(t_ms *v, t_cmdlist *cmdlist, int k)
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
	cmds_tokens_count(v, cmdlist, k);
	cmds_tokens_init(cmdlist);
	cmds_tokens_dup(v, cmdlist, k);
}
