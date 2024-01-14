/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acuva-nu <acuva-nu@student.42lisboa.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/11 14:40:40 by acuva-nu          #+#    #+#             */
/*   Updated: 2023/09/11 14:40:40 by acuva-nu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"


static int update_env(t_env *env)
{
    const char *pwd;

    pwd = getcwd(NULL, 0);
    set_env(&env, "OLDPWD", get_env(env, "PWD")->value);
    set_env(&env, "PWD", pwd);
    free((char *)pwd);
    return (0);
}

int msh_cd(char **args, t_env *env)
{
    const char *path;
    
    if (args[1] == NULL)
            path = get_env(env, "HOME")->value;
    else 
        path = *(args->str);
    if (chdir(path) == -1)
    {
        perror("error: cd failed\n");
        return (1);
    }
    update_env(env);
    return (0);
}
