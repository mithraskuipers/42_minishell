/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parse.h                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: rkieboom <rkieboom@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/11/27 15:01:52 by rkieboom      #+#    #+#                 */
/*   Updated: 2022/10/29 22:42:47 by mikuiper      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSE_H
# define PARSE_H

# include "../header.h"

int		parser_wrapper(t_ms *ms);
int		parser_command_len_wrapper(char **str, t_ms *ms);

char	**parser_split_semicolon(t_ms *ms, char c);
char	**parser_split_spaces(t_ms *ms, const char *str, char c);
void	parser_separate_words_tokens(t_ms *ms, int size, int k);

void	tokens_wrapper(t_ms *ms);

char	*expander_expand_dollar(t_ms *ms, char *str, int length);

void	quote_toggle(t_ms *ms, char *c);
int		str_has_token(t_ms *ms, char *str);
int		char_is_token(char *c);
int		check_exist(char *PATH);

void	allocate_heredoc(t_ms *ms, int k);
void	set_heredoc(t_ms *ms, int k);
void	heredoc_parse(t_ms *ms, int k, int i);
int		heredoc_get_str_len(t_ms *ms, char *str);
char	*heredoc_create_str(t_ms *ms, char *str, int length);

void	get_heredoc_eof(t_ms *ms, int k);
int		get_heredoc_input(t_ms *ms, int k);

int		ft_execve(t_ms *ms, char **str, int ret);

char	*search_env(t_env *v, char *name, int length, char *temp);

int		ft_fork(pid_t *pid, int *fd);
int		ft_pipe(int *fd);
int		get_return_status(int status);

void	update_signals_handler(void);
void	update_signals_default(void);

#endif