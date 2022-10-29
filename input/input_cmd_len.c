/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   input_cmd_len.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: mikuiper <mikuiper@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/29 20:17:54 by mikuiper      #+#    #+#                 */
/*   Updated: 2022/10/29 20:17:54 by mikuiper      ########   odam.nl         */
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
