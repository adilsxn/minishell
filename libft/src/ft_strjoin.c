/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acuva-nu@student.42.fr <acuva-nu>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/22 13:41:28 by acuva-nu          #+#    #+#             */
/*   Updated: 2022/10/31 17:04:03 by acuva-nu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(const char *s1, const char *s2)
{
	char	*res;
	int		a;
	int		c;

	if (!s1 || !s2)
		return (NULL);
	res = (char *)malloc(sizeof(char) * ft_strlen(s1) + ft_strlen(s2) + 1);
	if (!res)
		return (NULL);
	a = 0;
	c = 0;
	while (s1[a])
		res[c++] = s1[a++];
	a = 0;
	while (s2[a])
		res[c++] = s2[a++];
	res[c] = '\0';
	return (res);
}
