/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   checkword.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: mikuiper <mikuiper@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/24 14:35:44 by mikuiper      #+#    #+#                 */
/*   Updated: 2022/10/29 00:11:22 by mikuiper      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"

//Expands string to new value
char	*checkword(t_ms *ms, char *str)
{
	int		length;
	char	*temp;

	if (!ft_strchr(str, '$') && !ft_strchr(str, '\'') && !ft_strchr(str, '\"'))
		return (str);
	length = checkword_calclen(ms, str, 0, 0);
	if (length == 0)
	{
		free(str);
		return (ft_strdup(""));
	}
	temp = createstring(ms, str, length);
	free(str);
	return (temp);
}
