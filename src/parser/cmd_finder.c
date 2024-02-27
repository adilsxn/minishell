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

/*Code adapted from github.com/adilsxn/pipex*/

void	free_arr(char **arr)
{
	int	i;

	i = -1;
	if (arr == NULL)
		return ;
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
	paths = NULL;
	if (path == NULL)
		return (NULL);
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

char	*cmd_finder(t_env *env, char *cmd)
{
	char		**paths;
	struct stat	var;
	char		*path;
	int			i;

	if (!cmd)
		return (NULL);
	i = -1;
	ft_bzero(&var, sizeof(struct stat));
    path = NULL;
	stat(cmd, &var);
	if (S_ISREG(var.st_mode))
		if (access(cmd, X_OK) == 0)
			return (ft_strdup(cmd));
	paths = useful_paths(get_env(env, "PATH"));
	while (paths != NULL && paths[++i] != NULL)
	{
		path = ft_strjoin(paths[i], cmd);
		if (!path)
			break ;
		if (access(path, F_OK | X_OK) == 0)
			break ;
		ft_free((void **)&path);
	}
	free_arr(paths);
	return (path);
}
