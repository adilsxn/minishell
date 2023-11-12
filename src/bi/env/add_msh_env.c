/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_msh_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acuva-nu <acuva-nu@student.42lisboa.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/10 17:05:08 by acuva-nu          #+#    #+#             */
/*   Updated: 2023/11/10 17:05:08 by acuva-nu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../inc/minishell.h"

t_msh_env *mk_msh_env(const char *key, const char *value)
{
    t_msh_env *env;

    if (!key || !value)
        return (NULL);
    env = malloc(sizeof(*env));
    if (!env)
        return (NULL);
    env->key = key;
    env->value = value;
    env->next = NULL;
    return (env);
}

int add_msh_env(t_msh_envlist *list, const char *key, const char *value)
{
    t_msh_env *tmp;

    if (!list || !key || !value)
        return (1);
    if (list->head == NULL)
    {
        list->head = mk_msh_env(key, value);
        list->size++;
    }
    else
    {
        tmp = list->head;
        while (tmp != NULL)
            tmp = tmp->next;
        tmp->next = mk_msh_env(key, value);
        list->size++;
    }
    return (0);
}
