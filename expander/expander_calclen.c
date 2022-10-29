/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   expander_calclen.c                                :+:    :+:            */
/*                                                     +:+                    */
/*   By: mikuiper <mikuiper@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/24 14:35:23 by mikuiper      #+#    #+#                 */
/*   Updated: 2022/10/29 17:27:30 by mikuiper      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../parser/parse.h"

static void	expander_get_dollar_len_var(t_ms *ms, char *str, int *i, int *length)
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

static void	expander_get_dollar_len(t_ms *ms, char *str, int *i, int *length)
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
		expander_get_dollar_len_var(ms, str, i, length);
}

static void	expander_dquote(t_ms *ms, char *str, int *i, int *length)
{
	(*i)++;
	while (str[*i] && str[*i] != '\"')
	{
		if (str[*i] == '$')
			expander_get_dollar_len(ms, str, i, length);
		else
		{
			(*i)++;
			(*length)++;
		}
		ms->parse.dquote = 0;
	}
	(*length)--;
}

static void	expander_squote(t_ms *ms, char *str, int *i, int *length)
{
	(*i)++;
	while (str[*i] && str[*i] != '\'')
	{
		(*i)++;
		(*length)++;
		ms->parse.squote = 0;
	}
	(*length)--;
}

int	expander_calclen(t_ms *ms, char *str, int i, int length)
{
	while (str[i] && str[i] == ' ')
		i++;
	while (str[i])
	{
		quote_toggle(ms, &str[i]);
		while (str[i] == ' ' && str[i + 1] && \
		ms->parse.squote == 0 && ms->parse.dquote == 0)
			i++;
		if (str[i] == '$')
		{
			if (!(!ft_isdigit(str[i + 1]) \
			&& !ft_isalpha(str[i + 1]) \
			&& str[i + 1] != '_' && str[i + 1] != '?'))
				expander_get_dollar_len(ms, str, &i, &length);
		}
		else if (str[i] == '\"')
			expander_dquote(ms, str, &i, &length);
		else if (str[i] == '\'')
			expander_squote(ms, str, &i, &length);
		i++;
		length++;
	}
	return (length);
}
