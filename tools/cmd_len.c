/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cmd_len.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: mikuiper <mikuiper@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/29 15:58:56 by mikuiper      #+#    #+#                 */
/*   Updated: 2022/10/29 15:59:05 by mikuiper      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../header.h"
#include <unistd.h>

int	cmd_len(char **str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}
