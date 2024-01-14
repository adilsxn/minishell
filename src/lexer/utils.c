/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acuva-nu <acuva-nu@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/04 19:06:19 by matilde           #+#    #+#             */
/*   Updated: 2024/01/13 15:48:26 by acuva-nu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	count_spaces(char *str, int i)
{
	int	count;

	count = 0;
	while (ft_isspace(str[i + count]) == 1)
		count++;
	return (count);
}

int	len_quote(int i, char *str, char quote)
{
	int	count;

	count = 0;
	if (str[i + count] == quote)
	{
		count++;
		while (str[i + count] != quote && str[i + count] != '\0')
			count++;
		count++;
	}
	return (count);
}

t_token	get_tok(int c1, int c2)
{
	if (c1 == '<' && c2 == '<')
		return (LESS_LESS);
	else if (c1 == '>' && c2 == '>')
		return (GREAT_GREAT);
	else if (c1 == '|')
		return (PIPE);
	else if (c1 == '>')
		return (GREAT);
	else if (c1 == '<')
		return (LESS);
	return (0);
}
