/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   input_read.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: mikuiper <mikuiper@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/28 21:56:51 by mikuiper      #+#    #+#                 */
/*   Updated: 2022/10/31 11:24:10 by mikuiper      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../header.h"
#include <readline/readline.h>
#include <readline/history.h>

// input_is_ws() checks whether the user inputted line consists solely of
// whitespace.
static int	input_is_ws(t_ms *ms)
{
	int	i;

	i = 0;
	while (ms->line.array[i] && (ms->line.array[i] == 32 \
	|| (ms->line.array[i] >= 9 && ms->line.array[i] <= 13)))
		i++;
	if (ms->line.array[i])
		return (0);
	return (1);
}

// input_clean_array() frees the memory that was allocated for storing the
// user inputted line.
static void	input_clean_array(t_ms *ms)
{
	if (ms->line.array)
	{
		free(ms->line.array);
		ms->line.array = 0;
	}
}

// input_error() is called when an error occurred while storing the user
// inputted line.
static void	input_error(t_ms *ms)
{
	ft_putstr_fd(\
"minishell-4.2$: unexpected EOF while looking for matching '", 2);
	if (ms->parser.squote)
		ft_putstr_fd("''\n", 2);
	else
		ft_putstr_fd("\"'\n", 2);
}

// terminal_params() configures the terminal settings prior to reading in
// the user input.
static void	terminal_params(t_ms *ms)
{
	ms->hdoc_break = 0;
	tcsetattr(0, 0, &g_global.termios_new);
	signal(SIGINT, sig_handler);
	signal(SIGQUIT, SIG_IGN);
	input_clean_array(ms);
}

// input_read() configures the terminal settings and prompts the user for
// input. Mode 0 is called if the inputted line does not contain unclosed
// quotes. If unclosed quotes were detected 
void	input_read(t_ms *ms, int mode)
{
	terminal_params(ms);
	if (mode == 0)
	{
		while (!ms->line.array)
		{
			ms->line.array = readline("minishell-4.2$ ");
			if (!ms->line.array)
			{
				ft_putendl_fd("exit", 1);
				tcsetattr(0, 0, &g_global.termios_save);
				exit(0);
			}
			if (ms->line.array && input_is_ws(ms))
				input_clean_array(ms);
		}
	}
	else
	{
		ms->line.array = readline("> ");
		if (ms->line.array == NULL)
			input_error(ms);
	}
}
