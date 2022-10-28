/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parse_split_tokens.c                               :+:    :+:            */
/*                                                     +:+                    */
/*   By: mikuiper <mikuiper@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/24 14:35:11 by mikuiper      #+#    #+#                 */
/*   Updated: 2022/10/29 01:06:46 by mikuiper      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../parse.h"

typedef struct s_vars
{
	int		i;
	int		j;
	int		p;
	int		x;
	int		start;
	char	**newstr;
}				t_vars;

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
	ms->parse.commands[k] = newstr;
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
	if (ms->parse.comma1 == 0 && ms->parse.comma2 == 0 \
	&& ((vars->p == 1 && \
	!check_char(&ms->parse.commands[k][vars->j][vars->i + 1]) \
	&& array_thingy(&vars->p)) || (!ms->parse.commands[k] \
	[vars->j][vars->i + 1] && array_thingy(&vars->p))))
	{
		if (!ms->parse.commands[k][vars->j][vars->i + 1] \
		&& ft_strlen(ms->parse.commands[k][vars->j]) == 1)
			vars->i++;
		vars->newstr[vars->j + vars->x] = \
		ft_substr(ms->parse.commands[k][vars->j], \
		vars->start, vars->i - vars->start + 1);
		vars->start = vars->i + 1;
		vars->x++;
	}
	else if (ms->parse.comma1 == 0 && ms->parse.comma2 == 0 \
	&& (((vars->p == 0 && check_char(&ms->parse.commands[k] \
	[vars->j][vars->i + 1]) && array_thingy(&vars->p)))))
	{
		vars->newstr[vars->j + vars->x] = ft_substr(ms-> \
		parse.commands[k][vars->j], vars->start, vars->i - vars->start + 1);
		vars->start = vars->i + 1;
		vars->x++;
	}
	vars->i++;
}

//Seperate tokens
//Example: echo hallo>out = echo hallo > out
void	parse_split_tokens(t_ms *ms, int size, int k)
{
	t_vars	vars;

	init_vars(&vars, size);
	while (vars.j < size && ms->parse.commands[k][vars.j])
	{
		if (!check_char_str(ms, ms->parse.commands[k][vars.j]))
			vars.newstr[vars.j + vars.x] = \
			ft_strdup(ms->parse.commands[k][vars.j]);
		else
		{
			if (check_char(&ms->parse.commands[k][vars.j][vars.i]))
				vars.p = 1;
			else
				vars.p = 0;
			vars.start = vars.i;
			while (vars.i < (int)ft_strlen(ms->parse.commands[k] \
			[vars.j]) && ms->parse.commands[k][vars.j][vars.i])
				func(ms, &vars, k);
			vars.x -= 1;
		}
		vars.i = 0;
		vars.j++;
	}
	free_old_and_set(ms, k, ms->parse.commands[k], vars.newstr);
}
