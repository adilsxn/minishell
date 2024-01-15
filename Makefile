# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: acuva-nu <acuva-nu@student.42lisboa.com    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/11/29 12:35:24 by acuva-nu          #+#    #+#              #
#    Updated: 2024/01/14 21:14:58 by acuva-nu         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS       = set_env.c get_env.c unset_env.c env.c del_env.c init_env.c tree_utils.c   \
			 tree_utils_2.c parser.c error.c remove.c lexer_utils.c lexer_list.c       \
			 cmd_finder.c cmd_args.c command.c pipe.c redirection.c minishell_loop.c   \
			 pwd.c echo.c unset.c exit.c export.c cd.c builtins.c main.c sngl_child.c  \
			 sgnl_hd_parent.c sgnl_parent.c sgnl_hd_child.c setup_sgnl.c sgnl_prompt.c \
			 expand_utilspt2.c expand_utils.c expand.c

#Add any missing folder containing a .c to the vpath
vpath %.c src/executor src/expander src/bi src/lexer src/parser  src/env
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
	@$(CC) $(CFLAGS) -c $< -o $@ -I $(INCS)

${NAME}: ${OBJS} 
	@echo "Compiling minishell"
	@make -s -C libft
	@${CC} ${CFLAGS}  $^ -o $@  -I ${INCS} ${LDFLAGS}
	${RM} ${OBJ_DIR}
	make clean -s -C libft
	@echo "minishell created"


clean:
	${RM} ${OBJ_DIR} 
	make clean -s -C libft

fclean: clean
	${RM} ${NAME} 
	make fclean -s -C libft
	@echo "minishell deleted"

re: fclean all

norm:
	norminette -R CheckForbiddenSourceHeader ${SRCS}
	norminette -R CheckDefine ${INCS}

.PHONY: all re clean fclean 
