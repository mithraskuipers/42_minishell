/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parser_command_creation.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: rkieboom <rkieboom@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/03/17 12:47:40 by rkieboom      #+#    #+#                 */
/*   Updated: 2022/10/29 01:06:46 by mikuiper      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cmd.h"

//If there is no pipes we just create one simpe CMD
static void	parser_command_no_pipes(t_ms *v, t_cmdlist *cmd, int k)
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
int	parser_command_creation(t_ms *ms, int k)
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
			parser_command_no_pipes(ms, &ms->cmd[i], i);
		else
			parser_command_pipes(ms, &ms->cmd[i], pipes, i);
		if (ms->tokens[i].n_tokens)
			tokens_cmd(ms, &ms->cmd[i], i);
		i++;
	}
	return (0);
}
