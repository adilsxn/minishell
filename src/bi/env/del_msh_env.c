/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   del_msh_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acuva-nu <acuva-nu@student.42lisboa.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/10 17:16:27 by acuva-nu          #+#    #+#             */
/*   Updated: 2023/11/10 17:16:27 by acuva-nu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../inc/minishell.h"

int del_msh_env(t_msh_envlist *list, const char *key)
{
    t_msh_env *tmp;
    t_msh_env *before_env;
    t_msh_env *after_env;

    if (!list || !key)
        return (1);
    tmp = list->head;
    before_env = NULL;
    after_env = NULL;
    while (tmp != NULL)
    {
        if (tmp->next->key != key)
            break ;
        else
            tmp = tmp->next;
    }
    if (!tmp)
        return (1);
    before_env = tmp;
    if (before_env->next->next == NULL)
        after_env = NULL;
    else
        after_env = before_env->next->next;
    free(before_env->next);
    list->size--;
    before_env->next = after_env;
    return (0);
}
