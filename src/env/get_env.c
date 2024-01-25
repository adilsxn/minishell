/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lookup_msh_env.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acuva-nu <acuva-nu@student.42lisboa.com>    +#+  +:+
	+#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/12 17:54:43 by acuva-nu          #+#    #+#             */
/*   Updated: 2023/11/12 17:54:43 by acuva-nu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

t_env	*get_env(t_env *env, const char *key)
{
	t_env	*tmp;

	if (ft_strequ(key, "?"))
		set_env(&env, "?", ft_itoa(g_last_ret_code));
	tmp = env;
	while (tmp != NULL && !ft_strequ(key, tmp->key))
	{
		tmp = tmp->next;
	}
	return (tmp);
}
