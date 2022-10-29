/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   input_add_newline.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: rkieboom <rkieboom@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/05/14 23:34:24 by rkieboom      #+#    #+#                 */
/*   Updated: 2022/10/29 01:06:46 by mikuiper      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../header.h"

char	*input_add_newline(char *str)
{
	int		length;
	char	*result;

	length = ft_strlen(str);
	result = ft_calloc(length + 2, sizeof(char));
	if (!result)
		return_exit(1, PRNT_ERRNO_NL);
	ft_strlcpy(result, str, length + 1);
	result[length] = '\n';
	result[length + 1] = '\0';
	free(str);
	return (result);
}
