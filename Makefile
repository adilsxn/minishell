# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: matde-je <matde-je@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/11/29 12:35:24 by acuva-nu          #+#    #+#              #
#    Updated: 2024/01/23 22:22:54 by matde-je         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS       = set_env.c get_env.c unset_env.c env.c del_env.c init_env.c tree_utils.c   \
			 tree_utils_2.c parser.c error.c remove.c lexer_utils.c lexer_list.c       \
			 cmd_finder.c cmd_args.c command.c pipe.c redirection.c  \
			 pwd.c echo.c unset.c exit.c export.c cd.c builtins.c main.c  \
			 setup_sgnl.c  expand_utilspt2.c expand_utils.c expand.c main.c

#Add any missing folder containing a .c to the vpath
vpath %.c src/ src/signals src/executor src/expander src/bi src/lexer src/parser  src/env
OBJ_DIR = ./obj
OBJS = $(addprefix $(OBJ_DIR)/,$(SRCS:.c=.o))

INCS 	   = inc/
NAME       = minishell

CC         = cc
CFLAGS     = -g -Wall -Wextra -Werror -fsanitize=address

LDFLAGS	   = -L./libft -lft -lreadline
RM         = rm -rf

all: ${NAME}

$(OBJ_DIR)/%.o: %.c 
	@mkdir -p ${OBJ_DIR}
	@$(CC) $(CFLAGS) -c $< -o $@ -I $(INCS)

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
	make fclean -s -C libft
	@echo "minishell deleted"

re: fclean all

# norm:
# 	norminette -R CheckForbiddenSourceHeader ${SRCS}
# 	norminette -R CheckDefine ${INCS}

.PHONY: all re clean fclean 
