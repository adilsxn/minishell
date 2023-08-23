/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acuva-nu <acuva-nu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/06 16:51:29 by acuva-nu          #+#    #+#             */
/*   Updated: 2022/11/19 15:14:50 by acuva-nu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	getsize(int n, size_t size)
{
	while (n)
	{
		size++;
		n /= 10;
	}
	return (size);
}

static char	*getstring(long nbr, char *str, size_t size, int signal)
{
	str[size--] = '\0';
	while (nbr)
	{
		str[size--] = nbr % 10 + '0';
		nbr /= 10;
	}
	if (signal)
		str[0] = '-';
	if (size == 1 && str[1] == '\0')
		str[0] = '0';
	return (str);
}

char	*ft_itoa(int n)
{
	char	*str;
	long	nbr;
	int		signal;
	size_t	size;

	if (n == 0)
		return (ft_strdup("0"));
	nbr = n;
	size = 0;
	signal = 0;
	if (n < 0)
	{
		nbr = -nbr;
		size += 1;
		signal += 1;
	}
	size = getsize(n, size);
	str = (char *)malloc(size + 1);
	if (!str)
		return (NULL);
	return (getstring(nbr, str, size, signal));
}
