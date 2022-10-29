/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   char_is_tokens.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: mikuiper <mikuiper@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/24 14:35:16 by mikuiper      #+#    #+#                 */
/*   Updated: 2022/10/29 22:42:37 by mikuiper      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"

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
		if ((ms->parse.squote == 0 && ms->parse.dquote == 0) && \
			((str[i] == '>' && str[i + 1] == '>') || \
			(str[i] == '<' && str[i + 1] == '<')))
			return (2);
		if ((ms->parse.squote == 0 && ms->parse.dquote == 0) && \
			((str[i] == '>' || str[i] == '<') || str[i] == '|'))
			return (1);
		i++;
	}
	return (0);
}
