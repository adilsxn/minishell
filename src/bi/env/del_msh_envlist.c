/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   del_msh_envlist.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acuva-nu <acuva-nu@student.42lisboa.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/12 17:37:05 by acuva-nu          #+#    #+#             */
/*   Updated: 2023/11/12 17:37:05 by acuva-nu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../inc/minishell.h"

int del_msh_envlist(t_msh_envlist *list)
{
    t_msh_env *iter;
    t_msh_env *aux;

    if (!list)
        return (1);
    iter = list->head;
    aux = NULL;
    while (iter != NULL)
    {
        aux = iter->next;
        free(iter);
        iter = aux;
    }
    free(list);
    list = NULL;
    return (0);
}
