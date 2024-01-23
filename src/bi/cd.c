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



static void update_env(t_env *env, bool success)
{
    const char *pwd;

    pwd = getcwd(NULL, 0);
    if (success)
    {
        set_env(&env, "OLDPWD", get_env(env, "PWD")->value);
        set_env(&env, "PWD", pwd);
    }
    ft_free((char *)pwd);
}

static bool ft_chdir(char *path, t_env *env)
{
    char *ret;
    char cwd[PATH_MAX];

    ret = NULL;
    if (chdir(path) != 0)
        ft_err("cd: ", strerror(errno));
    ret = getcwd(cwd, PATH_MAX);
    if (ret == NULL)
        ft_err("cd: error getting current dir", 
                strerror(errno));
    ft_free(ret);
    update_env(env, true);
    return (true);
}

int msh_cd(char **args, t_tool *data)
{
    char *path;

    if (!args || args[1] == NULL || ft_isspace(args[1][0])
        || args[1][0] == '\0' || ft_strncmp(args[1], "--", 3) == 1)
    {
        path = (char *)get_env(data->env, "HOME")->value;
        if (!path || *path == '\0' || ft_isspace(*path))
            return (ft_err("cd: HOME not set", NULL), 1);
        return(!ft_chdir(path, data->env));
    }
    if (args[2])
        return (ft_err("cd: too many arguments", NULL), 1);
    if (ft_strncmp(args[1], "-", 2) == 0)
    {
        path = (char *)get_env(data->env, "OLDPWD")->value;
        if (!path)
            return (ft_err("cd: OLDPWD not set", NULL), 1);
        return(!ft_chdir(path, data->env));
    }
    return (!ft_chdir(args[1], data->env));
}

