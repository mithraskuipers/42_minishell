/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   header.h                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: mikuiper <mikuiper@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/28 21:57:11 by mikuiper      #+#    #+#                 */
/*   Updated: 2022/10/29 00:12:30 by mikuiper      ########   odam.nl         */
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

typedef struct s_parse
{
	char		***commands;
	int			comma1;
	int			comma2;
}				t_parse;

typedef struct s_gnl
{
	int			fd;
	char		*buf;
}				t_gnl;

typedef struct s_heredoc_data
{
	char					*str;
	struct s_heredoc_data	*next;
}				t_heredoc_data;

typedef struct s_heredoc
{
	int				pipe[2];
	int				heredoc_q;
	char			*eof;
	t_heredoc_data	*data;

}				t_heredoc;

typedef struct s_tokens
{
	int			total;
	int			stdin_fd;
	int			stdout_fd;
	char		**token;
	int			*token_pos;
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

typedef struct s_newcommand
{
	int						id;
	int						fd[2];
	int						read_pipe;
	char					**command;
	struct s_tokens			*tokens;
	struct s_newcommand		*next;
	struct s_newcommand		*prev;
}				t_newcommand;

typedef struct s_ms
{
	int				stdout_cpy;
	int				stdin_cpy;
	t_parse			parse;
	t_gnl			gnl;
	t_env			*env;
	t_tokens		*tokens;
	t_newcommand	*cmd;
	int				hdoc_break;
}				t_ms;

typedef struct s_global
{
	int				status;
	pid_t			pid;
	struct termios	termios_save;
	struct termios	termios_new;
	int				__dup__;
}				t_global;

extern t_global	g_global;

int		new_parse(t_ms *ms);

void	free_all(t_ms *ms);
void	free_commands(t_ms *ms, t_newcommand *temp, \
						t_newcommand *temp2, int totalcommands);
void	free_heredoc(t_ms *ms, int totalcommands);

void	ft_error(char *msg);
int		syntax_error_parse(t_ms *ms);
int		syntax_error(t_newcommand *cmd, int i);

void	execution(t_ms *ms, t_newcommand *cmd, int k);
int		skipspaces(const char *str);

void	check_quote(t_ms *ms, char *c);
char	*add_new_line(char *str);
int		cmd_len(char **str);

int		check_input(t_ms *v);
void	read_input(t_ms *ms, int option);
void	check_input_quotes(t_ms *ms);

int		create_cmd(t_ms *v, int k);

void	sig_handler(int sign_num);

#endif