/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   tokens.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: rkieboom <rkieboom@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/11/30 00:29:12 by rkieboom      #+#    #+#                 */
/*   Updated: 2022/10/29 01:06:46 by mikuiper      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"

static void	allocate_tokens_vars(t_ms *ms)
{
	int	j;
	int	k;
	int	total;

	k = 0;
	total = 0;
	while (ms->parse.commands[k])
	{
		j = 0;
		while (ms->parse.commands[k][j])
		{
			if (check_char(ms->parse.commands[k][j]))
				total++;
			j++;
		}
		ms->tokens[k].token = ft_calloc(total + 1, sizeof(char *));
		if (!ms->tokens[k].token)
			return_exit(1, PRNT_ERRNO_NL);
		ms->tokens[k].token_pos = ft_calloc(total + 1, sizeof(int));
		if (!ms->tokens[k].token_pos)
			return_exit(1, PRNT_ERRNO_NL);
		ms->tokens[k].total = total;
		total = 0;
		k++;
	}
}

static void	set_tokens(t_ms *ms)
{
	int	i;
	int	j;
	int	k;

	k = 0;
	while (ms->parse.commands[k])
	{
		i = 0;
		j = 0;
		while (ms->parse.commands[k][j])
		{
			if (check_char(ms->parse.commands[k][j]))
			{
				ms->tokens[k].token[i] = \
				ft_strdup(ms->parse.commands[k][j]);
				ms->tokens[k].token_pos[i] = j;
				i++;
			}
			j++;
		}
		k++;
	}
}

// Counts occurence of every token
static void	identify_tokens(t_ms *ms)
{
	int	i;
	int	j;

	i = 0;
	while (ms->parse.commands[i])
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
