/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   tokens.h                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: rkieboom <rkieboom@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/08/27 03:29:49 by rkieboom      #+#    #+#                 */
/*   Updated: 2022/10/29 13:43:39 by mikuiper      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOKENS_H
# define TOKENS_H

# include "../cmd.h"

void	count_tokens(t_ms *v, t_cmdlist *temp, int k);
void	init_new_tokens(t_cmdlist *cmdlist);
void	set_tokens(t_ms *v, t_cmdlist *pipes, int k);
void	set_heredoc_tokens(t_ms *ms, t_cmdlist *cmdlist, int k);

#endif