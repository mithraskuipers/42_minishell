/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   heredoc_parser.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: mikuiper <mikuiper@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/28 21:57:42 by mikuiper      #+#    #+#                 */
/*   Updated: 2022/10/29 01:06:46 by mikuiper      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../parse.h"

static void	heredoc_allocate(t_heredoc *heredoc, int len)
{
	t_heredoc_data *data;

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

	i =-0;
	while (arr[i])
	{
		free(arr[i]);
		i++;
	}
	free(arr);
}

static void	heredoc_parse_str(t_ms *ms, t_heredoc *heredoc, t_heredoc_data *data)
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
	arr = ft_split(temp, '\n'); //protect
	while (arr[i])
		i++;
	free(temp);
	len = i;
	heredoc_allocate(heredoc, len);
	data = heredoc->data;
	i = 0;
	while (data)
	{
		while (data && !ft_strchr(arr[i], '$'))
		{
			data->str = ft_strdup(arr[i]);//protect
			if (!data->str)
				return_exit(1, PRNT_ERRNO_NL);
			data = data->next;
			i++;
		}
		if (!data)
		{
			free_split(arr);
			return ;
		}
		len = heredoc_get_str_len(ms, arr[i]);
		data->str = heredoc_create_str(ms, arr[i], len);
		i++;
		data = data->next;
	}
	free_split(arr);
}

static void heredoc_noparse_str(t_heredoc *heredoc, t_heredoc_data *data)
{
	int		i;
	char **arr;
	int		len;
	char	*temp;

	i = 0;
	temp = ft_calloc(4096, sizeof(char));
	len = read(heredoc->pipe[0], temp, 4096);
	if (len < 0)
		return_exit(1, PRNT_ERRNO_NL);
	temp[len] = 0;
	arr = ft_split(temp, '\n'); //protect
	while (arr[i])
		i++;
	len = i;
	i = 0;
	heredoc_allocate(heredoc, len);
	data = heredoc->data;
	while (data)
	{
		data->str = ft_strdup(arr[i]); //protecet
		i++;
		data = data->next;
	}
	free_split(arr);
	free(temp);
}

//Expand data if there were no quotes
void	heredoc_parse(t_ms *ms, int k, int i)
{
	if (ms->tokens[k].heredoc[i].heredoc_q == 0)
		heredoc_parse_str(ms, &ms->tokens[k].heredoc[i], NULL);
	else
		heredoc_noparse_str(&ms->tokens[k].heredoc[i], NULL);
}
