/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acuva-nu <acuva-nu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/06 15:35:15 by acuva-nu          #+#    #+#             */
/*   Updated: 2022/11/06 15:46:31 by acuva-nu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	char	*newstr;
	size_t	i;

	newstr = ft_strdup(s);
	i = 0;
	if (!s || !f || !newstr)
		return (NULL);
	while (newstr[i])
	{
		newstr[i] = f(i, newstr[i]);
		i++;
	}
	return (newstr);
}
