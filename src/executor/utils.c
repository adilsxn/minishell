/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matilde <matilde@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/22 17:52:32 by matilde           #+#    #+#             */
/*   Updated: 2023/11/22 17:52:47 by matilde          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

//minimum number of quotes has to be 2
//return the number to advance the str already checked
int	find_quote(char *line, int i, int *nb_quote, int quote)
{
	int	j;

	j = i + 1;
	*nb_quote += 1;
	while (line[j] && line[j] != quote)
		j++;
	if (line[j] == quote)
		*nb_quote += 1;
	return (j - i);
}

//if == 1 meaning no balanced number of quotes
//if == 0 meaning balanced number of quotes
int	count_quote(char *line)
{
	int	i;
	int	s;
	int	d;

	s = 0;
	d = 0;
	i = -1;
	while (line[++i])
	{
		if (line[i] == 34)
			i += find_quote(line, i, &d, 34);
		if (line[i] == 39)
			i += find_quote(line, i, &s, 39);
	}
	if ((d > 0 && d % 2 != 0) || (s > 0 && s % 2 != 0))
		return (1);
	return (0);
}
