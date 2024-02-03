/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matde-je <matde-je@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 12:41:56 by matilde           #+#    #+#             */
/*   Updated: 2024/01/24 12:43:47 by matde-je         ###   ########.fr       */
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
		&& str1[i] != '"' && str1[i] != '\'' && str1[i] != '=')
		i++;
	return (ft_substr(str1, 0, i));
}

char	*double_strj(char *str2, char *str3, char *str1)
{
	str2 = ft_strjoin(str2, str3);
	if (str2)
		str2 = ft_strjoin(str2, str1);
	return (str2);
}

int	envy(t_env **env2, t_env *env, char **str3, char *tmp)
{
	// *env2 = env_iter(env, tmp);
	// if (env2 != NULL)
    (void)env2;
    *str3 = get_env(env, tmp);
	if (*str3 == NULL)
		return (1);
	return (0);
}

char	*tmpcheck(char **tmp, char **str1, int i)
{
	*tmp = get_key(str1[i]);
	return (*tmp);
}

char	*del_quote(char *str, char c)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (str[i])
	{
		if (str[i] == c)
		{
			j = 0;
			while (str[i + j] == c)
				j++;
			ft_strlcpy(&str[i], &str[i + j], strlen(str) - i);
		}
		i++;
	}
	return (str);
}
