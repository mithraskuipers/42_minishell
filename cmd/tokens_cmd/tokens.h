/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   tokens.h                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: rkieboom <rkieboom@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/08/27 03:29:49 by rkieboom      #+#    #+#                 */
/*   Updated: 2022/10/29 00:11:22 by mikuiper      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOKENS_H
# define TOKENS_H

# include "../cmd.h"

void	count_tokens(t_ms *v, t_newcommand *temp, int k);
void	init_new_tokens(t_newcommand *cmd);
void	set_tokens(t_ms *v, t_newcommand *pipes, int k);
void	set_heredoc_tokens(t_ms *ms, t_newcommand *cmd, int k);

#endif