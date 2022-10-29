/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   input_check.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: mikuiper <mikuiper@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/29 15:11:21 by mikuiper      #+#    #+#                 */
/*   Updated: 2022/10/29 15:16:56 by mikuiper      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../header.h"

static int	input_error(t_ms *v)
{
	ft_putendl_fd("minishell-4.2$: \
syntax error near unexpected token ;", 2);
	free(v->line.array);
	v->line.array = 0;
	g_global.status = 258;
	return (1);
}

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
