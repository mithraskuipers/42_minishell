/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   input_syntax_quotes.c                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: mikuiper <mikuiper@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/29 15:16:36 by mikuiper      #+#    #+#                 */
/*   Updated: 2022/10/29 20:30:54 by mikuiper      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../header.h"

static void	quote(t_ms *ms)
{
	char	*newstr;
	char	*temp;

	newstr = ft_strdup(ms->line.array);
	if (!newstr)
		return_exit(1, PRNT_ERRNO_NL);
	input_read(ms, 1);
	if (!ms->line.array)
	{
		free(newstr);
		return ;
	}
	temp = ms->line.array;
	newstr = input_add_newline(newstr);
	ms->line.array = ft_strjoin(newstr, ms->line.array);
	if (!ms->line.array)
		return_exit(1, PRNT_ERRNO_NL);
	free(temp);
	free(newstr);
}

void	input_syntax_quotes(t_ms *ms)
{
	int		i;

	i = 0;
	while (1)
	{
		if (!ms->line.array)
			return ;
		ms->parse.squote = 0;
		ms->parse.dquote = 0;
		while (ms->line.array[i])
		{
			quote_toggle(ms, &ms->line.array[i]);
			i++;
		}
		if (ms->parse.squote == 1 || ms->parse.dquote == 1)
			quote(ms);
		else
			break ;
		i = 0;
	}
}

// Receives char and checks whether it is a quote.
// If so, turn on quote toggle.
void	quote_toggle(t_ms *ms, char *c)
{
	if (*c == '\'')
	{
		if (ms->parse.squote == 0 && ms->parse.dquote == 0)
			ms->parse.squote = 1;
		else
			ms->parse.squote = 0;
	}
	if (*c == '\"')
	{
		if (ms->parse.dquote == 0 && ms->parse.squote == 0)
			ms->parse.dquote = 1;
		else
			ms->parse.dquote = 0;
	}
}
