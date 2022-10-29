/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_lstsize_bonus.c                                 :+:    :+:            */
/*                                                     +:+                    */
/*   By: mikuiper <mikuiper@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/29 15:51:12 by mikuiper      #+#    #+#                 */
/*   Updated: 2022/10/29 15:51:13 by mikuiper      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_lstsize(t_libft *lst)
{
	int	result;

	result = 0;
	if (lst == NULL)
		return (0);
	while (lst)
	{
		result++;
		lst = lst->next;
	}
	return (result);
}
