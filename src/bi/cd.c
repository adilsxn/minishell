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
#include <stdlib.h>
#include <unistd.h>

// TODO: create an enviroment type for the shell that should be given
// to this function as param

/**/
void msh_bi_cd(char *directory)
{
    char *env_path;
    char *curpath;
    char *pwd;
    char *oldpwd;

    env_path = NULL;
    curpath = NULL;
    pwd = NULL;
    oldpwd = NULL;
    if (directory == NULL)
    {
        env_path = getenv("HOME");
        if (env_path == NULL)
            ft_putstr_fd("The variable dosn't exit\n", 1);
    }
    if (ft_strequ(directory, "-"))
    {
        env_path = getenv("OLDPWD");
        if (env_path == NULL)
            ft_putstr_fd("The variable doesn't exist\n", 1);
    }
    if (ft_strequ(directory, ".."))
    {
        env_path = getenv("PWD");
        if (env_path == NULL)
            ft_putstr_fd("The variable doesn't exist\n", 1);
    }
    if (ft_strchr(directory, '/'))
    {
        if ()
    }
}
