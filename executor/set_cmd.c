/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   set_cmd.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: rkieboom <rkieboom@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/05/07 15:57:41 by rkieboom      #+#    #+#                 */
/*   Updated: 2022/10/29 18:13:47 by mikuiper      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "execute.h"

static int	calc_len(t_cmdlist *cmd)
{
	int	i;

	i = 0;
	while (cmd->command[i])
		i++;
	return (i - (cmd->tokens->n_tokens * 2));
}

static char	*get_str(t_cmdlist *cmd, int i)
{
	int	token_c;
	int	c;
	int	s;

	token_c = 0;
	c = 0;
	s = 0;
	while (cmd->command[c + s])
	{
		if (token_c < cmd->tokens->n_tokens && \
		((c + s) == cmd->tokens->token_pos[token_c]))
		{
			s += 2;
			token_c++;
		}
		if (c == i)
			return (cmd->command[c + s]);
		c++;
	}
	return (0);
}

char	**set_cmd(t_cmdlist *cmd)
{
	int		i;
	int		length;
	char	**newstr;

	i = 0;
	if (!cmd->tokens || cmd->tokens->n_tokens == 0)
		return (cmd->command);
	length = calc_len(cmd);
	newstr = ft_calloc(length + 1, sizeof(char *));
	while (i < length)
	{
		newstr[i] = get_str(cmd, i);
		i++;
	}
	newstr[length] = 0;
	return (newstr);
}
