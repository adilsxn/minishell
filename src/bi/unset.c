/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acuva-nu <acuva-nu@student.42lisboa.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/14 22:23:24 by acuva-nu          #+#    #+#             */
/*   Updated: 2023/09/14 22:23:24 by acuva-nu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

/*TODO: Need to refine the builtins and work on signals and the expander*/

/*NOTE: In short the inverse of export
 * if name is a var or function they are unset(meaning what? their
 * value is deleted or in the case of funcs they become unaccessible?)*/

int msh_unset (t_tool *tools, t_simple_cmd *args)
{
    int i;

    i = 1;
    while (args->str[i] != NULL)
    {
        unset_env(tools->our_env, args->str[i]);
        i++;
    }
    return (EXIT_SUCCESS);
}

