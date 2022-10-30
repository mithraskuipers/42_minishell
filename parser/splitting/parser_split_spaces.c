/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parser_split_spaces.c                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: mikuiper <mikuiper@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/30 13:20:54 by mikuiper      #+#    #+#                 */
/*   Updated: 2022/10/30 13:21:18 by mikuiper      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../parse.h"

typedef struct s_vars
{
	int	i;
	int	k;
	int	len;
}				t_vars;

static int	arraysize(const char *s, char c, t_ms *ms)
{
	int	i;
	int	k;

	i = 0;
	k = 0;
	i = str_skip_whitespace(s);
	if (s[i] == '\0')
		return (0);
	ms->parse.squote = 0;
	ms->parse.dquote = 0;
	while (s[i])
	{
		quote_toggle(ms, (char *)s + i);
		if (s[i] == c && \
			(ms->parse.squote == 0 && ms->parse.dquote == 0) && \
			i > 0 && s[i - 1] != c)
			k++;
		i++;
	}
	if (i > 0 && s[i - 1] != ' ')
		k++;
	return (k);
}

static void	init_vars(t_ms *ms, t_vars *vars)
{
	ft_bzero(vars, sizeof(t_vars));
	ms->parse.squote = 0;
	ms->parse.dquote = 0;
}

static char	**splitter(t_ms *ms, const char *str, char **result)
{
	t_vars	vars;

	init_vars(ms, &vars);
	while (str[vars.i])
	{
		quote_toggle(ms, (char *)str + vars.i);
		if (str[vars.i] != ' ' || ms->parse.squote || ms->parse.dquote)
			vars.len++;
		else
		{
			if (vars.len != 0)
			{
				result[vars.k] = ft_substr \
				(str, vars.i - vars.len, vars.len);
				if (!result[vars.k])
					return_exit(1, PRNT_ERRNO_NL);
				vars.k++;
				vars.len = 0;
			}
		}
		vars.i++;
	}
	if (str[vars.i] == '\0' && vars.i > 0 && str[vars.i - 1] != ' ')
		result[vars.k] = ft_substr(str, vars.i - vars.len, vars.len);
	return (result);
}

//Splits on spaces
char	**parser_split_spaces(t_ms *ms, const char *str, char c)
{
	int		len;
	char	**result;

	if (!str)
		return (NULL);
	len = arraysize(str, c, ms);
	result = ft_calloc(len + 1, sizeof(char *));
	if (!result)
		return_exit(1, PRNT_ERRNO_NL);
	result = splitter(ms, str, result);
	result[len] = NULL;
	return (result);
}
