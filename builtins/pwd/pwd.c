/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   pwd.c                                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: rkieboom <rkieboom@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/05/16 22:47:48 by rkieboom      #+#    #+#                 */
/*   Updated: 2022/10/31 12:57:27 by rkieboom      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../builtin.h"

int	pwd(void)
{
	char	*cwd;

	cwd = getcwd(0, 0);
	ft_putendl_fd(cwd, 1);
	if (cwd)
		free(cwd);
	return (0);
}
