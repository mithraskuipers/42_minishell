/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   execve.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: rkieboom <rkieboom@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/05/25 17:00:06 by rkieboom      #+#    #+#                 */
/*   Updated: 2022/10/31 12:57:06 by rkieboom      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../builtin.h"
#include <errno.h>
#include <string.h>
#include <stdio.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/wait.h>

static char	*get_full_env(t_env *env)
{
	int		i;
	int		j;
	int		length;
	char	*str;

	i = 0;
	j = 0;
	length = ft_strlen(env->name) + ft_strlen(env->content) + 2;
	str = ft_calloc(length, sizeof(char));
	if (!str)
		return_exit(1, PRNT_ERRNO_NL);
	str[length - 1] = 0;
	while (env->name[i])
	{
		str[i] = env->name[i];
		i++;
	}
	str[i] = '=';
	i++;
	while (env->content[j])
	{
		str[i + j] = env->content[j];
		j++;
	}
	return (str);
}

static int	get_length(t_env *temp)
{
	int	length;

	length = 0;
	while (temp)
	{
		if (temp->content)
			length++;
		temp = temp->next;
	}
	return (length);
}

static char	**recreate_envp(t_env *env)
{
	char	**envp;
	int		length;

	length = get_length(env);
	envp = ft_calloc(length + 1, sizeof(char *));
	if (!envp)
		return_exit(1, PRNT_ERRNO_NL);
	envp[length] = 0;
	length = 0;
	while (env)
	{
		if (env->content)
		{
			envp[length] = get_full_env(env);
			length++;
		}
		env = env->next;
	}
	return (envp);
}

void	ft_execve(t_ms *ms, char **str)
{
	char	*path;
	char	**envp;

	envp = recreate_envp(ms->env);
	if (is_absolute_path(str[0]))
		path = absolute_path(str[0]);
	else
		path = relative_path(str[0], ms->env);
	if (path && execve(path, str, envp) < 0)
		return_exit(1, PRNT_ERRNO_NL);
	else
		return_exit(g_global.status, 0);
	exit(0);
}
