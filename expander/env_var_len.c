/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   env_var_len.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: mikuiper <mikuiper@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/29 15:23:50 by mikuiper      #+#    #+#                 */
/*   Updated: 2022/10/29 15:24:04 by mikuiper      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../header.h"

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
