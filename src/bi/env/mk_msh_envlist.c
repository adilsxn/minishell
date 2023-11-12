/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mk_msh_envlist.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acuva-nu <acuva-nu@student.42lisboa.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/10 16:59:26 by acuva-nu          #+#    #+#             */
/*   Updated: 2023/11/10 16:59:26 by acuva-nu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../inc/minishell.h"

t_msh_envlist *mk_msh_envlist(void)
{
    t_msh_envlist *list;

    list = malloc(sizeof(*list));
    if (!list)
        return (NULL);
    list->head = NULL;
    list->size = 0;

    return (list);
}

