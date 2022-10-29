/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   functions.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: rkieboom <rkieboom@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/05/11 16:56:29 by rkieboom      #+#    #+#                 */
/*   Updated: 2022/10/29 15:23:16 by mikuiper      ########   odam.nl         */
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

int	cmd_len(char **str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}
