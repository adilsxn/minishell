/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env1pand_utilspt2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matilde <matilde@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 14:27:40 by matilde           #+#    #+#             */
/*   Updated: 2024/02/14 15:04:06 by matilde          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

char	*expander_help1(int len, char **str2, char **str1, int i)
{
	char	*temp;

	if (len != 1 && i > 0 && *str2 != NULL)
	{
		temp = ft_strjoin(*str2, str1[i]);
		if (temp)
		{
			free(*str2);
			*str2 = ft_strdup(temp);
			free(temp);
		}
		else
			ft_free((void **)&*str2);
	}
	return (*str2);
}

void	loop_help2(t_env1 **env1, char **str2, char *str3, char **str1)
{
	char	*tmp;
	char	*temp;

	tmp = get_key(str1[(*env1)->i]);
	if ((*env1)->i > 0 && *str2 != NULL)
	{
		temp = ft_strjoin(*str2, str3);
		if (temp)
		{
			free(*str2);
			*str2 = ft_strjoin(temp, str1[(*env1)->i] + ft_strlen(tmp) + 1);
			free(temp);
		}
		else
			ft_free((void **)&*str2);
	}
	else
	{
		free(*str2);
		*str2 = ft_strjoin(str3, str1[(*env1)->i] + ft_strlen(tmp) + 1);
	}
	ft_free((void **)&str3);
	free(tmp);
}

char	*init_expand(char **str, char ***str1)
{
	if ((*str)[0] == 39)
	{
		del_quote(*str, '\'');
		return (*str);
	}
	*str1 = ft_split2(*str, '$');
	return (NULL);
}

void	checker(t_env *env2, char **str2, int i)
{
	if (i == 0 && env2 == NULL)
		ft_free((void **)str2);
}
