/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   functions.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: rkieboom <rkieboom@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/05/11 16:56:29 by rkieboom      #+#    #+#                 */
/*   Updated: 2022/10/29 13:32:17 by mikuiper      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../header.h"
#include <unistd.h>

int	ft_putstr(char *str)
{
	if (write(1, str, ft_strlen(str)) == -1)
		return (-1);
	return (0);
}

void	ft_error(char *msg)
{
	tcsetattr(0, 0, &g_global.termios_save);
	write(2, msg, ft_strlen(msg));
	exit(1);
}

// Receives char and checks whether it is a quote.
// If so, turn on quote toggle.
void	check_quote(t_ms *ms, char *c)
{
	if (*c == '\'')
	{
		if (ms->input.squote == 0 && ms->input.dquote == 0)
			ms->input.squote = 1;
		else
			ms->input.squote = 0;
	}
	if (*c == '\"')
	{
		if (ms->input.dquote == 0 && ms->input.squote == 0)
			ms->input.dquote = 1;
		else
			ms->input.dquote = 0;
	}
}

int	env_str_length(char *str)
{
	int	i;

	i = 0;
	if (str[i] == '$')
		i++;
	while (str[i] && (ft_isdigit(str[i]) || \
	ft_isalpha(str[i]) || str[i] == '_'))
		i++;
	return (i);
}

int	cmd_len(char **str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}
