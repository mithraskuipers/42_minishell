/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parse.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: mikuiper <mikuiper@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/24 14:34:50 by mikuiper      #+#    #+#                 */
/*   Updated: 2022/10/29 01:32:28 by mikuiper      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"

typedef struct s_vars
{
	int		i;
	int		n_words;
	char	**splitted;
}				t_vars;

//Free the temporily struct
static void	freemem(char **result)
{
	int	i;

	i = 0;
	while (result[i])
	{
		free(result[i]);
		i++;
	}
	if (result)
		free(result);
}

//The actual big parsing and expanding
static void	parsing(t_ms *ms)
{
	int	i;
	int	j;
	int	x;

	j = 0;
	x = 0;
	while (ms->parse.commands[j])
	{
		i = 0;
		x = 0;
		while (ms->parse.commands[j][i] != NULL)
		{
			ms->parse.commands[j][i - x] = \
			checkword(ms, ms->parse.commands[j][i]);
			if (!ms->parse.commands[j][i])
				x++;
			i++;
		}
		j++;
	}
}

static void	parser_input_splitter(t_ms *ms, t_vars *vars)
{
	ft_bzero(vars, sizeof(t_vars));
	vars->splitted = parser_splitter_semicolon(ms, ';');
	while (vars->splitted[vars->n_words])
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
		ms->parse.commands[vars->i] = parser_splitter_spaces(ms, vars->splitted[vars->i], ' ');
		parser_separate_words_tokens(ms, parse_arraysize(ms->parse.commands[vars->i], ms), vars->i);
		vars->n_words--;
		vars->i++;
	}
}

// (1) scans input and allocates memory
// (2) adjusts input for easy parsing
// (3) extracts and stores tokens
int	parser_wrapper(t_ms *ms)
{
	t_vars	vars;

	parser_input_splitter(ms, &vars);
	tokens(ms);
	while (vars.splitted[vars.n_words])
		vars.n_words++;
	tilde_expansion(ms, vars.n_words);
	if (syntax_error_parse(ms))
	{
		freemem(vars.splitted);
		return (1);
	}
	allocate_heredoc(ms, vars.n_words);
	freemem(vars.splitted);
	parsing(ms);
	set_heredoc(ms, vars.n_words);
	return (0);
}
