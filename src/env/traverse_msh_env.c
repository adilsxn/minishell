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

#include "../../../inc/minishell.h"

int traverse_msh_env(t_msh_envlist *list)
{
    t_msh_env *iter;

    if (!list)
        return (1);
    iter = list->head;
    while (iter != NULL)
    {
        printf("%s=%s\n", iter->key, iter->value);
        iter = iter->next;
    }
    return (0);
}

