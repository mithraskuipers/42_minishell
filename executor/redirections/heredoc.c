/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   heredoc.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: rkieboom <rkieboom@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/17 12:48:35 by rkieboom      #+#    #+#                 */
/*   Updated: 2022/10/30 13:58:48 by mikuiper      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../executor.h"

void	heredoc_set_pipe(t_heredoc *heredoc, t_heredoc_data *data)
{
	if (pipe(heredoc->pipe) < 0)
		return_exit(1, PRNT_ERRNO_NL);
	while (data)
	{
		ft_putendl_fd(data->str, heredoc->pipe[1]);
		data = data->next;
	}
	close(heredoc->pipe[1]);
}
