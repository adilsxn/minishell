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

#include "../../inc/minishell.h"

t_env *get_env(t_env *env, const char *key)
{
    t_env *tmp;

    tmp = env;
    while (tmp != NULL && !ft_strequ(key, env->key))
        tmp = tmp->next;
    return (tmp);
}
