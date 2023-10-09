# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: matilde <matilde@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/11/29 12:35:24 by acuva-nu          #+#    #+#              #
#    Updated: 2023/10/04 19:33:23 by matilde          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS       = 	src/lexer/remove1.c \
				src/lexer/word_token1.c \
				src/lexer/lexer_list1.c \
				src/parser/init1.c \
				src/parser/redirect1.c \
				src/parser/simple_cmd1.c \
				src/parser/error1.c \
				src/lexer/main.c  \
				src/parser/parser1.c  \
				src/parser/pipes1.c \
				

OBJ_DIR = build/obj
OBJS = $(SRCS:.c=.o)

INCS 	   = inc/
NAME       = minishell

CC         = cc
CFLAGS     = -g -Wall -Wextra -Werror
LDFLAGS	   = -L./libft -lft
RM         = rm -rf

all: ${NAME}

$(OBJ_DIR)/%.o: %.c | DIRECTORIES
	$(CC) $(CFLAGS) -c $< -o $@ -I $(INCS) ${LDFLAGS}

${NAME}: ${OBJS}
	@echo "Compiling minishell"
	@make -s -C libft
	${CC} ${CFLAGS}  $^ -o $@  -I ${INCS} ${LDFLAGS}
	@echo "minishell created"

DIRECTORIES:
	mkdir -p ${OBJ_DIR}

clean:
	${RM} ${OBJS} 
	make clean -s -C libft

fclean: clean
	${RM} ${NAME} 
	${RM} ${OBJ_DIR}
	make fclean -s -C libft
	@echo "minishell deleted"

re: fclean all

norm:
	norminette -R CheckForbiddenSourceHeader ${SRCS}
	norminette -R CheckDefine ${INCS}

.PHONY: all re clean fclean 
