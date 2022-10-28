/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   read_input.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: mikuiper <mikuiper@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/28 21:56:51 by mikuiper      #+#    #+#                 */
/*   Updated: 2022/10/29 00:21:02 by mikuiper      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../header.h"
#include <readline/readline.h>
#include <readline/history.h>

static int	check_spaces(t_ms *ms)
{
	int	i;

	i = 0;
	while (ms->gnl.buf[i] && (ms->gnl.buf[i] == 32 \
	|| (ms->gnl.buf[i] >= 9 && ms->gnl.buf[i] <= 13)))
		i++;
	if (ms->gnl.buf[i])
		return (0);
	return (1);
}

static void	reset_buf(t_ms *ms)
{
	if (ms->gnl.buf)
	{
		free(ms->gnl.buf);
		ms->gnl.buf = 0;
	}
}

static void	print_error(t_ms *ms)
{
	ft_putstr_fd(\
"minishell-4.2$: unexpected EOF while looking for matching `", 2);
	if (ms->parse.comma1)
		ft_putstr_fd("''\n", 2);
	else
		ft_putstr_fd("\"'\n", 2);
}

static void	setup(t_ms *ms)
{
	ms->hdoc_break = 0;
	tcsetattr(0, 0, &g_global.termios_new);
	signal(SIGINT, sig_handler);
	signal(SIGQUIT, SIG_IGN);
	reset_buf(ms);
}

//Reads input and saves it in ms->gnl.buf
void	input_read(t_ms *ms, int mode)
{
	setup(ms);
	if (mode == 0)
	{
		while (!ms->gnl.buf)
		{
			ms->gnl.buf = readline("minishell-4.2$ ");
			if (!ms->gnl.buf)
			{
				ft_putendl_fd("exit", 1);
				tcsetattr(0, 0, &g_global.termios_save);
				exit(0);
			}
			if (ms->gnl.buf && check_spaces(ms))
				reset_buf(ms);
		}
	}
	else
	{
		ms->gnl.buf = readline("> ");
		if (ms->gnl.buf == NULL)
			print_error(ms);
	}
}
