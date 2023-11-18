/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acuva-nu <acuva-nu@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/18 09:47:15 by acuva-nu          #+#    #+#             */
/*   Updated: 2023/11/18 13:33:42 by acuva-nu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/lexer.h"

static t_type get_type(char *input)
{
    if (input[0] == REDIRECT_IN)
        return (tk_REDIRECT_IN);
    else if (input[0] == REDIRECT_OUT)
        return (tk_REDIRECT_OUT);
    else if (input[0] == PIPE)
        return (tk_PIPE);
    else if (input[0] == input[1] && input[1] == REDIRECT_OUT)
        return (tk_REDIRECT_APPND);
    else if (input[0] == input[1] && input[1] == REDIRECT_IN)
        return (tk_REDIRECT_HD);
    else
        return (tk_WORD);
}


static char *get_data(t_type *type, char *input,
             t_token *last, size_t *iter);
{
    if (type == tk_PIPE && (last == NULL || last->type == tk_PIPE))
        return (NULL);
    if (type == tk_REDIRECT_IN || type == tk_REDIRECT_OUT 
                || type == tk_REDIRECT_APPND)
        return ();  /*TODO:You need to get string associated with the redirect*/
    else if (type == tk_REDIRECT_HD)
        return ()   /*TODO:You need to get string associated with the redirect*/
    return ()       /*TODO: If nothing else then it must be a normal word*/ 
}
t_token *lexer(char *input)
{
    t_token *tmp;
    size_t  iter;

    iter = 0;
    tmp = NULL;
    
    while (input[iter] != '\0')
    {
        if (ft_isspace[input[iter])
            i++;
        tmp = ne
        iter++;
    }
}
