/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_calloc.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: mikuiper <mikuiper@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/29 15:51:37 by mikuiper      #+#    #+#                 */
/*   Updated: 2022/10/29 15:51:39 by mikuiper      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t count, size_t size)
{
	size_t	i;
	char	*result;

	i = 0;
	result = (char *)malloc(sizeof(char) * (count * size));
	if (result == NULL)
		return (NULL);
	while (i != (count * size))
	{
		result[i] = 0;
		i++;
	}
	return (result);
}
