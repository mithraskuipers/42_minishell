/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parser.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: mikuiper <mikuiper@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/30 17:20:32 by mikuiper      #+#    #+#                 */
/*   Updated: 2022/10/30 17:29:43 by mikuiper      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "../expander/expander.h"

typedef struct s_vars
{
	int		cmd_i;
	int		n_cmds;
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
	while (ms->parser.commands[cmd])
	{
		i = 0;
		x = 0;
		while (ms->parser.commands[cmd][i] != NULL)
		{
			ms->parser.commands[cmd][i - x] = expander_wrapper \
			(ms, ms->parser.commands[cmd][i]);
			if (!ms->parser.commands[cmd][i])
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
	while (vars->split_cmd[vars->n_cmds])
		vars->n_cmds++;
	ms->parser.commands = ft_calloc(vars->n_cmds + 1, sizeof(char **));
	if (!ms->parser.commands)
		return_exit(1, PRNT_ERRNO_NL);
	ms->parser.commands[vars->n_cmds] = 0;
	ms->tokens = ft_calloc(vars->n_cmds, sizeof(t_tokens));
	if (!ms->tokens)
		return_exit(1, PRNT_ERRNO_NL);
	while (vars->n_cmds)
	{
		ms->parser.commands[vars->cmd_i] = parser_split_spaces(\
		ms, vars->split_cmd[vars->cmd_i], ' ');
		parser_separate_words_tokens(ms, parser_command_len_wrapper(\
		ms->parser.commands[vars->cmd_i], ms), vars->cmd_i);
		vars->n_cmds--;
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
	while (vars.split_cmd[vars.n_cmds])
		vars.n_cmds++;
	expander_tilde(ms, vars.n_cmds);
	if (parser_syntax_tokens(ms))
	{
		clean_splitted_commands(vars.split_cmd);
		return (1);
	}
	allocate_heredoc(ms, vars.n_cmds);
	clean_splitted_commands(vars.split_cmd);
	expander_loop(ms);
	set_heredoc(ms, vars.n_cmds);
	return (0);
}
