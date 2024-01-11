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

/*Code adapted from github.com/adilsxn/pipex*/

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
}

static char	**useful_paths(char **envp)
{
	char	**paths;
	char	*path;
	char	*tmp;
	int		i;

	i = -1;
	path = get_path(envp);
	paths = ft_split(path, ':');
	if (!paths)
		return (NULL);
	while (paths[++i])
	{
		tmp = paths[i];
		paths[i] = ft_strjoin(paths[i], "/");
		free(tmp);
	}
	free(path);
	return (paths);
}

char	*cmd_finder(int iter, t_ppx *p)
{
	char	**paths;
	char	*path;
	int		i;

	paths = useful_paths(p->envp);
	p->cmd_opts = ft_split(p->av[iter + 2], ' ');
	i = -1;
	while (paths[++i])
	{
		path = ft_strjoin(paths[i], p->cmd_opts[0]);
		if (!path)
			return (NULL);
		if (access(path, F_OK | X_OK) == 0)
			return (ft_strdup(path));
		free(path);
	}
	free_strs(paths, NULL);
	return (NULL);
}
