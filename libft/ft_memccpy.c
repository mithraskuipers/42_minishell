/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_memccpy.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: mikuiper <mikuiper@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/29 15:50:14 by mikuiper      #+#    #+#                 */
/*   Updated: 2022/10/29 15:50:16 by mikuiper      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memccpy(void *dst, const void *src, int c, size_t n)
{
	size_t			i;
	unsigned char	*rdst;
	unsigned char	*rsrc;
	unsigned char	c1;

	rdst = dst;
	rsrc = (unsigned char *)src;
	i = 0;
	c1 = c;
	while (i < n)
	{
		rdst[i] = rsrc[i];
		if (c1 == rsrc[i])
			return (&rdst[i + 1]);
		i++;
	}
	return (0);
}
