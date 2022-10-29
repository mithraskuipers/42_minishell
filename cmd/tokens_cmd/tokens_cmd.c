/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   tokens_cmd.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: rkieboom <rkieboom@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/03/17 16:25:48 by rkieboom      #+#    #+#                 */
/*   Updated: 2022/10/29 13:47:07 by mikuiper      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "tokens.h"

//Sets the tokens to CMD
void	tokens_cmd(t_ms *v, t_cmdlist *cmdlist, int k)
{
	t_cmdlist	*temp;

	temp = cmdlist;
	if (v->tokens[k].total == 0)
		return ;
	while (temp)
	{
		temp->tokens = ft_calloc(1, sizeof(t_tokens));
		if (!temp->tokens)
			return_exit(1, PRNT_ERRNO_NL);
		temp = temp->next;
	}
	count_tokens(v, cmdlist, k);
	init_new_tokens(cmdlist);
	set_tokens(v, cmdlist, k);
}
