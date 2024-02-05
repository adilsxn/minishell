/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_finder.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acuva-nu <acuva-nu@student.42lisboa.com>    +#+  +:+
	+#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/11 23:23:33 by acuva-nu          #+#    #+#             */
/*   Updated: 2024/01/11 23:23:33 by acuva-nu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"
#include <string.h>

/*Code adapted from github.com/adilsxn/pipex*/

void	free_arr(char **arr)
{
	int	i;

	i = -1;
	while (arr[++i])
		free(arr[i]);
	free(arr);
}

static char	**useful_paths(char *path)
{
	char	**paths;
	char	*tmp;
	int		i;

	i = -1;
	paths = ft_split(path, ':');
	if (!paths)
		return (NULL);
	while (paths[++i])
	{
		tmp = paths[i];
		paths[i] = ft_strjoin(paths[i], "/");
		free(tmp);
	}
	return (paths);
}

char	*cmd_finder(t_tool *data, char *cmd)
{
	char	**paths;
	char	*path;
	int		i;

	i = -1;
	if (!cmd)
		return (NULL);
	if (access(cmd, F_OK | X_OK) == 0)
		return (ft_strdup(cmd));
	paths = useful_paths(get_env(data->env, "PATH"));
	while (paths[++i] != NULL)
	{
		path = ft_strjoin(paths[i], cmd);
		if (!path)
			break ;
		if (access(path, F_OK | X_OK) == 0)
			break ;
		free(path);
		path = NULL;
	}
	free_arr(paths);
	return (path);
}
