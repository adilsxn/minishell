/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acuva-nu <acuva-nu@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/18 10:20:43 by acuva-nu          #+#    #+#             */
/*   Updated: 2023/11/18 10:46:57 by acuva-nu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/lexer.h"

t_token *mk_token(t_type *type, char *data, t_token *last)
{
    t_token *new;

    new = malloc(sizeof(*new));
    if (!new)
        return (NULL);
    new->type = type;
    new->data = data;
    new->prev = last;
    if (!last)
        last->next = new;
    return (new);    
}

void del_tokens(t_token *token)
{
    if (!token)
        return ;
    del_tokens(token->next);
    free(token->data);
    free(token);
}