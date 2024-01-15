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


void *builtins(t_env *env, char **args)
{
    if (ft_strequ(*args, "echo"))
        return (msh_echo(tools, args));
    else if (ft_strequ(*args, "pwd"))
        return (msh_pwd(env));
    else if (ft_strequ(*args, "env"))
        return (msh_env(env));
    else if (ft_strequ(*args, "export"))
        return (msh_export(env, args));
    else if (ft_strequ(*args, "unset"))
        return (msh_unset(env, args));
    else if (ft_strequ(*args, "exit"))
        return (msh_exit(tools, args));
    else if (ft_strequ(*args, "cd"))
        return (msh_cd(tools, args));
    else
        return (NULL);
}
