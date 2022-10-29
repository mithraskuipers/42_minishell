/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   signal_handler.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: rkieboom <rkieboom@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/04 18:21:53 by rkieboom      #+#    #+#                 */
/*   Updated: 2022/10/29 12:55:51 by mikuiper      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../header.h"

static void	process(int signal_code)
{
	if (!kill(g_global.pid, signal_code))
	{
		if (signal_code == SIGQUIT)
		{
			ft_putstr_fd("Quit: 3\n", 2);
			rl_on_new_line();
			rl_replace_line("", 0);
			g_global.status = 131;
		}
		else if (signal_code == SIGINT)
		{
			ft_putstr_fd("\n", 2);
			rl_on_new_line();
			rl_replace_line("", 0);
			g_global.status = 130;
		}
	}
	else if (signal_code == SIGINT)
	{
		ft_putstr_fd("\n", 2);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
		g_global.status = 1;
	}
}

void	sig_handler(int signal_code)
{
	if ((signal_code == SIGINT || \
	signal_code == SIGQUIT) && g_global.pid != 0)
		process(signal_code);
	else
	{
		if (signal_code == SIGINT)
		{
			ft_putstr_fd("\n", 2);
			rl_on_new_line();
			rl_replace_line("", 0);
			rl_redisplay();
			g_global.status = 1;
		}
	}
}

//Setting the signals
void	update_signals_handler(void)
{
	signal(SIGINT, sig_handler);
	signal(SIGQUIT, sig_handler);
}

// TODO: PREVIOUSLY NAMED signals_dfl
//Setting all signals to IGN
void	update_signals_default(void)
{
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
}
