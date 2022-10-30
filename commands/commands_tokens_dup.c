/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   commands_tokens_dup.c                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: rkieboom <rkieboom@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/08/29 14:08:53 by rkieboom      #+#    #+#                 */
/*   Updated: 2022/10/30 17:16:39 by mikuiper      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "tokens.h"

typedef struct s_vars
{
	t_cmdlist	*temp;	
	int			tokens;
	int			i;
	int			token_c;
	int			token_local_c;
}				t_vars;

//Return the token we are at
static char	*ret_token(t_ms *v, int k, int token_count)
{
	int	count;
	int	i;

	i = 0;
	count = 0;
	while (count != token_count)
	{
		if (v->tokens[k].token[i] && \
		!ft_strncmp(v->tokens[k].token[i], "|", 2))
			i++;
		else
		{
			count++;
			if (count != token_count)
				i++;
		}
		if (!v->tokens[k].token[i])
			ms_error("Something went wrong in func: ret_token\n");
	}
	return (v->tokens[k].token[i]);
}

static int	get_resetter(t_ms *v, int k, int i)
{
	while (i > 0)
	{
		i--;
		if (!ft_strncmp(v->tokens[k].token[i], "|", 2))
			return (v->tokens[k].tkn_pos[i] + 1);
	}
	return (0);
}

// @param tkn_pos = Is the x token we want
// 
// *		 [-1] [-1] [0] [-1][1] [-1] [2][-1]
// *Example: cat main.c >  out  <  out2 > Makefile
// *tkn_pos = 0 will return >
// *tkn_pos = 1 will return <
static int	get_tkn_pos(t_ms *v, int k, int token_count)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (count != token_count)
	{
		if (v->tokens[k].token[i] && \
		!ft_strncmp(v->tokens[k].token[i], "|", 2))
			i++;
		else
		{
			count++;
			if (count != token_count)
				i++;
		}
		if (!v->tokens[k].token[i])
			ms_error("Something went wrong in func: get_tkn_pos\n");
	}
	return (v->tokens[k].tkn_pos[i] - get_resetter(v, k, i));
}

//Set the token values
void	commands_tokens_dup(t_ms *v, t_cmdlist *pipes, int k)
{
	t_vars	vars;

	ft_bzero(&vars, sizeof(t_vars));
	vars.temp = pipes;
	while (vars.temp)
	{
		vars.i = 0;
		vars.tokens = vars.temp->tokens->n_tokens;
		while (vars.tokens)
		{
			vars.temp->tokens->token[vars.token_local_c] = \
			ft_strdup(ret_token(v, k, vars.token_c + 1));
			if (!vars.temp->tokens->token[vars.token_local_c])
				return_exit(1, PRNT_ERRNO_NL);
			vars.temp->tokens->tkn_pos[vars.token_local_c] = \
			get_tkn_pos(v, k, vars.token_c + 1);
			vars.token_c++;
			vars.token_local_c++;
			vars.tokens--;
			vars.i++;
		}
		vars.temp = vars.temp->next;
		vars.token_local_c = 0;
	}
	set_heredoc_tokens(v, pipes, k);
}
