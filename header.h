/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   header.h                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: mikuiper <mikuiper@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/28 21:57:11 by mikuiper      #+#    #+#                 */
/*   Updated: 2022/10/31 17:25:05 by rkieboom      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef HEADER_H
# define HEADER_H

# include "libft/libft.h"
# include "env_list/env_list.h"

# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include <dirent.h>
# include <signal.h>
# include <termios.h>
# include <readline/readline.h>
# include <readline/history.h>

# define __DUP__ "MINISHELL_DUP_537425"
# define NO_PRNT 0
# define PRNT_ERRNO_NL 1

typedef struct s_parse
{
	char		***commands;
	int			squote;
	int			dquote;
}				t_parse;

typedef struct s_line
{
	char		*array;
}				t_line;

typedef struct s_heredoc_data
{
	char					*str;
	struct s_heredoc_data	*next;
}							t_heredoc_data;

typedef struct s_heredoc
{
	int				pipe[2];
	int				heredoc_q;
	char			*eof;
	t_heredoc_data	*data;
}					t_heredoc;

typedef struct s_tokens
{
	int			n_tokens;
	int			stdin_fd;
	int			stdout_fd;
	char		**token;
	int			*tkn_pos;
	int			single_redirection_left;
	int			single_redirection_right;
	int			double_redirection_left;
	int			double_redirection_right;
	int			pipe;
	int			last_l;
	int			last_r;
	int			error;
	t_heredoc	*heredoc;
}				t_tokens;

typedef struct s_cmdlist
{
	int					id;
	int					fd[2];
	int					read_pipe;
	char				**cmd_array;
	struct s_tokens		*tokens;
	struct s_cmdlist	*next;
	struct s_cmdlist	*prev;
}						t_cmdlist;

typedef struct s_ms
{
	int			stdout_cpy;
	int			stdin_cpy;
	t_parse		parser;
	t_line		line;
	t_env		*env;
	t_tokens	*tokens;
	t_cmdlist	*cmdlists;
	int			hdoc_break;
}				t_ms;

typedef struct s_global
{
	int				status;
	pid_t			pid;
	pid_t			*pids;
	struct termios	termios_save;
	struct termios	termios_new;
	int				__dup__;
}					t_global;

extern t_global	g_global;

char	*input_add_newline(char *s);
int		cmd_len(char **str);
int		input_syntax_semicolons(t_ms *v);
int		cmds_cmdlists_maker(t_ms *ms);
int		cmds_cmdlist_syntax_tokens(t_cmdlist *cmd, int i);
int		parser_wrapper(t_ms *ms);
int		str_skip_whitespace(const char *str);
int		parser_syntax_tokens(t_ms *ms);
void	clean_cmdlist(t_ms *ms, int n_cmds);
void	clean_commands(t_ms *ms);
void	clean_ms(t_ms *ms);
void	executor(t_ms *ms, t_cmdlist *cmdlist);
void	free_heredoc(t_ms *ms, int n_cmds);
void	ms_error(char *msg);
void	init_minishell(int argc, char **argv, t_ms *ms);
void	init_shell_level(t_ms *ms);
void	init_signals(t_env **env);
void	init_terminal_params(void);
void	input_read(t_ms *ms, int mode);
void	input_syntax_quotes(t_ms *ms);
void	quote_toggle(t_ms *ms, char *c);
void	sig_handler(int signal_code);

#endif
