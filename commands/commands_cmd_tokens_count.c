/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   commands_cmd_tokens_count.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: rkieboom <rkieboom@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/08/27 03:28:59 by rkieboom      #+#    #+#                 */
/*   Updated: 2022/10/29 18:13:14 by mikuiper      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "tokens.h"

typedef struct s_vars
{
	int				i;
	int				wc;
	int				t;
}				t_vars;

static void	check_token(t_ms *v, t_vars *vars, t_cmdlist *temp, int k)
{
	if (!ft_strncmp(temp->command[vars->i], ">>", 3) \
	&& v->tokens[k].token_pos[vars->t] == vars->i + vars->wc + temp->id)
	{
		temp->tokens->double_redirection_right++;
		vars->t++;
	}
	else if (!ft_strncmp(temp->command[vars->i], "<<", 3) \
	&& v->tokens[k].token_pos[vars->t] == vars->i + vars->wc + temp->id)
	{
		temp->tokens->double_redirection_left++;
		vars->t++;
	}
	else if (!ft_strncmp(temp->command[vars->i], ">", 2) \
	&& v->tokens[k].token_pos[vars->t] == vars->i + vars->wc + temp->id)
	{
		temp->tokens->single_redirection_right++;
		vars->t++;
	}
	else if (!ft_strncmp(temp->command[vars->i], "<", 2) \
	&& v->tokens[k].token_pos[vars->t] == vars->i + vars->wc + temp->id)
	{
		temp->tokens->single_redirection_left++;
		vars->t++;
	}
}

//Counts the amount of tokens we have and wich ones
void	commands_cmd_tokens_count(t_ms *v, t_cmdlist *temp, int k)
{
	t_vars	vars;

	ft_bzero(&vars, sizeof(t_vars));
	while (temp)
	{
		if (v->tokens[k].token[vars.t] && \
		!ft_strncmp(v->tokens[k].token[vars.t], "|", 2))
			vars.t++;
		check_token(v, &vars, temp, k);
		vars.i++;
		if (!temp->command[vars.i])
		{
			temp->tokens->n_tokens = temp->tokens->single_redirection_left + \
			temp->tokens->single_redirection_right + \
			temp->tokens->double_redirection_left + \
			temp->tokens->double_redirection_right;
			vars.wc += vars.i;
			vars.i = 0;
			temp = temp->next;
			if (vars.t == v->tokens[k].n_tokens)
				break ;
		}
	}
}