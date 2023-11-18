/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lex.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acuva-nu <acuva-nu@student.42lisboa.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/16 18:40:19 by acuva-nu          #+#    #+#             */
/*   Updated: 2023/11/16 18:40:19 by acuva-nu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H
# define LEXER_H

#define PIPE '|'
#define REDIRECT_IN '>'
#define REDIRECT_OUT '<'
#define SINGLE_QUOTE '\''
#define DOUBLE_QUOTE '"'

typedef enum e_type
{
	tk_PIPE,
	tk_REDIRECT_IN,
    tk_REDIRECT_OUT,
    tk_REDIRECT_APPND,
    tk_REDIRECT_HD,
    tk_COUNT,
    tk_WORD,
}t_type;

typedef struct s_token
{
	char			*data;
	t_type		type;
	struct s_token	*next;
	struct s_token	*prev;
}t_token;

t_token *mk_token(t_type type, char *data, t_token *last);
void del_tokens(t_token *token);
#endif 
