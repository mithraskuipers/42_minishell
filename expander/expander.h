#ifndef EXPANDER_H
# define EXPANDER_H

#include "../header.h"

typedef struct	s_varsexp
{
	int			i;
	int			x;
	int			length;
	char		*str;
	char		*newstr;
	char		*temp;
}				t_varsexp;

char	*expander_wrapper(t_ms *ms, char *str);
int		expander_get_len(t_ms *ms, char *str, int i, int length);
void	expander_tilde(t_ms *ms, int length);
void	set_env_value(t_ms *ms, t_varsexp *vars);
void	return_ret_status(t_varsexp *vars);
void	init_vars(t_ms *ms, t_varsexp *vars, int length, char *str);


#endif