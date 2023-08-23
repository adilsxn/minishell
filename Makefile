# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: acuva-nu <acuva-nu@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/11/29 12:35:24 by acuva-nu          #+#    #+#              #
#    Updated: 2023/02/25 16:34:52 by acuva-nu         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


SRCS       = src/main.c 
B_SRC      = 	
OBJS       = ${SRCS:src/%.c=$(OBJ_DIR)/%.o}
B_OBJS     = ${B_SRC:src/%.c=$(B_OBJ_DIR)/%.o}
BUILD_DIR  = build
OBJ_DIR    = ${BUILD_DIR}/obj
B_OBJ_DIR  = ${BUILD_DIR}/b_obj
INCS 			 = inc/
NAME       = minishell
B_NAME     = b_minishell
CC         = cc
CFLAGS     = -g -Wall -Wextra -Werror
LDFLAGS 	 = -L./libft -lft
RM         = rm -rf

all: ${NAME}

$(OBJ_DIR)/%.o: src/%.c | DIRECTORIES
	@$(CC) $(CFLAGS) -c $< -o $@ -I $(INCS) ${LDFLAGS}

${NAME}: ${OBJS}
	@echo "Compiling minishell"
	@make -s -C libft
	@${CC} ${CFLAGS}  $^ -o $@  -I ${INCS} ${LDFLAGS}
	@echo "minishell created"

$(B_OBJ_DIR)/%.o: src/%.c | DIRECTORIES
	@$(CC) $(CFLAGS) -I $(INCS) -c $< -o $@

bonus: ${B_OBJS}
	@echo "Compiling b_minishell"
	@make -s -C libft
	@${CC} ${CFLAGS}  $^ -o ${B_NAME} -I ${INCS} ${LDFLAGS}
	@echo "b_minishell created"

DIRECTORIES:
	@mkdir -p ${BUILD_DIR}
	@mkdir -p ${OBJ_DIR} ${B_OBJ_DIR}

clean:
	@${RM} ${OBJS} ${B_OBJS}
	@make clean -s -C libft

fclean: clean
	@${RM} ${NAME} ${B_NAME}
	@${RM} ${BUILD_DIR}
	@make fclean -s -C libft
	@echo "minishell deleted"

re: fclean all

norm:
	norminette -R CheckForbiddenSourceHeader ${SRCS}
	norminette -R CheckDefine ${INCS}

.PHONY: all re clean fclean bonus
