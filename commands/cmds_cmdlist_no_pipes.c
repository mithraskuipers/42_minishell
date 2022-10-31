/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cmds_cmdlist_no_pipes.c                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: mikuiper <mikuiper@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/31 07:40:30 by mikuiper      #+#    #+#                 */
/*   Updated: 2022/10/31 07:41:40 by mikuiper      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cmds.h"

// cmds_cmdlist_no_pipes() fills the t_cmdlist struct for a single command 
// (i.e. command without pipes). It will result in a linked list without
// neighbouring nodes (i.e. no next).
static void	cmds_cmdlist_no_pipes(t_ms *v, t_cmdlist *cmdlist, int k)
{
	int	i;

	i = 0;
	while (v->parser.commands[k][i])
		i++;
	cmdlist->cmd_array = ft_calloc(i + 1, sizeof(char *));
	if (!cmdlist->cmd_array)
		return_exit(1, PRNT_ERRNO_NL);
	i = 0;
	while (v->parser.commands[k][i])
	{
		cmdlist->cmd_array[i] = ft_strdup(v->parser.commands[k][i]);
		if (!cmdlist->cmd_array[i])
			return_exit(1, PRNT_ERRNO_NL);
		i++;
	}
}

// Creates a command struct with the data from the parse and token structs.
// Used to execute the commands
// 
int	cmds_cmdlists_maker(t_ms *ms)
{
	int	i;
	int	n_cmds;
	int	pipes;

	i = 0;
	n_cmds = 0;
	while (ms->parser.commands[n_cmds])
		n_cmds++;
	ms->cmdlists = ft_calloc(n_cmds, sizeof(t_cmdlist));
	if (!ms->cmdlists)
		return_exit(1, PRNT_ERRNO_NL);
	while (i < n_cmds)
	{
		pipes = ms->tokens[i].pipe;
		if (pipes == 0)
			cmds_cmdlist_no_pipes(ms, &ms->cmdlists[i], i);
		else
			cmds_cmdlist_pipes(ms, &ms->cmdlists[i], pipes, i);
		if (ms->tokens[i].n_tokens)
			cmds_set_tokens_cmdlist(ms, &ms->cmdlists[i], i);
		i++;
	}
	return (0);
}
