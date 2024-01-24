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

int	init_env(char **envp, t_env **env)
{
	const char	*key;
	const char	*data;
	const char	*sign;

	key = NULL;
	data = NULL;
	sign = NULL;
	while (*envp != NULL)
	{
		sign = ft_strchr(*envp, '=');
		key = ft_substr(*envp, 0, sign - *envp);
		data = ft_strdup(sign + 1);
		set_env(env, key, data);
		free((void *)key);
		free((void *)data);
		envp++;
	}
	return (0);
}
