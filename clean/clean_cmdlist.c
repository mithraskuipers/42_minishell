/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   clean_cmdlist.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: mikuiper <mikuiper@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/29 13:13:34 by mikuiper      #+#    #+#                 */
/*   Updated: 2022/10/29 18:18:05 by mikuiper      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

// TODO: created separate function free_cmdlist_tokens() for clarity and 
// improving readability of free_cmdlist().

#include "../header.h"

static void	free_cmdlist_tokens(t_cmdlist *temp)
{
	free(temp->tokens->token);
	free(temp->tokens->token_pos);
	free(temp->tokens);	
}

static void	free_cmdlist(t_cmdlist *temp, int k)
{
	int	j;

	j = 0;
	while (temp->command && temp->command[j])
	{
		free(temp->command[j]);
		j++;
	}
	if (temp->command)
		free(temp->command);
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


// TODO: Removed arguments 2 and 3, added those inside the function
void	clean_cmdlist(t_ms *ms, int n_cmds)
{
	int	i;
	int	k;
	t_cmdlist	*temp1;
	t_cmdlist	*temp2;

	temp1 = 0;
	temp2 = 0;
	i = 0;
	while (n_cmds)
	{
		k = 0;
		temp1 = &ms->cmd[i];
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
	free(ms->cmd);
}
