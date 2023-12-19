/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acuva-nu <acuva-nu@student.42lisboa.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/23 10:35:43 by acuva-nu          #+#    #+#             */
/*   Updated: 2023/11/23 10:35:43 by acuva-nu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static t_env *mk_env(const char *key, const char *value, t_env *prev)
{
    t_env *env;

    env = NULL;
    if (!key || !value)
        return (NULL);
    env = malloc(sizeof(*env));
    if (!env)
        return (NULL);
    env->key = ft_strdup(key);
    env->value = ft_strdup(value);
    env->next = NULL;
    env->prev = prev;
    return (env);
}

static t_env *update_env(t_env *env, const char *value)
{
    free((void *)env->value);
    env->value = ft_strdup(value);
    return (env);
}

    t_env *set_env(t_env **env, const char *key, const char *value)
{
    t_env *tmp;

    tmp = NULL;
    if (!key || !value)
        return (NULL);
    if (*env == NULL)
    {
        *env = mk_env(key, value, NULL);
        return (*env);
    }
    tmp = get_env(*env, key);
    if (tmp)
        return (update_env(tmp, value));
    tmp = *env;
    while (tmp->next != NULL)
        tmp = tmp->next;
    tmp->next = mk_env(key, value, tmp);
    return (tmp->next);
}

