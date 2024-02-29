/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_utilspt2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matilde <matilde@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 14:27:40 by matilde           #+#    #+#             */
/*   Updated: 2024/02/29 15:44:53 by matilde          ###   ########.fr       */
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
	else if (i == 0 && *str2 != NULL)
	{
		if ((*str2)[0] == '$' && !(*str2)[1] && (!str1[1] || str1[1][0] != '$'))
			return (*str2);
		temp = ft_strtrim(*str2, "$");
		free(*str2);
		*str2 = ft_strdup(temp);
		free(temp);
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

void	bigger_i(t_env1 *env1, char *temp, int i, char **str1)
{
	int	j;
	int	a;

	j = -1;
	a = 0;
	while (str1[++j] && j <= env1->i)
	{
		i = -1;
		while (str1[j][++i])
			if (str1[j][i] == 34)
				a = 1;
	}
	if (a == 0)
		return ;
	temp = ft_strtrim(str1[env1->i], "$");
	i = 0;
	while (temp[i] == env1->tmp[i])
		i++;
	free(temp);
	temp = ft_strjoin(env1->str2, str1[env1->i] + i + 1);
	free(env1->str2);
	env1->str2 = ft_strdup(temp);
	free(temp);
}

void checker_aux(t_env1 *env1, char *temp)
{
	free(env1->str2);
	env1->str2 = ft_strdup(temp);
	ft_free((void **)&temp);
	if (env1->env2 == NULL && env1->str2 == NULL)
		ft_free((void **)&env1->str2);
}

void	checker(t_env1 *env1, int i, char **str1)
{
	char	*temp;

	temp = NULL;
	if (env1->i != 0)
		bigger_i(env1, temp, i, str1);
	if (env1->i != 0)
		return ;
	while (str1[0][++i])
		if (str1[0][i] == 34)
			break ;
	if (i >= (int)ft_strlen(str1[0]) && env1->env2 == NULL)
	{
		ft_free((void **)&env1->str2);
		return ;
	}
	temp = ft_strtrim(env1->str2, "$");
	free(env1->str2);
	env1->str2 = ft_strdup(temp);
	free(temp);
	i = 0;
	while (env1->tmp[i] && env1->tmp[i] == env1->str2[i])
		i++;
	if (!env1->tmp[i] || env1->tmp[i] != env1->str2[i])
		temp = ft_substr(env1->str2, i, ft_strlen(env1->str2));
	checker_aux(env1, temp);
}
