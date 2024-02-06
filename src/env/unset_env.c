/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   del_msh_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acuva-nu <acuva-nu@student.42lisboa.com>    +#+  +:+
	+#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/10 17:16:27 by acuva-nu          #+#    #+#             */
/*   Updated: 2023/11/10 17:16:27 by acuva-nu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	unset_env(t_env **env, const char *key)
{
	t_env	*tmp;

	if (!env || !key)
		return (1);
	tmp = env_iter(*env, key);
	if (tmp == NULL)
		return (1);
	if (tmp->prev != NULL)
		tmp->prev->next = tmp->next;
	else
		*env = tmp->next;
	if (tmp->next != NULL)
		tmp->next->prev = tmp->prev;
	tmp->prev = NULL;
	tmp->next = NULL;
	free((void *)tmp->key);
	free((void *)tmp->value);
	free(tmp);  
	return (0);
}
