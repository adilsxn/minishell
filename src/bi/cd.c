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


// TODO: create an enviroment type for the shell that should be given
// to this function as param

/**/
static void update_env(t_env *env)
{
    const char *pwd;

    pwd = getcwd(NULL, 0);
    set_env("OLDPWD", get_env("PWD")->value);
    set_env("PWD", pwd);
    free((char *)pwd);
}

int msh_cd(t_tool *tools, t_simple_cmd *simple_cmd)
{
    const char *path;
    
    if (!simple_cmd->str[1])
            path = get_env(tools->ourenv, "HOME")->value;
    else 
        path = *(simple_cmd->str);
    if (chdir(path) == -1)
    {
        perror("error");
        return (1);
    }
    update_env(tools->ourenv);
    return (0);
}
