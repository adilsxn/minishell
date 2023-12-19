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


void *builtins(t_tool *tools, t_simple_cmd *args)
{
    if (ft_strequ(args->str[0], "echo"))
        return (msh_echo(tools, args));
    else if (ft_strequ(args->str[0], "pwd"))
        return (msh_pwd(tools, args));
    else if (ft_strequ(args->str[0], "env"))
        return (msh_env(tools, args));
    else if (ft_strequ(args->str[0], "export"))
        return (msh_export(tools, args));
    else if (ft_strequ(args->str[0], "unset"))
        return (msh_unset(tools, args));
    else if (ft_strequ(args->str[0], "exit"))
        return (msh_exit(tools, args));
    else if (ft_strequ(args->str[0], "cd"))
        return (msh_cd(tools, args));
    else
        return (NULL);
}
