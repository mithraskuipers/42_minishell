/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   get_heredoc_input.c                                :+:    :+:            */
/*                                                     +:+                    */
/*   By: mikuiper <mikuiper@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/28 21:57:30 by mikuiper      #+#    #+#                 */
/*   Updated: 2022/10/28 21:57:32 by mikuiper      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../parse.h"
#include <sys/wait.h>

static void	free_and_get_data(t_list *list, int k, int i)
{
	if (list->gnl.buf)
	{
		free(list->gnl.buf);
		list->gnl.buf = 0;
	}
	list->gnl.buf = readline("> ");
	if (!list->gnl.buf)
		list->gnl.buf = ft_strdup(list->tokens[k].heredoc[i].eof);
}

//Saving the actual data
static void	heredoc_write_to_pipe(t_list *list, int k, int i)
{
	if (!list->tokens[k].heredoc->eof)
		return ;
	free_and_get_data(list, k, i);
	while (ft_strncmp(list->gnl.buf, \
	list->tokens[k].heredoc[i].eof, ft_strlen(list->tokens[k].heredoc[i].eof) + 1))
	{
		write(list->tokens[k].heredoc[i].pipe[1], list->gnl.buf, ft_strlen(list->gnl.buf));
		write(list->tokens[k].heredoc[i].pipe[1], "\n", 1);
		free_and_get_data(list, k, i);
	}
	if (list->gnl.buf)
	{
		free(list->gnl.buf);
		list->gnl.buf = 0;
	}
	exit(0);
}

//We read the input for heredoc
//and save it in heredoc data structure
int	get_heredoc_input(t_list *list, int k)
{
	int	i;
	int	length;
	int	status;

	i = 0;
	length = list->tokens[k].double_redirection_left;
	signal(SIGINT, sig_handler);
	signal(SIGQUIT, SIG_IGN);
	while (i < length)
	{
		if (ft_pipe(list->tokens[k].heredoc[i].pipe))
			return (1);
		if (ft_fork(&g_global.pid, NULL))
		{
			close(list->tokens[k].heredoc[i].pipe[0]);
			close(list->tokens[k].heredoc[i].pipe[1]);
			return (1);
		}
		if (!g_global.pid)
		{
			signals_dfl();
			heredoc_write_to_pipe(list, k, i);
		}
		else
		{
			close(list->tokens[k].heredoc[i].pipe[1]);
			waitpid(g_global.pid, &status, 0);
			g_global.status = get_return_status(status);
			if (g_global.status != 0)
			{
				close(list->tokens[k].heredoc[i].pipe[0]);
				return (1);
			}
			heredoc_parse(list, k, i);
			close(list->tokens[k].heredoc[i].pipe[0]);
		}
		i++;
	}
	return (0);
}
