#ifndef EXPANDER_H
# define EXPANDER_H

#include "../header.h"

char	*expander(t_ms *ms, char *str);
int		expander_calclen(t_ms *ms, char *str, int i, int length);
void	expander_tilde(t_ms *ms, int length);


#endif