/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matde-je <matde-je@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/06 15:22:48 by acuva-nu          #+#    #+#             */
/*   Updated: 2024/01/23 11:51:02 by matde-je         ###   ########.fr       */
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

static void	stralloc2(char const *s, char c, char **arr, int i)
{
	int	char_count;

	char_count = 0;
	while (*s != c && *s)
	{
		char_count++;
		s++;
	}
	arr[i] = (char *)malloc(sizeof(char) * (char_count + 2));
	if (!arr[i])
	{
		while (i--)
			free(arr[i]);
		free(arr);
	}
}

char	**ft_split2(char const *s, char c)
{
	char	**arr;
	int		str_count;
	int		i;
	int		j;
	int		trig;

	if (!s)
		return (NULL);
	trig = 0;
	if (s[0] == c)
		trig = 1;
	str_count = ft_wordcount(s, c);
	arr = (char **)malloc(sizeof(char *) * (str_count + 1));
	if (!arr)
		return (NULL);
	i = 0;
	while (i != str_count)
	{
		while (*s == c && *s)
			s++;
		stralloc2(s, c, arr, i);
		j = 0;
		if (i != 0 || (i == 0 && trig == 1))
			arr[i][j++] = c;
		while (*s != c && *s)
			arr[i][j++] = (char)*s++;
		arr[i][j] = '\0';
		i++;
	}
	arr[i] = NULL;
	return (arr);
}
