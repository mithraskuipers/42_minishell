# **************************************************************************** #
#                                                                              #
#                                                         ::::::::             #
#    Makefile                                           :+:    :+:             #
#                                                      +:+                     #
#    By: mikuiper <mikuiper@student.codam.nl>         +#+                      #
#                                                    +#+                       #
#    Created: 2022/10/28 21:58:30 by mikuiper      #+#    #+#                  #
#    Updated: 2022/10/29 18:07:21 by mikuiper      ########   odam.nl          #
#                                                                              #
# **************************************************************************** #

# The name of your executable
NAME		= minishell

# Compiler and compiling flags
CC	= gcc
CFLAGS	= -Wall -Werror -Wextra

# Debug, use with`make DEBUG=1` undefined kan ook als optie
ifeq ($(DEBUG),1)
CFLAGS	+= -g3
endif
ifeq ($(DEBUG),2)
CFLAGS	+= -g3 -fsanitize=address -fno-omit-frame-pointer
endif
ifeq ($(DEBUG),3)

CFLAGS	+= -g3 -fsanitize=leak
endif

# Folder name
SRCDIR	= ./
OBJDIR	= bin/
LIBFTDIR = libft/

INCLUDES = header.h parser/parse.h executor/execute.h cosmetics/splash.h \
libft/libft.h env_list/env_list.h builtin/commands.h cmd/cmd.h cmd/tokens_cmd/tokens.h \
expander/expander.h

LIBFTLIB = $(LIBFTDIR)/libft.a

INCLUDES_L = -L./libft/.

SRCS =					main.c \
						signals.c \
						$(INIT) \
						$(SPLASH) \
						$(TOOLS) \
						$(INPUT) \
						$(EXPANDER) \
						$(SRCS.COMMANDS.CD) \
						$(SRCS.COMMANDS.ECHO) \
						$(SRCS.COMMANDS.ENV) \
						$(SRCS.COMMANDS.PWD) \
						$(SRCS.COMMANDS.EXPORT) \
						$(SRCS.COMMANDS.UNSET) \
						$(SRCS.COMMANDS.EXECVE) \
						$(SRCS.COMMANDS.EXIT) \
						$(SRCS.ENV.LIST) \
						$(SRCS.ENV.LIST.FUNC) \
						$(SRCS.CLEAN) \
						$(SRCS.LINE) \
						$(SRCS.PARSER) \
						$(SRCS.CREATE.CMD) \
						$(SRCS.EXECUTE)
						
						
TOOLS =					tools/str_skip_whitespace.c \
						tools/array_thingy.c \
						tools/ft_error.c \
						tools/signal_handler.c \
						tools/cmd_len.c \

EXPANDER =				expander/expander.c \
						expander/expander_calclen.c \
						expander/expander_tilde.c \

INPUT =					input/input_read.c \
						input/input_add_newline.c \
						input/input_check.c \
						input/input_syntax_quotes.c \
						input/input_syntax_error.c \

INIT =					init/init.c \

SPLASH =				cosmetics/splash.c

SRCS.COMMANDS.CD =		builtin/cd/cd.c \
						builtin/cd/cd_check_permissions.c \

SRCS.COMMANDS.ECHO =	builtin/echo/echo.c \

SRCS.COMMANDS.ENV =		builtin/env/env.c \

SRCS.COMMANDS.PWD =		builtin/pwd/pwd.c \

SRCS.COMMANDS.EXPORT =	builtin/export/export.c \
						builtin/export/export_utils.c \

SRCS.COMMANDS.UNSET =	builtin/unset/unset.c \

SRCS.COMMANDS.EXECVE =	builtin/execve/execve.c \
						builtin/execve/commands.c \
						builtin/execve/relative_path.c \
						builtin/execve/absolute_path.c \

SRCS.COMMANDS.EXIT = 	builtin/exit/ms_exit.c \
						builtin/exit/ms_return_exit.c \

SRCS.ENV.LIST =			env_list/env_lst_new.c \
						env_list/env_lstadd_back.c \
						env_list/env_lstlast.c \
						env_list/env_lstsize.c \
						env_lst_remove.c \

SRCS.ENV.LIST.FUNC =	env_list/tools/env_init.c \
						env_list/tools/env_tools_manipulation.c \
						env_list/tools/env_tools_check.c \
						env_list/tools/env_tools_get.c \

SRCS.EXECUTE =			executor/execute.c executor/run_cmd.c \
						executor/exec_functions.c \
						executor/set_cmd.c \
						executor/redirs/redirs_looper.c \
						executor/redirs/redirs.c \
						executor/redirs/heredoc.c \
						executor/setup_single_cmd.c \
						executor/setup_pipes_cmd.c \
						executor/setup_builtin.c \
						

SRCS.NEWEXECUTE =		newexecute/execute.c newexecute/run_cmd.c \
						newexecute/set_cmd.c \
						newexecute/redirs/redirection_functions.c \
						newexecute/redirs/redirs.c \
						newexecute/redirs/set_redirs.c \
						newexecute/redirs/get_last_redir.c \
						newexecute/pipes/heredoc_pipes.c \
						newexecute/pipes/pipes.c \
						newexecute/pipes/setup_pipes.c \
						newexecute/pipes/clear_pipes.c \

SRCS.CLEAN =			clean/clean_ms.c \
						clean/clean_commands.c \
						clean/clean_cmdlist.c \
						clean/free_heredoc.c \

SRCS.PARSER =			parser/parse.c \
						parser/parse_arraysize.c \
						parser/splitting/parser_splitter_spaces.c \
						parser/splitting/parser_splitter_semicolons.c \
						parser/splitting/parser_separate_words_tokens.c \
						parser/createstring.c \
						parser/tokens.c \
						parser/heredoc/allocate_heredoc.c \
						parser/heredoc/get_heredoc_input.c \
						parser/heredoc/heredoc_calc_len.c \
						parser/heredoc/heredoc_create_str.c \
						parser/heredoc/heredoc_parsing.c \
						parser/heredoc/set_heredoc.c \
						parser/check_chars.c \
						parser/search_env.c \

SRCS.CREATE.CMD =		cmd/parser_command_creation.c \
						cmd/parser_command_pipes.c \
						cmd/tokens_cmd/tokens_cmd.c \
						cmd/tokens_cmd/tokens_dup.c \
						cmd/tokens_cmd/init_new_tokens.c \
						cmd/tokens_cmd/count_tokens.c \
						cmd/tokens_cmd/set_heredoc_tokens.c \

# String manipulation magic
SRC		:= $(notdir $(SRCS))
OBJ		:= $(SRC:.c=.o)
OBJS	:= $(addprefix $(OBJDIR), $(OBJ))

SRC_B		:= $(notdir $(SRCS.BONUS))
OBJ_B		:= $(SRC_B:.c=.o)
OBJS_B	:= $(addprefix $(OBJDIR), $(OBJ_B))

# Colors
GR	= \033[32;1m
RE	= \033[31;1m
YE	= \033[33;1m
CY	= \033[36;1m
RC	= \033[0m

# Implicit rules
VPATH := $(SRCDIR) $(OBJDIR) $(shell find $(SRCDIR) -type d)

# ================================== RULES =================================== #

all : $(NAME)

linux : $(LIBFTLIB) $(SRCS)  $(OBJS)
	@printf "\n$(GR)=== Compiled [$(CC) $(CFLAGS)] ===\n--- $(SRC)$(RC)\n"
	@$(CC) $(INCLUDES_L) $(CFLAGS) $(LIBFTLIB) $(OBJS) -o $(NAME) -lreadline -l:libft.a

# Compiling
$(OBJDIR)%.o : %.c $(INCLUDES)
	@mkdir -p $(OBJDIR)
	@printf "$(GR)+$(RC)"
	@$(CC) $(CFLAGS) -c $< -o $@ -I/usr/local/opt/readline/include

#voor rowan:
#@$(CC) $(CFLAGS) -c $< -o $@ -I/opt/homebrew/opt/readline/include

# Linking
$(NAME)	: $(LIBFTLIB) $(SRCS)  $(OBJS) $(INCLUDES)
	@printf "\n$(GR)=== Compiled [$(CC) $(CFLAGS)] ===\n--- $(SRC)$(RC)\n"
	@$(CC) $(CFLAGS) $(LIBFTLIB) $(OBJS) -o $(NAME) -lreadline -L/usr/local/opt/readline/lib

#voor rowan:
#@$(CC) $(CFLAGS) $(LIBFTLIB) $(OBJS) -o $(NAME) -lreadline -L/opt/homebrew/opt/readline/lib

$(LIBFTLIB) :
	make -C $(LIBFTDIR)
	
# Cleaning
clean :
	@printf "$(RE)--- Removing $(OBJDIR)$(RC)\n"
	@rm -rf $(OBJDIR)
	@make -C $(LIBFTDIR) clean

fclean : clean
	@printf "$(RE)--- Removing $(NAME)$(RC)\n"
	@rm -f $(NAME)
	@rm -f $(NAME_BONUS)
	@make -C $(LIBFTDIR) fclean

# Special rule to force to remake everything
re : fclean all

# This runs the program
run : $(NAME)
	@printf "$(CY)>>> Running $(NAME)$(RC)\n"
	./$(NAME)

# This specifies the rules that does not correspond to any filename
.PHONY	= all run clean fclean re bonus