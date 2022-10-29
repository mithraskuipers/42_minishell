/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parse.h                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: rkieboom <rkieboom@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/11/27 15:01:52 by rkieboom      #+#    #+#                 */
/*   Updated: 2022/10/29 17:50:20 by mikuiper      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSE_H
# define PARSE_H

# include "../header.h"

int		parser_wrapper(t_ms *ms);
int		parse_arraysize(char **str, t_ms *ms);

char	**parser_splitter_semicolon(t_ms *ms, char c);
char	**parser_splitter_spaces(t_ms *ms, const char *str, char c);
void	parser_separate_words_tokens(t_ms *ms, int size, int k);

void	tokens_wrapper(t_ms *ms);

char	*createstring(t_ms *ms, char *str, int length);

void	check_quote(t_ms *ms, char *c);
int		check_char_str(t_ms *ms, char *str);
int		check_char(char *c);
int		check_exist(char *PATH);

void	allocate_heredoc(t_ms *ms, int k);
void	set_heredoc(t_ms *ms, int k);
void	heredoc_parse(t_ms *ms, int k, int i);
int		heredoc_get_str_len(t_ms *ms, char *str);
char	*heredoc_create_str(t_ms *ms, char *str, int length);

void	get_heredoc_eof(t_ms *ms, int k);
int		get_heredoc_input(t_ms *ms, int k);

int		array_thingy(int *p);

int		ft_execve(t_ms *ms, char **str, int ret);

char	*search_env(t_env *v, char *name, int length, char *temp);

int		ft_fork(pid_t *pid, int *fd);
int		ft_pipe(int *fd);
int		get_return_status(int status);

void	update_signals_handler(void);
void	update_signals_default(void);

#endif