/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cmds_tokens_count.c                                :+:    :+:            */
/*                                                     +:+                    */
/*   By: mikuiper <mikuiper@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/31 07:40:45 by mikuiper      #+#    #+#                 */
/*   Updated: 2022/10/31 07:42:16 by mikuiper      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cmds_tokens.h"

typedef struct s_vars
{
	int				i;
	int				wc;
	int				t;
}				t_vars;

static void	check_token(t_ms *v, t_vars *vars, t_cmdlist *cmdlist, int k)
{
	if (!ft_strncmp(cmdlist->cmd_array[vars->i], ">>", 3) \
	&& v->tokens[k].tkn_pos[vars->t] == vars->i + vars->wc + cmdlist->id)
	{
		cmdlist->tokens->double_redirection_right++;
		vars->t++;
	}
	else if (!ft_strncmp(cmdlist->cmd_array[vars->i], "<<", 3) \
	&& v->tokens[k].tkn_pos[vars->t] == vars->i + vars->wc + cmdlist->id)
	{
		cmdlist->tokens->double_redirection_left++;
		vars->t++;
	}
	else if (!ft_strncmp(cmdlist->cmd_array[vars->i], ">", 2) \
	&& v->tokens[k].tkn_pos[vars->t] == vars->i + vars->wc + cmdlist->id)
	{
		cmdlist->tokens->single_redirection_right++;
		vars->t++;
	}
	else if (!ft_strncmp(cmdlist->cmd_array[vars->i], "<", 2) \
	&& v->tokens[k].tkn_pos[vars->t] == vars->i + vars->wc + cmdlist->id)
	{
		cmdlist->tokens->single_redirection_left++;
		vars->t++;
	}
}

//Counts the amount of tokens we have and wich ones
void	cmds_tokens_count(t_ms *v, t_cmdlist *cmdlist, int k)
{
	t_vars	vars;

	ft_bzero(&vars, sizeof(t_vars));
	while (cmdlist)
	{
		if (v->tokens[k].token[vars.t] && \
		!ft_strncmp(v->tokens[k].token[vars.t], "|", 2))
			vars.t++;
		check_token(v, &vars, cmdlist, k);
		vars.i++;
		if (!cmdlist->cmd_array[vars.i])
		{
			cmdlist->tokens->n_tokens = \
			cmdlist->tokens->single_redirection_left + \
			cmdlist->tokens->single_redirection_right + \
			cmdlist->tokens->double_redirection_left + \
			cmdlist->tokens->double_redirection_right;
			vars.wc += vars.i;
			vars.i = 0;
			cmdlist = cmdlist->next;
			if (vars.t == v->tokens[k].n_tokens)
				break ;
		}
	}
}
