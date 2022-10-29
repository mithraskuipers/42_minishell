/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ms_return_exit.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: mikuiper <mikuiper@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/29 15:14:15 by mikuiper      #+#    #+#                 */
/*   Updated: 2022/10/29 15:14:17 by mikuiper      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../commands.h"

/**
 * @param ret exits with ret as value if not 0
 * @param print 1 prints errno with newline
 * @param print 2 prints errno without newline
 * @param print 0 doesn't print
**/
void	return_exit(int ret, int print)
{
	if (print == 1)
	{
		ft_putstr_fd("minishell-4.2$: ", 2);
		ft_putendl_fd(strerror(errno), 2);
	}
	else if (print == 2)
	{
		ft_putstr_fd("minishell-4.2$: ", 2);
		ft_putstr_fd(strerror(errno), 2);
		ft_putchar_fd(' ', 2);
	}
	if (ret != 0)
	{
		tcsetattr(0, 0, &g_global.termios_save);
		exit(ret);
	}
}