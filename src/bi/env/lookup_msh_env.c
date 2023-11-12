/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lookup_msh_env.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acuva-nu <acuva-nu@student.42lisboa.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/12 17:54:43 by acuva-nu          #+#    #+#             */
/*   Updated: 2023/11/12 17:54:43 by acuva-nu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../inc/minishell.h"

char *lookup_msh_env(t_msh_envlist *list, const char *key)
{
    t_msh_env *iter;

    if (!list)
        return (NULL);
    iter = list->head;
    while (iter != NULL)
    {
        if (iter->key == key)
            break;
        else
            iter = iter->next;
    }
    if (!iter)
        return (NULL);
    else
        return ((char *)iter->value);
}

