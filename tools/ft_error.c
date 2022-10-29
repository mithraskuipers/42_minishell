/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_error.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: mikuiper <mikuiper@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/29 15:59:48 by mikuiper      #+#    #+#                 */
/*   Updated: 2022/10/29 15:59:49 by mikuiper      ########   odam.nl         */
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
