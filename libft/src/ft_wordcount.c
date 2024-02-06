/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_wordcount.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matilde <matilde@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/08 14:53:22 by acuva-nu          #+#    #+#             */
/*   Updated: 2024/02/06 13:10:52 by matilde          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_wordcount(char const *s, char c)
{
	int	count;

	count = 0;
	while (*s)
	{
		while (*s == c)
			s++;
		if (*s == '\0')
			break ;
		while (*s != c && *s)
			s++;
		count++;
	}
	return (count);
}

int	ft_wordcount1(char const *s, char c)
{
	int	count;
	int	trig;

	count = 0;
	trig = 0;
	while (*s)
	{
		while (*s == c)
			s++;
		if (*s == '\0')
		{
			trig = 1;
			break ;
		}
		while (*s != c && *s)
			s++;
		count++;
	}
	if (count == 0 && trig == 1)
	{
		return (1);
	}
	return (count);
}
