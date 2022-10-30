/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   tokens.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: rkieboom <rkieboom@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/11/30 00:29:12 by rkieboom      #+#    #+#                 */
/*   Updated: 2022/10/30 14:50:15 by mikuiper      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

static void	tokens_allocation(t_ms *ms)
{
	int	j;
	int	cmd;
	int	total;

	cmd = 0;
	total = 0;
	while (ms->parser.commands[cmd])
	{
		j = 0;
		while (ms->parser.commands[cmd][j])
		{
			if (char_is_token(ms->parser.commands[cmd][j]))
				total++;
			j++;
		}
		ms->tokens[cmd].token = ft_calloc(total + 1, sizeof(char *));
		if (!ms->tokens[cmd].token)
			return_exit(1, PRNT_ERRNO_NL);
		ms->tokens[cmd].token_pos = ft_calloc(total + 1, sizeof(int));
		if (!ms->tokens[cmd].token_pos)
			return_exit(1, PRNT_ERRNO_NL);
		ms->tokens[cmd].n_tokens = total;
		total = 0;
		cmd++;
	}
}

static void	tokens_dup(t_ms *ms)
{
	int	tkn;
	int	wrd;
	int	cmd;

	cmd = 0;
	while (ms->parser.commands[cmd])
	{
		tkn = 0;
		wrd = 0;
		while (ms->parser.commands[cmd][wrd])
		{
			if (char_is_token(ms->parser.commands[cmd][wrd]))
			{
				ms->tokens[cmd].token[tkn] = ft_strdup(\
				ms->parser.commands[cmd][wrd]);
				ms->tokens[cmd].token_pos[tkn] = wrd;
				tkn++;
			}
			wrd++;
		}
		cmd++;
	}
}

// Counts occurence of every token
static void	tokens_count(t_ms *ms)
{
	int	i;
	int	j;

	i = 0;
	while (ms->parser.commands[i])
	{
		j = 0;
		while (j < ms->tokens[i].n_tokens)
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

//It saves which word is a token, as well as its location
void	tokens_wrapper(t_ms *ms)
{
	tokens_allocation(ms);
	tokens_dup(ms);
	tokens_count(ms);
}
