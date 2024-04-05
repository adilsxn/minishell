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
	struct stat	s;
	char		**paths;
	char		*path;
	int			i;

	if (!cmd)
		return (NULL);
	i = -1;
	path = NULL;
	paths = NULL;
	stat(cmd, &s);
	if (ft_strequ(cmd, ".."))
		return (NULL);
	if (ft_strchr(cmd, '/'))
		return (ft_strdup(cmd));
	if (!access(cmd, X_OK) && S_ISREG(s.st_mode))
		return (ft_strjoin("./", cmd));
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
