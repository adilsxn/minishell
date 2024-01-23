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
    char *sign;
    char *key;
    char *data;
    bool valid;

    sign = ft_strchr(input, '=');
    if (sign == NULL)
        return (1);
    if (sign == input)
        return (ft_err("export: invalid key", NULL), 1);
    key = ft_substr(input, 0, sign - input);
    valid =  valid_key(key);
    if (valid == false)
    {
        ft_free(key);
        return (ft_err("export: invalid key", NULL), 1);
    }
    else
    {
        data = ft_strdup(sign + 1);
        set_env(&env, key, data);
        ft_free((void *) data);
    }
    ft_free((void *)key);
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

