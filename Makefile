# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: achahlao <achahlao@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/08/23 19:12:38 by achahlao          #+#    #+#              #
#    Updated: 2024/09/21 09:58:25 by achahlao         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = cc
CFLAGS = -Wall -Wextra -Werror
LDFLAGS = -lreadline 
SRC = builtins/export.c \
	builtins/ft_cd.c \
	builtins/ft_echo.c \
	builtins/ft_echo_utils.c \
	builtins/ft_env.c \
	builtins/ft_exit.c \
	builtins/ft_pwd.c \
	builtins/ft_unset.c \
	builtins/otuls_expand_2.c \
	builtins/otuls_export.c \
	builtins/otuls_export_1.c \
	builtins/update_cd.c \
	execution/empty_args.c \
	execution/env_to_tab.c \
	execution/execution.c \
	execution/outils_execution.c \
	execution/outils_execution1.c \
	execution/outils_execution_2.c \
	execution/outils_execution_3.c \
	execution/outils_get_path.c \
	execution/redirections.c \
	execution/split_command.c \
	expanding/expand.c \
	expanding/expand_wildcart.c \
	expanding/get_add_env.c \
	expanding/otils_expand.c \
	expanding/otils_expand2.c \
	expanding/otils_expand3.c \
	expanding/otils_expand_4.c \
	expanding/remove_q_all_cmd.c \
	expanding/search_env.c \
	expanding/search_env_1.c \
	herdoc/herdoc.c \
	herdoc/tools_herd.c \
	parssing/add_espace.c \
	parssing/check_pipe.c \
	parssing/exit_stat.c \
	parssing/ft_split.c \
	parssing/minishell_main.c \
	parssing/outils_pipe.c \
	parssing/parssing.c \
	parssing/parssing_utils.c \
	parssing/quotes.c \
	parssing/read_in_line.c \
	parssing/split_pipe.c \
	parssing/trim_espace.c \
	parssing/utils_lib.c \
	ft_wildcard.c \
	minishell.c \
	signals.c
	
OBJ = $(SRC:.c=.o)   
NAME = minishell

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(OBJ) -o $@ $(LDFLAGS)

%.o: %.c minishell.h
	$(CC) $(CFLAGS) -c $< -o $@ 

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all 

.PHONY: all clean fclean re
