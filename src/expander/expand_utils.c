/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matilde <matilde@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 12:41:56 by matilde           #+#    #+#             */
/*   Updated: 2024/02/29 14:29:20 by matilde          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

char	*get_key(char *str)
{
	int		i;
	char	*str1;

	str1 = ft_strchr(str, '$');
	if (str1 == NULL)
		return (NULL);
	if (str1 != NULL && *str1 == '$')
		str1++;
	i = 0;
	while (str1[i] != '\0' && !ft_isspace(str1[i]) && str1[i] != 47
		&& str1[i] != '"' && str1[i] != '\'' && str1[i] != '='
		&& str1[i] != '|')
		i++;
	return (ft_substr(str1, 0, i));
}

int	env1_func(t_env **env2, t_env *env, char **str3, char *tmp)
{
	char	*str4;

	if (ft_strequ(tmp, "?") == 1)
	{
		*str3 = ft_itoa(g_last_ret_code);
		return (1);
	}
	if (tmp[0] == '?')
	{
		str4 = ft_itoa(g_last_ret_code);
		*str3 = ft_strjoin(str4, tmp + 1);
		free(str4);
		return (1);
	}
	*env2 = env_iter(env, tmp);
	if (*env2 != NULL)
	{
		if ((char *)(*env2)->value != NULL)
			*str3 = ft_strdup((*env2)->value);
		return (1);
	}
	else
		*str3 = NULL;
	return (0);
}

char	*tmpcheck(char **tmp, char **str1, int i)
{
	*tmp = get_key(str1[i]);
	if (*tmp != NULL)
		if ((*tmp)[0] == '\0')
			return (NULL);
	return (*tmp);
}
