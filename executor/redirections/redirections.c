/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   redirections.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: rkieboom <rkieboom@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/11 22:09:17 by rkieboom      #+#    #+#                 */
/*   Updated: 2022/10/29 13:55:17 by mikuiper      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../execute.h"

int	tokens_exist(t_cmdlist *cmdlist)
{
	if (cmdlist->tokens && cmdlist->tokens->total > 0)
		return (1);
	else
		return (0);
}

int	redir_left(t_cmdlist *cmdlist)
{
	if (!ft_strncmp(cmdlist->command[cmdlist->tokens->last_l], "<<", 3))
	{
		heredoc_set_pipe(&cmdlist->tokens->heredoc \
	[cmdlist->tokens->double_redirection_left - 1], \
cmdlist->tokens->heredoc[cmdlist->tokens->double_redirection_left - 1].data);
		if (dup2(cmdlist->tokens->heredoc \
	[cmdlist->tokens->double_redirection_left - 1].pipe[0], 0) < 0)
			return_exit(1, PRNT_ERRNO_NL);
		close(cmdlist->tokens->heredoc \
	[cmdlist->tokens->double_redirection_left - 1].pipe[0]);
		return (0);
	}
	cmdlist->tokens->stdin_fd = open(cmdlist->command[cmdlist->tokens->last_l + 1], O_RDONLY);
	if (cmdlist->tokens->stdin_fd < 0)
	{
		ft_putstr_fd("minishell-4.2$: no such file or directory: ", 2);
		ft_putstr_fd(cmdlist->command[cmdlist->tokens->last_l + 1], 2);
		ft_putchar_fd('\n', 2);
		return (1);
	}
	if (dup2(cmdlist->tokens->stdin_fd, 0) < 0)
		return_exit(1, PRNT_ERRNO_NL);
	close(cmdlist->tokens->stdin_fd);
	return (0);
}

int	redir_right(t_cmdlist *cmdlist)
{
	if (!strncmp(cmdlist->command[cmdlist->tokens->last_r], ">>", 3))
		cmdlist->tokens->stdout_fd = open(\
		cmdlist->command[cmdlist->tokens->last_r + 1], O_RDWR | O_APPEND | O_CREAT, 0644);
	else
		cmdlist->tokens->stdout_fd = open(\
		cmdlist->command[cmdlist->tokens->last_r + 1], O_RDWR | O_TRUNC | O_CREAT, 0644);
	if (cmdlist->tokens->stdout_fd < 0)
	{
		return_exit(0, 1);
		return (1);
	}
	if (dup2(cmdlist->tokens->stdout_fd, 1) < 0)
		return_exit(1, PRNT_ERRNO_NL);
	close(cmdlist->tokens->stdout_fd);
	return (0);
}

int	redirections(t_cmdlist *cmdlist)
{
	if (tokens_exist(cmdlist) && loop_over_redirs(cmdlist, 0, cmdlist->tokens->total))
		return (1);
	if (tokens_exist(cmdlist) && cmdlist->tokens->last_l != -1)
	{
		if (redir_left(cmdlist))
			return (1);
	}
	if (tokens_exist(cmdlist) && cmdlist->tokens->last_r != -1)
	{
		if (redir_right(cmdlist))
			return (1);
	}
	return (0);
}
