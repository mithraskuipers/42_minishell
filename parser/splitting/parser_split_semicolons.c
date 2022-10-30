/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parser_split_semicolons.c                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: mikuiper <mikuiper@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/29 00:58:15 by mikuiper      #+#    #+#                 */
/*   Updated: 2022/10/29 20:30:54 by mikuiper      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../parser.h"
#include "../../header.h"

static int	arraysize(const char *s, char c, t_ms *ms)
{
	int	i;
	int	k;

	i = 0;
	k = 0;
	i = str_skip_whitespace(s);
	if (s[i] == '\0')
		return (0);
	ms->parser.squote = 0;
	ms->parser.dquote = 0;
	while (s[i])
	{
		quote_toggle(ms, (char *)s + i);
		if (s[i] == c && (ms->parser.squote == 0 && ms->parser.dquote == 0))
			k++;
		while (s[i] && s[i + 1] && s[i] == c)
			i++;
		i++;
	}
	ms->parser.squote = 0;
	ms->parser.dquote = 0;
	return (k + 1);
}

static void	findstart(const char *s, char c, int *i, int *start)
{
	while (s[*i] && s[*i] == c)
		(*i)++;
	if (s[*i] != c && s[*i])
		*start = *i;
}

static char	**splitter(t_ms *ms, char c, char **result, int i)
{
	int	strlength;
	int	arrayindex;
	int	start;

	strlength = 0;
	arrayindex = 0;
	while (arrayindex != arraysize(ms->line.array, c, ms))
	{
		findstart(ms->line.array, c, &i, &start);
		while (ms->line.array[i] && (ms->line.array[i] != c || \
				(ms->parser.squote == 1 || ms->parser.dquote == 1)))
		{
			quote_toggle(ms, &ms->line.array[i]);
			i++;
			strlength++;
		}
		result[arrayindex] = ft_substr(ms->line.array, start, strlength);
		if (!result[arrayindex])
			return_exit(1, PRNT_ERRNO_NL);
		strlength = 0;
		arrayindex++;
		i++;
	}
	result[arrayindex] = NULL;
	return (result);
}

char	**parser_split_semicolon(t_ms *ms, char c)
{
	char	**result;

	if (!ms->line.array)
		return (NULL);
	result = ft_calloc(arraysize(ms->line.array, c, ms) + 1, sizeof(char *));
	if (!result)
		return_exit(1, PRNT_ERRNO_NL);
	result = splitter(ms, c, result, 0);
	return (result);
}
