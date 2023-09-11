/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matilde <matilde@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/23 12:14:55 by acuva-nu          #+#    #+#             */
/*   Updated: 2023/09/11 11:51:01 by matilde          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <stdlib.h>
# include <string.h>
# include <fcntl.h>
# include <unistd.h>
# include "../libft/inc/libft.h"

typedef enum s_tokens
{
	PIPE = 1,
	GREAT,
	GREAT_GREAT,
	LESS,
	LESS_LESS,
}t_tokens;

typedef struct s_lexer
{
	char			*str;
	t_tokens		token;
	int				i;
	struct s_lexer	*next;
	struct s_lexer	*prev;
}t_lexer;

int					is_whitespace(char c);
int					count_spaces(char *str, int i);
int					add_lexer_node(char *str, int token, t_lexer **lexer_list);
int					len_quote(int i, char *str, char quote);
t_tokens			check_token(int c1, int c2);
int					len_word(int i, char *str, t_lexer **lexer_list);

#endif
