/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cmds_cmdlist_pipes.c                               :+:    :+:            */
/*                                                     +:+                    */
/*   By: mikuiper <mikuiper@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/31 07:40:22 by mikuiper      #+#    #+#                 */
/*   Updated: 2022/10/31 07:41:40 by mikuiper      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cmds.h"

//Returns location of the pipe
// 

/**
 * @param tkn_pos = Is the x token we want
 * 
 * *		 [0]  [1]  [2][3][4][5][6][7]
 * *Example: cat main.c > out | cat | head
 * *tkn_pos = 0 will return 4
 * *tkn_pos = 1 will return 6
**/

int	cmds_get_pipe_pos(t_ms *v, int k, int tkn_pos)
{
	int	i;
	int	len;

	i = 0;
	len = 0;
	while (i < v->tokens[k].n_tokens)
	{
		if (v->tokens[k].token[i][0] == '|')
		{
			if (len == tkn_pos)
				return (v->tokens[k].tkn_pos[i]);
			len++;
		}
		i++;
	}
	return (-1);
}

//Creates the first CMD
static void	cmds_cmdlist_first(t_ms *v, t_cmdlist *cmdlist, int k)
{
	int	i;
	int	j;

	i = 0;
	j = cmds_get_pipe_pos(v, k, 0);
	if (j == -1)
		ms_error("Something went wrong func cmds_cmdlist_first!\n");
	cmdlist->cmd_array = ft_calloc(j + 1, sizeof(char *));
	if (!cmdlist->cmd_array)
		return_exit(1, PRNT_ERRNO_NL);
	while (j)
	{
		cmdlist->cmd_array[i] = ft_strdup(v->parser.commands[k][i]);
		if (!cmdlist->cmd_array[i])
			return_exit(1, PRNT_ERRNO_NL);
		j--;
		i++;
	}
}

//Creates all CMD's in the middle
static void	cmds_cmdlist_middle(t_ms *v, t_cmdlist *cmdlist, int pipes, int k)
{
	int	i;
	int	j;
	int	l;

	i = cmds_get_pipe_pos(v, k, pipes - 1);
	if (i == -1)
		ms_error("Something went wrong in func cmds_cmdlist_middle\n");
	j = cmds_get_pipe_pos(v, k, pipes);
	if (j == -1)
		ms_error("Something went wrong in func cmds_cmdlist_middle\n");
	cmdlist->cmd_array = ft_calloc(j - i, sizeof(char *));
	if (!cmdlist->cmd_array)
		return_exit(1, PRNT_ERRNO_NL);
	j = j - i - 1;
	i++;
	l = 0;
	while (j)
	{
		cmdlist->cmd_array[l] = ft_strdup(v->parser.commands[k][i]);
		if (!cmdlist->cmd_array[l])
			return_exit(1, PRNT_ERRNO_NL);
		l++;
		i++;
		j--;
	}
}

//Creates the last CMD
static void	cmds_cmdlist_last(t_ms *v, t_cmdlist *cmdlist, int pipes, int k)
{
	int	i;
	int	j;
	int	l;

	i = 0;
	j = cmds_get_pipe_pos(v, k, pipes);
	while (v->parser.commands[k][i + j])
		i++;
	i += j;
	if (i - j == 1)
		return ;
	cmdlist->cmd_array = ft_calloc(i - j, sizeof(char *));
	if (!cmdlist->cmd_array)
		return_exit(1, PRNT_ERRNO_NL);
	j = i - j - 1;
	i = 0;
	l = cmds_get_pipe_pos(v, k, pipes) + 1;
	while (j)
	{
		cmdlist->cmd_array[i] = ft_strdup(v->parser.commands[k][l + i]);
		if (!cmdlist->cmd_array[i])
			return_exit(1, PRNT_ERRNO_NL);
		i++;
		j--;
	}
}

// cmds_cmdlist_pipes() fills the t_cmdlist struct for a command that
// contains multiple commands, separated from eachother by a pipe operator.
// It will result in a linked list neighbouring nodes (i.e. next nodes).
void	cmds_cmdlist_pipes(t_ms *v, t_cmdlist *pipes_cmd, int pipes, int k)
{
	int			i;
	t_cmdlist	*cmdlist;

	cmdlist = pipes_cmd;
	i = 0;
	while (pipes + 1)
	{
		cmdlist->id = i;
		if (i == 0)
			cmds_cmdlist_first(v, cmdlist, k);
		else if (pipes == 0)
			cmds_cmdlist_last(v, cmdlist, v->tokens[k].pipe - 1, k);
		else
			cmds_cmdlist_middle(v, cmdlist, i, k);
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
