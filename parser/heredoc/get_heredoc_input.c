/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   get_heredoc_input.c                                :+:    :+:            */
/*                                                     +:+                    */
/*   By: mikuiper <mikuiper@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/28 21:57:30 by mikuiper      #+#    #+#                 */
/*   Updated: 2022/10/30 14:50:15 by mikuiper      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../parser.h"
#include <sys/wait.h>

static void	free_and_get_data(t_ms *ms, int k, int i)
{
	if (ms->line.array)
	{
		free(ms->line.array);
		ms->line.array = 0;
	}
	ms->line.array = readline("> ");
	if (!ms->line.array)
		ms->line.array = ft_strdup(ms->tokens[k].heredoc[i].eof);
}

//Saving the actual data
static void	heredoc_write_to_pipe(t_ms *ms, int k, int i)
{
	if (!ms->tokens[k].heredoc->eof)
		return ;
	free_and_get_data(ms, k, i);
	while (ft_strncmp(ms->line.array, \
	ms->tokens[k].heredoc[i].eof, ft_strlen(ms->tokens[k].heredoc[i].eof) + 1))
	{
		write(ms->tokens[k].heredoc[i].pipe[1], ms->line.array, ft_strlen(ms->line.array));
		write(ms->tokens[k].heredoc[i].pipe[1], "\n", 1);
		free_and_get_data(ms, k, i);
	}
	if (ms->line.array)
	{
		free(ms->line.array);
		ms->line.array = 0;
	}
	exit(0);
}

//We read the input for heredoc
//and save it in heredoc data structure
int	get_heredoc_input(t_ms *ms, int k)
{
	int	i;
	int	length;
	int	status;

	i = 0;
	length = ms->tokens[k].double_redirection_left;
	signal(SIGINT, sig_handler);
	signal(SIGQUIT, SIG_IGN);
	while (i < length)
	{
		if (ft_pipe(ms->tokens[k].heredoc[i].pipe))
			return (1);
		if (ft_fork(&g_global.pid, NULL))
		{
			close(ms->tokens[k].heredoc[i].pipe[0]);
			close(ms->tokens[k].heredoc[i].pipe[1]);
			return (1);
		}
		if (!g_global.pid)
		{
			update_signals_default();
			heredoc_write_to_pipe(ms, k, i);
		}
		else
		{
			close(ms->tokens[k].heredoc[i].pipe[1]);
			waitpid(g_global.pid, &status, 0);
			g_global.status = get_return_status(status);
			if (g_global.status != 0)
			{
				close(ms->tokens[k].heredoc[i].pipe[0]);
				return (1);
			}
			heredoc_parse(ms, k, i);
			close(ms->tokens[k].heredoc[i].pipe[0]);
		}
		i++;
	}
	return (0);
}
