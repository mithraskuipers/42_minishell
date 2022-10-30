/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parse.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: mikuiper <mikuiper@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/24 14:34:50 by mikuiper      #+#    #+#                 */
/*   Updated: 2022/10/30 13:20:33 by mikuiper      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"
#include "../expander/expander.h"

typedef struct s_vars
{
	int		cmd_i;
	int		n_words;
	char	**split_cmd;
}				t_vars;

//Free the temporily struct
static void	clean_splitted_commands(char **split_cmd)
{
	int	i;

	i = 0;
	while (split_cmd[i])
	{
		free(split_cmd[i]);
		i++;
	}
	if (split_cmd)
		free(split_cmd);
}

// expander_loop() iterates over each semicolon splitted command and each of its
// space splitted words.
static void	expander_loop(t_ms *ms)
{
	int	i;
	int	cmd;
	int	x;

	cmd = 0;
	x = 0;
	while (ms->parse.commands[cmd])
	{
		i = 0;
		x = 0;
		while (ms->parse.commands[cmd][i] != NULL)
		{
			ms->parse.commands[cmd][i - x] = expander_wrapper \
			(ms, ms->parse.commands[cmd][i]);
			if (!ms->parse.commands[cmd][i])
				x++;
			i++;
		}
		cmd++;
	}
}

// parser_input_splitter() is a wrapper function, handling the command splitting
// process on semicolons and spaces. It also detects if redirections are stuck
// to a word, and splits them accordingly.
static void	parser_input_splitter(t_ms *ms, t_vars *vars)
{
	ft_bzero(vars, sizeof(t_vars));
	vars->split_cmd = parser_split_semicolon(ms, ';');
	while (vars->split_cmd[vars->n_words])
		vars->n_words++;
	ms->parse.commands = ft_calloc(vars->n_words + 1, sizeof(char **));
	if (!ms->parse.commands)
		return_exit(1, PRNT_ERRNO_NL);
	ms->parse.commands[vars->n_words] = 0;
	ms->tokens = ft_calloc(vars->n_words, sizeof(t_tokens));
	if (!ms->tokens)
		return_exit(1, PRNT_ERRNO_NL);
	while (vars->n_words)
	{
		ms->parse.commands[vars->cmd_i] = parser_split_spaces(\
		ms, vars->split_cmd[vars->cmd_i], ' ');
		parser_separate_words_tokens(ms, parser_command_len_wrapper(\
		ms->parse.commands[vars->cmd_i], ms), vars->cmd_i);
		vars->n_words--;
		vars->cmd_i++;
	}
}

// parser_wrapper() is a wrapper function for the entire input line parsing
// tasks. It appropriately splits the input line, extracts and stores detected
// redirections from the input, handles heredoc, and expands the line if
// applicable.
int	parser_wrapper(t_ms *ms)
{
	t_vars	vars;

	parser_input_splitter(ms, &vars);
	tokens_wrapper(ms);
	while (vars.split_cmd[vars.n_words])
		vars.n_words++;
	expander_tilde(ms, vars.n_words);
	if (syntax_error_parse(ms))
	{
		clean_splitted_commands(vars.split_cmd);
		return (1);
	}
	allocate_heredoc(ms, vars.n_words);
	clean_splitted_commands(vars.split_cmd);
	expander_loop(ms);
	set_heredoc(ms, vars.n_words);
	return (0);
}
