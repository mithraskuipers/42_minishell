/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   execute.h                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: rkieboom <rkieboom@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/11 15:33:40 by rkieboom      #+#    #+#                 */
/*   Updated: 2022/10/29 12:42:28 by mikuiper      ########   odam.nl         */
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

void	setup_single_cmd(t_ms *ms, t_cmdlist *cmd);
void	setup_pipe_cmd(t_ms *ms, t_cmdlist *cmd);
void	run_cmd(t_ms *ms, char **cmd, int quit);

/**
 * 
 * Redirections
 * 
**/
void	heredoc_set_pipe(t_heredoc *heredoc, t_heredoc_data *data);
int		loop_over_redirs(t_cmdlist *v, int i, int total);
int		redir_left(t_cmdlist *v);
int		redir_right(t_cmdlist *v);
int		redirections(t_cmdlist *cmd);
int		tokens_exist(t_cmdlist *cmd);

/**
 * 
 * Extra
 * 
**/

int		ft_pipe(int *fd);
int		ft_fork(pid_t *pid, int *fd);
int		get_return_status(int status);

char	**set_cmd(t_cmdlist *cmd);
void	setup_builtin(t_ms *ms, t_cmdlist *cmd, char **command, int token_exist);
void	setup_pipe_stuff(t_cmdlist *cmd);
int		exit_status(int status);

#endif
