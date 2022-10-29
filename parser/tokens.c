/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   tokens.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: rkieboom <rkieboom@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/11/30 00:29:12 by rkieboom      #+#    #+#                 */
/*   Updated: 2022/10/29 13:35:24 by mikuiper      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"

static void	allocate_tokens_vars(t_ms *ms)
{
	int	j;
	int	cmd;
	int	total;

	cmd = 0;
	total = 0;
	while (ms->input.cmds[cmd])
	{
		j = 0;
		while (ms->input.cmds[cmd][j])
		{
			if (check_char(ms->input.cmds[cmd][j]))
				total++;
			j++;
		}
		ms->tokens[cmd].token = ft_calloc(total + 1, sizeof(char *));
		if (!ms->tokens[cmd].token)
			return_exit(1, PRNT_ERRNO_NL);
		ms->tokens[cmd].token_pos = ft_calloc(total + 1, sizeof(int));
		if (!ms->tokens[cmd].token_pos)
			return_exit(1, PRNT_ERRNO_NL);
		ms->tokens[cmd].total = total;
		total = 0;
		cmd++;
	}
}

static void	set_tokens(t_ms *ms)
{
	int	tkn;
	int	wrd;
	int	cmd;

	cmd = 0;
	while (ms->input.cmds[cmd])
	{
		tkn = 0;
		wrd = 0;
		while (ms->input.cmds[cmd][wrd])
		{
			if (check_char(ms->input.cmds[cmd][wrd]))
			{
				ms->tokens[cmd].token[tkn] = ft_strdup(ms->input.cmds[cmd][wrd]);
				ms->tokens[cmd].token_pos[tkn] = wrd;
				tkn++;
			}
			wrd++;
		}
		cmd++;
	}
}

// Counts occurence of every token
static void	identify_tokens(t_ms *ms)
{
	int	i;
	int	j;

	i = 0;
	while (ms->input.cmds[i])
	{
		j = 0;
		while (j < ms->tokens[i].total)
		{
			if (!ft_strncmp(ms->tokens[i].token[j], "<<", 3))
				ms->tokens[i].double_redirection_left++;
			else if (!ft_strncmp(ms->tokens[i].token[j], ">>", 3))
				ms->tokens[i].double_redirection_right++;
			else if (!ft_strncmp(ms->tokens[i].token[j], "<", 2))
				ms->tokens[i].single_redirection_left++;
			else if (!ft_strncmp(ms->tokens[i].token[j], ">", 2))
				ms->tokens[i].single_redirection_right++;
			else if (!ft_strncmp(ms->tokens[i].token[j], "|", 2))
				ms->tokens[i].pipe++;
			j++;
		}
		i++;
	}
}

//It saves wich word is a token
//And it saves the location of the token
void	tokens(t_ms *ms)
{
	allocate_tokens_vars(ms);
	set_tokens(ms);
	identify_tokens(ms);
}
