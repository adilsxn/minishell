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

int	msh_unset(char **args, t_tool *data)
{
	int	i;

	i = 1;
	while (args[i] != NULL)
	{
		if (!valid_key(args[i]))
			return (ft_err("unset: not a valid identifier", NULL, NULL, 1), 1);
		unset_env(&(data->env), args[i]);
		i++;
	}
	return (EXIT_SUCCESS);
}
