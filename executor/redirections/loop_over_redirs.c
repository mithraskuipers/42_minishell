/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   loop_over_redirs.c                                 :+:    :+:            */
/*                                                     +:+                    */
/*   By: rkieboom <rkieboom@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/11 21:58:05 by rkieboom      #+#    #+#                 */
/*   Updated: 2022/10/29 13:54:05 by mikuiper      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../execute.h"

static int	single_redirection_right(t_cmdlist *cmdlist, int i)
{
	cmdlist->tokens->stdout_fd = open(\
	cmdlist->command[cmdlist->tokens->token_pos[i] + 1] \
	, O_RDWR | O_TRUNC | O_CREAT, 0644);
	if (cmdlist->tokens->stdout_fd < 0)
	{
		return_exit(0, 1);
		return (1);
	}
	close(cmdlist->tokens->stdout_fd);
	cmdlist->tokens->last_r = cmdlist->tokens->token_pos[i];
	return (0);
}

static int	double_redirection_right(t_cmdlist *cmdlist, int i)
{
	cmdlist->tokens->stdout_fd = open(\
	cmdlist->command[cmdlist->tokens->token_pos[i] + 1] \
	, O_RDWR | O_APPEND | O_CREAT, 0644);
	if (cmdlist->tokens->stdout_fd < 0)
	{
		return_exit(0, 1);
		return (1);
	}
	close(cmdlist->tokens->stdout_fd);
	cmdlist->tokens->last_r = cmdlist->tokens->token_pos[i];
	return (0);
}

static int	single_redirection_left(t_cmdlist *cmdlist, int i)
{
	cmdlist->tokens->stdin_fd = open(\
	cmdlist->command[cmdlist->tokens->token_pos[i] + 1], O_RDONLY);
	if (cmdlist->tokens->stdin_fd < 0)
	{
		ft_putstr_fd("minishell-4.2$: no such file or directory: ", 2);
		ft_putstr_fd(cmdlist->command[cmdlist->tokens->token_pos[i] + 1], 2);
		ft_putchar_fd('\n', 2);
		return (1);
	}
	close(cmdlist->tokens->stdin_fd);
	cmdlist->tokens->last_l = cmdlist->tokens->token_pos[i];
	return (0);
}

static void	double_redirection_left(t_cmdlist *cmdlist, int i)
{
	cmdlist->tokens->last_l = cmdlist->tokens->token_pos[i];
}

int	loop_over_redirs(t_cmdlist *cmdlist, int i, int total)
{
	cmdlist->tokens->last_l = -1;
	cmdlist->tokens->last_r = -1;
	while (i < total)
	{
		if (!ft_strncmp(cmdlist->tokens->token[i], "<<", 3))
			double_redirection_left(cmdlist, i);
		else if (!ft_strncmp(cmdlist->tokens->token[i], "<", 2))
		{
			if (single_redirection_left(cmdlist, i))
				return (1);
		}
		else if (!ft_strncmp(cmdlist->tokens->token[i], ">>", 3))
		{
			if (double_redirection_right(cmdlist, i))
				return (1);
		}
		else if (!ft_strncmp(cmdlist->tokens->token[i], ">", 2))
		{
			if (single_redirection_right(cmdlist, i))
				return (1);
		}
		i++;
	}
	return (0);
}
