/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   env_lstlast.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: mikuiper <mikuiper@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/29 15:49:47 by mikuiper      #+#    #+#                 */
/*   Updated: 2022/10/29 15:49:48 by mikuiper      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "env_list.h"

t_env	*env_lstlast(t_env *lst)
{
	while (lst->next)
		lst = lst->next;
	return (lst);
}
