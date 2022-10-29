/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_memcpy.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: mikuiper <mikuiper@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/29 15:51:16 by mikuiper      #+#    #+#                 */
/*   Updated: 2022/10/29 15:51:18 by mikuiper      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	char	*rdest;
	char	*rsrc;
	size_t	i;

	if (!dst && !src)
		return (dst);
	rdest = (char *)dst;
	rsrc = (char *)src;
	i = 0;
	while (i < n)
	{
		rdest[i] = rsrc[i];
		i++;
	}
	return (rdest);
}
