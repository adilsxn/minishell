/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acuva-nu <acuva-nu@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/28 21:40:35 by acuva-nu          #+#    #+#             */
/*   Updated: 2023/12/18 22:04:03 by acuva-nu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"


int exec_bi(char **argv, t_tree *tree, t_env *env)
{
    int ret;

    ret = 0;
    if (ft_strequ(*argv, "echo"))
        ret = msh_echo(argv);
    else if (ft_strequ(*argv, "pwd"))
         ret = msh_pwd(env);
    else if (ft_strequ(*argv, "env"))
         ret = msh_env(env);
    else if (ft_strequ(*argv, "export"))
         ret = msh_export(env, argv);
    else if (ft_strequ(*argv, "unset"))
         ret = msh_unset(env, argv);
    else if (ft_strequ(*argv, "exit"))
         ret = msh_exit(tree, env);
    else if (ft_strequ(*argv, "cd"))
         ret = msh_cd(argv, env);
    return (ret);
}
