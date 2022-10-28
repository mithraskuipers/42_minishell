/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_str_skip_whitespace.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: rkieboom <rkieboom@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/11/29 10:15:46 by rkieboom      #+#    #+#                 */
/*   Updated: 2021/10/11 15:56:07 by spelle        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

int	str_skip_whitespace(const char *str)
{
	int	i;

	i = 0;
	while (str[i] != '\0' && (str[i] == ' ' || str[i] == '\t'))
		i++;
	return (i);
}
