/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   env_lstsize.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: mikuiper <mikuiper@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/29 15:49:51 by mikuiper      #+#    #+#                 */
/*   Updated: 2022/10/29 15:49:52 by mikuiper      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "env_list.h"

int	env_lstsize(t_env *lst)
{
	int	i;

	i = 0;
	while (lst)
	{
		i++;
		lst = lst->next;
	}
	return (i);
}
