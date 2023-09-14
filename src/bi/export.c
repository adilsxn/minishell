/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acuva-nu <acuva-nu@student.42lisboa.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/14 21:57:35 by acuva-nu          #+#    #+#             */
/*   Updated: 2023/09/14 21:57:35 by acuva-nu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"
#include <stdlib.h>
//TODO: implement hash tables/ red black treees 
//to store the env variables
/*NOTE: 
 * the export serves mainly three purposes all of the related
 * to the env and its variables
 * 1. Assigning value to an env variables
 * 2. Making the var available to child procs (HOW?)
 * -- this functions either creates new variable 
 * when given a new with a value
 * -- when given a existing var name it just makes it
 *  available to all th children proc, but if given a value
 *  it does the former plus assigns it a new value
 *  -- if no var name is given then it prints the all the global vars*/


typedef struct s_sh{
    char *var;
}t_sh;

int msh_bi_export(t_sh *env, void *value)
{
    env->var = (char *)value;
    return(EXIT_SUCCESS);
}

