/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_utilspt2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matde-je <matde-je@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 14:27:40 by matilde           #+#    #+#             */
/*   Updated: 2024/01/23 15:15:50 by matde-je         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

//incrementing the i, to skip over it
size_t	equal_sign(char *str)
{
	size_t	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '=')
			return (i + 1);
		i++;
	}
	return (0);
}

int	question_mark(char **tmp)
{
	free(*tmp);
	*tmp = ft_itoa(1);
	return (ft_strlen(*tmp) + 1);
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

void	free_array(char **array)
{
	int	i;

	i = -1;
	while (array[++i])
		free(array[i]);
	free(array);
}
