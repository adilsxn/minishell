/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   del_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acuva-nu <acuva-nu@student.42lisboa.com>    +#+  +:+
	+#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/27 16:11:54 by acuva-nu          #+#    #+#             */
/*   Updated: 2023/11/27 16:11:54 by acuva-nu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	del_env(t_env *env)
{
	t_env	*tmp;
	t_env	*next;

	tmp = env;
	while (tmp != NULL)
	{
		next = tmp->next;
		ft_free((void *)tmp->key);
		ft_free((void *)tmp->value);
		if (tmp->ex)
		{
			ft_free(tmp->ex->str2);
			ft_free(tmp->ex);
		}
		ft_free(tmp);
		tmp = next;
	}
	env = NULL;
	return (0);
}
