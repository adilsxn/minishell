/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_finder.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acuva-nu <acuva-nu@student.42lisboa.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/11 23:23:33 by acuva-nu          #+#    #+#             */
/*   Updated: 2024/01/11 23:23:33 by acuva-nu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"
#include <string.h>

/*Code adapted from github.com/adilsxn/pipex*/

static void free_arr(char **arr)
{
	int i;

	i = -1;
	while (arr[++i])
	{
		free(arr[i]);
		arr[i] = NULL;
	}
	free(arr);
}
/*
static char	*get_path(char **envp)
{
	char	*path;
	int		i;

	i = 0;
	path = NULL;
	while (envp[i] && !ft_strnstr(envp[i], "PATH=", 5))
		i++;
	path = ft_substr(envp[i], 5, ft_strlen(envp[i]));
	return (path);
} */

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

char	*cmd_finder(t_tree *tree, t_env *env)
{
	char	**paths;
	char	*path;
	int		i;

	i = -1;
    if (ft_strchr(tree->token, '/') != NULL)
        return (tree->token);
    paths = useful_paths((char *)get_env(env, "PATH")->value);
	while (paths[++i])
	{
		path = ft_strjoin(paths[i], tree->token);
		if (!path)
			return (NULL);
		if (access(path, F_OK | X_OK) == 0)
			return (ft_strdup(path));
		free(path);
	}
	free_arr(paths);
	return (NULL);
}
