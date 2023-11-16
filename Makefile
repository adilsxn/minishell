# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: matilde <matilde@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/11/29 12:35:24 by acuva-nu          #+#    #+#              #
#    Updated: 2023/11/11 19:19:55 by matilde          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

#Append/add the filename.c to the variable below 
SRCS       = 	remove.c  word_token.c  lexer_list.c  init.c redirect.c  \
				simple_cmd.c error.c parser.c  pipes.c expand.c          \
				expand_utils.c expand_utilspt2.c main.c minishell_loop.c 

#Add any missing folder containing a .c to the vpath
vpath %.c src src/executor src/expander src/lexer src/parser tests 
OBJ_DIR = ./obj
OBJS = $(addprefix $(OBJ_DIR)/,$(SRCS:.c=.o))

INCS 	   = inc/
NAME       = minishell

CC         = cc
CFLAGS     = -g -Wall -Wextra -Werror

LDFLAGS	   = -L./libft -lft -lreadline
RM         = rm -rf

all: ${NAME}

$(OBJ_DIR)/%.o: %.c 
	@mkdir -p ${OBJ_DIR}
	@$(CC) $(CFLAGS) -c $< -o $@ -I $(INCS) ${LDFLAGS}

${NAME}: ${OBJS} 
	@echo "Compiling minishell"
	@make -s -C libft
	@${CC} ${CFLAGS}  $^ -o $@  -I ${INCS} ${LDFLAGS}
	@echo "minishell created"


clean:
	${RM} ${OBJ_DIR} 
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
