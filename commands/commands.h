/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   commands.h                                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: rkieboom <rkieboom@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/03/17 13:45:45 by rkieboom      #+#    #+#                 */
/*   Updated: 2022/10/30 14:36:23 by mikuiper      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef CMD_H
# define CMD_H

# include "../header.h"

void	commands_cmd_cmdlist_pipes(t_ms *v, t_cmdlist *temp, int pipes, int k);
void	commands_cmd_tokens(t_ms *v, t_cmdlist *pipes, int k);

#endif