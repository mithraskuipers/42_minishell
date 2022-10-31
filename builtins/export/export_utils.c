/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   export_utils.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: rkieboom <rkieboom@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/19 17:32:03 by rkieboom      #+#    #+#                 */
/*   Updated: 2022/10/31 12:57:20 by rkieboom      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../builtin.h"

void	export_declare_list(t_env *v)
{
	while (v)
	{
		ft_putstr_fd("declare -x ", 1);
		ft_putstr_fd(v->name, 1);
		if (v->content)
		{
			ft_putstr_fd("=", 1);
			ft_putstr_fd("\"", 1);
			ft_putstr_fd(v->content, 1);
			ft_putstr_fd("\"", 1);
		}
		ft_putstr_fd("\n", 1);
		v = v->next;
	}
}
