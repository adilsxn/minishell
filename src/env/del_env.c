/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   del_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acuva-nu <acuva-nu@student.42lisboa.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/27 16:11:54 by acuva-nu          #+#    #+#             */
/*   Updated: 2023/11/27 16:11:54 by acuva-nu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int del_env(t_env *env)
{
    t_env *tmp;
    t_env *next;

    tmp = env;
    while(tmp != NULL)
    {
        next = tmp->next;
        free((void *)tmp->key);
        free((void *)tmp->value);
        free(tmp); 
        tmp = next;
    }
    return (0);
}
