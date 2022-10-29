/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   functions.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: rkieboom <rkieboom@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/05/11 16:56:29 by rkieboom      #+#    #+#                 */
/*   Updated: 2022/10/29 14:58:40 by mikuiper      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../header.h"
#include <unistd.h>

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
		if (ms->parse.comma1 == 0 && ms->parse.comma2 == 0)
			ms->parse.comma1 = 1;
		else
			ms->parse.comma1 = 0;
	}
	if (*c == '\"')
	{
		if (ms->parse.comma2 == 0 && ms->parse.comma1 == 0)
			ms->parse.comma2 = 1;
		else
			ms->parse.comma2 = 0;
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
