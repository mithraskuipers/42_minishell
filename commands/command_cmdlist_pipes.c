/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   command_cmdlist_pipes.c                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: mikuiper <mikuiper@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/30 11:20:38 by mikuiper      #+#    #+#                 */
/*   Updated: 2022/10/30 11:28:30 by mikuiper      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cmd.h"

//Returns location of the pipe
// 

/**
 * @param token_pos = Is the x token we want
 * 
 * *		 [0]  [1]  [2][3][4][5][6][7]
 * *Example: cat main.c > out | cat | head
 * *token_pos = 0 will return 4
 * *token_pos = 1 will return 6
**/

int	command_get_pipe_pos(t_ms *v, int k, int token_pos)
{
	int	i;
	int	len;

	i = 0;
	len = 0;
	while (i < v->tokens[k].n_tokens)
	{
		if (v->tokens[k].token[i][0] == '|')
		{
			if (len == token_pos)
				return (v->tokens[k].token_pos[i]);
			len++;
		}
		i++;
	}
	return (-1);
}

//Creates the first CMD
static void	command_cmdlist_first(t_ms *v, t_cmdlist *temp, int k)
{
	int	i;
	int	j;

	i = 0;
	j = command_get_pipe_pos(v, k, 0);
	if (j == -1)
		ft_error("Something went wrong func command_cmdlist_first!\n");
	temp->command = ft_calloc(j + 1, sizeof(char *));
	if (!temp->command)
		return_exit(1, PRNT_ERRNO_NL);
	while (j)
	{
		temp->command[i] = ft_strdup(v->parse.commands[k][i]);
		if (!temp->command[i])
			return_exit(1, PRNT_ERRNO_NL);
		j--;
		i++;
	}
}

//Creates all CMD's in the middle
static void	command_cmdlist_middle(t_ms *v, t_cmdlist *temp, int pipes, int k)
{
	int	i;
	int	j;
	int	l;

	i = command_get_pipe_pos(v, k, pipes - 1);
	if (i == -1)
		ft_error("Something went wrong in func command_cmdlist_middle\n");
	j = command_get_pipe_pos(v, k, pipes);
	if (j == -1)
		ft_error("Something went wrong in func command_cmdlist_middle\n");
	temp->command = ft_calloc(j - i, sizeof(char *));
	if (!temp->command)
		return_exit(1, PRNT_ERRNO_NL);
	j = j - i - 1;
	i++;
	l = 0;
	while (j)
	{
		temp->command[l] = ft_strdup(v->parse.commands[k][i]);
		if (!temp->command[l])
			return_exit(1, PRNT_ERRNO_NL);
		l++;
		i++;
		j--;
	}
}

//Creates the last CMD
static void	command_cmdlist_last(t_ms *v, t_cmdlist *temp, int pipes, int k)
{
	int	i;
	int	j;
	int	l;

	i = 0;
	j = command_get_pipe_pos(v, k, pipes);
	while (v->parse.commands[k][i + j])
		i++;
	i += j;
	if (i - j == 1)
		return ;
	temp->command = ft_calloc(i - j, sizeof(char *));
	if (!temp->command)
		return_exit(1, PRNT_ERRNO_NL);
	j = i - j - 1;
	i = 0;
	l = command_get_pipe_pos(v, k, pipes) + 1;
	while (j)
	{
		temp->command[i] = ft_strdup(v->parse.commands[k][l + i]);
		if (!temp->command[i])
			return_exit(1, PRNT_ERRNO_NL);
		i++;
		j--;
	}
}

// command_cmdlist_pipes() fills the t_cmdlist struct for a command that
// contains multiple commands, separated from eachother by a pipe operator.
// It will result in a linked list neighbouring nodes (i.e. next nodes).
void	command_cmdlist_pipes(t_ms *v, t_cmdlist *pipes_cmd, int pipes, int k)
{
	int			i;
	t_cmdlist	*cmdlist;

	cmdlist = pipes_cmd;
	i = 0;
	while (pipes + 1)
	{
		cmdlist->id = i;
		if (i == 0)
			command_cmdlist_first(v, cmdlist, k);
		else if (pipes == 0)
			command_cmdlist_last(v, cmdlist, v->tokens[k].pipe - 1, k);
		else
			command_cmdlist_middle(v, cmdlist, i, k);
		i++;
		pipes--;
		if (pipes >= 0)
		{
			cmdlist->next = ft_calloc(1, sizeof(t_cmdlist));
			if (!cmdlist->next)
				return_exit(1, PRNT_ERRNO_NL);
			cmdlist->next->prev = cmdlist;
			cmdlist = cmdlist->next;
		}
	}
}

//cat main.c | cat | cat | cat | cat | cat
