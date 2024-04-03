/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   del_msh_envlist.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acuva-nu <acuva-nu@student.42lisboa.com>    +#+  +:+
	+#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/12 17:37:05 by acuva-nu          #+#    #+#             */
/*   Updated: 2023/11/12 17:37:05 by acuva-nu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static void	free_2str(void *key, void *data)
{
	free((void *)key);
	free((void *)data);
}

t_env	*init_env(char **envp)
{
	t_env		*env;
	const char	*key;
	const char	*data;

	env = NULL;
	key = NULL;
	data = NULL;
	if (*envp == NULL)
	{
		data = getcwd(NULL, 0);
		set_env(&env, "PWD", data);
		ft_free((void **)&data);
		return (env);
	}
	while (*envp != NULL)
	{
		key = ft_substr(*envp, 0, ft_strchr(*envp, '=') - *envp);
		data = ft_strdup(ft_strchr(*envp, '=') + 1);
		set_env(&env, key, data);
		free_2str((void *)key, (void *)data);
		envp++;
	}
	return (env);
}
