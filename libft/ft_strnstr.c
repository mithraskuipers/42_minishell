/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strnstr.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: mikuiper <mikuiper@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/29 15:51:53 by mikuiper      #+#    #+#                 */
/*   Updated: 2022/10/29 15:51:54 by mikuiper      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t	i;
	size_t	j;
	size_t	needlelength;

	i = 0;
	j = 0;
	needlelength = 0;
	while (needle[needlelength] != '\0')
		needlelength++;
	if (needlelength == 0)
		return ((char *)haystack);
	while (haystack[i] && i != len)
	{
		j = 0;
		while (haystack[i + j] == needle[j] && len != j + i)
		{
			j++;
			if (j == needlelength)
				return ((char *)haystack + i);
		}
		i++;
	}
	return (NULL);
}
