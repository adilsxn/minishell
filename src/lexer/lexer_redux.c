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

static void renumber(t_lexer **lst)
{
    int i;
    t_lexer *it;

    i = 0;
    it = *lst; 
    while(it != NULL)
    {
        it->i = i;
        it = it->next;
        i++;
    }
}

void lexer_redux(t_lexer **lexer)
{
    t_lexer *it;
    t_lexer *del;

    it = *lexer;
    del = NULL;
    while(it != NULL && it->next != NULL)
    {
        if (it->token > 1)
        {
            it->str = it->next->str;
            del = it->next;
            it->next = del->next;
            if (del->next != NULL)
                del->next->prev = it;
            ft_free(del); 
        }    
        it = it->next;
    }
    renumber(lexer);
}
