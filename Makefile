# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: matilde <matilde@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/11/29 12:35:24 by acuva-nu          #+#    #+#              #
#    Updated: 2023/11/12 20:59:03 by matilde          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS = src/lexer/remove.c \
       src/lexer/word_token.c \
       src/lexer/lexer_list.c \
       src/parser/init.c \
       src/parser/redirect.c \
       src/parser/simple_cmd.c \
       src/parser/error.c \
       src/parser/parser.c \
       src/parser/pipes.c \
       src/expander/expand.c \
       src/expander/expand_utils.c \
       src/expander/expand_utilspt2.c \
       src/main/main.c \
       src/executor/minishell_loop.c

OBJ_DIR := obj
OBJS := $(patsubst src/%.c,$(OBJ_DIR)/%.o,$(SRCS))

INCS := inc/
NAME := minishell

CC := cc
CFLAGS := -g -Wall -Wextra -Werror -fsanitize=address
LDFLAGS := -L./libft -lft -lreadline
RM := rm -rf

all: ${NAME}

$(OBJ_DIR)/%.o: src/%.c
	$(CC) $(CFLAGS) -c $< -o $@ -I $(INCS) ${LDFLAGS}

${NAME}: ${OBJS}
	@echo "Compiling minishell"
	@make -s -C libft
	${CC} ${CFLAGS} $^ -o $@ -I ${INCS} ${LDFLAGS}
	@echo "minishell created"

clean:
	make clean -s -C libft
	${RM} ${OBJS}

fclean: clean
	${RM} ${NAME}
	make fclean -s -C libft
	@echo "minishell deleted"

re: fclean all

norm:
	norminette -R CheckForbiddenSourceHeader ${SRCS}
	norminette -R CheckDefine ${INCS}

.PHONY: all re clean fclean
