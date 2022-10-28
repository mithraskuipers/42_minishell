/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parse_split_spaces.c                               :+:    :+:            */
/*                                                     +:+                    */
/*   By: mikuiper <mikuiper@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/24 14:35:06 by mikuiper      #+#    #+#                 */
/*   Updated: 2022/10/29 00:25:23 by mikuiper      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../parse.h"

typedef struct s_vars
{
	int	i;
	int	k;
	int	length;
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
	ms->parse.comma1 = 0;
	ms->parse.comma2 = 0;
	while (s[i])
	{
		check_quote(ms, (char *)s + i);
		if (s[i] == c && \
			(ms->parse.comma1 == 0 && ms->parse.comma2 == 0) && \
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
	ms->parse.comma1 = 0;
	ms->parse.comma2 = 0;
}

static char	**splitter(t_ms *ms, const char *str, char **result)
{
	t_vars	vars;

	init_vars(ms, &vars);
	while (str[vars.i])
	{
		check_quote(ms, (char *)str + vars.i);
		if (str[vars.i] != ' ' || ms->parse.comma1 || ms->parse.comma2)
			vars.length++;
		else
		{
			if (vars.length != 0)
			{
				result[vars.k] = ft_substr \
				(str, vars.i - vars.length, vars.length);
				if (!result[vars.k])
					ft_ret_exit(1, 1);
				vars.k++;
				vars.length = 0;
			}
		}
		vars.i++;
	}
	if (str[vars.i] == '\0' && vars.i > 0 && str[vars.i - 1] != ' ')
		result[vars.k] = ft_substr(str, vars.i - vars.length, vars.length);
	return (result);
}

//Splits on spaces
char	**parse_split_spaces(t_ms *ms, const char *str, char c)
{
	int		length;
	char	**result;

	if (!str)
		return (NULL);
	length = arraysize(str, c, ms);
	result = ft_calloc(length + 1, sizeof(char *));
	if (!result)
		ft_ret_exit(1, 1);
	result = splitter(ms, str, result);
	result[length] = NULL;
	return (result);
}
