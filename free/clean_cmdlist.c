/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   clean_cmdlist.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: mikuiper <mikuiper@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/29 13:13:34 by mikuiper      #+#    #+#                 */
/*   Updated: 2022/10/31 17:13:13 by rkieboom      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../header.h"

static void	free_cmdlist_tokens(t_cmdlist *temp)
{
	free(temp->tokens->token);
	free(temp->tokens->tkn_pos);
	free(temp->tokens);
}

static void	free_cmdlist(t_cmdlist *temp, int k)
{
	int	j;

	j = 0;
	while (temp->cmd_array && temp->cmd_array[j])
	{
		free(temp->cmd_array[j]);
		j++;
	}
	if (temp->cmd_array)
		free(temp->cmd_array);
	if (temp->tokens && temp->tokens->n_tokens == 0)
		free(temp->tokens);
	else if (temp->tokens)
	{	
		j = 0;
		while (temp->tokens->token[j])
		{
			free(temp->tokens->token[j]);
			j++;
		}
		free_cmdlist_tokens(temp);
	}
	if (k != 0)
		free(temp);
}

void	clean_cmdlist(t_ms *ms, int n_cmds)
{
	int			i;
	int			k;
	t_cmdlist	*temp1;
	t_cmdlist	*temp2;

	temp1 = 0;
	temp2 = 0;
	i = 0;
	while (n_cmds)
	{
		k = 0;
		temp1 = &ms->cmdlists[i];
		while (temp1)
		{
			temp2 = temp1->next;
			free_cmdlist(temp1, k);
			temp1 = temp2;
			k++;
		}
		i++;
		n_cmds--;
	}
	free(ms->cmdlists);
}
