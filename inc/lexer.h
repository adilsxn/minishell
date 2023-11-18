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

typedef enum e_kind
{
	PIPE,
	REDIRECT_IN,
    REDIRECT_OUT,
    REDIRECT_APPND,
    REDIRECT_HD,
    COUNT,
    WORD,
}t_kind;

typedef struct s_token
{
	char			*data;
	t_kind		token;
	struct s_lexer	*next;
	struct s_lexer	*prev;
}t_token;

t_token mk_token(t_kind kind, char *value, t_token *prev);
void free_token(t_token *token);
#endif 
