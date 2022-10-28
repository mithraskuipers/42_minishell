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
// Stores current gnl.buf and prompts user for input again using input_read()
static void	quote(t_ms *ms)
{
	char	*newstr;
	char	*temp;

	newstr = ft_strdup(ms->gnl.buf);
	if (!newstr)
		ft_ret_exit(1, 1);
	input_read(ms, 1);
	if (!ms->gnl.buf)
	{
		free(newstr);
		return ;
	}
	temp = ms->gnl.buf;
	newstr = add_new_line(newstr);
	ms->gnl.buf = ft_strjoin(newstr, ms->gnl.buf);
	if (!ms->gnl.buf)
		ft_ret_exit(1, 1);
	free(temp);
	free(newstr);
}

// Checks if gnl.buf contains unclosed quotes.
// User remains in this function unrtil input has closed quotes.
void	input_syntax_quotes(t_ms *ms)
{
	int		i;

	i = 0;
	while (1)
	{
		if (!ms->gnl.buf)
			return ;
		ms->parse.comma1 = 0;
		ms->parse.comma2 = 0;
		while (ms->gnl.buf[i])
		{
			check_quote(ms, &ms->gnl.buf[i]);
			i++;
		}
		if (ms->parse.comma1 == 1 || ms->parse.comma2 == 1)
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
	free(v->gnl.buf);
	v->gnl.buf = 0;
	g_global.status = 258;
	return (1);
}

// Checking semicolons syntax error
int	input_syntax_semicolon(t_ms *v)
{
	int		i;
	char	*str;

	i = 0;
	str = v->gnl.buf;
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
