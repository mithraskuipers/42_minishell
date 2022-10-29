/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   checkword_calclen.c                                :+:    :+:            */
/*                                                     +:+                    */
/*   By: mikuiper <mikuiper@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/24 14:35:23 by mikuiper      #+#    #+#                 */
/*   Updated: 2022/10/29 01:06:46 by mikuiper      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"

static void	calculate_dollar_length_2(\
t_ms *ms, char *str, int *i, int *length)
{
	if (str[*i + 1] == '\0' || \
	(!ft_isdigit(str[*i + 1]) && \
	!ft_isalpha(str[*i + 1]) && str[*i + 1] != '_'))
	{
		(*i)++;
		(*length)++;
	}
	else
	{
		*length += ft_strlen(search_env(ms->env, str + *i, 0, 0));
		(*length)--;
		(*i)++;
		while (str[*i] && (ft_isdigit(str[*i]) || \
		ft_isalpha(str[*i]) || (str[*i] == '_')))
			(*i)++;
		(*i)--;
	}
}

static void	calculate_dollar_length(\
t_ms *ms, char *str, int *i, int *length)
{
	char	*temp;

	if (str[*i + 1] && str[*i + 1] == '?')
	{
		temp = ft_itoa(g_global.status);
		if (!temp)
			return_exit(1, PRNT_ERRNO_NL);
		(*length) += ft_strlen(temp);
		free(temp);
		(*i)++;
		(*length)--;
	}
	else
		calculate_dollar_length_2(ms, str, i, length);
}

static void	double_quote(t_ms *ms, char *str, int *i, int *length)
{
	(*i)++;
	while (str[*i] && str[*i] != '\"')
	{
		if (str[*i] == '$')
			calculate_dollar_length(ms, str, i, length);
		else
		{
			(*i)++;
			(*length)++;
		}
		ms->parse.comma2 = 0;
	}
	(*length)--;
}

static void	single_quote(t_ms *ms, char *str, int *i, int *length)
{
	(*i)++;
	while (str[*i] && str[*i] != '\'')
	{
		(*i)++;
		(*length)++;
		ms->parse.comma1 = 0;
	}
	(*length)--;
}

int	checkword_calclen(t_ms *ms, char *str, int i, int length)
{
	while (str[i] && str[i] == ' ')
		i++;
	while (str[i])
	{
		check_quote(ms, &str[i]);
		while (str[i] == ' ' && str[i + 1] && \
		ms->parse.comma1 == 0 && ms->parse.comma2 == 0)
			i++;
		if (str[i] == '$')
		{
			if (!(!ft_isdigit(str[i + 1]) \
			&& !ft_isalpha(str[i + 1]) \
			&& str[i + 1] != '_' && str[i + 1] != '?'))
				calculate_dollar_length(ms, str, &i, &length);
		}
		else if (str[i] == '\"')
			double_quote(ms, str, &i, &length);
		else if (str[i] == '\'')
			single_quote(ms, str, &i, &length);
		i++;
		length++;
	}
	return (length);
}
