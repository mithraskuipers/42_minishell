/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parser.h                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: mikuiper <mikuiper@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/30 17:20:41 by mikuiper      #+#    #+#                 */
/*   Updated: 2022/10/30 17:21:24 by mikuiper      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include "../header.h"

char	**parser_split_semicolon(t_ms *ms, char c);
char	**parser_split_spaces(t_ms *ms, const char *str, char c);
char	*expander_expand_dollar(t_ms *ms, char *str, int length);
char	*heredoc_create_str(t_ms *ms, char *str, int length);
char	*search_env(t_env *v, char *name, int length, char *temp);
int		char_is_token(char *c);
int		check_exist(char *PATH);
int		ft_execve(t_ms *ms, char **str, int ret);
int		ft_fork(pid_t *pid, int *fd);
int		ft_pipe(int *fd);
int		get_heredoc_input(t_ms *ms, int k);
int		get_return_status(int status);
int		heredoc_get_str_len(t_ms *ms, char *str);
int		parser_command_len_wrapper(char **str, t_ms *ms);
int		parser_wrapper(t_ms *ms);
int		str_has_token(t_ms *ms, char *str);
void	allocate_heredoc(t_ms *ms, int k);
void	get_heredoc_eof(t_ms *ms, int k);
void	heredoc_parse(t_ms *ms, int k, int i);
void	parser_separate_words_tokens(t_ms *ms, int size, int k);
void	quote_toggle(t_ms *ms, char *c);
void	set_heredoc(t_ms *ms, int k);
void	tokens_wrapper(t_ms *ms);
void	update_signals_default(void);
void	update_signals_handler(void);

#endif
