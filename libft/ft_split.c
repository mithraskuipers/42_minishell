/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_split.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: mikuiper <mikuiper@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/29 15:51:21 by mikuiper      #+#    #+#                 */
/*   Updated: 2022/10/29 19:51:42 by mikuiper      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	arraysize(const char *s, char c)
{
	int	i;
	int	k;

	i = 0;
	k = 0;
	if (s[i] == '\0')
		return (0);
	while (s[i])
	{
		while (s[i] == c && s[i])
			i++;
		while (s[i] != c && s[i])
		{
			i++;
			if (s[i] == c || !s[i])
				k++;
		}
	}
	return (k);
}

static void	findstart(const char *s, char c, int *i, int *start)
{
	while (s[*i] && s[*i] == c)
		(*i)++;
	if (s[*i] != c && s[*i])
		*start = *i;
}

static int	freemem(char **result, int k)
{
	if (!result[k])
	{
		while (k > 0)
		{
			k--;
			free(result[k]);
		}
		free(result);
		return (1);
	}
	return (0);
}

static char	**splitter(const char *s, char c, char **result, int i)
{
	int	strlength;
	int	arrayindex;
	int	start;

	strlength = 0;
	arrayindex = 0;
	while (arrayindex != arraysize(s, c))
	{
		findstart(s, c, &i, &start);
		while (s[i] && s[i] != c)
		{
			i++;
			strlength++;
		}
		result[arrayindex] = ft_substr(s, start, strlength);
		if (freemem(result, arrayindex))
			break ;
		strlength = 0;
		arrayindex++;
		i++;
	}
	result[arrayindex] = NULL;
	return (result);
}

char	**ft_split(char const *s, char c)
{
	char	**result;

	if (!s)
		return (NULL);
	result = (char **)malloc((arraysize(s, c) + 1) * sizeof(char *));
	if (!result)
		return (NULL);
	result = splitter(s, c, result, 0);
	return (result);
}
