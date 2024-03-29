/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parser_separate_words_tokens.c                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: mikuiper <mikuiper@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/29 01:32:56 by mikuiper      #+#    #+#                 */
/*   Updated: 2022/10/30 14:54:26 by mikuiper      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../parser.h"

typedef struct s_vars
{
	int		i;
	int		j;
	int		p;
	int		x;
	int		start;
	char	**newstr;
}				t_vars;

static int	binary_toggler(int *p)
{
	if (*p == 1)
		*p = 0;
	else if (*p == 0)
		*p = 1;
	return (1);
}

void	free_old_and_set(t_ms *ms, int k, char **str, char **newstr)
{
	int	i;

	i = 0;
	if (str)
	{
		while (str[i])
		{
			free(str[i]);
			i++;
		}
		free(str);
	}
	ms->parser.commands[k] = newstr;
}

static void	init_vars(t_vars *vars, int size)
{
	vars->i = 0;
	vars->j = 0;
	vars->x = 0;
	vars->newstr = ft_calloc(size + 1, sizeof(char *));
	if (!vars->newstr)
		return_exit(1, PRNT_ERRNO_NL);
	vars->newstr[size] = 0;
}

static void	func(t_ms *ms, t_vars *vars, int k)
{
	if (ms->parser.squote == 0 && ms->parser.dquote == 0 \
	&& ((vars->p == 1 && \
	!char_is_token(&ms->parser.commands[k][vars->j][vars->i + 1]) \
	&& binary_toggler(&vars->p)) || (!ms->parser.commands[k] \
	[vars->j][vars->i + 1] && binary_toggler(&vars->p))))
	{
		if (!ms->parser.commands[k][vars->j][vars->i + 1] \
		&& ft_strlen(ms->parser.commands[k][vars->j]) == 1)
			vars->i++;
		vars->newstr[vars->j + vars->x] = \
		ft_substr(ms->parser.commands[k][vars->j], \
		vars->start, vars->i - vars->start + 1);
		vars->start = vars->i + 1;
		vars->x++;
	}
	else if (ms->parser.squote == 0 && ms->parser.dquote == 0 \
	&& (((vars->p == 0 && char_is_token(&ms->parser.commands[k] \
	[vars->j][vars->i + 1]) && binary_toggler(&vars->p)))))
	{
		vars->newstr[vars->j + vars->x] = ft_substr(ms-> \
		parser.commands[k][vars->j], vars->start, vars->i - vars->start + 1);
		vars->start = vars->i + 1;
		vars->x++;
	}
	vars->i++;
}

//Seperate tokens
//Example: echo hallo>out = echo hallo > out
void	parser_separate_words_tokens(t_ms *ms, int size, int k)
{
	t_vars	vars;

	init_vars(&vars, size);
	while (vars.j < size && ms->parser.commands[k][vars.j])
	{
		if (!str_has_token(ms, ms->parser.commands[k][vars.j]))
			vars.newstr[vars.j + vars.x] = \
			ft_strdup(ms->parser.commands[k][vars.j]);
		else
		{
			if (char_is_token(&ms->parser.commands[k][vars.j][vars.i]))
				vars.p = 1;
			else
				vars.p = 0;
			vars.start = vars.i;
			while (vars.i < (int)ft_strlen(ms->parser.commands[k] \
			[vars.j]) && ms->parser.commands[k][vars.j][vars.i])
				func(ms, &vars, k);
			vars.x -= 1;
		}
		vars.i = 0;
		vars.j++;
	}
	free_old_and_set(ms, k, ms->parser.commands[k], vars.newstr);
}
