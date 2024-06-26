# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: matde-je <matde-je@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/11/29 12:35:24 by acuva-nu          #+#    #+#              #
#    Updated: 2024/04/05 21:23:58 by matde-je         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS       = set_env.c get_env.c unset_env.c env.c del_env.c init_env.c cmd_finder.c hdoc_utils.c                \
			 cmd_args.c command.c pipe.c hdoc.c redirection_utils.c redirection.c signals.c lexer_redux.c        \
			 remove.c lexer_utils.c lexer_list.c exec_rdr.c exec_cmd.c exec_pipe.c                             \
			 exec_bin.c exec_bi.c pwd.c echo.c unset.c exit.c export.c cd.c builtins.c                         \
			 error.c cleanup.c main.c expand_utilspt2.c expand_utils.c expand.c lexer_utilspt2.c err_lex.c  

#Add any missing folder containing a .c to the vpath
vpath %.c src/ src/signals src/executor src/executor src/expander src/bi src/lexer src/parser  src/env
OBJ_DIR = ./obj
OBJS = $(addprefix $(OBJ_DIR)/,$(SRCS:.c=.o))

INCS 	   = inc/
NAME       = minishell

CC         = cc
CFLAGS     = -g3 -Wall -Wextra -Werror #-fsanitize=address,undefined

LDFLAGS	   = -L./libft -lft -lreadline
RM         = rm -rf

all: ${NAME}

$(OBJ_DIR)/%.o: %.c 
	@mkdir -p ${OBJ_DIR}
	@$(CC) $(CFLAGS) -c $< -o $@
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
