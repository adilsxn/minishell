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

static int valid_key(char *key)
{
    if (!key)
        return (1);
    while(*key != '\0')
    {
        if ((ft_isalnum(*key) == 0) && (*key != '_'))
            return (1);
        key++;
    }
    return(0);
}

static int real_export(char *input, t_env *env)
{
    const char *sign;
    const char *key;
    const char *data;
    int valid;

    sign = ft_strchr(input, '=');
    if (sign == NULL)
        return (1);
    if (sign == input)
    {
        perror("export: invalid key");
        return (1);
    }
    key = ft_substr(input, 0, sign - env);
    valid =  valid_key((char *)key);
    if (valid == 1)
        perror("export: invalid key");
    else
    {
        data = ft_strdup(sign + 1);
        set_env(env, key, data);
        free((void *) data);
    }
    free((void *)key);
    return (valid == 0);
}

int msh_export(t_tool *tools, t_simple_cmd *args)
{
    int ret_code;

    ret_code = 0;
    while(*(args->str)  != NULL)
    {
        if (real_export( *(args->str), tools->our_env) != 0)
            ret_code = 1;
        (args->str)++;
    }
    return(ret_code);
}

