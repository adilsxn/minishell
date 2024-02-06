/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acuva-nu <acuva-nu@student.42lisboa.com>    +#+  +:+
	+#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/14 21:57:35 by acuva-nu          #+#    #+#             */
/*   Updated: 2023/09/14 21:57:35 by acuva-nu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

bool	valid_key(char *key)
{
	int	i;

	i = 0;
	if (ft_isalpha(key[i]) == 0 && key[i] != '_')
		return (false);
	i++;
	while (key[i] != '\0' && key[i] != '=')
	{
		if ((ft_isalnum(key[i]) == 0) && (key[i] != '_'))
			return (false);
		i++;
	}
	return (true);
}

static int	real_export(char *input, t_env *env)
{
	char	*key;
	char	*data;

	key = NULL;
	data = NULL;
	if (valid_key(input) != false)
	{
		if (ft_strchr(input, '=') != NULL)
		{
			key = ft_substr(input, 0, ft_strchr(input, '=') - input);
			data = ft_strdup(ft_strchr(input, '=') + 1);
			set_env(&env, key, data);
			ft_free(key);
			ft_free(data);
		}
		return (0);
	}
	return (ft_err("export: not a valid identifier", NULL, NULL, 1), 1);
}

int	msh_export(char **args, t_tool *data)
{
	int	i;
	int	ret_code;

	i = 1;
	ret_code = EXIT_SUCCESS;
	if (!args)
		msh_env(NULL, data);
	while (args[i] != NULL)
	{
		if (real_export(args[i], data->env) != 0)
			ret_code = EXIT_FAILURE;
		i++;
	}
	return (ret_code);
}
