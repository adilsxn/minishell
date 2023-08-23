/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_csdiu.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acuva-nu <acuva-nu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/26 18:15:29 by acuva-nu          #+#    #+#             */
/*   Updated: 2022/12/01 18:13:09 by acuva-nu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_c(int c)
{
	write(1, &c, 1);
	return (1);
}

int	ft_s(const char *str)
{
	int	i;

	i = 0;
	if (!str)
		str = "(null)";
	while (str[i])
	{
		write(1, &str[i], 1);
		i++;
	}
	return (i);
}

int	ft_di(int n)
{
	long	nbr;
	int		size;

	nbr = (long)n;
	size = 0;
	if (nbr < 0)
	{
		size += ft_c('-');
		nbr = -nbr;
	}
	if (nbr >= 10)
	{
		size += ft_di(nbr / 10);
		size += ft_c("0123456789"[nbr % 10]);
	}
	else
		size += ft_c("0123456789"[nbr % 10]);
	return (size);
}

int	ft_u(unsigned int n)
{
	unsigned long	nbr;
	int				size;

	nbr = (unsigned long)n;
	size = 0;
	if (nbr >= 10)
	{
		size += ft_di(nbr / 10);
		size += ft_c("0123456789"[nbr % 10]);
	}
	else
		size += ft_c("0123456789"[nbr % 10]);
	return (size);
}
