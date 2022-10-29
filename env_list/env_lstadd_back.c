/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   env_lstadd_back.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: mikuiper <mikuiper@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/29 15:51:32 by mikuiper      #+#    #+#                 */
/*   Updated: 2022/10/29 15:51:34 by mikuiper      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "env_list.h"

//Adds new t_env at the back of the list
void	env_lstadd_back(t_env **lst, t_env *new)
{
	t_env	*temp;

	temp = *lst;
	if (!temp)
		*lst = new;
	else
	{
		temp = env_lstlast(temp);
		temp->next = new;
		new->prev = temp;
	}
}
