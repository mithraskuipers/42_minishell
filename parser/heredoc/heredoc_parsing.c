/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   heredoc_parsing.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: mikuiper <mikuiper@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/31 14:57:59 by mikuiper      #+#    #+#                 */
/*   Updated: 2022/10/31 15:58:35 by rkieboom      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../parser.h"

static void	heredoc_allocate(t_heredoc *heredoc, int len)
{
	t_heredoc_data	*data;

	while (len)
	{
		if (!heredoc->data)
		{
			heredoc->data = ft_calloc(1, sizeof(t_heredoc_data));
			if (!heredoc->data)
				return_exit(1, PRNT_ERRNO_NL);
			data = heredoc->data;
		}
		else
		{
			data->next = ft_calloc(1, sizeof(t_heredoc_data));
			if (!data->next)
				return_exit(1, PRNT_ERRNO_NL);
			data = data->next;
		}
		len--;
	}
}

static void	free_split(char **arr)
{
	int	i;

	i = 0;
	while (arr[i])
	{
		free(arr[i]);
		i++;
	}
	free(arr);
}

static void	heredoc_parse_helper(t_ms *ms, t_heredoc_data *data, \
char **arr, int expand)
{
	int	i;
	int	len;

	i = 0;
	while (data)
	{
		if (!ft_strchr(arr[i], '$') || expand)
		{
			data->str = ft_strdup(arr[i]);
			if (!data->str)
				return_exit(1, PRNT_ERRNO_NL);
		}
		else
		{
			len = heredoc_get_str_len(ms, arr[i]);
			data->str = heredoc_create_str(ms, arr[i], len);
		}
		i++;
		data = data->next;
	}
}

static void	heredoc_parse_str(t_ms *ms, t_heredoc *heredoc, int expand)
{
	int		i;
	int		len;
	char	*temp;
	char	**arr;

	i = 0;
	temp = ft_calloc(4096, sizeof(char));
	len = read(heredoc->pipe[0], temp, 4096);
	if (len < 0)
		return_exit(1, PRNT_ERRNO_NL);
	temp[len] = 0;
	arr = ft_split(temp, '\n');
	if (!arr)
		return_exit(1, PRNT_ERRNO_NL);
	while (arr[i])
		i++;
	free(temp);
	len = i;
	heredoc_allocate(heredoc, len);
	heredoc_parse_helper(ms, heredoc->data, arr, expand);
	free_split(arr);
}

//Expand data if there were no quotes
void	heredoc_parse(t_ms *ms, int k, int i)
{
	if (ms->tokens[k].heredoc[i].heredoc_q == 0)
		heredoc_parse_str(ms, &ms->tokens[k].heredoc[i], NULL, 1);
	else
		heredoc_parse_str(ms, &ms->tokens[k].heredoc[i], NULL, 0);
}
