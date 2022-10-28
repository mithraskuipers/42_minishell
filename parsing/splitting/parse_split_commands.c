/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parse_split_commands.c                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: mikuiper <mikuiper@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/24 14:35:00 by mikuiper      #+#    #+#                 */
/*   Updated: 2022/10/29 00:25:23 by mikuiper      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../parse.h"

static int	arraysize(const char *s, char c, t_ms *ms)
{
	int	i;
	int	k;

	i = 0;
	k = 0;
	i = str_skip_whitespace(s);
	if (s[i] == '\0')
		return (0);
	ms->parse.comma1 = 0;
	ms->parse.comma2 = 0;
	while (s[i])
	{
		check_quote(ms, (char *)s + i);
		if (s[i] == c && (ms->parse.comma1 == 0 && ms->parse.comma2 == 0))
			k++;
		while (s[i] && s[i + 1] && s[i] == c)
			i++;
		i++;
	}
	ms->parse.comma1 = 0;
	ms->parse.comma2 = 0;
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
	while (arrayindex != arraysize(ms->gnl.buf, c, ms))
	{
		findstart(ms->gnl.buf, c, &i, &start);
		while (ms->gnl.buf[i] && (ms->gnl.buf[i] != c || \
				(ms->parse.comma1 == 1 || ms->parse.comma2 == 1)))
		{
			check_quote(ms, &ms->gnl.buf[i]);
			i++;
			strlength++;
		}
		result[arrayindex] = ft_substr(ms->gnl.buf, start, strlength);
		if (!result[arrayindex])
			ft_ret_exit(1, 1);
		strlength = 0;
		arrayindex++;
		i++;
	}
	result[arrayindex] = NULL;
	return (result);
}

char	**parse_split_commands(t_ms *ms, char c)
{
	char	**result;

	if (!ms->gnl.buf)
		return (NULL);
	result = ft_calloc(arraysize(ms->gnl.buf, c, ms) + 1, sizeof(char *));
	if (!result)
		ft_ret_exit(1, 1);
	result = splitter(ms, c, result, 0);
	return (result);
}
