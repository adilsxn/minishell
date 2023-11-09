/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matilde <matilde@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 15:49:07 by matilde           #+#    #+#             */
/*   Updated: 2023/11/09 18:14:16 by matilde          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	envi(t_tool *tool)
{
	int		i;

	i = 0;
	while (tool->env[i])
	{
		ft_putendl_fd(tool->env[i], 2);
		i++;
	}
	return (0);
}

// int	find_pwd(t_tool *tool)
// {
// 	int	i;

// 	i = 0;
// 	while (tool->env[i])
// 	{
// 		if (ft_strncmp(tool->env[i], "PWD=", 4) == 0)
// 			tool->pwd = ft_substr(tool->env[i], 4, ft_strlen(tool->env[i]) - 4);
// 		if (ft_strncmp(tool->env[i], "OLDPWD=", 7) == 0)
// 			tool->old_pwd = ft_substr(tool->env[i], 7, 
// 				ft_strlen(tool->env[i]) - 7);
// 		i++;
// 	}
// 	return (1);
// }

// char	*find_path(char **env)
// {
// 	int		i;

// 	i = 0;
// 	while (env[i])
// 	{
// 		if (ft_strncmp(env[i], "PATH=", 5) == 0)
// 			return (ft_substr(env[i], 5, ft_strlen(env[i]) - 5));
// 		i++;
// 	}
// 	return (NULL);
// }

// // : in paths are used as separators to indicate where one directory path ends
// //and the next one begins
// //path ends in /, so if it doesnt have it, we add it
// int	parse_env(t_tool *tool)
// {
// 	char	*path_from_env;
// 	int		i;
// 	char	*tmp;

// 	path_from_env = find_path(tool->env);
// 	tool->path = ft_split(path_from_env, ':');
// 	free(path_from_env);
// 	i = 0;
// 	while (tool->path[i])
// 	{
// 		if (ft_strncmp(&tool->path[i][ft_strlen(tool->path[i]) - 1], 
// 			"/", 1) != 0)
// 		{
// 			tmp = ft_strjoin(tool->path[i], "/");
// 			free(tool->path[i]);
// 			tool->path[i] = tmp;
// 		}
// 		i++;
// 	}
// 	return (0);
// }

