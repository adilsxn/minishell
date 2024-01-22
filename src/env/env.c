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

int msh_env(t_env *env, char **args)
{
    int i;
    t_env *iter;

    if (args && args[1])
        return (ft_putendl_fd("env: too many arguments", 2), 1);
    i = 0;
    iter = env;
    if (iter == NULL)
        return (EXIT_FAILURE);
    while (iter != NULL)
    {
        printf("%s=%s\n", iter->key, iter->value);
        iter = iter->next;
    }
    return (EXIT_SUCCESS);
}
