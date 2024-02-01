/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_utilspt2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matilde <matilde@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 14:27:40 by matilde           #+#    #+#             */
/*   Updated: 2024/02/01 18:31:22 by matilde          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

char	*expander_help1(int len, char *str2, char **str1, int i)
{
	if (len == 1)
		str2 = ft_strdup(str2);
	else if (i > 0 && str2 != NULL)
		str2 = ft_strjoin(str2, str1[i]);
	return (str2);
}

void	loop_help2(int *i, char **str2, char *str3, char **str1)
{
	char	*tmp;

	tmp = get_key(str1[*i]);
	if (*i > 0 && *str2 != NULL)
	{
		*str2 = ft_strjoin(*str2, str3);
		*str2 = ft_strjoin(*str2, str1[*i] + ft_strlen(tmp) + 1);
	}
	else
		*str2 = ft_strjoin(str3, str1[*i] + ft_strlen(tmp) + 1);
	free(tmp);
}

char	*init_expand(char **str, char ***str1)
{
	*str = del_quotes(*str, '\"');
	if ((*str)[0] == 39)
	{
		del_quotes(*str, '\'');
		return (*str);
	}
	*str1 = ft_split2(*str, '$');
	return (NULL);
}

void	checker(t_env *env2, char **str2, int i)
{
	if (i == 0 && env2 == NULL)
		*str2 = NULL;
}

char	**ft_arrdup(char **arr)
{
	char	**array2;
	size_t	i;

	i = 0;
	while (arr[i] != NULL)
		i++;
	array2 = ft_calloc(sizeof(char *), i + 1);
	if (!array2)
		return (NULL);
	i = 0;
	while (arr[i] != NULL)
	{
		array2[i] = ft_strdup(arr[i]);
		if (array2[i] == NULL)
		{
			free_array(array2);
			return (array2);
		}
		i++;
	}
	return (array2);
}
