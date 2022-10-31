/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   executor.h                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: mikuiper <mikuiper@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/30 17:19:41 by mikuiper      #+#    #+#                 */
/*   Updated: 2022/10/31 07:41:40 by mikuiper      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTOR_H
# define EXECUTOR_H

# include "../builtins/cmds.h"
# include "../header.h"
# include <sys/wait.h>

// Executor
void	executor_cmd_portal(t_ms *ms, char **cmd, int quit);
void	executor_run_multiple_cmds(t_ms *ms, t_cmdlist *cmdlist);
void	executor_run_single_command(t_ms *ms, t_cmdlist *cmdlist);

// Redirections
int		redir_left(t_cmdlist *v);
int		redir_right(t_cmdlist *v);
int		redirs_looper(t_cmdlist *v, int i, int n_tokens);
int		redirs(t_cmdlist *cmdlist);
int		tokens_present(t_cmdlist *cmdlist);
void	heredoc_set_pipe(t_heredoc *heredoc, t_heredoc_data *data);

// miscellaneous
int		ft_pipe(int *fd);
int		ft_fork(pid_t *pid, int *fd);
int		get_return_status(int status);
char	**executor_get_command(t_cmdlist *cmd);
void	executor_run_builtin(t_ms *ms, t_cmdlist *cmdlist, char **command, \
int token_exist);
void	executor_pipe_stuff(t_cmdlist *cmd);
int		exit_status(int status);

#endif
