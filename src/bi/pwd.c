/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acuva-nu <acuva-nu@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/11 13:45:03 by acuva-nu          #+#    #+#             */
/*   Updated: 2024/01/22 00:04:19 by acuva-nu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"


int   msh_pwd(t_env *env)
{
    char buf[PATH_MAX];
    char *cwd;
    if (get_env(env, "PWD") != NULL)
    {
        ft_putendl_fd((char *)get_env(env, "PWD")->value, 1);
        return (EXIT_SUCCESS);
    }
    else
        cwd = getcwd(buf, PATH_MAX);
    if (cwd != NULL)
    {
        ft_putendl_fd(cwd, STDOUT_FILENO);
        return (EXIT_SUCCESS);
    }
    return (EXIT_FAILURE);
}
