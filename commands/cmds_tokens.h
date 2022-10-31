/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cmds_tokens.h                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: mikuiper <mikuiper@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/31 07:43:22 by mikuiper      #+#    #+#                 */
/*   Updated: 2022/10/31 07:43:28 by mikuiper      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef CMDS_TOKENS_H
# define CMDS_TOKENS_H

# include "cmds.h"

void	cmds_tokens_count(t_ms *v, t_cmdlist *temp, int k);
void	cmds_tokens_init(t_cmdlist *cmdlist);
void	set_heredoc_tokens(t_ms *ms, t_cmdlist *cmd, int k);
void	cmds_tokens_dup(t_ms *v, t_cmdlist *pipes, int k);
void	cmds_set_tokens_cmdlist(t_ms *v, t_cmdlist *cmdlist, int k);

#endif