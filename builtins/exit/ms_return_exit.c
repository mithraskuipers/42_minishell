/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ms_return_exit.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: mikuiper <mikuiper@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/29 15:14:15 by mikuiper      #+#    #+#                 */
/*   Updated: 2022/10/30 13:05:03 by mikuiper      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../commands.h"

// return_exit() prints an error and exits with provided exit code if != 0.
// The error message ends with a newline if print_mode == 1, and without newline
// if print_mode == 2.
void	return_exit(int exit_code, int print_mode)
{
	if (print_mode == 1)
	{
		ft_putstr_fd("minishell-4.2$: ", 2);
		ft_putendl_fd(strerror(errno), 2);
	}
	else if (print_mode == 2)
	{
		ft_putstr_fd("minishell-4.2$: ", 2);
		ft_putstr_fd(strerror(errno), 2);
		ft_putchar_fd(' ', 2);
	}
	if (exit_code != 0)
	{
		tcsetattr(0, 0, &g_global.termios_save);
		exit(exit_code);
	}
}
