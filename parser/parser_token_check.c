/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parser_token_check.c                               :+:    :+:            */
/*                                                     +:+                    */
/*   By: mikuiper <mikuiper@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/30 13:18:18 by mikuiper      #+#    #+#                 */
/*   Updated: 2022/10/30 14:54:26 by mikuiper      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

int	char_is_token(char *c)
{
	if ((c[0] == '>' && c[1] == '>') || (c[0] == '<' && c[1] == '<'))
		return (2);
	if ((c[0] == '>' || c[0] == '<') || c[0] == '|')
		return (1);
	return (0);
}

int	str_has_token(t_ms *ms, char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		quote_toggle(ms, &str[i]);
		if ((ms->parser.squote == 0 && ms->parser.dquote == 0) && \
			((str[i] == '>' && str[i + 1] == '>') || \
			(str[i] == '<' && str[i + 1] == '<')))
			return (2);
		if ((ms->parser.squote == 0 && ms->parser.dquote == 0) && \
			((str[i] == '>' || str[i] == '<') || str[i] == '|'))
			return (1);
		i++;
	}
	return (0);
}
