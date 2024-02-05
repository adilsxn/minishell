# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: acuva-nu <acuva-nu@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/10/29 10:45:20 by acuva-nu          #+#    #+#              #
#    Updated: 2023/02/25 16:35:53 by acuva-nu         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS		=  src/ft_wordcount.c src/ft_isascii.c src/ft_substr.c src/ft_lstmap.c src/ft_strlcpy.c src/get_next_line.c src/ft_lstclear.c src/ft_strjoin.c             \
           src/ft_isspace.c src/ft_strnstr.c src/ft_toupper.c src/ft_strlcat.c src/ft_lstadd_back.c src/ft_strtrim.c src/ft_bzero.c src/ft_calloc.c                \
					 src/ft_lstsize.c src/ft_striteri.c src/ft_itoa.c src/ft_strdup.c src/ft_strncmp.c src/ft_atoi.c src/ft_strlen.c src/ft_memmove.c src/ft_strchr.c        \
           src/ft_isprint.c src/ft_memcpy.c src/ft_lstadd_front.c src/ft_isalnum.c src/ft_putnbr_fd.c src/ft_csdiu.c src/ft_isalpha.c src/ft_strrchr.c             \
					 src/ft_tolower.c src/ft_memset.c src/ft_strmapi.c src/ft_putchar_fd.c src/ft_putendl_fd.c src/ft_hex.c src/ft_lstlast.c src/ft_printf.c src/ft_memcmp.c \
           src/ft_memchr.c src/ft_strequ.c src/ft_split.c src/ft_putstr_fd.c src/ft_lstdelone.c src/ft_lstiter.c src/ft_lstnew.c src/ft_isdigit.c
OBJS		= $(SRCS:src/%.c=$(OBJ_DIR)/%.o)
OBJ_DIR = obj
INCS		= inc/
CC			= cc
CFLAGS 		= -Wall -Wextra -Werror -g
NAME		= libft.a
RM       = rm -rf

all:	$(NAME)

${OBJ_DIR}/%.o: src/%.c | DIRECTORIES
		@${CC} -c ${CFLAGS} $< -o $@ -I ${INCS}

$(NAME): $(OBJS) $(OBJ_DIR)
	@ar rcs $(NAME) $(OBJS)
	@ranlib $(NAME)
	@echo "Libft compiled"

DIRECTORIES:
	@mkdir -p $(OBJ_DIR)

clean:
	@$(RM) $(OBJS)

fclean:	clean
	@$(RM) $(NAME) $(OBJ_DIR)

re:	fclean all

norm: 
		@norminette -R CheckForbiddenSourceHeader ${SRCS}
		@norminette -R CheckDefine ${INCS}

.PHONY:	all clean fclean re norm bonus
