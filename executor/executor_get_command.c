/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   executor_get_command.c                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: mikuiper <mikuiper@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/30 11:30:51 by mikuiper      #+#    #+#                 */
/*   Updated: 2022/10/30 18:32:55 by mikuiper      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"

static int	calc_len(t_cmdlist *cmdlist)
{
	int	i;

	i = 0;
	while (cmdlist->cmd_array[i])
		i++;
	return (i - (cmdlist->tokens->n_tokens * 2));
}

static char	*get_str(t_cmdlist *cmdlist, int i)
{
	int	token_c;
	int	c;
	int	s;

	token_c = 0;
	c = 0;
	s = 0;
	while (cmdlist->cmd_array[c + s])
	{
		if (token_c < cmdlist->tokens->n_tokens && \
		((c + s) == cmdlist->tokens->tkn_pos[token_c]))
		{
			s += 2;
			token_c++;
		}
		if (c == i)
			return (cmdlist->cmd_array[c + s]);
		c++;
	}
	return (0);
}

// executor_get_command() parses the provided cmdlist and extracts its command
// words, storing it in cmd_array and returning cmd_array.
char	**executor_get_command(t_cmdlist *cmdlist)
{
	int		i;
	int		len;
	char	**cmd_array;

	i = 0;
	if (!cmdlist->tokens || cmdlist->tokens->n_tokens == 0)
		return (cmdlist->cmd_array);
	len = calc_len(cmdlist);
	cmd_array = ft_calloc(len + 1, sizeof(char *));
	while (i < len)
	{
		cmd_array[i] = get_str(cmdlist, i);
		i++;
	}
	cmd_array[len] = NULL;
	return (cmd_array);
}
