/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_redux.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acuva-nu <acuva-nu@student.42lisboa.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/07 22:31:48 by acuva-nu          #+#    #+#             */
/*   Updated: 2024/02/07 22:31:48 by acuva-nu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../../inc/minishell.h"


void lexer_redux(t_lexer *lexer)
{
    t_lexer *it;
    t_lexer *del;

    it = lexer;
    del = NULL;
    while(it != NULL && it->next != NULL)
    {
        if (it->token > 1)
        {
            it->str = it->next->str;
            del = it->next;
            if (del->next != NULL)
            {
                it->next = del->next;
                del->next->prev = it;
            }
            ft_free2((void **)&del); 
        }    
        it = it->next;
    }
}
