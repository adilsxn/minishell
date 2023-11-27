/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   traverse_msh_env.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acuva-nu <acuva-nu@student.42lisboa.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/12 18:02:56 by acuva-nu          #+#    #+#             */
/*   Updated: 2023/11/12 18:02:56 by acuva-nu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int env(t_env *env, int ac, char **args)
{
    t_env *iter;

    iter = env;
    while (iter != NULL)
    {
        printf("%s=%s\n", iter->key, iter->value);
        iter = iter->next;
    }
    (void)ac;
    (void)args;
    return (0);
}

