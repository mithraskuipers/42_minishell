/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   input_syntax.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: rkieboom <rkieboom@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/02/02 17:32:12 by rkieboom      #+#    #+#                 */
/*   Updated: 2022/10/29 00:20:49 by mikuiper      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../header.h"

// Called when user input has unclosed quotes.
// Stores current line.array and prompts user for input again using input_read()
static void	quote(t_ms *ms)
{
	char	*newstr;
	char	*temp;

	newstr = ft_strdup(ms->line.array);
	if (!newstr)
		return_exit(1, PRNT_ERRNO_NL);
	input_read(ms, 1);
	if (!ms->line.array)
	{
		free(newstr);
		return ;
	}
	temp = ms->line.array;
	newstr = add_new_line(newstr);
	ms->line.array = ft_strjoin(newstr, ms->line.array);
	if (!ms->line.array)
		return_exit(1, PRNT_ERRNO_NL);
	free(temp);
	free(newstr);
}

// Checks if line.array contains unclosed quotes.
// User remains in this function unrtil input has closed quotes.
void	input_syntax_quotes(t_ms *ms)
{
	int		i;

	i = 0;
	while (1)
	{
		if (!ms->line.array)
			return ;
		ms->input.squote = 0;
		ms->input.dquote = 0;
		while (ms->line.array[i])
		{
			check_quote(ms, &ms->line.array[i]);
			i++;
		}
		if (ms->input.squote == 1 || ms->input.dquote == 1)
			quote(ms);
		else
			break ;
		i = 0;
	}
}

static int	input_error(t_ms *v)
{
	ft_putendl_fd("minishell-4.2$: \
syntax error near unexpected token ;", 2);
	free(v->line.array);
	v->line.array = 0;
	g_global.status = 258;
	return (1);
}

// Checking semicolons syntax error
int	input_syntax_semicolons(t_ms *v)
{
	int		i;
	char	*str;

	i = 0;
	str = v->line.array;
	while (str[i])
	{
		i += str_skip_whitespace(str + i);
		if (!str[i])
			return (1);
		if (str[i] == ';')
			return (input_error(v));
		else
			while (str[i] && str[i] != ';')
				i++;
		if (str[i])
			i++;
	}
	return (0);
}
