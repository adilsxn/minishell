/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_hex.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acuva-nu <acuva-nu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/26 18:15:29 by acuva-nu          #+#    #+#             */
/*   Updated: 2022/12/01 18:11:03 by acuva-nu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_hexing(unsigned long int n, char *b)
{
	int	size;

	size = 0;
	if (n >= 16)
	{
		size += ft_hexing(n / 16, b);
		size += ft_hexing(n % 16, b);
	}
	else
		size += ft_c(b[n % 16]);
	return (size);
}

int	ft_x(unsigned int n, char c)
{
	int	size;

	size = 0;
	if (c == 'x')
		size += ft_hexing(n, "0123456789abcdef");
	else
		size += ft_hexing(n, "0123456789ABCDEF");
	return (size);
}

int	ft_p(unsigned int long n)
{
	int	size;

	if (!n)
		return (write(1, "(nil)", 5));
	size = 2;
	write(1, "0x", 2);
	size += ft_hexing(n, "0123456789abcdef");
	return (size);
}
