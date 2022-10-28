/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   create_cmd.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: rkieboom <rkieboom@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/03/17 12:47:40 by rkieboom      #+#    #+#                 */
/*   Updated: 2022/10/29 01:06:46 by mikuiper      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cmd.h"

//If there is no pipes we just create one simpe CMD
static void	create_command(t_ms *v, t_newcommand *cmd, int k)
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
int	create_cmd(t_ms *v, int k)
{
	int	i;
	int	pipes;

	i = 0;
	while (v->parse.commands[k])
		k++;
	v->cmd = ft_calloc(k, sizeof(t_newcommand));
	if (!v->cmd)
		return_exit(1, PRNT_ERRNO_NL);
	while (i < k)
	{
		pipes = v->tokens[i].pipe;
		if (pipes == 0)
			create_command(v, &v->cmd[i], i);
		else
			declaring_values(v, &v->cmd[i], pipes, i);
		if (v->tokens[i].total)
			tokens_cmd(v, &v->cmd[i], i);
		i++;
	}
	return (0);
}
