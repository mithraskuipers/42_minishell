/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   execute.h                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: rkieboom <rkieboom@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/11 15:33:40 by rkieboom      #+#    #+#                 */
/*   Updated: 2022/10/29 18:28:25 by mikuiper      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTE_H
# define EXECUTE_H

# include "../builtin/commands.h"
# include "../header.h"
# include <sys/wait.h>

/**
 * 
 * executor
 * 
**/

void	executor_single_cmd(t_ms *ms, t_cmdlist *cmd);
void	executor_pipe_cmd(t_ms *ms, t_cmdlist *cmd);
void	run_cmd(t_ms *ms, char **cmd, int quit);

/**
 * 
 * redirs
 * 
**/
void	heredoc_set_pipe(t_heredoc *heredoc, t_heredoc_data *data);
int		redirs_looper(t_cmdlist *v, int i, int n_tokens);
int		redir_left(t_cmdlist *v);
int		redir_right(t_cmdlist *v);
int		redirs(t_cmdlist *cmd);
int		tokens_present(t_cmdlist *cmd);

/**
 * 
 * Extra
 * 
**/

int		ft_pipe(int *fd);
int		ft_fork(pid_t *pid, int *fd);
int		get_return_status(int status);

char	**set_cmd(t_cmdlist *cmd);
void	executor_builtin(t_ms *ms, t_cmdlist *cmd, char **command, int token_exist);
void	executor_pipe_stuff(t_cmdlist *cmd);
int		exit_status(int status);

#endif
