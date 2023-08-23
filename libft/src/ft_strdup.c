/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acuva-nu <acuva-nu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/21 19:36:50 by acuva-nu          #+#    #+#             */
/*   Updated: 2022/11/06 15:44:16 by acuva-nu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *src)
{
	char	*dupl;

	dupl = malloc(ft_strlen(src) + 1);
	if (!dupl)
		return (NULL);
	ft_memcpy(dupl, src, (ft_strlen(src) + 1));
	return (dupl);
}
