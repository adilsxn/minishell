/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acuva-nu <acuva-nu@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/11 13:45:03 by acuva-nu          #+#    #+#             */
/*   Updated: 2023/12/18 22:18:50 by acuva-nu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

// TODO: adapt the func to the shell env(not created yet)
int   msh_pwd(t_env *env)
{
    ft_putendl_fd((char *)get_env(env, "PWD")->value, 1);
    return (EXIT_SUCCESS);
}
