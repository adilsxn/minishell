/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acuva-nu <acuva-nu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/26 18:15:15 by acuva-nu          #+#    #+#             */
/*   Updated: 2023/02/18 12:25:00 by acuva-nu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_mng(int c, va_list *args)
{
	int	size;

	size = 0;
	if (c == 'c')
		size += ft_c((char)va_arg(*args, int));
	else if (c == 's')
		size += ft_s((char *)va_arg(*args, char *));
	else if (c == 'p')
		size += ft_p((unsigned long)va_arg(*args, unsigned long));
	else if (c == 'd')
		size += ft_di((int)va_arg(*args, int));
	else if (c == 'i')
		size += ft_di((int)va_arg(*args, int));
	else if (c == 'u')
		size += ft_u((unsigned int)va_arg(*args, unsigned int));
	else if (c == 'x' || c == 'X')
	{
		if (c == 'x')
			size += ft_x((unsigned int)va_arg(*args, unsigned int), 'x');
		else
			size += ft_x((unsigned int)va_arg(*args, unsigned int), 'X');
	}
	else if (c == '%')
		size += ft_c('%');
	return (size);
}

int	ft_printf(const char *fmt, ...)
{
	va_list	args;
	int		size;

	va_start(args, fmt);
	size = 0;
	while (*fmt)
	{
		if (*fmt == '%')
		{
			size += ft_mng(*++fmt, &args);
		}
		else
			size += ft_c(*fmt);
		fmt++;
	}
	return (size);
	va_end(args);
	return (0);
}
