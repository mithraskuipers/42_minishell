/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   input_syntax_quotes.c                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: mikuiper <mikuiper@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/29 15:16:36 by mikuiper      #+#    #+#                 */
/*   Updated: 2022/10/29 22:17:27 by mikuiper      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../header.h"

// input_getnextline() handles the processing of an additional input prompt
// whenever the user had inputted a line with unclosed quotation marks. It adds
// a newline to the previous input line, and joins the previous input line with
// the new input line, storing the result in ms->line.array.
static void	input_getnextline(t_ms *ms)
{
	char	*s_new;
	char	*s_prev;

	s_new = ft_strdup(ms->line.array);
	if (!s_new)
		return_exit(1, PRNT_ERRNO_NL);
	input_read(ms, 1);
	if (!ms->line.array)
	{
		free(s_new);
		return ;
	}
	s_prev = ms->line.array;
	s_new = input_add_newline(s_new);
	ms->line.array = ft_strjoin(s_new, ms->line.array);
	if (!ms->line.array)
		return_exit(1, PRNT_ERRNO_NL);
	free(s_prev);
	free(s_new);
}

// input_syntax_quotes() parses the user input on a char-by-char basis and
// checks if the input contains closed quotation marks. If so, it prompts the
// user for a new input line.
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
			input_getnextline(ms);
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
