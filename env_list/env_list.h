/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   env_list.h                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: rkieboom <rkieboom@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/23 22:54:00 by rkieboom      #+#    #+#                 */
/*   Updated: 2022/10/30 12:52:05 by mikuiper      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENV_LIST_H
# define ENV_LIST_H

# include <stdlib.h>
# include "../libft/libft.h"

typedef struct s_env
{
	char			*name;
	char			*content;
	struct s_env	*next;
	struct s_env	*prev;
}					t_env;

char	*env_get_content(t_env *v, char *key);
char	*env_get_name(t_env *v, char *key);
int		env_exist(t_env *v, char *key);
int		env_has_data(t_env *v, char *key);
int		env_lstsize(t_env *lst);
t_env	*create_envp(t_env *v, char **envp);
t_env	*env_get(t_env *v, char *key);
t_env	*env_lst_new(void *name, void *content);
t_env	*env_lstlast(t_env *lst);
void	env_add_content(t_env **v, char *envname, char *envcontent);
void	env_change_content(t_env *v, char *envname, char *envcontent);
void	env_lst_remove(t_env **v, char *key);
void	env_lstadd_back(t_env **lst, t_env *new);
void	return_exit(int ret, int print);

#endif
