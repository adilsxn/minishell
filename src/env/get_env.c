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

t_env *env_iter(t_env *env, const char *key)
{
    t_env *it;

    it = env;
    if (!it)
        return (NULL);
    while(it != NULL && !ft_strequ(key, it->key))
        it = it->next;
    return (it);
}

char	*get_env(t_env *env, const char *key)
{
	t_env	*tmp;

	if (!env)
		return (NULL);
    if (ft_strequ(key, "?"))
        return (ft_itoa(g_last_ret_code));
    tmp = env_iter(env, key);
    return ((char *)tmp->value);
}
