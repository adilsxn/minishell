/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acuva-nu <acuva-nu@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/11 13:45:03 by acuva-nu          #+#    #+#             */
/*   Updated: 2024/01/22 21:26:41 by acuva-nu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

// if (get_env(data->env, "PWD") != NULL)
// {
// 	ft_putendl_fd(get_env(data->env, "PWD"), 1);
// 	return (EXIT_SUCCESS);
// }
// else
int	msh_pwd(char **args, t_tool *data)
{
	char	buf[PATH_MAX];
	char	*cwd;

	(void)args;
	(void)data;
	cwd = getcwd(buf, PATH_MAX);
	if (cwd != NULL)
	{
		ft_putendl_fd(cwd, STDOUT_FILENO);
		return (EXIT_SUCCESS);
	}
	return (EXIT_FAILURE);
}
