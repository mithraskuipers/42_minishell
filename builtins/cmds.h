/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cmds.h                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: rkieboom <rkieboom@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/05/11 16:35:27 by rkieboom      #+#    #+#                 */
/*   Updated: 2022/10/30 12:38:03 by mikuiper      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef COMMANDS_H
# define COMMANDS_H

# include "../header.h"
# include "../libft/libft.h"
# include <string.h>
# include <sys/errno.h>
# include <sys/stat.h>
# include <fcntl.h>

char	*absolute_path(char *PATH);
char	*relative_path(char *PATH, t_env *env);
int		cd_check_permissions(char *path);
int		cd_exec_cmd(t_env *env, char *path);
int		cd_expander_tilde(t_ms *ms, char *str);
int		cd(t_ms *v, char **str);
int		check_exist(char *PATH);
int		check_permission(char *PATH);
int		echo(char **str);
int		env(t_env *v);
int		export(t_env **v, char **str);
int		is_absolute_path(char *str);
int		pwd(void);
int		unset(t_env **v, char **str);
void	export_declare_list(t_env *v);
void	ft_execve(t_ms *ms, char **str);
void	ms_exit(char **str);
void	return_exit(int ret, int print);
void	update_signals_default(void);
void	update_signals_handler(void);

#endif
