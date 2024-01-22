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

static bool valid_key(char *key)
{
    int i;

    i = 0;
    if(ft_isalpha(key[i]) == 0 && key[i] != '_')
        return (false);
    i++;
    while(key[i] != '\0' && key[i] != '=')
    {
        if ((ft_isalnum(key[i]) == 0) && (key[i] != '_'))
            return (false);
        i++;
    }
    return(true);
}

static int real_export(char *input, t_env *env)
{
    const char *sign;
    const char *key;
    const char *data;
    bool valid;

    sign = ft_strchr(input, '=');
    if (sign == NULL)
        return (1);
    if (sign == input)
    {
        ft_putendl_fd("export: invalid key", 2);
        return (1);
    }
    key = ft_substr(input, 0, sign - input);
    valid =  valid_key(key);
    if (valid == false)
        ft_putendl_fd("export: invalid key", 2);
    else
    {
        data = ft_strdup(sign + 1);
        set_env(&env, key, data);
        free((void *) data);
    }
    free((void *)key);
    return (valid == 0);
}

int msh_export(char **args, t_tool *data)
{
    int i;
    int ret_code;

    i = 1;
    ret_code = 0;
    while(args[i] != NULL)
    {
        if (real_export( args[i], data->env) != 0)
            ret_code = 1;
        i++;
    }
    return(ret_code);
}

