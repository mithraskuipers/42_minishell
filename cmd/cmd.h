/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cmd.h                                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: rkieboom <rkieboom@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/03/17 13:45:45 by rkieboom      #+#    #+#                 */
/*   Updated: 2022/08/27 03:23:56 by rkieboom      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef CMD_H
# define CMD_H

# include "../header.h"

void	declaring_values(t_list *v, t_newcommand *temp, int pipes, int k);
void	tokens_cmd(t_list *v, t_newcommand *pipes, int k);

#endif