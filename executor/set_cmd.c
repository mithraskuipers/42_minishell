/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   set_cmd.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: rkieboom <rkieboom@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/05/07 15:57:41 by rkieboom      #+#    #+#                 */
/*   Updated: 2022/10/29 13:50:59 by mikuiper      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "execute.h"

static int	calc_len(t_cmdlist *cmdlist)
{
	int	i;

	i = 0;
	while (cmdlist->command[i])
		i++;
	return (i - (cmdlist->tokens->total * 2));
}

static char	*get_str(t_cmdlist *cmdlist, int i)
{
	int	token_c;
	int	c;
	int	s;

	token_c = 0;
	c = 0;
	s = 0;
	while (cmdlist->command[c + s])
	{
		if (token_c < cmdlist->tokens->total && \
		((c + s) == cmdlist->tokens->token_pos[token_c]))
		{
			s += 2;
			token_c++;
		}
		if (c == i)
			return (cmdlist->command[c + s]);
		c++;
	}
	return (0);
}

char	**set_cmd(t_cmdlist *cmdlist)
{
	int		i;
	int		length;
	char	**newstr;

	i = 0;
	if (!cmdlist->tokens || cmdlist->tokens->total == 0)
		return (cmdlist->command);
	length = calc_len(cmdlist);
	newstr = ft_calloc(length + 1, sizeof(char *));
	while (i < length)
	{
		newstr[i] = get_str(cmdlist, i);
		i++;
	}
	newstr[length] = 0;
	return (newstr);
}
