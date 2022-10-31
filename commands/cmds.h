/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cmds.h                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: mikuiper <mikuiper@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/31 07:43:03 by mikuiper      #+#    #+#                 */
/*   Updated: 2022/10/31 07:43:04 by mikuiper      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef CMDS_H
# define CMDS_H

# include "../header.h"

void	cmds_cmdlist_pipes(t_ms *v, t_cmdlist *temp, int pipes, int k);
void	cmds_set_tokens_cmdlist(t_ms *v, t_cmdlist *pipes, int k);

#endif