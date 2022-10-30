/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   redirs.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: mikuiper <mikuiper@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/29 18:08:07 by mikuiper      #+#    #+#                 */
/*   Updated: 2022/10/30 13:58:48 by mikuiper      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../executor.h"

int	tokens_present(t_cmdlist *cmd)
{
	if (cmd->tokens && cmd->tokens->n_tokens > 0)
		return (1);
	else
		return (0);
}

int	redir_left(t_cmdlist *v)
{
	if (!ft_strncmp(v->command[v->tokens->last_l], "<<", 3))
	{
		heredoc_set_pipe(&v->tokens->heredoc \
	[v->tokens->double_redirection_left - 1], \
v->tokens->heredoc[v->tokens->double_redirection_left - 1].data);
		if (dup2(v->tokens->heredoc \
	[v->tokens->double_redirection_left - 1].pipe[0], 0) < 0)
			return_exit(1, PRNT_ERRNO_NL);
		close(v->tokens->heredoc \
	[v->tokens->double_redirection_left - 1].pipe[0]);
		return (0);
	}
	v->tokens->stdin_fd = open(v->command[v->tokens->last_l + 1], O_RDONLY);
	if (v->tokens->stdin_fd < 0)
	{
		ft_putstr_fd("minishell-4.2$: no such file or directory: ", 2);
		ft_putstr_fd(v->command[v->tokens->last_l + 1], 2);
		ft_putchar_fd('\n', 2);
		return (1);
	}
	if (dup2(v->tokens->stdin_fd, 0) < 0)
		return_exit(1, PRNT_ERRNO_NL);
	close(v->tokens->stdin_fd);
	return (0);
}

int	redir_right(t_cmdlist *v)
{
	if (!strncmp(v->command[v->tokens->last_r], ">>", 3))
		v->tokens->stdout_fd = open(\
		v->command[v->tokens->last_r + 1], O_RDWR | O_APPEND | O_CREAT, 0644);
	else
		v->tokens->stdout_fd = open(\
		v->command[v->tokens->last_r + 1], O_RDWR | O_TRUNC | O_CREAT, 0644);
	if (v->tokens->stdout_fd < 0)
	{
		return_exit(0, 1);
		return (1);
	}
	if (dup2(v->tokens->stdout_fd, 1) < 0)
		return_exit(1, PRNT_ERRNO_NL);
	close(v->tokens->stdout_fd);
	return (0);
}

int	redirs(t_cmdlist *cmdlist)
{
	if (tokens_present(cmdlist) && redirs_looper(cmdlist, 0, \
	cmdlist->tokens->n_tokens))
		return (1);
	if (tokens_present(cmdlist) && cmdlist->tokens->last_l != -1)
	{
		if (redir_left(cmdlist))
			return (1);
	}
	if (tokens_present(cmdlist) && cmdlist->tokens->last_r != -1)
	{
		if (redir_right(cmdlist))
			return (1);
	}
	return (0);
}
