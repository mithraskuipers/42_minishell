/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parser_command_pipes.c                                 :+:    :+:            */
/*                                                     +:+                    */
/*   By: rkieboom <rkieboom@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/03/17 13:14:16 by rkieboom      #+#    #+#                 */
/*   Updated: 2022/10/29 01:06:46 by mikuiper      ########   odam.nl         */
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
int	pipe_location(t_ms *v, int k, int token_pos)
{
	int	i;
	int	len;

	i = 0;
	len = 0;
	while (i < v->tokens[k].total)
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
static void	first_cmd(t_ms *v, t_cmdlist *temp, int k)
{
	int	i;
	int	j;

	i = 0;
	j = pipe_location(v, k, 0);
	if (j == -1)
		ft_error("Something went wrong func first_cmd!\n");
	temp->command = ft_calloc(j + 1, sizeof(char *));
	if (!temp->command)
		return_exit(1, PRNT_ERRNO_NL);
	while (j)
	{
		temp->command[i] = ft_strdup(v->input.cmds[k][i]);
		if (!temp->command[i])
			return_exit(1, PRNT_ERRNO_NL);
		j--;
		i++;
	}
}

//Creates all CMD's in the middle
static void	middle_cmd(t_ms *v, t_cmdlist *temp, int pipes, int k)
{
	int	i;
	int	j;
	int	l;

	i = pipe_location(v, k, pipes - 1);
	if (i == -1)
		ft_error("Something went wrong in func middle_cmd\n");
	j = pipe_location(v, k, pipes);
	if (j == -1)
		ft_error("Something went wrong in func middle_cmd\n");
	temp->command = ft_calloc(j - i, sizeof(char *));
	if (!temp->command)
		return_exit(1, PRNT_ERRNO_NL);
	j = j - i - 1;
	i++;
	l = 0;
	while (j)
	{
		temp->command[l] = ft_strdup(v->input.cmds[k][i]);
		if (!temp->command[l])
			return_exit(1, PRNT_ERRNO_NL);
		l++;
		i++;
		j--;
	}
}

//Creates the last CMD
static void	last_cmd(t_ms *v, t_cmdlist *temp, int pipes, int k)
{
	int	i;
	int	j;
	int	l;

	i = 0;
	j = pipe_location(v, k, pipes);
	while (v->input.cmds[k][i + j])
		i++;
	i += j;
	if (i - j == 1)
		return ;
	temp->command = ft_calloc(i - j, sizeof(char *));
	if (!temp->command)
		return_exit(1, PRNT_ERRNO_NL);
	j = i - j - 1;
	i = 0;
	l = pipe_location(v, k, pipes) + 1;
	while (j)
	{
		temp->command[i] = ft_strdup(v->input.cmds[k][l + i]);
		if (!temp->command[i])
			return_exit(1, PRNT_ERRNO_NL);
		i++;
		j--;
	}
}

//Make multiple commands
void	parser_command_pipes(t_ms *v, t_cmdlist *pipes_cmd, int pipes, int k)
{
	int				i;
	t_cmdlist	*temp;

	temp = pipes_cmd;
	i = 0;
	while (pipes + 1)
	{
		temp->id = i;
		if (i == 0)
			first_cmd(v, temp, k);
		else if (pipes == 0)
			last_cmd(v, temp, v->tokens[k].pipe - 1, k);
		else
			middle_cmd(v, temp, i, k);
		i++;
		pipes--;
		if (pipes >= 0)
		{
			temp->next = ft_calloc(1, sizeof(t_cmdlist));
			if (!temp->next)
				return_exit(1, PRNT_ERRNO_NL);
			temp->next->prev = temp;
			temp = temp->next;
		}
	}
}
//cat main.c | cat | cat | cat | cat | cat


