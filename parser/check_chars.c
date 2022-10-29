/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   check_chars.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: mikuiper <mikuiper@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/24 14:35:16 by mikuiper      #+#    #+#                 */
/*   Updated: 2022/10/29 13:32:17 by mikuiper      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"

int	check_char(char *c)
{
	if ((c[0] == '>' && c[1] == '>') || (c[0] == '<' && c[1] == '<'))
		return (2);
	if ((c[0] == '>' || c[0] == '<') || c[0] == '|')
		return (1);
	return (0);
}

int	check_char_str(t_ms *ms, char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		check_quote(ms, &str[i]);
		if ((ms->input.squote == 0 && ms->input.dquote == 0) && \
			((str[i] == '>' && str[i + 1] == '>') || \
			(str[i] == '<' && str[i + 1] == '<')))
			return (2);
		if ((ms->input.squote == 0 && ms->input.dquote == 0) && \
			((str[i] == '>' || str[i] == '<') || str[i] == '|'))
			return (1);
		i++;
	}
	return (0);
}
