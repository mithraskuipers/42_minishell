/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   tokens.h                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: rkieboom <rkieboom@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/08/27 03:29:49 by rkieboom      #+#    #+#                 */
/*   Updated: 2022/10/30 16:11:45 by mikuiper      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOKENS_H
# define TOKENS_H

# include "commands.h"

void	commands_cmd_tokens_count(t_ms *v, t_cmdlist *temp, int k);
void	commands_cmd_tokens_init(t_cmdlist *cmdlist);
void	set_heredoc_tokens(t_ms *ms, t_cmdlist *cmd, int k);
void	commands_tokens_dup(t_ms *v, t_cmdlist *pipes, int k);

#endif