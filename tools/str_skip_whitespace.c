/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   str_skip_whitespace.c                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: mikuiper <mikuiper@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/29 15:57:26 by mikuiper      #+#    #+#                 */
/*   Updated: 2022/10/29 15:57:27 by mikuiper      ########   odam.nl         */
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
