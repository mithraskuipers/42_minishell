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

char	*input_add_newline(char *s)
{
	int		len;
	char	*s_newline;

	len = ft_strlen(s);
	s_newline = ft_calloc(len + 2, sizeof(char));
	if (!s_newline)
		return_exit(1, PRNT_ERRNO_NL);
	ft_strlcpy(s_newline, s, len + 1);
	s_newline[len] = '\n';
	s_newline[len + 1] = '\0';
	free(s);
	return (s_newline);
}
