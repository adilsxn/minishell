/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acuva-nu <acuva-nu@student.42lisboa.com>    +#+  +:+
	+#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/14 22:23:24 by acuva-nu          #+#    #+#             */
/*   Updated: 2023/09/14 22:23:24 by acuva-nu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static bool	valid_key(char *key)
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

int	msh_unset(char **args, t_tool *data)
{
	int	i;

	i = 1;
	while (args[i] != NULL)
	{
		if (!valid_key(args[i]) || ft_strchr(args[i], '=') != NULL)
			return (ft_err("unset: not a valid identifier", NULL, NULL, 1), 1);
		else if (unset_env(&(data->env), args[i]))
			return (EXIT_FAILURE);
		i++;
	}
	return (EXIT_SUCCESS);
}
