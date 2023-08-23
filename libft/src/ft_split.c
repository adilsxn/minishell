/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acuva-nu <acuva-nu@student.42lisboa.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/06 15:22:48 by acuva-nu          #+#    #+#             */
/*   Updated: 2023/04/08 15:01:14 by acuva-nu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	stralloc(char const *s, char c, char **arr, int i)
{
	int	char_count;

	char_count = 0;
	while (*s != c && *s)
	{
		char_count++;
		s++;
	}
	arr[i] = (char *)malloc(sizeof(char) * (char_count + 1));
	if (!arr[i])
	{
		while (i--)
			free(arr[i]);
		free(arr);
	}
}

char	**ft_split(char const *s, char c)
{
	char	**arr;
	int		str_count;
	int		i;
	int		j;

	if (!s)
		return (NULL);
	str_count = ft_wordcount(s, c);
	arr = (char **)malloc(sizeof(char *) * (str_count + 1));
	if (!arr)
		return (NULL);
	i = 0;
	while (i != str_count)
	{
		while (*s == c && *s)
			s++;
		stralloc(s, c, arr, i);
		j = 0;
		while (*s != c && *s)
			arr[i][j++] = (char)*s++;
		arr[i][j] = '\0';
		i++;
	}
	arr[i] = NULL;
	return (arr);
}
