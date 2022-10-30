/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   commands_cmd_cmdlist_no_pipes.c               :+:    :+:            */
/*                                                     +:+                    */
/*   By: mikuiper <mikuiper@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/30 11:20:23 by mikuiper      #+#    #+#                 */
/*   Updated: 2022/10/30 11:29:05 by mikuiper      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "commands.h"

// commands_cmd_cmdlist_no_pipes() fills the t_cmdlist struct for a single command 
// (i.e. command without pipes). It will result in a linked list without
// neighbouring nodes (i.e. no next).
static void	commands_cmd_cmdlist_no_pipes(t_ms *v, t_cmdlist *cmd, int k)
{
	int	i;

	i = 0;
	while (v->parse.commands[k][i])
		i++;
	cmd->command = ft_calloc(i + 1, sizeof(char *));
	if (!cmd->command)
		return_exit(1, PRNT_ERRNO_NL);
	i = 0;
	while (v->parse.commands[k][i])
	{
		cmd->command[i] = ft_strdup(v->parse.commands[k][i]);
		if (!cmd->command[i])
			return_exit(1, PRNT_ERRNO_NL);
		i++;
	}
}

// Creates a command struct with the data from the parse and token structs.
// Used to execute the commands
// 
int	commands_cmdlists_maker(t_ms *ms, int k)
{
	int	i;
	int	pipes;

	i = 0;
	while (ms->parse.commands[k])
		k++;
	ms->cmd = ft_calloc(k, sizeof(t_cmdlist));
	if (!ms->cmd)
		return_exit(1, PRNT_ERRNO_NL);
	while (i < k)
	{
		pipes = ms->tokens[i].pipe;
		if (pipes == 0)
			commands_cmd_cmdlist_no_pipes(ms, &ms->cmd[i], i);
		else
			commands_cmd_cmdlist_pipes(ms, &ms->cmd[i], pipes, i);
		if (ms->tokens[i].n_tokens)
			commands_cmd_tokens(ms, &ms->cmd[i], i);
		i++;
	}
	return (0);
}
