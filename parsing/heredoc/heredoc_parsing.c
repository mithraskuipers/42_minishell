/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   heredoc_parsing.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: mikuiper <mikuiper@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/28 21:57:42 by mikuiper      #+#    #+#                 */
/*   Updated: 2022/10/28 21:57:45 by mikuiper      ########   odam.nl         */
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
				ft_ret_exit(1, 1);
			data = heredoc->data;
		}
		else
		{
			data->next = ft_calloc(1, sizeof(t_heredoc_data));
			if (!data->next)
				ft_ret_exit(1, 1);
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

static void	heredoc_parse_str(t_list *list, t_heredoc *heredoc, t_heredoc_data *data)
{
	int		i;
	int		len;
	char	*temp;
	char	**arr;

	i = 0;
	temp = ft_calloc(4096, sizeof(char));
	len = read(heredoc->pipe[0], temp, 4096);
	if (len < 0)
		ft_ret_exit(1, 1);
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
				ft_ret_exit(1, 1);
			data = data->next;
			i++;
		}
		if (!data)
		{
			free_split(arr);
			return ;
		}
		len = heredoc_get_str_len(list, arr[i]);
		data->str = heredoc_create_str(list, arr[i], len);
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
		ft_ret_exit(1, 1);
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
void	heredoc_parse(t_list *list, int k, int i)
{
	if (list->tokens[k].heredoc[i].heredoc_q == 0)
		heredoc_parse_str(list, &list->tokens[k].heredoc[i], NULL);
	else
		heredoc_noparse_str(&list->tokens[k].heredoc[i], NULL);
}
